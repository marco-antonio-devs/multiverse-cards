#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <MCards/UserInterface/MCards_UserDisplay.h>
#include <MCards/Core/Register/MCards_Register.h>

MCards_UserDeck * MCards_CreateUserDeck(char ** ac, char * al)
{
	MCards_UserDeck * userDeck = malloc(sizeof(MCards_UserDeck));
	
	if(!userDeck)
	{
		perror("Houve uma falha ao tentar alocar o baralho do usuário.\n");
		
		return NULL;
	}
	
	if(registry == NULL)
	{
		perror("Por favor, incialize o registro principal.\n");
		free(userDeck);
		
		return NULL;
	}
	
	if(!ac)
	{
		perror("Não há identificadores de cartas citados para a criação do baralho. Por favor, defina-os.\n");
		free(userDeck);
		
		return NULL;
	}
	
	size_t cardCount = sizeof(ac);
	
	if(cardCount > DEF_MCards_RequiredCardCount)
	{
		fprintf(stderr, "O número de cartas solicitadas (%zu) ultrapassa o limite de oito (8) identificadores.\n", cardCount);
		free(userDeck);
		
		return NULL;
	}
	
	if(cardCount < DEF_MCards_RequiredCardCount)
	{
		fprintf(stderr, "O número de cartas solicitadas (%zu) está abaixo do limite de oito (8) identificadores.\n", cardCount);
		free(userDeck);
		
		return NULL;
	}
	
	if(!al)
	{
		perror("Não foi citado um líder a ser anexado para a criação do baralho. Por favor, defina-os.\n");
		free(userDeck);
		
		return NULL;
	}
	
	userDeck->cardCount = cardCount;
	
	for(size_t index = 0; index < cardCount; index++)
	{
		if(ac[index] == NULL)
		{
			continue;
		}
		
		printf("Verificando pela carta com o identificador \"%s\".\n", ac[index]);
		
		if(!MCards_ContainsCard(ac[index]))
		{
			fprintf(stderr, "A carta citada (%s) não foi encontrada. Por favor, tente novamente.\n", ac[index]);
			free(userDeck);
			
			return NULL;
		}
		
		printf("O identificador \"%s\" foi verificado com sucesso.\n", ac[index]);
	}
	
	if(!MCards_ContainsLeaderCard(al))
	{
		perror("A carta de líder citada não foi encontrada no registro principal. Por favor, tente novamente.\n");
		free(userDeck);
		
		return NULL;
	}
	
	userDeck->attachedLeader = al;
	userDeck->allCards = ac;
	
	return userDeck;
}

void MCards_CleanUpDeck(MCards_UserDeck * userDeck)
{
	if(userDeck == NULL)
	{
		perror("O baralho solicitado para a limpeza está nulo. Por favor, defina-o.");
		
		return;
	}
	
	free(userDeck->allCards);
	free(userDeck);
}
