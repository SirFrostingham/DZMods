class SupplyDropPlusConfig
{
	private int DropTime;
	private int DespawnTime;
	private int MaxDrops;
	private int lootCount;

	private ref array<string> AirDropLoot;
	private ref array<vector> AirDropLocations;
	static const string SETTINGS_FILE = "$profile:\\SupplyDropConfig.json";


	void SupplyDropPlusConfig()
	{
		AirDropLoot = new ref array<string>;
		AirDropLocations = new ref array<vector>;
		DropTime = 60;
		lootCount = 5;		//def: 5
		DespawnTime = 60000;	//def: 60
		MaxDrops = 200;
	}
	
	void createDefaults()
	{
		ref array<string> loot = {
			"TTSKOPants",
			"TacticalBaconCan",
			"M4A1",
			"PlateCarrierComplete",
			"BakedBeansCan",
			"WaterBottle",
		};
		
		ref array<vector> locations = {
			"8400 0 10200",
			"9120 0 5415",
			"6800 0 9000",
			"6000 0 11500",
			"1550 0 6750",
			"3600 0 3600",
			"1200 0 3100",
			"8428 0 12767",
			"11172 0 12314",
			"7537 0 5211",
			"6046 0 7733",
			"11322 0 5463",
			"3784 0 8923",
			"9514 0 8863",
			"13402 0 6303",
			"4540 0 9645",
			"4823 0 10457",
			"4214 0 10977",
			"4467 0 2496",
			"11921 0 12525",
			"6649 0 27103",
			"6374 0 2361",
			"7331 0 28503",
			"10077 0 1988",
			"10553 0 2313",
			"12319 0 9530",
			"11991 0 9116",
			"12823 0 10078",
			"13900 0 13258",	
			"2572 0 5105",
			"2741 0 5416",
			"2714 0 9996",
			"1723 0 13983",
			"3395 0 13013",
			"7085 0 7720",
			"5952 0 10367",
			"5363 0 8594",
			"7500 0 7500",
		};
		
		int max = 10;
		int time = 600;
		int despawnTime = 60000;
		int lootCount = 5;
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
		JsonFileLoader<SupplyDropPlusConfig>.JsonSaveFile(SETTINGS_FILE, this);
	}

	void load(){
		if (FileExist(SETTINGS_FILE)) {
			JsonFileLoader<SupplyDropPlusConfig>.JsonLoadFile(SETTINGS_FILE, this);
		}
		else
		{
			Print("No Airdrop Config found, creating Airdrop json.");
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