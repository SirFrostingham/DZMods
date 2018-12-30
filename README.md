# Simple instructions:
1. Establish an instance directory under DayZ server directory, such as: instance
2. Copy ModdedScripts to DayZ server directory (now referred to as: DayZServerDir from here on out)
3. Copy mission to mpmissions: DayZServerDir\mpmissions
4. Start your server: Use some sort of batch file to start/restart server with this in it...
 - .\DayZServerDir\DayZServer_x64.exe -server -mod=ModdedScripts -scrAllowFileWrite -filePatching -port=2302 -config=instance\serverdz.cfg -profiles=instance -name=instance -BEpath=BattlEye -cpuCount=8 -exThreads=7 -maxMem=20000 -noPause -noSound -noLogs -adminlog -freezecheck

I chose this version of DaOne's Vanilla++ to branch off and go a NO CLIENT MODS route. The latest verions of Vanilla++ incorporates required client-side mods. This implementation keeps all mods server-side only.

All credit goes to DaOne and his dev/qa team. Their instructions listed below... or search GitHub for https://github.com/Da0ne/DZMods

——

# DayZ Vanilla++ Mission by DaOne v0.2
#### CREDITS: @Sen (@zalexki zalexki ) from DayZModders Discord Server for the KillScore system https://github.com/zalexki
#### NOTE: DO NOT sign the mod ModdedScripts, if you do then verifySignature would not work!!

##### UPDATE  8/11/2018
### ChangeLog:
#### Fixed Mission to work with build 0.63.149358
#### The Mission was re-structered
#### 'ModSettings.c' is not a thing anymore, check 'Tunables.c'
### Issues:
#### Custom MOTD mod is currently unfucntional, due to its terrible state.

##### UPDATE  31/10/2018
### ChangeLog:
####  New Features/Changes to existing features:
#### -Removed the use of command lines as keys to disable and enable mods due to complications with third party hosting services
#### -Added 'ModSettings.c' that handles all the mod options. Enabling/Disabling features are all now manipulated via this file.
#### -Added the ability to generate and save static loadouts.
 >Usage: As an admin use the command /export and the gear that is currently on your player will be saved and can be utilized as a loadout-on-spawn if you enable 'm_CustomLoadouts' & 'm_StaticLoadouts' make sure to disable 'm_RandomizedLoadouts'
 -Added Customizable Infected randomized server events. ( check InfectedHordes.c For more info )
 -AdminTool: Added a new command  /LoadoutType used to switch from using static loadouts to randomized. Works only if custom loadouts is enabled in ModSettings.c
  
  
#### BugFixes:
-Fixed a bug with the AdminTool printing error messages in crash.log and scripts.log due to shitty code :P
-Improved the functionailty of some loops that could have caused possible FPS drops (safezone...)

#### KnownIssues:
-New Loadout feature does not attach secondary weapon attachmnets (pistol/weapon that is placed within an inventory container).
-SafeZone Godmode is not really godmode thats because the damage fucntions are hard-codded into the game engine.

#### Future Plans & updates:
 -Support for client side.
	-UI for trader system, admin tool interface/panel, Customizable map UI, Killfeed UI
 - Fully Customizable Randomized AI server events.
 - Support of 'event mode' ( switching the server from survival to PvP style with ability to customize playzones,match duration etc )
----------------------------------------------------------------------------------------------------------------------
## How to Setup
### IMPORTANT : For those who own a server provide by [www.Vilayer.com](Vilayer.com), can auto install the mod via the `AddonManager` (special thanks goes to the Vilayer team)!
![Vilayer.com](https://ci5.googleusercontent.com/proxy/yE1RaRsPdehe3Y5lTBg3K2UmKkKYBPUl4HOLneY8hzalp34EayGB0c8qeUxsz4W_vaGETV57DzOYC1huj7bvJmDlyfIodhIE2p07uyLeVuvkyCvCOmKg=s0-d-e1-ft#https://www.vilayer.com/templates/ColoNode/html/img/logo_dark.png)
### Step One:
##### Go to your server directory and create a folder, name the folder what ever you desire son. (just give it a damn name that is not NewFolder)

### Step Two:
##### open the folder 'mpmissions' in your server directory, copy the file 'DayZSurvival.chernarusplus' and place it in there. (If you had any edits done to your loot xmls and wish to keep the storage make sure you replace it with the ones that are in 'DayZSurvival.chernarusplus' ) The db folder contains NO MODDED features/changes its all vanilla same goes with other xmls. Replace it with your modded xmls if you wish to.

### Step Three:
##### The server config file 'serverDZ.cfg' is in the main directory (Vanilla Fresh copy from steam), MOVE that file into the folder you created in step 1 Open up the config file and go to the bottom where you see 'dayzOffline.chernarusplus' REPLACE IT with 'DayZSurvival.chernarusplus' Save and exit.

### Step Four:
##### Place the foler 'ModdedScripts' into your main DayZ Server directory where the .exe is and all that stuff.

### Step Five:
##### add the following startup command lines to your server: -mod=ModdedScripts -config=NameOfFolderFromStep1\serverDZ.cfg -profiles=NameOfFolderFromStep1 -name=myServerName The -name command will change the name that shows up in global chat. When players join/leave/getkilled and other GlobalMessages. if you wish to actiavte any other mods listed in the Features list. Just add the command line to whatever starts your server exe.


# ----Features----

## -Enable/Disable player Join/leave messages. Check the file "Settings.C"

##  -Ability to Enabled/Disable Custom Spawn lodaouts.
#####  This feature allows the fresh spawn players to load in with preset randomized gear. To Configure the type of items to spawn on your players check the folder "mpmissions/DayZSurvival.chernarusplus/ScriptedMods/LoadOuts" Each Catagory is in a seperate .txt file If you wish to remove an item or add, make sure you follow the same layout as the file comes in. The Script will randomly select an item from each catagory. If you wish to remove a certain catagory simply leave the file empty or delete it. You can modify the lodaouts while the server is running! After you make your edits login as admin in game and use the Admin command /updateLoadouts

## -Ability to Enable/Disable Weapons on spawn.
##### This feature allows you to give fresh spawns a gun on startup To edit the types of guns it spawns, go into the following file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/DayZSurvival.c " LINE 352 That function is a randomizer. This might be helpful --> SpawnGunIn( PlayerBase player, string ClassName, bool isPrimary, TstringArray Attachments, TstringArray Extras) NOTE:  Set bool isPrimary to 'true' if you wish to make the weapon a primary


## - Disable/Enable stamina Add this command line -DisableStamina  to disable it on server startup.

## - Custom SafeZone with gmode.
##### This feature allows you to place a safezone anywhere on the map with a radius you wish for. To modifiy the safeZone area check this file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/SafeZoneFunctions "

## - Spawn Custom Buildings anywhere on the map
##### This feature is just an easy way to place your CustomBuildings code in a tidy spot and not in the main init where shit gets clustred. Check the file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/BuildingSpawner.c" it does not matter how you spawn your buildings or set thier direction oritention etc, just make sure the script is inside the Void() to get executed on server startup A nice way to get buildings imported is to use the COM (Community Offline Mode from Arkensor). You can place buidlings and extract thier info. Thank @DannyDog for that feature

## - Chat Based Admin Tool set.  
#### Simply Add your steam 64 ID into the file mpmissions/DayZSurvival.chernarusplus/ScriptedMods/Admins.txt" Set a server admin password in the server.cfg, in game login using the password. #login myPassword The Admintoolset feature can be found here: https://pastebin.com/GGrCDg3f

## - Player score tracking system and Kill Activity tracker with timestamps
##### This feature creates two files in the server profile ( if you use -instance command line it would be placed there ) the serevr profile is in Documents folder by deafult (its where your logs are). provides detailed kill log and records players stats such as total deaths and total kills on the server. This feature is implemented within the mod.

## - Chat based kill messages
##### Shows who killed who, committed suicide.

## - Custom MOTD based within the mission
##### Random preset messages popup for all players. To change the messages check the file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/MOTDMessages.c "

### USEFUL THINGS:
#### How to generate new loot positions for your custom buildings: https://pastebin.com/FqunXuzc
