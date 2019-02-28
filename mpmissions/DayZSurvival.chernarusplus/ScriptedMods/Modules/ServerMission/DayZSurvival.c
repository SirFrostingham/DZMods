#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\ModuleManager.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Tunables.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\AdminTool\\AdminTool.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\AdvancedLoadouts\\AdvancedLoadouts.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\Misc\\BuildingSpawner.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\SafeZone\\SafeZoneFunctions.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\ServerEvents\\InfectedHordes.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\SupplyDropPlus\\SupplyDropPlusManager.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\CrashSite\\CrashSiteDropPlusManager.c"
//#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\CrashSite\\CrashSite.c"
//#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\CrashSite\\CrashSiteManager.c"

//#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\Misc\\MOTDMessages.c"

class DayZSurvival : MissionServer
{
	//ref CrashSiteManager m_crashSiteSpawner;
	ref SupplyDropPlusManager airdrop;
	ref CrashSiteDropPlusManager crashSiteDrop;
	private ref set<ref ModuleManager> m_Modules;
	ref InfectedHordes m_ZombieEvents;
	protected float m_LogInTimerLength = 1;     //in seconds the spawn timer when players login!
	bool m_StaminaStatus = false;
	//sheep
	bool m_HungerStatus = false;
	bool m_ThirstStatus = false;
	bool EnableAirdrops = false;
	bool SpawnZombie = false;
	bool ShowSignal = false;
	bool m_Debugmonitor = false;
	
	ref AirDrop AirDropClass;


	void DayZSurvival()
	{
		Print("VANILLA++ IS ALIVE!!");
		m_Modules = new set<ref ModuleManager>;
		RegisterModules();
		
		//Airdrop
		AirDropClass = new AirDrop;
		
		//supply drop
		airdrop = new SupplyDropPlusManager();
		
		//supply drop
		crashSiteDrop = new CrashSiteDropPlusManager();
		
		//crash sites
		//m_crashSiteSpawner = new CrashSiteManager();
		//new CrashSiteManager();
	}
	
	void ~DayZSurvival()
	{
		
	}
	
	void RegisterModules()
	{
		m_Modules.Insert(new ModTunables(this));
		
		if (ModTunables.Cast(GetModule(ModTunables)).IsActive("AdminTools"))
		{
			m_Modules.Insert(new AdminTool(this));
		}

		if (ModTunables.Cast(GetModule(ModTunables)).IsActive("AdvancedLoadouts"))
		{
			m_Modules.Insert(new AdvancedLoadouts(this));
		}

		if (ModTunables.Cast(GetModule(ModTunables)).IsActive("SafeZone"))
		{
			m_Modules.Insert(new SafeZone(this));
		}
	}
	
	void InitModules()
	{
		for ( int i = 0; i < m_Modules.Count(); ++i)
		{
			m_Modules.Get(i).Init();
		}
	}
	
	ModuleManager GetModule(typename moduleType)
	{
		for ( int i = 0; i < m_Modules.Count(); ++i)
		{
			ModuleManager module = m_Modules.Get(i);
			if (module.GetModuleType() == moduleType) 
			{
				return module;
			}
		}
		return NULL;
	}
	
	
	override void OnInit()
	{
		super.OnInit();
		InitModules();
		
		if (!ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("Debugmode"))
		{
			Hive ce = CreateHive();
			if (ce)
			ce.InitOffline();
		}

		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("ProxyExportMode"))
		{
			CETesting TestHive = GetTesting();
			TestHive.ExportProxyProto();
			TestHive.ExportProxyData( "7500 0 7500", 15000 );
		}

		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("SessionFeed"))
		{
			g_Game.SetProfileString("SessionFeed", "true");
		}
		else
		{
			g_Game.SetProfileString("SessionFeed", "false");
		}

		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("CustomBuildings"))
		{
			ref BuildingSpawner bldspnwer = new BuildingSpawner;
			bldspnwer.Init();
		}

		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("StaminaStatus"))
		{
			m_StaminaStatus = true; //Disable Stamina
		}
		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("HungerStatus"))
		{
			m_HungerStatus = true; //Disable Hunger
		}
		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("ThirstStatus"))
		{
			m_ThirstStatus = true; //Disable Thirst
		}
		if (ModTunables.Cast(GetModule(ModTunables)).IsActive("InfectedHordes"))
		{
			m_ZombieEvents = new InfectedHordes;
		}
		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("Airdrops"))
		{
			EnableAirdrops = true; //Airdrops
		}
		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("AirdropZombies"))
		{
			SpawnZombie = true; //AirdropZombies
		}
		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("AirdropFlare"))
		{
			ShowSignal = true; //AirdropFlares
		}
		if (ModTunables.Cast(GetModule(ModTunables)).IsActiveMisc("AirdropFlare"))
		{
			m_Debugmonitor = true; //Debug monitor
			GetGame().SetDebugMonitorEnabled(1);
		}
		
		//-----------
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.PlayerCounter, 110000, true);  //Default 120000 2 mins Looped
		//GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CustomMOTD, TIME_INTERVAL, true);  //Default 120000 2 mins Looped
		//-----------
	}

	override void OnPreloadEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int queueTime)
	{
		if (GetHive())
		{
			useDB = true;
			queueTime = m_LogInTimerLength;
		}
		else
		{
			useDB = false;
			pos = "7500 0 7500";
			yaw = 0;
			queueTime = m_LogInTimerLength;
		}
	}

	override void TickScheduler(float timeslice)
	{
		GetGame().GetWorld().GetPlayerList(m_Players);
		if( m_Players.Count() == 0 ) return;
		for(int i = 0; i < SCHEDULER_PLAYERS_PER_TICK; i++)
		{
			if(m_currentPlayer >= m_Players.Count() )
			{
				m_currentPlayer = 0;
			}

			if(m_Players.Get(m_currentPlayer) != NULL)
			{
				PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(m_currentPlayer));
				
				currentPlayer.OnTick();

				if (m_StaminaStatus) {
					currentPlayer.GetStaminaHandler().SyncStamina(1000,1000);
					currentPlayer.GetStatStamina().Set(currentPlayer.GetStaminaHandler().GetStaminaCap());
				}
				if (m_HungerStatus) {
					currentPlayer.GetStatEnergy().Set(20000);
				}
				if (m_ThirstStatus) {
					currentPlayer.GetStatWater().Set(5000);
				}
				
				if (GetModule(SafeZone)) { SafeZone.Cast(GetModule(SafeZone)).SafeZoneHandle(currentPlayer); }
				m_currentPlayer++;
			}
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;

		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
		Class.CastTo(m_player, playerEnt);
		
		GetGame().SelectPlayer(identity, m_player);
		return m_player;
	}
	
	override void OnEvent(EventType eventTypeId, Param params) 
	{
		super.OnEvent(eventTypeId,params);

		PlayerIdentity identity;
		switch(eventTypeId)
		{
			case ChatMessageEventTypeID:
			 ChatMessageEventParams chat_params = ChatMessageEventParams.Cast(params);
			 if (chat_params.param1 == 0 && chat_params.param2 != "") //trigger only when channel is Global == 0 and Player Name does not equal to null
				{
					Param4<int,string,string,string> request_info = new Param4<int,string,string,string>(chat_params.param1, chat_params.param2, chat_params.param3, chat_params.param4);
					AdminTool.Cast(GetModule(AdminTool)).RequestHandler(request_info); //Send the param to Admintools
				}
			break;
		}
	}
	
	void GlobalMessage(int Channel, string Message)
	{
		if (Message != "")
		{
			//GetGame().ChatPlayer(Channel,Message);
			GetGame().ChatPlayer(Message);
		}
	}

	void PlayerCounter()
	{
		array<Man> players = new array<Man>;
	    GetGame().GetPlayers( players );
	    int numbOfplayers = players.Count();
	    GlobalMessage(1,"Online Players: "+ numbOfplayers.ToString());
	}
	
	// This overrides '5_Mission\mission\missionServer.c', but because we changed the 
	// type from PlayerBase to PlayerBase, there is NO NEED for 'overrride keyword'
	void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		ItemBase itemBs;
		EntityAI itemEnt;
		
		if (GetModule(AdvancedLoadouts))
		{
			if (AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).CheckTunables("StaticLoadouts"))
			{
				bool reqld = AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).LoadRandomStaticLD(PlayerBase.Cast(player));
			}
			else if (AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).CheckTunables("RandomizedLoadouts"))
			{
				AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).LoadRndGenLoadout(PlayerBase.Cast(player));
			}
			else
			{
				//Vanilla
				itemEnt = player.GetInventory().CreateInInventory( "Rag" );
				itemBs = ItemBase.Cast(itemEnt);							
				itemBs.SetQuantity(6);
			
				itemEnt = player.GetInventory().CreateInInventory("Flashlight");
				itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("Battery9V");
				itemBs = ItemBase.Cast(itemEnt);
				itemEnt = player.GetInventory().CreateInInventory("PersonalRadio");
				itemBs = ItemBase.Cast(itemEnt);
			}

			if (AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).CheckTunables("SpawnArmed"))
			{
			    //Gun spawner Handle
				//SpawnGunIn( PlayerBase player, string ClassName, bool isPrimary, TstringArray Attachments, TstringArray Extras) NOTE: Set bool to 'true' IF weapon was primary
				int oRandValue = Math.RandomIntInclusive(0,2);
				switch(oRandValue.ToString())
				{
					case "0":
					AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).SpawnGunIn( PlayerBase.Cast(player) , "fnx45", true, {"fnp45_mrdsoptic","PistolSuppressor"},{"mag_fnx45_15rnd","mag_fnx45_15rnd"} );
					break;

					case "1":
					AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).SpawnGunIn( PlayerBase.Cast(player) , "CZ75", true, {"PistolSuppressor"} , {"Mag_CZ75_15Rnd","Mag_CZ75_15Rnd"} );
					break;

					case "2":
					AdvancedLoadouts.Cast(GetModule(AdvancedLoadouts)).SpawnGunIn( PlayerBase.Cast(player) , "makarovij70", true, {"PistolSuppressor"} , {"mag_ij70_8rnd","mag_ij70_8rnd"} );
					break;
				}
			}
		}
		else
		{
			//Vanilla
			itemEnt = player.GetInventory().CreateInInventory( "Rag" );
			itemBs = ItemBase.Cast(itemEnt);							
			itemBs.SetQuantity(6);
			
			itemEnt = player.GetInventory().CreateInInventory("Flashlight");
			itemBs = ItemBase.Cast(itemEnt);
			itemEnt = player.GetInventory().CreateInInventory("Battery9V");
			itemBs = ItemBase.Cast(itemEnt);
			itemEnt = player.GetInventory().CreateInInventory("PersonalRadio");
			itemBs = ItemBase.Cast(itemEnt);
		}
	}
	//airdrop
	float TimerSlice; // Timeslice
	override void OnUpdate( float timeslice )
	{
		super.OnUpdate( timeslice );

		// FPS Fix
		TimerSlice += timeslice;
		if (TimerSlice >= AirDropClass.TimesliceMultiplyier)
		{
			AirDropClass.CreateAirDrop();
			TimerSlice = 0;	
		}
		//todo: research this: GetGame().IsMultiplayer() || !GetGame().IsClient()
		
		//supply drop
		airdrop.onUpdateMaxSupplyDrops(timeslice);
		
		//supply drop
		crashSiteDrop.onUpdateMaxCrashes(timeslice);
		
		//crash sites
		//m_crashSiteSpawner.PollCrashSite();		
	}
}