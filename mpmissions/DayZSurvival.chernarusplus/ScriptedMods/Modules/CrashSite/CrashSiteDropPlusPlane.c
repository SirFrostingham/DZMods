//////////////////////////////////////////////
//Airdrop System 			   			 	//
//Author: GravityWolf 					 	//
//Github: github.com/gravitywolfnotamused	//
//////////////////////////////////////////////

#include "$CurrentDir:\\mpmissions\\DayZSurvival.chernarusplus\\ScriptedMods\\Modules\\CrashSite\\CrashSiteCratePlus.c"

typedef array<ref CrashSiteDropPlusPlane> CrashSitePlanes;

class CrashSiteDropPlusPlane{
	private vector position;
	private vector dropPosition;

	private EntityAI planeAI;
	private Object plane;

	private bool hasDroppedCrashSites;
	
	const float airPlaneSpeed = 0.10;
	const float planeHeight = 700;

	void CrashSiteDropPlusPlane(vector startingPosition, vector dropPosition){
		this.position = startingPosition;
		this.dropPosition = dropPosition;
		this.plane = GetGame().CreateObject("Wreck_UH1Y", this.position, false, true);
		
		Class.CastTo(planeAI, plane);
		plane.SetDirection(getDirection());
		hasDroppedCrashSites = false;

		Print("Helo was spawn on the map at: " + position.ToString() + " headed for " + dropPosition.ToString());
	}

	void ~CrashSiteDropPlusPlane(){
		GetGame().ObjectDelete(plane);
	}
	
	void move(){
		float f = plane.GetOrientation()[0] * 0.017453292;
        float motionX  = (double)(Math.Sin(f) * airPlaneSpeed);
        float motionZ = (double)(Math.Cos(f) * airPlaneSpeed); 

		position[0] = position[0] - motionX;
		position[1] = planeHeight;
		position[2] = position[2] - motionZ;

		plane.SetPosition(position);
	}

	bool hasDroppedCrashSites(){
		return hasDroppedCrashSites;
	}

	void setHasDroppedCrashSites(){
		hasDroppedCrashSites = true;
	}
	
	vector getDirection(){
		return position - dropPosition;
	}

	Object getObject(){
		return plane;
	}

	vector getDropPosition(){
		return dropPosition;
	}

	vector getPosition(){
		return position;
	}

}
