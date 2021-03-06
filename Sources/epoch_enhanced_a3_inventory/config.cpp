/*
	Author: Aaron Clark - EpochMod.com

    Contributors:

	Description:
	Epoch Enhanced Armor Stats for Arma 3

    Licence:
    Arma Public License Share Alike (APL-SA) - https://www.bistudio.com/community/licenses/arma-public-license-share-alike

    Github:
    https://github.com/EpochModTeam/Enhanced-Arma3-Inventory
*/
class CfgPatches {
	class A3_epoch_enhanced_a3_inventory {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"A3_Ui_F"};
	};
};

class CfgMods
{
	class epoch_enhanced_a3_inventory
	{
		dir = "@EEA3I";
		name = "Epoch Enhanced Arma 3 Inventory";
		picture = "\epoch_enhanced_a3_inventory\epoch_ca.paa";
		hidePicture = 0;
		hideName = 0;
		action = "http://www.epochmod.com";
		version = "1.1";
		ArmAVersion = 166;
		overview = "Enhanced Inventory for Arma 3";
	};
};

// custom UI stuff for armor stats
class RscProgress;
class RscCustomProgress : RscProgress
{
	texture = "";
	textureExt = "";
	colorBar[] = { 0.9, 0.9, 0.9, 0.9 };
	colorExtBar[] = { 1, 1, 1, 1 };
	colorFrame[] = { 1, 1, 1, 1 };
	x = "0 * 			(			((safezoneW / safezoneH) min 1.2) / 40)";
	y = "16 * 			(			(			((safezoneW / safezoneH) min 1.2) / 1.2) / 25)";
	w = "26 * 			(			((safezoneW / safezoneH) min 1.2) / 40)";
	h = "1 * 			(			(			((safezoneW / safezoneH) min 1.2) / 1.2) / 25)";
	colorBackground[] = { 1, 1, 1, 0.75 };
};
class RscTotalArmorProgress : RscProgress
{
    texture = "";
    textureExt = "";
    colorBar[] = { 0.9, 0.9, 0.9, 0.9 };
    colorExtBar[] = { 1, 1, 1, 1 };
    colorFrame[] = { 1, 1, 1, 1 };
    x = "1.5 * 					(			((safezoneW / safezoneH) min 1.2) / 40) + 		(safezoneX + (safezoneW - 					((safezoneW / safezoneH) min 1.2))/2)";
    y = "22.5 * 					(			(			((safezoneW / safezoneH) min 1.2) / 1.2) / 25) + 		(safezoneY + (safezoneH - 					(			((safezoneW / safezoneH) min 1.2) / 1.2))/2)";
    w = "11 * 					(			((safezoneW / safezoneH) min 1.2) / 40)";
    h = "1 * 					(			(			((safezoneW / safezoneH) min 1.2) / 1.2) / 25)";
};

// code
class CfgFunctions {
	class epoch_enhanced_a3_inventory {
		tag = "EPOCH";
		project = "epoch";
		class GUI
		{
			file = "epoch_enhanced_a3_inventory\scripts";
			class armorCalc{};
            class subMenu{};
            class ammoRepack{};
            class armorInit
            {
                postInit = 1;
            };
		};
	};
};

/* example custom sub menu config
 The condition and button action code have the following special variables available.
     _thisItem = contains the classname of the item
     _thisItemType = contains the type numbers:
          type=256 magazine
          type=801 uniform
          etc.

 interactActions Format:
     0 = Text Name of Action
     1 = Code to execute when button is pressed.
     2 = (optional) Condition evaluates string as code, code needs to return a BOOL.
     3 = (optional) 0 = Do not display button if above condition is false (default), 1 =  Display Button and use alternate button action code below.
     4 = (optional) Code to execute when the button is pressed on a failed condition above.
*/
class CfgItemInteractions {
    class AllAmmoSettings // this is a fake class that holds the settings for the ammo repack feature.
    {
        interactActions[] = {
            {"REPACK", "call EPOCH_fnc_ammoRepack;" } // To disable set this to an empty array here or in description.ext. interactActions[] = {};
        };
    };
    class FirstAidKit
    {
        interactActions[] = {
            // Test actions - requires the player to have a watch equipped for "Check Pulse" action to show on double click of the First Aid Kit.
            {"Check Pulse", "_target = player; if (cursorTarget isKindof 'Man') then {_target = cursorTarget}; if ((damage _target) > 0.1) then { hintSilent format['%1 Needs Medical Attention!',name _target];} else {hintSilent format['%1, Does Not Need Medical Attention.',name _target];};", "!('ItemWatch' in (assignedItems player))", 1 , "hintSilent 'Watch Needed';" }
            // {"Debug 1", "hintSilent str[_thisItem,_thisItemType];" },
        };
    };
};
