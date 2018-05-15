/*
 *  DataTypes.h
 *  SpriteEngine
 *
 *  Created by Damodar on 11/08/10.
 *  Copyright 2010 Sourcebits. All rights reserved.
 *
 */

#ifndef _DATA_TYPES_H
#define _DATA_TYPES_H

#import "Tuple2f.h"
#import "Point2f.h"
#include <string>
#import "Vector2f.h"
#import <vector>
#import "EnemyData.h"

using namespace std;


#define ERROR 1E-15

typedef struct TransformKey
{
	float rotationKey;
	Point2f posKey;
	Point2f scaleKey;
	Point2f shearKey;
	Point2f pivotkey;
	float    transparencyKey;
	bool equals( TransformKey& otherTransformKey )
	{
		return ( fabs( rotationKey - otherTransformKey.rotationKey ) < ERROR   && 
				   posKey.equals( otherTransformKey.posKey )               &&
				   scaleKey.equals( otherTransformKey.scaleKey )           &&
				   shearKey.equals( otherTransformKey.shearKey ) );
				 
	}

} TransformKey;

typedef struct 
{
	// Parameters used in UI
	string weaponName;
	
	BOOL isLocked;
	BOOL isPurchased;
	
	int ammoUsed;
	int totalAmmoCount;
	
	int damage;
	int rateOfFire;
	
	// Internally used parameters
	int weaponCost;
	int ammoCostPerPurchase;
	int ammoCountPerPurchase;
	
} WeaponDetails;



typedef struct FrameKey
{
	string frameName;
	unsigned short frameNumber;
	unsigned short zOrder;
	float transparencyKey;
	TransformKey   transformKey;	
	
	FrameKey( )
	{
		frameNumber = 0;
		zOrder      = 0;
		transparencyKey = 1.0f;
	}	
	
	bool equals( FrameKey& otherFrameKey )
	{
		return ( transformKey.equals ( otherFrameKey.transformKey ) && frameNumber == otherFrameKey.frameNumber );
	}
} FrameKey;

typedef struct PhysicalProperties
{
	float elasticity;
	float density;
	float friction;
} PhysicalProperties;

typedef struct MovieClipProperties
{
	std::string movieClipName;
	float offsetX;
	float offsetY;
	
	MovieClipProperties()
	{
		movieClipName = "";
		offsetX = 0.0f;
		offsetY = 0.0f;
	}
	
}MovieClipProperties;

typedef struct ObjectProperties
{
	int		typeID;
	float	damage;
	
} ObjectProperties;

typedef struct LevelObjectData
{
	std::string spriteName;
	
	Point2f positionKey;
	Point2f scaleKey;
	Point2f pivotKey;
	
	float alpha;
	float width;
	float height;
	
	float scaleFactor;
	float rotationKey;
	
	bool isDynamic;
	
	unsigned short  zOrder;
	
	PhysicalProperties physicalProperties;
	
	MovieClipProperties movieClipProperties;
	
	ObjectProperties objectProperties;
	
} LevelObjectData;


class PlatformData
{
public:
	LevelObjectData levelObjectData; 
	NSArray* vecCollisionSegments;
	bool isDynamic; // Mobile platforms cannot be dynamic !
    bool isBooster;
	bool isMobile;
	bool isConveyor;
	
	// Booster Platforms
	Vector2f boostVector;
	float    boostMagnitude;
	
	// Mobile Platforms
	vector<Point2f> wayPoints;
	float movingPlatformSpeed;
	
	// Conveyor Platforms
	Vector2f conveyorVelocity;
	
public:
	PlatformData()
	{
		isDynamic  = false;
 		isBooster  = false;
		isMobile   = false;
		isConveyor = false;
		
		// Booster Platforms
		boostMagnitude = 0.0f;
		
		// Mobile Platforms
		//float movingPlatformSpeed = 0.0f;
	}
};


class SpawnBaseData  {
	
public:	
	
	LevelObjectData levelObjectData;
	CGPoint rangeStartPoint;
	CGPoint rangeEndPoint;	
	int maxSpwan;
	float frequency;
	int enemiesPerSpawn;
	int liveEnemies;
	bool bEnable;
	float radius;
	int m_SpawnBaseType;
	
	vector<EnemyData*> vecEnemyData;
	
	
	//destructor
	~SpawnBaseData()
	{
		vecEnemyData.clear();
	}
	
};

class ViewControllerData {
public:
	Point2f position;
	float zoomScale;
};



struct stringCompare
{
	bool operator()(NSString* s1, NSString* s2) const
	{
		bool res = [s1 isEqual:s2];
		return res;
	}
};


//Weapon info data structure.
struct WeaponInfo
{
	
	//weapon-ID
	int m_WeaponID;
	
	
	//class constructor
	WeaponInfo()
	{
		m_WeaponID = -1;
	}
	
	//class destructor
	~WeaponInfo()
	{
		
	}
	
};
	
//Health pack data structure
struct HealthPackInfo
{
	
	//health pack count
	int m_HealthPackCount;
	
	//class constructor
	HealthPackInfo()
	{
		m_HealthPackCount = 0;
	}

	//class destructor
	~HealthPackInfo()
	{
		
	}	
};

typedef enum 
{
	eLandMines = 1,
	eAirStrike,
	eDrones,
	ePiranha,
	eUndergroundSpawn,
	eExplodableBarrels,
	eFallingRocks,
	eGasCan,
	
} SpecialElements;

typedef struct
{
	SpecialElements elementType;
	Tuple2f position;
	
} SpecialElementData;


//player respawn point.
struct RespawnPoint
{
	float m_X;
	float m_Y;
	
	//constructor
	RespawnPoint()
	{
		m_X = 300.0f;
		m_Y = 800.0f;
	}
	
	//Destructor
	~RespawnPoint()
	{
		
	}
		
};
//KK - 26-may
//Scoring Module Data Types

#define WEAPONCOUNT 10
#define ZOMBIECOUNT 21
#define MAXHITPOSITIONS 3
#define MULTIKILLTIMERANGE 2
#define MULTIKILL 1
#define KNIFEID 1
enum KillType {
	eSpecialKillsNone,
	eMultikill
};

enum HitInfo {
	headshot,
	chestshot,
	legshot
};

struct  LevelDetails
{
	int m_currentLevelNumber;
	int m_currentStageNumber;
};

#endif