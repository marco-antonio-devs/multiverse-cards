#include <stdlib.h>
#include <stdio.h>

#include <MCards/Core/Register/MCards_Register.h>
#include <MCards/Core/Register/MCards_Factory.h>

int main()
{
	MCards_InitializeRegistry();
	MCards_StartUpCards();
	MCards_StartUpUnits();
	MCards_StartUpLeaders();
	MCards_StartUpLeaderCards();
	
	MCards_CardBase ** cardData = MCards_GetAllCardDatas();
	
	for(size_t index = 0; index < registry->cardCount; index++)
	{
		printf("Foi localizada uma carta no índice %zu (chave do nome de exibição: %s).\n", index, cardData[index]->displayName);
		printf("- Custo de implantação da carta: %d;\n", cardData[index]->deployCost);
		printf("- Total de conjurações da carta: %ld;\n", cardData[index]->spawnCount);
		printf("- Dados de conjuração da carta: ");
		
		MCards_CardSpawn ** spawns = cardData[index]->spawns;
		
		for(size_t spawnIndex = 0; spawnIndex < cardData[index]->spawnCount; spawnIndex++)
		{
			printf("{ iD = %s, count = %u };", spawns[spawnIndex]->iD, spawns[spawnIndex]->count);
		}
		
		printf("\n\n");
	}
	
	free(cardData);
	
	MCards_UnitBase ** unitData = MCards_GetAllUnitDatas();
	
	for(size_t index = 0; index < registry->unitCount; index++)
	{
		printf("Foi localizada uma unidade no índice %zu (identificador único: %s).\n", index, registry->unitIDs[index]);
		printf("- Pontos de vida: %d;\n", unitData[index]->hitpoints);
		printf("- Pontos de dano direto: %d;\n", unitData[index]->directDamage);
		printf("- Intervalo de ataque em segundos: %.2f;\n", unitData[index]->attackDelay);
		printf("- Velocidade em ladrilhos por segundo: %.2f;\n", unitData[index]->movementSpeed);
		printf("- Alcance de ataque em ladrilhos: %.2f;\n", unitData[index]->attackRange);
		printf("\n");
	}
	
	free(unitData);
	
	MCards_CleanUpRegistry();
	
	return 0;
}
