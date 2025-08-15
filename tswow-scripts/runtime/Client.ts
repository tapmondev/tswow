/*
 * This file is part of tswow (https://github.com/tswow)
 *
 * Copyright (C) 2020 tswow <https://github.com/tswow/>
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
import * as crypto from 'crypto';
import { sleep } from 'deasync';
import { Args } from '../util/Args';
import { ClientPatches, EXTENSION_DLL_PATCH_NAME } from '../util/ClientPatches';
import { mpath, wfs } from '../util/FileSystem';
import { WDirectory, WNode } from '../util/FileTree';
import { ClientPath, findLocaleDir, ipaths } from '../util/Paths';
import { isWindows, isMacOS } from '../util/Platform';
import { Process } from '../util/Process';
import { term } from '../util/Terminal';
import { StartCommand } from './CommandActions';
import { Dataset } from './Dataset';
import { Identifier } from './Identifiers';
import { NodeConfig } from './NodeConfig';
import * as path from "path";

export const CLEAN_CLIENT_MD5 = '45892bdedd0ad70aed4ccd22d9fb5984'

const processMap: {[datasetName: string]: Process[]} = {}

export class Client {
    readonly dataset: Dataset

    constructor(dataset: Dataset) {
        this.dataset = dataset;
    }

    get path() {
        if(!wfs.exists(this.dataset.config.client_path)) {
            throw new Error(
                `Invalid client: ${this.dataset.config.client_path} does not exist`
            )
        }

        const useLocale = this.dataset.config.ClientPatchUseLocale
        let patchdir = mpath(this.dataset.config.client_path,'Data')
        if(useLocale) {
            patchdir = findLocaleDir(patchdir).get();
        }

        let patchFile = useLocale
            ? `patch-${wfs.basename(patchdir)}-${this.dataset.config.ClientDevPatchLetter}.MPQ`
            : `patch-${this.dataset.config.ClientDevPatchLetter}.MPQ`
        let patchPath = mpath(patchdir,patchFile);

        return ClientPath(
              this.dataset.config.client_path
            , wfs.relative(this.dataset.config.client_path+'/Data',patchPath)
        )
    }

    patchDir() {
        return (this.dataset.config.ClientPatchUseLocale
            ? this.path.Data.locale()
            : this.path.Data
            ) as WDirectory
    }

    locale() {
        return this.path.Data.locale().basename()
    }

    async kill() {
        term.debug('client', `Killing client`)
        let processes = processMap[this.dataset.fullName];
        let count = 0;
        if(processes !== undefined) {
            count = processes.length;
            await Promise.all(processes.map(x=>x.stop()));
        }
        delete processMap[this.dataset.fullName];
        return count;
    }

    async cleanFrameXML() {
        await this.kill();
        this.mpqPatches().forEach(x=>{
            x.join('Interface','FrameXML','TSAddons')
        })
    }

    mpqPatches() {
        const nodes: WNode[] = []
        const iter = (dir: WDirectory) => {
            dir.iterate('FLAT','BOTH','FULL',node=>{
                if (
                    node.basename()
                        .toLowerCase()
                        .match(/patch-[a-zA-Z1-9].mpq/)
                ) {
                    nodes.push(node);
                }
            });
        }
        iter(this.path.Data);
        iter(this.path.Data.locale());
        return nodes;
    }

    writeRealmlist() {
        term.debug('client', `Writing realmlist`)
        const realmlist = this.path.Data.locale().realmlist_wtf.readString();
        if(realmlist !== 'set realmlist localhost') {
            wfs.makeBackup(this.path.Data.locale().realmlist_wtf.get())
        }
        this.path.Data.locale().realmlist_wtf.write('set realmlist localhost');
    }

    async start(count: number = 1) {
        if(count === 0) {
            return;
        }

        let processes = processMap[this.dataset.fullName]
            || (processMap[this.dataset.fullName] = []);

        for(let i=0;i<count;++i) {
            term.log('client',`Starting client for dataset ${this.dataset.name}`)
            let process = new Process('client').showOutput(false);
            if(isWindows()) {
                process.start(this.path.wow_exe.get())
            } else if(isMacOS()) {
                try {
                    // Use the configured Wine/CrossOver path for macOS
                    const winePath = NodeConfig.MacOSWinePath;
                    term.debug('client', `Using macOS Wine path: ${winePath}`);
                    
                    if(!winePath || winePath.trim() === '') {
                        throw new Error('MacOS.WinePath is not configured in node.conf');
                    }
                    
                    // Log the WoW executable path
                    const wowExePath = this.path.wow_exe.get();
                    term.debug('client', `WoW executable path: ${wowExePath}`);
                    
                    // Set up environment variables for Wine/CrossOver on macOS
                    const env: {[key: string]: string} = {};
                    
                    // Wine DLL overrides for Direct3D compatibility
                    env['WINEDLLOVERRIDES'] = NodeConfig.MacOSWineDllOverrides;
                    term.debug('client', `Setting WINEDLLOVERRIDES=${env['WINEDLLOVERRIDES']}`);
                    
                    // Metal HUD for debugging graphics (optional)
                    if (NodeConfig.MacOSEnableMetalHUD) {
                        env['MTL_HUD_ENABLED'] = '1';
                        term.debug('client', 'Enabling Metal HUD (MTL_HUD_ENABLED=1)');
                    }
                    
                    // Synchronous queue submits for Metal
                    if (NodeConfig.MacOSSynchronousQueueSubmits) {
                        env['MVK_CONFIG_SYNCHRONOUS_QUEUE_SUBMITS'] = '1';
                        term.debug('client', 'Enabling synchronous queue submits (MVK_CONFIG_SYNCHRONOUS_QUEUE_SUBMITS=1)');
                    }
                    
                    // DXVK async for better performance
                    if (NodeConfig.MacOSDXVKAsync) {
                        env['DXVK_ASYNC'] = '1';
                        term.debug('client', 'Enabling DXVK async (DXVK_ASYNC=1)');
                    }
                    
                    // Since Process.start() doesn't support environment variables directly,
                    // we'll use the env command to set them
                    let envCommand = '/usr/bin/env';
                    let envArgs: string[] = [];
                    
                    // Add all environment variables to the args array
                    if (env['WINEDLLOVERRIDES']) {
                        envArgs.push(`WINEDLLOVERRIDES=${env['WINEDLLOVERRIDES']}`);
                    }
                    if (env['MTL_HUD_ENABLED']) {
                        envArgs.push('MTL_HUD_ENABLED=1');
                    }
                    if (env['MVK_CONFIG_SYNCHRONOUS_QUEUE_SUBMITS']) {
                        envArgs.push('MVK_CONFIG_SYNCHRONOUS_QUEUE_SUBMITS=1');
                    }
                    if (env['DXVK_ASYNC']) {
                        envArgs.push('DXVK_ASYNC=1');
                    }
                    
                    // Add the Wine command and WoW executable path
                    // Handle paths with spaces by properly escaping them
                    // The env command will pass the arguments correctly to Wine
                    
                    
                    // Escape the Wine path and WoW executable path
                    const escapedWinePath = winePath;
                    const escapedWowPath = this.path.wow_exe.get();

                    envArgs.push(escapedWinePath);
                    envArgs.push(escapedWowPath);
                    
                    // Log the full command that will be executed
                    const fullCommand = `${envCommand} ${envArgs.join(' ')}`;
                    term.debug('client', `Executing command: ${fullCommand}`);
                    
                    // Log the specific Wine and WoW paths for debugging
                    term.debug('client', `Wine path (escaped): ${escapedWinePath}`);
                    term.debug('client', `WoW path (escaped): ${escapedWowPath}`);
                    

                    // Extract the directory
                    const wowCwd = path.dirname(wowExePath);


                    // Start the process with environment variables
                    process.startIn(wowCwd,envCommand, envArgs);
                    term.debug('client', 'Started WoW client with macOS-specific environment variables');
                } catch(err) {
                    term.error('client', `Failed to start WoW client on macOS: ${err.message}`);
                    term.log('client', 'Please ensure Wine or CrossOver is installed and MacOS.WinePath is correctly configured in node.conf');
                    term.log('client', 'If your Wine path contains spaces, make sure it is correctly configured in node.conf');
                    term.debug('client', `Current Wine path: ${NodeConfig.MacOSWinePath}`);
                    term.debug('client', `Current WoW path: ${this.path.wow_exe.get()}`);
                    throw err;
                }
            } else {
                // Linux
                process.start('wine',[this.path.wow_exe.get()])
            }
            processes.push(process);
            sleep(200)
        }
    }

    async startup(count: number = 1, ip: string = '127.0.0.1') {
        await this.kill();
        await this.applyExePatches();
        this.installAddons();
        this.clearCache();
        this.writeRealmlist();
        this.start(count);
    }

    async exePatches() {
        await this.dataset.worldDest.connect();
        // default roles
        let values = [
            { class: 1, tank: 1, healer: 0, damage: 1, leader: 1},
            { class: 2, tank: 1, healer: 1, damage: 1, leader: 1},
            { class: 3, tank: 0, healer: 0, damage: 1, leader: 1},
            { class: 4, tank: 0, healer: 0, damage: 1, leader: 1},
            { class: 5, tank: 0, healer: 1, damage: 1, leader: 1},
            { class: 6, tank: 1, healer: 0, damage: 1, leader: 1},
            { class: 7, tank: 0, healer: 1, damage: 1, leader: 1},
            { class: 8, tank: 0, healer: 0, damage: 1, leader: 1},
            { class: 9, tank: 0, healer: 0, damage: 1, leader: 1},
            { class: 11, tank: 1, healer: 1, damage: 1, leader: 1},
        ]
        try {
            values = await this.dataset.worldDest.query(
                `SELECT \`class\`,\`tank\`,\`healer\`,\`damage\`,\`leader\``
                + `FROM \`player_class_roles\``
            )
        // table might not exist yet, ignore errors
        } catch(err) {
            term.log('client'
                , `Could not load class roles, using default values.`
                + ` This usually just means you haven't built your`
                + ` database yet.`
            )
        }
        return ClientPatches(
              this.dataset.config.DatasetGameBuild
            , values
            )
    }

    async applyExePatches() {
        term.log('client',`Applying client patches...`)
        this.path.wow_exe.copyOnNoTarget(this.path.wow_exe_clean)

        let wowbin = this.path.wow_exe_clean.read()
        const md5 = (value: Buffer) => crypto
            .createHash('md5')
            .update(value)
            .digest('hex')
        let hash = md5(wowbin)
        if(hash !== CLEAN_CLIENT_MD5) {
            let exebin = this.path.wow_exe.read();
            if(md5(exebin) === CLEAN_CLIENT_MD5) {
                // user placed a new exe that's actually clean
                wowbin = exebin
                hash = CLEAN_CLIENT_MD5
                this.path.wow_exe_clean.writeBuffer(wowbin);
            } else {
                // todo: stupid bugged code
                //term.warn('client',
                //    `Unclean Wow.exe detected. Consider `
                // + `replacing it with a clean 3.3.5a client`)
            }
        }

        if(hash == CLEAN_CLIENT_MD5) {
            term.success('client',`Source wow client hash is ${hash}`);
        } else {
            term.success('client',`Source wow client hash is ${hash}`);
        }

        if(this.dataset.config.client_patches.includes(EXTENSION_DLL_PATCH_NAME)) {
            term.log('client', `Writing ClientExtensions.dll`)
            if(!ipaths.bin.ClientExtensions_dll.exists()) {
                throw new Error(
                      `Dataset ${this.dataset.name}`
                    + ` has client extensions enabled but this tswow`
                    + ` installation does not have one. Please put a working`
                    + ` dll at ${ipaths.bin.ClientExtensions_dll.get()}`
                )
            }
            wowbin = wowbin.subarray(0,0x758c00)
            ipaths.bin.ClientExtensions_dll
                .copy(this.path.ClientExtensions_dll)
        }

        term.debug('client', `Applying client patches`)
        const usedPatchNames = this.dataset.config.client_patches
        const usedPatches = (await this.exePatches())
            .filter(x=>usedPatchNames.includes(x.name));
        usedPatches.forEach(cat=>{
            term.log('client', `Applying client patch ${cat.name}`)
            cat.patches.forEach(patch=>{
                patch.values.forEach((value,offset)=>{
                    wowbin.writeUInt8(value,patch.address+offset);
                })
            })
        })
        term.log('client', `Writing patched wow.exe`)

        hash = md5(wowbin)
        term.log('client', `New wow.exe hash is ${hash}`);
        this.path.wow_exe.writeBuffer(wowbin);
    }

    patchPath(letter: string) {
        return this.dataset.config.ClientPatchUseLocale
            ? this.path.Data.locale()
                .join(`patch-${this.locale()}-${letter.toUpperCase()}.MPQ`)
            : this.path.Data
                .join(`patch-${letter.toUpperCase()}.MPQ`)
    }

    verify() {
        [this.path,this.path.wow_exe,this.path.Data]
            .forEach(x=>{
                if(x.exists()) {
                    throw new Error(`Missing/broken client: ${x.get()} does not exist`)
                }
            })
    }

    installAddons() {
        term.debug('client', `Installing addons`)
        ipaths.bin.addons.iterate('FLAT','DIRECTORIES','FULL',node=>{
            node.copy(this.path.Interface.AddOns.join(node.basename()));
        })
    }

    clearCache() {
        term.debug('client', `Clearing cache`)
        return this.path.Cache.remove();
    }

    freePatches() {
        const ids: WNode[] = []

        const order: string[] = []
        for(let i=4;i<9;++i) order.push(`${i}`)
        for(let i='A'.charCodeAt(0);i<'Z'.charCodeAt(0);++i) {
            order.push(`${String.fromCharCode(i)}`)
        }

        let start = order.indexOf(this.dataset.config.ClientDevPatchLetter.toUpperCase())
        if(start === -1) {
            throw new Error(
                  `Invalid patch letter: ${this.dataset.config.ClientDevPatchLetter}`
                + ` (in dataset ${this.dataset.fullName})`
            )
        }

        for(let i=start;i<order.length;++i) {
            let path = this.patchPath(order[i]);
            if( !path.exists()
                && path.abs().get() !== this.path.Data.devPatch.abs().get()
            ) {
                ids.push(path)
            }
        }

        return ids;
    }

    static initialize() {
        term.debug('client', `Initializing client`)
        if(!process.argv.includes('noclient') && NodeConfig.AutoStartClient > 0) {
            Identifier.getDataset(NodeConfig.DefaultDataset)
                .client.startup(NodeConfig.AutoStartClient)
        }

        StartCommand.addCommand(
              'client'
            , ''
            , 'Starts the WoW client'
            , args => {
                return Promise.all(Identifier.getDatasets(
                      args
                    , 'MATCH_ANY'
                    , NodeConfig.DefaultDataset
                ).map(x=>{
                    return x.client
                        .startup(Args.getNumber('--count',1,args));
                }))
            }
        )
    }
}
