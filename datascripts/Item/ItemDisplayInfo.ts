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
import { ItemDisplayInfoQuery, ItemDisplayInfoRow } from "wotlkdata/dbc/types/ItemDisplayInfo";
import { Table } from "wotlkdata/table/Table";
import { DBC, SQL } from "wotlkdata/wotlkdata";
import { MainEntity } from "../Misc/Entity";
import { DynamicIDGenerator, Ids } from "../Misc/Ids";
import { ParticleColorRegistry } from "../Misc/ParticleColor";
import { RegistryDynamic } from "../Refs/Registry";
import { SpellVisualRegistry } from "../Spell/SpellVisual";
import { ItemIcon } from "./ItemIcon";
import { ItemEffectsRegistry } from "./ItemVisualEffect";
import { ItemVisualModels } from "./ItemVisualModels";

export class ItemDisplayInfo extends MainEntity<ItemDisplayInfoRow> {
    get ID() { return this.row.ID.get(); }
    get Flags() { return this.wrap(this.row.Flags); }
    get GeosetGroup() { return this.wrapArray(this.row.GeosetGroup); }
    get HelmGeosetVis() { return this.wrapArray(this.row.HelmetGeosetVis); }
    get Effects() { return ItemEffectsRegistry.ref(this, this.row.ItemVisual); }
    get Models() { return new ItemVisualModels(this); }
    get ParticleColor() { return ParticleColorRegistry.ref(this, this.row.ParticleColorID); }
    get SpellVisual() { return SpellVisualRegistry.ref(this, this.row.SpellVisualID); }
    get Texture() { return this.wrapArray(this.row.Texture); }
    get Icon() { return new ItemIcon(this); }

    copyFromDisplay(displayId: number) {
        DBC.ItemDisplayInfo
            .findById(displayId)
            .clone(Ids.ItemDisplayInfo.id())
        return this;
    }

    copyFromTemplate(templateId: number) {
        this.copyFromDisplay(
            SQL.item_template.find({entry:templateId}).displayid.get())
        return this;
    }
}

export class ItemDisplayInfoRegistryClass
    extends RegistryDynamic<
          ItemDisplayInfo
        , ItemDisplayInfoRow
        , ItemDisplayInfoQuery
        >
{
    protected Table(): Table<any, ItemDisplayInfoQuery, ItemDisplayInfoRow> & { add: (id: number) => ItemDisplayInfoRow; } {
        return DBC.ItemDisplayInfo
    }
    protected ids(): DynamicIDGenerator {
        return Ids.ItemDisplayInfo
    }
    Clear(entity: ItemDisplayInfo): void {
        entity.Effects.set(0)
              .Flags.set(0)
              .GeosetGroup.fill(0)
              .HelmGeosetVis.fill(0)
              .Icon.set('')
              .Models.clearAll()
              .ParticleColor.set(0)
              .SpellVisual.set(0)
              .Texture.fill('')
    }
    protected Clone(entity: ItemDisplayInfo, parent: ItemDisplayInfo): void {
        throw new Error("Method not implemented.");
    }
    protected FindByID(id: number): ItemDisplayInfoRow {
        return DBC.ItemDisplayInfo.findById(id);
    }
    protected EmptyQuery(): ItemDisplayInfoQuery {
        return {}
    }
    ID(e: ItemDisplayInfo): number {
        return e.ID
    }
    protected Entity(r: ItemDisplayInfoRow): ItemDisplayInfo {
        return new ItemDisplayInfo(r);
    }
}

export const ItemDisplayinfoRegistry = new ItemDisplayInfoRegistryClass();