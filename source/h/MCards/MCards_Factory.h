#ifndef DEF_MCards_Factory_Header
#define DEF_MCards_Factory_Header

#include <stddef.h>

typedef struct
{
	char * displayName;
	
	int deployCost;
	
	const char ** spawns;
	size_t spawnCount;
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
