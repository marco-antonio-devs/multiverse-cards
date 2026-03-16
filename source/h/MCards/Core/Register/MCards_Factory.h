#ifndef DEF_MCards_Factory_Header
#define DEF_MCards_Factory_Header

#include <stddef.h>

/**
 * @brief   Dados de conjuração da carta.
 * @details Sua alocação consiste em um identificador existente e uma quantidade a ser conjurada.
 */
typedef struct
{
	const char * iD;
	unsigned int count;
}
MCards_CardSpawn;

/**
 * @brief   Dados de alocação da carta na memória.
 * @details Contém o nome de exibição e descrição, que são chaves para traduzir-las.
 *          Veja o seguinte cabeçalho para um melhor entendimento: `h/MCards/UserInterface/MCards_Localization.h`.
 * @note    Não confunda esta estrutura com a estrutura `MCards_LeaderCardBase`.
 */
typedef struct
{
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
