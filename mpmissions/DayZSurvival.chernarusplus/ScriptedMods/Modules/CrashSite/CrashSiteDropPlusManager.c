//////////////////////////////////////////////
//Airdrop System 			   			 	//
//Author: GravityWolf 					 	//
//Github: github.com/gravitywolfnotamused	//
//////////////////////////////////////////////

#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\CrashSite\\CrashSiteDropPlusPlane.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\CrashSite\\CrashSiteDropPlusConfig.c"

class CrashSiteDropPlusManager
{
	private float timeSnapshot;
	private float roundedSnapShot;
	private float lifeTimeClock;
	
	private bool hasAirdrop = false;
	private bool debuggingMode = false;
	
	ref CrashSitePlanes planes;
	ref CrashSites crashSites;
	ref CrashSiteDropPlusConfig config;

	void CrashSiteDropPlusManager()
	{	
		planes = new CrashSitePlanes;
		crashSites = new CrashSites;

		config = new CrashSiteDropPlusConfig();
		config.load();
	}
	
	void ~CrashSiteDropPlusManager(){

	}
	
	void Init(){
		Print("CrashSiteDrop::Init Plugin Initialized.");
	}
	
	void onUpdateMaxCrashes(float timeslice){		
		timeSnapshot += timeslice;
		
		UpdateDebugTimer();

		if(crashSites.Count() != 0){		
			lifeTimeClock += timeslice;
		}

		if(planes.Count() == config.getMaxDrops()){
			hasAirdrop = false;
		}else{
			hasAirdrop = true;
		}
		
		if(timeSnapshot >= config.getDropTime()){
			timeSnapshot = 0;
			roundedSnapShot = 0;

			if(planes.Count() != config.getMaxDrops()){
				vector location = getStartingPosition();
				
				if(debuggingMode){
					//GetGame().ChatPlayer(1, "A helicopter was spotted at " + location.ToString());
					GetGame().ChatPlayer("A helicopter was spotted at " + location.ToString());
				}
				Print("A helicopter was spotted at " + location.ToString());
				planes.Insert(new CrashSiteDropPlusPlane(location, config.chooseDropLocation()));
			}
		}

		if(hasAirdrop){
			foreach(CrashSiteDropPlusPlane plane : planes){
				if(Math.Round(plane.getPosition()[0]) >= Math.Round(plane.getDropPosition()[0]) - 25 && Math.Round(plane.getPosition()[0]) <= Math.Round(plane.getDropPosition()[0]) + 25){
					if(Math.Round(plane.getPosition()[2]) >= Math.Round(plane.getDropPosition()[2]) - 25 && Math.Round(plane.getPosition()[2]) <= Math.Round(plane.getDropPosition()[2]) + 25){
						if(!plane.hasDroppedCrashSites()){
							
							if(debuggingMode){
								//GetGame().ChatPlayer(1, "Crash site seen near " + plane.getPosition());
								GetGame().ChatPlayer("Crash site seen near " + plane.getPosition());
							}
							Print("Crash site seen near " + plane.getPosition());
							crashSites.Insert(new CrashSiteCratePlus(Vector(plane.getPosition()[0],plane.getPosition()[1] - 15,plane.getPosition()[2]), config.chooseLoot()));
							plane.setHasDroppedCrashSites();
							
							// delete helo on drop
							GetGame().ObjectDelete(plane.getObject());
							planes.RemoveItem(plane);	
						}
					}
				}
				
				if((plane.getPosition()[0] < 1 || plane.getPosition()[2] < 1 || plane.getPosition()[0] > 15400 || plane.getPosition()[2] > 15400)){
					GetGame().ObjectDelete(plane.getObject());
					planes.RemoveItem(plane);			
					Print("Helo hit out of bounds, deleting.");
				}
				plane.move();
			}
		}

		if(crashSites.Count() != 0){
			foreach(CrashSiteCratePlus crashSiteDrop : crashSites){
				crashSiteDrop.setCurrentLifetime(timeslice);
				
				//Print("config.getDespawnTime() = " + config.getDespawnTime().ToString());
				//Print("Crash site: " + crashSiteDrop.getPosition().ToString() + ": DespawnTime: " + crashSiteDrop.getLifeTime().ToString());
				
				if(config.getDespawnTime() < crashSiteDrop.getLifeTime()){
					GetGame().ObjectDelete(crashSiteDrop.getObject());
					crashSites.RemoveItem(crashSiteDrop);
					Print("Crash site Create has lived it's life, it has been despawned.");
					continue;
				}

				if (!crashSiteDrop.hasGravity()) {
					crashSiteDrop.applyGravity();
				} 

				if(crashSiteDrop.hasGravity() && crashSiteDrop.getEndY() <= crashSiteDrop.getObject().GetPosition()[1] + 5 && crashSiteDrop.getObject().GetPosition()[1] != crashSiteDrop.getEndY()){
					crashSiteDrop.setPosition(crashSiteDrop.getEndYVector());
				}
			}
		}
	}
	
	void onUpdate(float timeslice){		
		timeSnapshot += timeslice;
		
		UpdateDebugTimer();

		if(crashSites.Count() != 0){		
			lifeTimeClock += timeslice;
		}

		if(planes.Count() == 0){
			hasAirdrop = false;
		}else{
			hasAirdrop = true;
		}
		
		if(timeSnapshot >= config.getDropTime()){
			timeSnapshot = 0;
			roundedSnapShot = 0;

			if(planes.Count() != config.getMaxDrops()){
				vector location = getStartingPosition();
				
				if(debuggingMode){
					//GetGame().ChatPlayer(1, "A helicopter was spotted at " + location.ToString());
					GetGame().ChatPlayer("A helicopter was spotted at " + location.ToString());
				}
				Print("A helicopter was spotted at " + location.ToString());
				planes.Insert(new CrashSiteDropPlusPlane(location, config.chooseDropLocation()));
			}
		}

		if(hasAirdrop){
			foreach(CrashSiteDropPlusPlane plane : planes){
				if(Math.Round(plane.getPosition()[0]) >= Math.Round(plane.getDropPosition()[0]) - 25 && Math.Round(plane.getPosition()[0]) <= Math.Round(plane.getDropPosition()[0]) + 25){
					if(Math.Round(plane.getPosition()[2]) >= Math.Round(plane.getDropPosition()[2]) - 25 && Math.Round(plane.getPosition()[2]) <= Math.Round(plane.getDropPosition()[2]) + 25){
						if(!plane.hasDroppedCrashSites()){
				
							if(debuggingMode){
								//GetGame().ChatPlayer(1, "Crash site seen near " + plane.getPosition());
								GetGame().ChatPlayer("Crash site seen near " + plane.getPosition());
							}
							Print("Crash site seen near " + plane.getPosition());
							crashSites.Insert(new CrashSiteCratePlus(Vector(plane.getPosition()[0],plane.getPosition()[1] - 15,plane.getPosition()[2]), config.chooseLoot()));
							plane.setHasDroppedCrashSites();
							
							// delete helo on drop
							GetGame().ObjectDelete(plane.getObject());
							planes.RemoveItem(plane);	
						}
					}
				}
				
				if((plane.getPosition()[0] < 1 || plane.getPosition()[2] < 1 || plane.getPosition()[0] > 15400 || plane.getPosition()[2] > 15400)){
					GetGame().ObjectDelete(plane.getObject());
					planes.RemoveItem(plane);			
					Print("Helo hit out of bounds, deleting.");
				}
				plane.move();
			}
		}

		if(crashSites.Count() != 0){
			foreach(CrashSiteCratePlus crashSiteDrop : crashSites){
				crashSiteDrop.setCurrentLifetime(timeslice);
				
				//Print("config.getDespawnTime() = " + config.getDespawnTime().ToString());
				//Print("Crash site: " + crashSiteDrop.getPosition().ToString() + ": DespawnTime: " + crashSiteDrop.getLifeTime().ToString());
				
				if(config.getDespawnTime() < crashSiteDrop.getLifeTime()){
					GetGame().ObjectDelete(crashSiteDrop.getObject());
					crashSites.RemoveItem(crashSiteDrop);
					Print("Crash site Create has lived it's life, it has been despawned.");
					continue;
				}

				if (!crashSiteDrop.hasGravity()) {
					crashSiteDrop.applyGravity();
				} 

				if(crashSiteDrop.hasGravity() && crashSiteDrop.getEndY() <= crashSiteDrop.getObject().GetPosition()[1] + 5 && crashSiteDrop.getObject().GetPosition()[1] != crashSiteDrop.getEndY()){
					crashSiteDrop.setPosition(crashSiteDrop.getEndYVector());
				}
			}
		}
	}

	void UpdateDebugTimer(){
		if(debuggingMode){
			if(Math.Round(timeSnapshot) > roundedSnapShot){
				roundedSnapShot = Math.Round(timeSnapshot);
				Print("Snapshot is: " + roundedSnapShot);
			}
		}
	}
	
	vector getStartingPosition(){
		vector starting = "0 0 1";
		starting[0] = Math.RandomFloat(0,15100);

		if(starting[0] >= 14400){
			starting[2] = Math.RandomFloat(0, 12200);
		}
		return starting;
	}
}
