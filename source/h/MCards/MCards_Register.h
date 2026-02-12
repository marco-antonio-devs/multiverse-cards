#ifndef DEF_MCards_Register_Header
#define DEF_MCards_Register_Header

#include <stddef.h>

#include <MCards/MCards_Factory.h>

typedef struct
{
	size_t cardCount;
	size_t unitCount;
	size_t leaderCount;
	
	size_t maxCards;
	size_t maxUnits;
	size_t maxLeaders;
	
	MCards_CardBase ** cardData;
	MCards_UnitBase ** unitData;
	MCards_LeaderBase ** leaderData;
	
	const char ** cardIDs;
	const char ** unitIDs;
	const char ** leaderIDs;
}
MCards_Registry;

extern MCards_Registry * registry;

/**
 * @brief   Inicialização do registro principal de cartas, unidades e líderes.
 * @details Deve ser chamado uma única vez no começo de chamadas para previnir problemas de consulta.
 */
void MCards_InitializeRegistry();

/**
 * @brief   Limpeza e desativação do registro principal de cartas, unidades e líderes.
 * @details Deve ser chamada uma única vez no final para liberação de memória R.A.M.
 */
void MCards_CleanUpRegistry();

/**
 * @brief   Registro de uma carta para o sistema.
 * @details Deve ser chamada <b>após</b> o registro principal de cartas, unidades e líderes estar finalmente inicializado.
 * @param [in] leaderBase A estrutura base de carta solicitada para o registro.
 * @param [in] iD O identificador da carta.
 */
void MCards_RegisterCard(MCards_CardBase * cardBase, const char * iD);

/**
 * @brief   Registro de uma unidade para o sistema.
 * @details Deve ser chamada <b>após</b> o registro principal de cartas, unidades e líderes estar finalmente inicializado.
 * @param [in] leaderBase A estrutura base da unidade solicitada para o registro.
 * @param [in] iD O identificador da unidade.
 */
void MCards_RegisterUnit(MCards_UnitBase * unitBase, const char * iD);

/**
 * @brief   Registro de líder para o sistema.
 * @details Deve ser chamada <b>após</b> o registro principal de cartas, unidades e líderes estar finalmente inicializado.
 * @param [in] leaderBase A base de líder solicitado para o registro.
 * @param [in] iD O identificador do líder.
 */
void MCards_RegisterLeader(MCards_LeaderBase * leaderBase, const char * iD);

/**
 * @brief   Inicialização todas as cartas para o registro principal.
 * @details Deve ser chamada após a inicialização do registro.
 */
void MCards_StartUpCards();

/**
 * @brief   Inicialização todas as unidades para o registro principal.
 * @details Deve ser chamada após a inicialização do registro.
 */
void MCards_StartUpUnits();

/**
 * @brief   Inicialização todos os líderes para o registro principal.
 * @details Deve ser chamada após a inicialização do registro.
 */
void MCards_StartUpLeaders();

/**
 * @brief   Criação e alocação uma nova carta na memória.
 * @details Deve ser chamada antes da chamada de inicializar as unidades ao registro principal.
 * @param   [in] dn O nome de exibição da carta.
 * @param   [in] dc O custo de implantação da carta.
 * @return  Uma estrutura base de carta genérica alocada na memória.
 */
MCards_CardBase * MCards_CreateCard(const char * dn, int dc);

/**
 * @brief   Criação e alocação uma nova unidade na memória.
 * @details Deve ser chamada antes da chamada de inicializar as unidades ao registro principal.
 * @param   [in] hp Os pontos de saúde da unidade.
 * @param   [in] dm Os pontos de dano-direto da unidade.
 * @param   [in] ad O intervalo de ataque da unidade em segundos.
 * @param   [in] ms A velocidade de movimentação da unidade em ladrilhos por segundo.
 * @param   [in] ar O alcance de ataque da unidade em ladrilhos.
 * @return  Uma estrutura base de unidade genérica alocada na memória.
 */
MCards_UnitBase * MCards_CreateUnit(int hp, int dm, float ad, float ms, float ar);

/**
 * @brief   Criação e alocação um novo líder na memória.
 * @details Deve ser chamada antes da chamada de inicializar as unidades ao registro principal.
 * @param   [in] hp Os pontos de saúde do líder.
 * @param   [in] dm Os pontos de dano-direto do líder.
 * @param   [in] ad O intervalo de ataque do líder em segundos.
 * @param   [in] ar O alcance de ataque do líder em ladrilhos.
 * @return  Uma estrutura base de líder genérico alocada na memória.
 */
MCards_LeaderBase * MCards_CreateLeader(int hp, int dm, float ad, float ar);

#endif
