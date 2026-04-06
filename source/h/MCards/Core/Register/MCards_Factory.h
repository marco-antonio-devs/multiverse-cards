#ifndef DEF_MCards_Factory_Header
#define DEF_MCards_Factory_Header

#include <stddef.h>

#include <MCards/Core/Rarity/MCards_Rarity.h>
#include <MCards/Core/Basic/MCards_BasicObject.h>

/**
 * @brief   Dados de conjuração da carta.
 * @details Sua alocação consiste em um identificador existente e uma quantidade a ser conjurada.
 */
typedef struct
{
	char * iD;
	unsigned int count;
}
MCards_SpawnData;

/**
 * @brief   Dados de alocação da carta na memória.
 * @details Contém o nome de exibição e descrição, que são chaves para traduzir-las.
 *          Veja o seguinte cabeçalho para um melhor entendimento: `h/MCards/UserInterface/MCards_Localization.h`.
 * @note    Não confunda esta estrutura com a estrutura `MCards_LeaderCardBase`.
 */
typedef struct
{
	MCards_ObjectBase * objectBase; /**< Base de objeto para esta estrutura.*/
	
	char * displayName;             /**< Chave de tradução do nome de exibição da carta.*/
	char * displayDescription;      /**< Chave de tradução da descrição da carta.*/

	int deployCost;                 /**< Custo de implantação da carta, limitado entre uma (1) e dez (10) unidades de Energia.*/

	size_t spawnCount;              /**< Quantidade total de unidades conjuradas ao usar a carta.*/
	
	MCards_Rarity rarity;           /**< Raridade de obter uma cópia da carta.*/
	MCards_SpawnData * spawns[];    /**< Lista de dados de conjuração da carta.*/
}
MCards_CardBase;


typedef struct
{
	MCards_ObjectBase * objectBase; /**< Base de objeto para esta estrutura.*/
	
	int hitpoints;                  /**< Quantidade dos pontos de vida da unidade.*/
	int directDamage;               /**< Quantidade de dano direto da unidade (incluindo ataques a distância por projéteis).*/

	float attackDelay;              /**< Intervalo de ataque em segundos.*/
	float movementSpeed;            /**< Velocidade de movimentação em ladrilhos por segundo.*/
	float attackRange;              /**< Raio de alcance de ataque em ladrilhos.*/
}
MCards_UnitBase;

/**
 * @brief   Dados de alocação do estático na memória.
 * @details Contém dados básicos da base, como pontos de vida, dano direto e outros atributos.
 * 
 * @note    Não confunda esta estrutura com `MCards_LeaderBase`.
 */
typedef struct
{
	MCards_ObjectBase * objectBase; /**< Base de objeto para esta estrutura.*/
	
	int hitpoints;                  /**< Quantidade dos pontos de vida da unidade.*/
	int directDamage;               /**< Quantidade de dano direto do estático (incluindo ataques a distância por projéteis).*/

	float attackDelay;              /**< Intervalo de ataque em segundos.*/
	float attackRange;              /**< Raio de alcance de ataque em ladrilhos.*/
	float lifeTime;                 /**< Tempo de vida da construção em segundos.*/
}
MCards_StaticBase;

/**
 * @brief   Dados de alocação do estático na memória (conjurador).
 * @details Contém atributos herdados de `MCards_StaticBase`.
 */
typedef struct
{
	MCards_StaticBase * base;           /**< Base de atributos do estático.*/
	MCards_SpawnData ** spawnHordeData; /**< Dados de conjuração por hordas.*/
}
MCards_StaticSummonerBase;

/**
 * @brief   Dados de alocação da carta de líder na memória.
 * @details Contém o nome de exibição e descrição, que são chaves para traduzir-las.
 *          Veja o seguinte cabeçalho para um melhor entendimento: `h/MCards/UserInterface/MCards_Localization.h`.
 * @note    Não confunda esta estrutura com a estrutura `MCards_CardBase`.
 */
typedef struct
{
	MCards_ObjectBase * objectBase; /**< Base de objeto para esta estrutura.*/
	
	char * displayName;             /**< Chave de tradução do nome de exibição da carta de líder.*/
	char * displayDescription;      /**< Chave de tradução da descrição da carta de líder.*/
	char * referenceID;             /**< Identificador de líder referenciado pela carta de líder.*/
	
	MCards_Rarity rarity;           /**< Raridade de obter uma cópia da carta de líder.*/
}
MCards_LeaderCardBase;

typedef struct
{
	MCards_ObjectBase * objectBase; /**< Base de objeto para esta estrutura.*/
	
	int hitpoints;                  /**< Quantidade dos pontos de vida do líder.*/
	int directDamage;               /**< Quantidade de dano direto do líder (incluindo ataques a distância por projéteis).*/

	float attackDelay;              /**< Intervalo de ataque em segundos.*/
	float attackRange;              /**< Raio de alcance de ataque em ladrilhos.*/
}
MCards_LeaderBase;

#endif
