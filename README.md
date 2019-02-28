# Simple instructions:
1. Establish an instance directory under DayZ server directory, such as: instance
2. Copy ModdedScripts to DayZ server directory (now referred to as: DayZServerDir from here on out)
3. Copy mission to mpmissions: DayZServerDir\mpmissions
4. Start your server: Use some sort of batch file to start/restart server with this in it...
 - .\DayZServerDir\DayZServer_x64.exe -server -mod=ModdedScripts;DayZ-Sa-Tomato -scrAllowFileWrite -filePatching -port=2302 -config=instance\serverdz.cfg -profiles=instance -name=instance -BEpath=BattlEye -cpuCount=8 -exThreads=7 -maxMem=20000 -noPause -noSound -noLogs -adminlog -freezecheck

Features I personally created/contributed:
 - Dynamic helo drops
 - Dynamic treasure chest drops
 
Admin tools:
Recommend a server side only Admin tool, like the specific version of Tomato included here, since it does not crash the server.

Do note, I improved the functionality of all of this code and kept it compatible with the latest version of DayZ.

I chose this version of DaOne's Vanilla++ to branch off and go a NO CLIENT MODS route. The latest versions of Vanilla++ incorporates required client-side mods. This implementation keeps all mods server-side only.

Credit to DaOne and his dev/qa team. Their feature list below... or search GitHub for https://github.com/Da0ne/DZMods for the latest version of that mod system.

——

# DayZ Vanilla++ Mission by DaOne v0.2


# ----Features built into this----

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
 - NOTE: This chat based admin tool does not work very well, which is why the Tomato admin tool is included.

## - Player score tracking system and Kill Activity tracker with timestamps
##### This feature creates two files in the server profile ( if you use -instance command line it would be placed there ) the serevr profile is in Documents folder by deafult (its where your logs are). provides detailed kill log and records players stats such as total deaths and total kills on the server. This feature is implemented within the mod.

## - Chat based kill messages
##### Shows who killed who, committed suicide.

## - Custom MOTD based within the mission
##### Random preset messages popup for all players. To change the messages check the file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/MOTDMessages.c "

##Chat based admin commands...

#login [password]

INSTRUCTIONS:


------------
Teleport locations list:
------------

Severograd

Krasnostav

Mogilevka

Stary

Msta

Vybor

Gorka

Solni

NWAFS

NWAFC

NWAFN

BAF

NEAF

ChernoC

ChernoW

ChernoE

ElektroW

ElektroE

BerezC

BerezS

BerezN

Svet

ZelenoS

ZelenoN

Lopatino

Tisy

Novaya

Novy

Grishino

Kabanino

--------------
Commands avaibale for use:

/export				  - Saves current gear on admin player as possible load-out to spawn with for players on server

/LoadoutType	      - Switches the load out type on spawn: static or randomly generated

/CustomLoadouts       -Enable or Disable custom loadouts

/godmode 			  -Enable/Diable God Mode

/freecam  			  -enables freecam, to disable type the command again

/spi itemClassName    -Spawns item in your inventory make sure you leave space after the command then insert item name

/spg itemClassName	  -Spawns item around your player make sure you leave space after the command then insert item name

/tpto TownName        - Teleports your player to the town selected (case sensative!) use names from list above!

/tpc 7500 0 7500      - Teleports player to the corrds make sure you leave space after the command and after each value x z y

/debug                - Enables/Disables debug monitor for all players on server. After Disabling players need to relog so the UI goes away.

/nighttime 			  - Not sure what this command does :P

/daytime		      - Not sure what this command does :P

/heal				  - Heals admin only

/tpalltome			  - welp, it will TP all players to you :)

/killall		      - yep, that ugly ass black screen will show up :P

/kill			      - Suicide is a problem within our society.

/spawncar			  - Spawns a blue Hatchback ready to drive right next to you :)

/tpp                  -Tp player to you by name, leave space after command

/tppm                 -tp your player to the player selected by name, leave space after command

/stamina			  -Enable/Disable Stamina on the server. Applies to all players.

/updateLoadouts       -Reads and constructs the custom loadouts files.

/strip PlayerName     -Strips the player from thier items (Deletes everything). leave space between command and name

/ammo				  - Reloads and Heals weapon in hand

/SpawnArmed			  -Enable/Disable the spawn with gun feature.