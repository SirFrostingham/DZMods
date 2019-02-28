class CrashSiteDropPlusConfig
{
	private int DropTime;
	private int DespawnTime;
	private int MaxDrops;
	private int lootCount;

	private ref array<string> AirDropLoot;
	private ref array<vector> AirDropLocations;
	static const string SETTINGS_FILE = "$profile:\\CrashSiteDropConfig.json";


	void CrashSiteDropPlusConfig()
	{
		AirDropLoot = new ref array<string>;
		AirDropLocations = new ref array<vector>;
		DropTime = 60;
		lootCount = 15;		//def: 5
		DespawnTime = 60000;	//def: 60
		MaxDrops = 10;
	}
	
	void createDefaults()
	{
		ref array<string> loot = {
			"AKM", 					// weapons 
			"M4A1", 
			"Izh18", 
			"MP5K", 
			"UMP45", 
			"mosin9130",
			"mosin9130_black",
			"mosin9130_green",
			"mosin9130_camo",
			"CombatKnife",
			"AliceBag_Camo",		// backpacks
			"AliceBag_Green",
			"GhillieBushrag_Mossy",	// clothes
			"GhillieSuit_Mossy",
			"M65Jacket_Black",
			"USMCJacket_Woodland",
			"USMCPants_Woodland",
			"SVD",
			"FNX45",
			"ammo_45acp", 			// ammo
			"ammo_308win", 
			"ammo_9x19", 
			"ammo_380", 
			"ammo_556x45", 
			"ammo_762x54", 
			"ammo_762x54tracer", 
			"ammo_762x39", 
			"ammo_9x39", 
			"ammo_22", 
			"ammo_12gapellets",
			"mag_cmag_10rnd",
			"mag_cmag_30rnd", 
			"mag_cmag_30rnd_black",
			"mag_cmag_30rnd_green", 
			"mag_cmag_40rnd", 
			"mag_cmag_40rnd_black", 
			"mag_cmag_40rnd_green",
			"MP5_PlasticHndgrd",	// weapon attachments
			"PUScopeOptic",
			"PSO1Optic",
			"M68Optic",
			"AK_Woodbttstck",
			"M4_PlasticHndgrd",
			"M4_MPBttstck",
			"M4_T3NRDSOptic",
			"M4_Suppressor",
		};
		
		ref array<vector> locations = {
			"11341.7 84.2 9595.98",
			"12465.5 39.9 10159.3",
			"13052.8 17 10081.1",
			"13277.5 5.2 10697.5",
			"10717.7 252 8717.88",
			"10232.4 259.3 8571.46",
			"7501.3 325.5 7905.63",
			"6643.84 321.5 8017.03",
			"6556.58 296.2 7261.61",
			"7530.51 308 7397.4",
			"7961.37 350.2 7311.12",
			"8408.57 333.9 6323.07",
			"7254.65 262.3 5987.68",
			"4075.79 340 9540.97",
			"4459.29 342.9 10425.8",
			"4995.71 341 9341.83",
			"4203.58 345 9749.21",
			"3633.36 359.3 10377.5",
			"4728.53 255 11930.7",
			"5824.95 268 10946.3",
			"4166.81 338.5 10785.4",
			"7316.7 302 10641.8",
			"7455 294.3 11508.9",
			"9796.12 85.9 2526.79",
			"9101.13 58 2473.27",
			"8422.35 14.3 3175.09",
			"6874.07 82.4 3420.93",
			"7152.52 43.3 2926.18",
			"6010.6 6.5 2068.96",
			"5096.19 10 2419.68",
			"3837.79 30.2 2990.54",
			"3277.11 152 3369.23",
			"1890.82 778 2830.06",
			"1304.81 108.5 3641.41",
			"2109.67 185 4246.29",
			"2998.98 240.9 4817.31",
			"2950.85 282.9 5950.97",
			"3964.32 327 6490.89",
			"4599.16 295 6020.36",
			"4053.45 298.6 7804.46",
			"4768.9 325.8 8512.8",
			"5737.4 317.6 8363.19",
			"6119.66 333.3 8580.07",
			"12010.4 140.50 12663.8",
			"11557.6 173.8 12999.2",
			"8687.02 118.75 13008",
			"8654.42 107.8 13290.2",
			"8314.58 167.75 13371.2",
			"5793 179.75 12832",
			"3753.86 201.75 12755",
			"4795.97 250.75 11963.1",
		};
		
		int max = 10;
		int time = 600;
		int despawnTime = 60000;
		int lootCount = 15;
		addData(max, time, despawnTime, loot, locations, lootCount);
	}

	void addData(int max, int time, int despawntime, ref array<string> loot, ref array<vector> locations, int lootCount){
		AirDropLoot = loot;
		AirDropLocations = locations;
		DropTime = time;
		DespawnTime = despawntime;
		MaxDrops = max;
		this.lootCount = lootCount;
	}
	void save(){
		JsonFileLoader<CrashSiteDropPlusConfig>.JsonSaveFile(SETTINGS_FILE, this);
	}

	void load(){
		if (FileExist(SETTINGS_FILE)) {
			JsonFileLoader<CrashSiteDropPlusConfig>.JsonLoadFile(SETTINGS_FILE, this);
		}
		else
		{
			Print("No Helo Airdrop Config found, creating Airdrop json.");
			createDefaults();
			save();
		}
	}

	int getDespawnTime()
	{
		return DespawnTime;
	}
	
	vector chooseDropLocation()
	{
		return AirDropLocations.GetRandomElement();
	}

	ref array<string> chooseLoot(){
		ref array<string> lootArray = new array<string>;
		for(int i = 0; i < lootCount; i++){
			lootArray.Insert(AirDropLoot.GetRandomElement());
		}

		return lootArray;
	}

	int getDropTime()
	{
		return DropTime;
	}
	
	int getMaxDrops()
	{
		return MaxDrops;
	}
}