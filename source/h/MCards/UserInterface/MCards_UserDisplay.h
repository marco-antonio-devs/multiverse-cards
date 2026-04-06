#ifndef DEF_MCards_UserDisplay_Header
#define DEF_MCards_UserDisplay_Header

#include <stddef.h>

#include <MCards/Core/Register/MCards_Factory.h>

#define DEF_MCards_CardHandSize 4
#define DEF_MCards_RequiredCardCount 8

/**
 * @brief   Estrutura básica de baralho do usuário.
 * @details Contém a lista total de cartas e o líder anexado.
 */
typedef struct
{
	size_t cardCount;      /**< Quantidade de cartas do baralho.*/
	char * attachedLeader; /**< O líder anexado ao baralho do jogador.*/
	char ** allCards;      /**< Todas as cartas do baralho. Requer exatamente oito (8) cartas.*/
}
MCards_UserDeck;

/**
 * @brief   Criação e alocação do baralho do usuário.
 * @details Requer que o registro principal seja préviamente alocado.
 *          A mão do jogador é definida aleatóriamente na partida.
 * 
 * @param   [in] ac Todas as cartas do baralho em seus identificadores.
 * @param   [in] al Identificador único da carta de líder.
 * 
 * @return  Uma nova instância de baralho do jogador.
 */
MCards_UserDeck * MCards_CreateUserDeck(char ** ac, char * al);

/**
 * @brief   Limpeza e liberação do baralho do jogador.
 * @details Requer que o baralho não esteja nulo.
 * 
 * @param   [in] userDeck O baralho do usuário.
 */
void MCards_CleanUpDeck(MCards_UserDeck * userDeck);

#endif
