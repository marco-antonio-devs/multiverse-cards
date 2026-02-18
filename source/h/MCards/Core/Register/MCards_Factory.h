#ifndef DEF_MCards_Factory_Header
#define DEF_MCards_Factory_Header

#include <stddef.h>

typedef struct
{
	const char * iD;
	unsigned int count;
}
MCards_CardSpawn;

typedef struct
{
	const char * localizationKey;
	const char * displayName;
	const char * displayDescription;
	
	int deployCost;
	
	size_t spawnCount;
	MCards_CardSpawn * spawns[];
}
MCards_CardBase;

typedef struct
{
	int hitpoints;
	int directDamage;
	
	float attackDelay;
	float movementSpeed;
	float attackRange;
}
MCards_UnitBase;

typedef struct
{
	const char * localizationKey;
	const char * displayName;
	const char * displayDescription;
	const char * referenceID;
}
MCards_LeaderCardBase;

typedef struct
{
	int hitpoints;
	int directDamage;
	
	float attackDelay;
	float attackRange;
}
MCards_LeaderBase;

#endif
