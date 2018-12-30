/*
	The Following class allows you to enable/disable and modifiy mods.
*/
class ModTunables extends ModuleManager
{
	//============Mods============
	protected bool m_AdminTool         = true;   //Set to 'true' to enable admin tools
	protected bool m_AdvancedLoadouts  = false;	 //Set to true to Spawn Players with custom loadouts, set false to spawn with Vanilla DayZ gear ( check 'AdvancedLoadouts.c' for more settings )
	protected bool m_InfectedHordes	   = true;   //Random zombie hordes that spawn on the map (The tunables for this mod can be found in 'InfectedHordes.c')
	protected bool m_SafeZone		   = false;   //set 'true' to Enable Safe Zone
	//============================

	//==============Misc==========
	protected bool m_Debugmonitor	   	= true; //Debug monitor enable/disable
	protected bool m_Debugmode 		   	= false; //Set true to disable db for faster server loading and for testing purposes
	protected bool m_ProxyExportMode  	= false; //Set to ture to export a new loot positions xml (export can be found in your Storage folder).
	protected bool m_StaminaStatus   	= true;  //set to true to disable Stamina
	protected bool m_HungerStatus    	= false;  //set to true to disable Health
	protected bool m_ThirstStatus    	= false;  //set to true to disable Thirst
	protected bool m_CustomBuildings  	= true;  //Spawns the buildings you add in file BuildingSpawner.c
	protected bool m_SessionFeed	  	= true;  //Set to true to enable Disconnect/Connect Messages
	//============================
	
	//==============Airdrops==========
	protected bool EnableAirdrops		= true;  //random airdrops
	protected bool SpawnZombie 			= true; // Spawn zombie near airdrop when landed
	protected bool ShowSignal 			= true; // Show smoke signal when airdrop landed
	//============================
	
	void ModTunables( DayZSurvival ServerMission )
	{
		
	}
	
	override void Init()
	{
		Print("ModTunables:: Init():: Loading Mod Settings...");
	}

	bool IsActiveMisc(string MiscName)
	{
		switch(MiscName)
		{
			case "Debugmode":
			Print("Debugmode: " + m_Debugmode.ToString());
			return m_Debugmode;
			break;
			
			case "Debugmomitor":
			Print("Debugmomitor: " + m_Debugmonitor.ToString());
			return m_Debugmonitor;
			break;

			case "ProxyExportMode":
			Print("ProxyExportMode: " + m_ProxyExportMode.ToString());
			return m_ProxyExportMode;
			break;

			case "StaminaStatus":
			Print("StaminaStatus: " + m_StaminaStatus.ToString());
			return m_StaminaStatus;
			break;
			
			case "HungerStatus":
			Print("HungerStatus: " + m_HungerStatus.ToString());
			return m_HungerStatus;
			break;
			
			case "ThirstStatus":
			Print("ThirstStatus: " + m_ThirstStatus.ToString());
			return m_ThirstStatus;
			break;
			
			case "Airdrops":
			Print("Airdrops: " + EnableAirdrops.ToString());
			return EnableAirdrops;
			break;
			
			case "AirdropZombies":
			Print("AirdropZombies: " + SpawnZombie.ToString());
			return SpawnZombie;
			break;
			
			case "AirdropFlare":
			Print("AirdropFlare: " + ShowSignal.ToString());
			return ShowSignal;
			break;

			case "CustomBuildings":
			Print("CustomBuildings: " + m_CustomBuildings.ToString());
			return m_CustomBuildings;
			break;

			case "SessionFeed":
			Print("SessionFeed: " + m_SessionFeed.ToString());
			return m_SessionFeed;
			break;
		}
		return false;
	}
	
	bool IsActive(string ModName)
	{
		switch(ModName)
		{
			case "AdminTools":
			Print("AdminTools: " + m_AdminTool.ToString());
			return m_AdminTool;
			break;

			case "AdvancedLoadouts":
			Print("AdvancedLoadouts: " + m_AdvancedLoadouts.ToString());
			return m_AdvancedLoadouts;
			break;

			case "InfectedHordes":
			Print("InfectedHordes: " + m_InfectedHordes.ToString());
			return m_InfectedHordes;
			break;

			case "SafeZone":
			Print("SafeZone: " + m_SafeZone.ToString());
			return m_SafeZone;
			break;
		}
		return false;
	}
}
