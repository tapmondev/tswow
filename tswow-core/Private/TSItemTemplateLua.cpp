#include "TSLua.h"
#include "TSItemTemplate.h"
#include "TSGlobal.h"
#include "TSObjectLua.h"

void TSLuaState::load_itemtemplate_methods(uint32_t modid)
{
    auto ts_itemtemplate = new_usertype < TSItemTemplate>("TSItemTemplate");
    load_entity_methods_t(ts_itemtemplate, modid, "TSItemTemplate");
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMinA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMinB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMaxA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMaxB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageTypeA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageTypeB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetClass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSubClass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSoundOverrideSubclass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDisplayInfoID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetQuality);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetFlags);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetFlags2);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetBuyCount);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetBuyPrice);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSellPrice);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetInventoryType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetAllowableClass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetAllowableRace);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetItemLevel);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredLevel);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredSkill);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredSkillRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredSpell);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredHonorRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredCityRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredReputationFaction);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredReputationRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetMaxCount);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStackable);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetContainerSlots);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStatsCount);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStatType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStatValue);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetScalingStatDistribution);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetScalingStatValue);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetArmor);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetHolyRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetFireRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetNatureRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetFrostRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetShadowRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetArcaneRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDelay);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetAmmoType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRangedModRange);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetBonding);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetPageText);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetLanguageID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetPageMaterial);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStartQuest);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetLockID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetMaterial);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSheath);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRandomProperty);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRandomSuffix);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetBlock);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetItemSet);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetMaxDurability);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetArea);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetMap);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetBagFamily);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetTotemCategory);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSocketBonus);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetGemProperties);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetRequiredDisenchantSkill);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetArmorDamageModifier);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDuration);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetItemLimitCategory);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetHolidayID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetScriptID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDisenchantID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetFoodType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetMinMoneyLoot);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetMaxMoneyLoot);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetFlagsCu);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, IsCurrencyToken);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetMaxStackSize);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDPS);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, CanChangeEquipStateInCombat);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetTotalAPBonus);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetItemLevelIncludingQuality);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSkill);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, IsPotion);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, IsWeaponVellum);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, IsArmorVellum);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, IsConjuredConsumable);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, HasSignature);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, Save);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, InitializeQueryData);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetEntry);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetEntry);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetClass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSubClass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSoundOverrideSubclass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetName);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDisplayInfoID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetQuality);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetFlags);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetFlags2);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetBuyCount);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetBuyPrice);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSellPrice);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetInventoryType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetAllowableClass);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetAllowableRace);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetItemLevel);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredLevel);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredSkill);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredSkillRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredSpell);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredHonorRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredCityRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredReputationFaction);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredReputationRank);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetMaxCount);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetStackable);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetContainerSlots);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStatsCount);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetStatsCount);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetScalingStatValue);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetArmor);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetHolyRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetFireRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetNatureRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetFrostRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetShadowRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetArcaneRes);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDelay);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetAmmoType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRangedModRange);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetBonding);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDescription);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetPageText);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetLanguageID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetPageMaterial);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetStartQuest);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetLockID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetMaterial);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSheath);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRandomProperty);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRandomSuffix);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetBlock);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetItemSet);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetMaxDurability);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetArea);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetMap);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetBagFamily);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetTotemCategory);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSocketBonus);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetGemProperties);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetRequiredDisenchantSkill);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetArmorDamageModifier);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDuration);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetItemLimitCategory);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetHolidayID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetScriptID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDisenchantID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetFoodType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetMinMoneyLoot);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetMaxMoneyLoot);

    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetFlagsCu);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetStatType);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStatType);

    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetStatValue);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetStatValue);

    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDamageMinA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMinA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDamageMinB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMinB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDamageMaxA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMaxA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDamageMaxB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageMaxB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageTypeA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDamageTypeA);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetDamageTypeB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetDamageTypeB);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSpellCategory);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSpellCategory);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSpellCategoryCooldown);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSpellCategoryCooldown);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSpellCharges);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSpellCharges);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSpellCooldown);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSpellCooldown);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSpellID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSpellID);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSpellPPMRate);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSpellPPMRate);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, GetSpellTrigger);
    LUA_FIELD(ts_itemtemplate, TSItemTemplate, SetSpellTrigger);

    ts_itemtemplate.set_function("GetFeralBonus", sol::overload(
        &TSItemTemplate::LGetFeralBonus0
        , &TSItemTemplate::LGetFeralBonus1
    ));
    ts_itemtemplate.set_function("GetName", &TSItemTemplate::LGetName);
    ts_itemtemplate.set_function("GetDescription", &TSItemTemplate::LGetDescription);
    set_function("GetItemTemplate", &GetItemTemplate);
    set_function("CreateItemTemplate", &CreateItemTemplate);
}
