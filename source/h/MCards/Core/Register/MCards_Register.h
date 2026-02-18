 #ifndef DEF_MCards_Register_Header
#define DEF_MCards_Register_Header

#include <stddef.h>

#include <MCards/MCards_Factory.h>

typedef struct
{
	size_t cardCount;
	size_t unitCount;
	size_t leaderCount;
	size_t leaderCardCount;
	
	size_t maxCards;
	size_t maxUnits;
	size_t maxLeaders;
	size_t maxLeaderCards;
	
	MCards_CardBase ** cardData;
	MCards_UnitBase ** unitData;
	MCards_LeaderBase ** leaderData;
	MCards_LeaderCardBase ** leaderCardData;
	
	const char ** cardIDs;
	const char ** unitIDs;
	const char ** leaderIDs;
	const char ** leaderCardIDs;
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
 * @param   [in] leaderBase A estrutura base de carta solicitada para o registro.
 * @param   [in] iD O identificador da carta.
 */
void MCards_RegisterCard(MCards_CardBase * cardBase, const char * iD);

/**
 * @brief   Registro de uma unidade para o sistema.
 * @details Deve ser chamada <b>após</b> o registro principal de cartas, unidades e líderes estar finalmente inicializado.
 * @param   [in] leaderBase A estrutura base da unidade solicitada para o registro.
 * @param   [in] iD O identificador da unidade.
 */
void MCards_RegisterUnit(MCards_UnitBase * unitBase, const char * iD);

/**
 * @brief   Registro de líder para o sistema.
 * @details Deve ser chamada <b>após</b> o registro principal de cartas, unidades e líderes estar finalmente inicializado.
 * @param   [in] leaderBase A base de líder solicitado para o registro.
 * @param   [in] iD O identificador do líder.
 */
void MCards_RegisterLeader(MCards_LeaderBase * leaderBase, const char * iD);

/**
 * @brief   Registro de carta de líder para o sistema.
 * @details Deve ser chamada <b>após</b> o registro principal de cartas, unidades e líderes estar finalmente inicializado.
 * @param   [in] leaderCardBase A base de carta de líder solicitada para o registro.
 * @param   [in] iD O identificador da carta de líder.
 */
void MCards_RegisterLeaderCard(MCards_LeaderCardBase * leaderCardBase, const char * iD);

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
 * @brief   Inicialização todos as cartas de líderes para o registro principal.
 * @details Deve ser chamada após a inicialização do registro.
 */
void MCards_StartUpLeaderCards();

/**
 * @brief   Criação e alocação de um novo dado de conjuração de carta memória.
 * @details Deve ser chamada antes da chamada de inicializar as cartas ao registro principal.
 * @param   [in] iD O identificador referente à unidade conjurável.
 * @param   [in] count A quantidade de unidades conjuradas.
 */
MCards_CardSpawn * MCards_CreateCardSpawn(const char * iD, unsigned int count);

/**
 * @brief   Criação e alocação uma nova carta na memória.
 * @details Deve ser chamada antes da chamada de inicializar as unidades ao registro principal.
 * @param   [in] lk A chave de localização da carta.
 * @param   [in] dc O custo de implantação da carta.
 * @param   [in] spawns Os dados de conjuração da carta.
 * @param   [in] spawnCount A quantidade de dados de conjuração (definidos no parâmetro anterior) da carta.
 * @return  Uma estrutura base de carta genérica alocada na memória.
 */
MCards_CardBase * MCards_CreateCard(const char * lk, int dc, MCards_CardSpawn * spawns[], size_t spawnCount);

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
 * @details Deve ser chamada antes da chamada de inicializar os líderes ao registro principal.
 * @param   [in] hp Os pontos de saúde do líder.
 * @param   [in] dm Os pontos de dano-direto do líder.
 * @param   [in] ad O intervalo de ataque do líder em segundos.
 * @param   [in] ar O alcance de ataque do líder em ladrilhos.
 * @return  Uma estrutura base de líder genérico alocada na memória.
 */
MCards_LeaderBase * MCards_CreateLeader(int hp, int dm, float ad, float ar);

/**
 * @brief   Criação e alocação de uma nova carta de líder na memória.
 * @details Deve ser chamada antes da chamada de inicializar os líderes ao registro principal.
 * @param   [in] lk A chave de localização da carta de líder.
 * @param   [in] dn O nome de exibição da carta de líder.
 * @param   [in] dd A descrição da carta de líder.
 * @param   [in] ri O identificador do líder dentro do registro.
 * @return  Uma estruturs base de carta de líder genérica alocada na memória.
 */
MCards_LeaderCardBase * MCards_CreateLeaderCard(const char * lk, const char * dn, const char * dd, const char * ri);

/**
 * @brief   Consulta e verificação da existência de uma carta no registro.
 * @details Deve ser chamada após a inicialização das cartas no registro.
 * @param   [in] iD O identificador da carta a ser pesquisada.
 */
bool MCards_ContainsCard(const char * iD);

/**
 * @brief   Consulta e verificação da existência de um líder no registro.
 * @details Deve ser chamada após a inicialização dos líderes no registro.
 * @param   [in] iD O identificador do líder a ser pesquisado.
 */
bool MCards_ContainsUnit(const char * iD);

/**
 * @brief   Consulta e verificação da existência de um líder no registro.
 * @details Deve ser chamada após a inicialização dos líderes no registro.
 * @param   [in] iD O identificador do líder a ser pesquisado.
 */
bool MCards_ContainsLeader(const char * iD);

#endif
