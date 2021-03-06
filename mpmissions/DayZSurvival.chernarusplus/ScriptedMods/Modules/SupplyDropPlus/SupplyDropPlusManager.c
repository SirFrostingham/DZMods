//////////////////////////////////////////////
//Airdrop System 			   			 	//
//Author: GravityWolf 					 	//
//Github: github.com/gravitywolfnotamused	//
//////////////////////////////////////////////

#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\SupplyDropPlus\\SupplyDropPlusPlane.c"
#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\SupplyDropPlus\\SupplyDropPlusConfig.c"

class SupplyDropPlusManager
{
	private float timeSnapshot;
	private float roundedSnapShot;
	private float lifeTimeClock;
	
	private bool hasAirdrop = false;
	private bool debuggingMode = false;
	
	ref SupplyPlanes planes;
	ref Supplies supplies;
	ref SupplyDropPlusConfig config;

	void SupplyDropPlusManager()
	{	
		planes = new SupplyPlanes;
		supplies = new Supplies;

		config = new SupplyDropPlusConfig();
		config.load();
	}
	
	void ~SupplyDropPlusManager(){

	}
	
	void Init(){
		Print("SupplyDrop::Init Plugin Initialized.");
	}
	
	void onUpdateMaxSupplyDrops(float timeslice){		
		timeSnapshot += timeslice;
		
		UpdateDebugTimer();

		if(supplies.Count() != 0){		
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
					//GetGame().ChatPlayer(1, "A supply plane was spotted at " + location.ToString());
					GetGame().ChatPlayer("A supply plane was spotted at " + location.ToString());
				}
				Print("A supply plane was spotted at " + location.ToString());
				planes.Insert(new SupplyDropPlusPlane(location, config.chooseDropLocation()));
			}
		}

		if(hasAirdrop){
			foreach(SupplyDropPlusPlane plane : planes){
				if(Math.Round(plane.getPosition()[0]) >= Math.Round(plane.getDropPosition()[0]) - 25 && Math.Round(plane.getPosition()[0]) <= Math.Round(plane.getDropPosition()[0]) + 25){
					if(Math.Round(plane.getPosition()[2]) >= Math.Round(plane.getDropPosition()[2]) - 25 && Math.Round(plane.getPosition()[2]) <= Math.Round(plane.getDropPosition()[2]) + 25){
						if(!plane.hasDroppedSupplies()){
							
							if(debuggingMode){
								//GetGame().ChatPlayer(1, "Supplies were dropped at " + plane.getPosition());
								GetGame().ChatPlayer("Supplies were dropped at " + plane.getPosition());
							}
							Print("Supplies were dropped at " + plane.getPosition());
							supplies.Insert(new SupplyCratePlus(Vector(plane.getPosition()[0],plane.getPosition()[1] - 15,plane.getPosition()[2]), config.chooseLoot()));
							plane.setHasDroppedSupplies();
							
							// delete helo on drop
							GetGame().ObjectDelete(plane.getObject());
							planes.RemoveItem(plane);	
						}
					}
				}
				
				if((plane.getPosition()[0] < 1 || plane.getPosition()[2] < 1 || plane.getPosition()[0] > 15400 || plane.getPosition()[2] > 15400)){
					GetGame().ObjectDelete(plane.getObject());
					planes.RemoveItem(plane);			
					Print("Plane hit out of bounds, deleting.");
				}
				plane.move();
			}
		}

		if(supplies.Count() != 0){
			foreach(SupplyCratePlus supplyDrop : supplies){
				supplyDrop.setCurrentLifetime(timeslice);
				
				//Print("config.getDespawnTime() = " + config.getDespawnTime().ToString());
				//Print("Supply drop: " + supplyDrop.getPosition().ToString() + ": DespawnTime: " + supplyDrop.getLifeTime().ToString());
				
				if(config.getDespawnTime() < supplyDrop.getLifeTime()){
					GetGame().ObjectDelete(supplyDrop.getObject());
					supplies.RemoveItem(supplyDrop);
					Print("Supply Create has lived it's life, it has been despawned.");
					continue;
				}

				if (!supplyDrop.hasGravity()) {
					supplyDrop.applyGravity();
				} 

				if(supplyDrop.hasGravity() && supplyDrop.getEndY() <= supplyDrop.getObject().GetPosition()[1] + 5 && supplyDrop.getObject().GetPosition()[1] != supplyDrop.getEndY()){
					supplyDrop.setPosition(supplyDrop.getEndYVector());
				}
			}
		}
	}
	
	void onUpdate(float timeslice){		
		timeSnapshot += timeslice;
		
		UpdateDebugTimer();

		if(supplies.Count() != 0){		
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
					//GetGame().ChatPlayer(1, "A supply plane was spotted at " + location.ToString());
					GetGame().ChatPlayer("A supply plane was spotted at " + location.ToString());
				}
				Print("A supply plane was spotted at " + location.ToString());
				planes.Insert(new SupplyDropPlusPlane(location, config.chooseDropLocation()));
			}
		}

		if(hasAirdrop){
			foreach(SupplyDropPlusPlane plane : planes){
				if(Math.Round(plane.getPosition()[0]) >= Math.Round(plane.getDropPosition()[0]) - 25 && Math.Round(plane.getPosition()[0]) <= Math.Round(plane.getDropPosition()[0]) + 25){
					if(Math.Round(plane.getPosition()[2]) >= Math.Round(plane.getDropPosition()[2]) - 25 && Math.Round(plane.getPosition()[2]) <= Math.Round(plane.getDropPosition()[2]) + 25){
						if(!plane.hasDroppedSupplies()){
							
							if(debuggingMode){
								//GetGame().ChatPlayer(1, "Supplies were dropped at " + plane.getPosition());
								GetGame().ChatPlayer("Supplies were dropped at " + plane.getPosition());
							}
							Print("Supplies were dropped at " + plane.getPosition());
							supplies.Insert(new SupplyCratePlus(Vector(plane.getPosition()[0],plane.getPosition()[1] - 15,plane.getPosition()[2]), config.chooseLoot()));
							plane.setHasDroppedSupplies();
						}
					}
				}
				
				if((plane.getPosition()[0] < 1 || plane.getPosition()[2] < 1 || plane.getPosition()[0] > 15400 || plane.getPosition()[2] > 15400)){
					GetGame().ObjectDelete(plane.getObject());
					planes.RemoveItem(plane);			
					Print("Plane hit out of bounds, deleting.");
				}
				plane.move();
			}
		}

		if(supplies.Count() != 0){
			foreach(SupplyCratePlus supplyDrop : supplies){
				supplyDrop.setCurrentLifetime(timeslice);
				
				if(config.getDespawnTime() < supplyDrop.getLifeTime()){
					GetGame().ObjectDelete(supplyDrop.getObject());
					supplies.RemoveItem(supplyDrop);
					Print("Supply Create has lived it's life, it has been despawned.");
					continue;
				}

				if (!supplyDrop.hasGravity()) {
					supplyDrop.applyGravity();
				} 

				if(supplyDrop.hasGravity() && supplyDrop.getEndY() <= supplyDrop.getObject().GetPosition()[1] + 5 && supplyDrop.getObject().GetPosition()[1] != supplyDrop.getEndY()){
					supplyDrop.setPosition(supplyDrop.getEndYVector());
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
