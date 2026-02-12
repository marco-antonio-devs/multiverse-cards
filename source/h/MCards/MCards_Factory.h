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
	char * displayName;
	
	int deployCost;
	
	MCards_CardSpawn * spawns[];
	int spawnCount;
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
	int hitpoints;
	int directDamage;
	
	float attackDelay;
	float attackRange;
}
MCards_LeaderBase;

#endif
