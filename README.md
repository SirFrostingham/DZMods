DayZ Survival Mission by DaOne v0.1

CREDITS: @Sen (@zalexki zalexki ) from DayZModders Discord Server for the KillScore system
https://github.com/zalexki

NOTE: DO NOT sign the mod ModdedScripts, if you do then verifySignature would not work!!

How to Setup
=

Step One:
=
Go to your server directory and create a folder, name the folder whatever you want
-

Step Two: 
=
open the folder 'mpmissions' in your server directory, copy the file 'DayZSurvival.chernarusplus' and place it in there. 
(If you had any edits done to your loot xmls and wish to keep the storage make sure you replace it with the ones that are in 'DayZSurvival.chernarusplus' )
The db folder contains NO MODDED features/changes its all vanilla same goes with other xmls. Replace it with your modded xmls if you wish to.
-	
Step Three:
=
The server config file 'serverDZ.cfg' is in the main directory (Vanilla Fresh copy from steam), MOVE that file into the folder you created in step 1
Open up the config file and go to the bottom where you see 'dayzOffline.chernarusplus' REPLACE IT with 'DayZSurvival.chernarusplus' Save and exit.
-	
Step Four:
=
Place the foler 'ModdedScripts' into your main DayZ Server directory where the .exe is and all that stuff.
-

Step Five:
=
add the following startup command lines to your server: -mod=ModdedScripts -config=NameOfFolderFromStep1\serverDZ.cfg -profiles=NameOfFolderFromStep1 -name=myServerName
The -name command will change the name that shows up in global chat. When players join/leave/getkilled and other GlobalMessages.
if you wish to actiavte any other mods listed in the Features list. Just add the command line to whatever starts your server exe.
-




----Features List----
=

=================================
=

Feature:
Enable/Disable player Join/leave messages
=

Usage:
=
Addd this command line to enable: -SessionFeed


=================================
=


Feature:
Ability to Enabled/Disable Custom Spawn lodaouts.
=

Description:
=
This feature allows the fresh spawn players to load in with preset randomized gear.
To Configure the type of items to spawn on your players check the folder "mpmissions/DayZSurvival.chernarusplus/ScriptedMods/LoadOuts"
Each Catagory is in a seperate .txt file If you wish to remove an item or add, make sure you follow the same layout as the file comes in.
The Script will randomly select an item from each catagory. If you wish to remove a certain catagory simply leave the file empty or delete it.
You can modify the lodaouts while the server is running! After you make your edits login as admin in game and use the Admin command /updateLoadouts

Usage:
=
Add the command line -CustomLoadGear to the server .exe on startup to enable

=================================
=


Feature:
Ability to Enabled/Disable Weapons on spawn.
=

Description:
=
This feature allows you to give fresh spawns a gun on startup
To edit the types of guns it spawns, go into the following file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/DayZSurvival.c " LINE 352
That function is a randomizer.

Note:
=
This might be helpful --> SpawnGunIn( PlayerBase player, string ClassName, bool isPrimary, TstringArray Attachments, TstringArray Extras) NOTE: Set bool isPrimary to 'true' if you wish to make the weapon a primary

Usage:
=
Add the command line   -SpawnArmed   to the server .exe on startup to enable

=================================
=

Feature:
Disable/Enable stamina
=

Description:
=
I personnaly enjoy stamina...but here for those who hate it..

Usage:
=
Add this command line -DisableStamina  to disable it on server startup.

=================================
=

Feature:
Custom SafeZone with gmode.
=

Description:
=
This feature allows you to place a safezone anywhere on the map with a radius you wish for.
To modifiy the safeZone area check this file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/SafeZoneFunctions "

Usage:
=
Add -SafeZone as a commandline to the server .exe

=================================
=

Feature:
Spawn CustomBuildings anywhere on the map
=

Description:
=
This feature is just an easy way to place your CustomBuildings code in a tidy spot and not in the main init where shit gets clustred.
Check the file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/BuildingSpawner.c"
it does not matter how you spawn your buildings or set thier direction oritention etc, just make sure the script is inside the Void() to get executed on server startup
A nice way to get buildings imported is to use the COM (Community Offline Mode from Arkensor). You can place buidlings and extract thier info. Thank @DannyDog for that feature
			 
Usage:
=
add the command line -CustomBuildings to enable

=================================
=

Feature:
Chat Based Admin Tool set.
=

Description:
=
This mod includes a chat based admin toolset.

Usage:
=
Simply Add your steam 64 ID ( eg 76561198420222029 ) into the file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/Admins.txt "
Set a server admin password in the server.cfg, in game login using the password. #login myPassword
The Admintoolset feature can be found here: https://pastebin.com/U4FiYhSf
	   
=================================
=

Feature:
Player score tracking system and Kill Activity tracker with timestamps
=

Description:
=
This feature creates two files in the server profile ( if you use -instance command line it would be placed there ) 
the serevr profile is in Documents folder by deafult (its where your logs are).
provides detailed kill log and records players stats such as total deaths and total kills on the server
			 
Usage:
=
This feature is implemented within the mod.

=================================
=

Feature:
Chat based kill messages, Login/logout messages
=

Description:
=
Shows who killed who, committed suicide, joined/left the server.

Usage:
=
This feature is implemented within the mod.

=================================
=

Feature:
Custom MOTD based within the mission
=

Description:
=
Random preset messages popup for all players
To change the messages check the file " mpmissions/DayZSurvival.chernarusplus/ScriptedMods/MOTDMessages.c "

Usage:
=
This feature is implemented within the mod.

=================================
=