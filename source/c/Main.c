#include <stdlib.h>
#include <stdio.h>

#include <MCards/Core/Register/MCards_Register.h>
#include <MCards/Core/Register/MCards_Factory.h>
#include <MCards/Core/Renderer/MCards_Renderer.h>
#include <MCards/UserInterface/MCards_Localization.h>

#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

SDL_AppResult SDL_AppInit(void ** appstate, int argc, char * argv[])
{
	if(!SDL_SetAppMetadata("Multiverse Cards", "1.0.0", "org.madevs.mcards"))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Houve uma falha ao tentar inicializar os metadados do aplicativo. Erro específico: %s;", SDL_GetError());
		
		return SDL_APP_FAILURE;
	}
	
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Houve uma falha ao tentar inicializar a biblioteca de gráficos da SDL3. Erro específico: %s;", SDL_GetError());
		
		return SDL_APP_FAILURE;
	}
	
	if(!SDL_Init(SDL_INIT_EVENTS))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Houve uma falha ao tentar inicializar a biblioteca de eventos da SDL3. Erro específico: %s;", SDL_GetError());
		
		return SDL_APP_FAILURE;
	}
	
	if(!SDL_Init(SDL_INIT_AUDIO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Houve uma falha ao tentar inicializar a biblioteca de áudio da SDL3. Erro específico: %s;", SDL_GetError());
		
		return SDL_APP_FAILURE;
	}
	
	if(!SDL_CreateWindowAndRenderer("Multiverse Cards", 720, 1280, SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Houve uma falha ao tentar inicializar a biblioteca de áudio da SDL3. Erro específico: %s;", SDL_GetError());
		
		return SDL_APP_FAILURE;
	}
	
	SDL_SetRenderLogicalPresentation(renderer, 720, 1280, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	
	MCards_InitializeRegistry();
	MCards_InitializeLocalization();
	MCards_StartUpCards();
	MCards_StartUpUnits();
	MCards_StartUpLeaders();
	MCards_StartUpLeaderCards();
	
	MCards_CardBase ** cardData = MCards_GetAllCardDatas();
	
	for(size_t index = 0; index < registry->cardCount; index++)
	{
		printf("Foi localizada uma carta no índice %zu (identificador único: %s).\n", index, registry->cardIDs[index]);
		printf("- Custo de implantação da carta: %d;\n", cardData[index]->deployCost);
		printf("- Total de conjurações da carta: %ld;\n", cardData[index]->spawnCount);
		printf("- Raridade de obtenção: %s;\n", MCards_TranslateRarityType(cardData[index]->rarity));
		printf("- Dados de conjuração da carta:\n");
		
		MCards_CardSpawn ** spawns = cardData[index]->spawns;
		
		for(size_t spawnIndex = 0; spawnIndex < cardData[index]->spawnCount; spawnIndex++)
		{
			printf("   { iD = %s, count = %u };\n", spawns[spawnIndex]->iD, spawns[spawnIndex]->count);
		}
		
		printf("\n");
	}
	
	free(cardData);
	
	MCards_UnitBase ** unitData = MCards_GetAllUnitDatas();
	
	for(size_t index = 0; index < registry->unitCount; index++)
	{
		printf("Foi localizada uma unidade no índice %zu (identificador único: %s).\n", index, registry->unitIDs[index]);
		printf("- Pontos de vida: %d;\n", unitData[index]->hitpoints);
		printf("- Pontos de dano direto: %d;\n", unitData[index]->directDamage);
		printf("- Intervalo de ataque em segundos: %.2f segundos;\n", unitData[index]->attackDelay);
		printf("- Velocidade em ladrilhos por segundo: %.2f;\n", unitData[index]->movementSpeed);
		printf("- Alcance de ataque em ladrilhos: %.2f;\n", unitData[index]->attackRange);
		printf("\n");
	}
	
	free(unitData);
	
	MCards_LeaderBase ** leaderData = MCards_GetAllLeaderDatas();
	
	for(size_t index = 0; index < registry->leaderCount; index++)
	{
		printf("Foi localizada um líder no índice %zu (identificador único: %s).\n", index, registry->leaderIDs[index]);
		printf("- Pontos de vida: %d;\n", leaderData[index]->hitpoints);
		printf("- Pontos de dano direto: %d;\n", leaderData[index]->directDamage);
		printf("- Intervalo de ataque em segundos: %.2f segundos;\n", leaderData[index]->attackDelay);
		printf("- Alcance de ataque em ladrilhos: %.2f;\n", leaderData[index]->attackRange);
		printf("\n");
	}
	
	free(leaderData);
	
	MCards_LeaderCardBase ** leaderCardData = MCards_GetAllLeaderCardDatas();
	
	for(size_t index = 0; index < registry->leaderCardCount; index++)
	{
		printf("Foi localizada uma carta de líder no índice %zu (chave do nome de exibição: %s).\n", index, leaderCardData[index]->displayName);
		printf("- Raridade de obtenção: %s;\n", MCards_TranslateRarityType(leaderCardData[index]->rarity));
		printf("- Identificador do líder referenciado: %s;", leaderCardData[index]->referenceID);
		
		printf("\n\n");
	}
	
	free(leaderCardData);
	
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void * appstate, SDL_Event * event)
{
	if(event->type == SDL_EVENT_QUIT)
	{
		return SDL_APP_SUCCESS;
	}
	
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void * appstate)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	
	for(size_t index = 0; index < 4; index++)
	{
		SDL_FRect rectangle = {0, 1024, 132, 192};
		
		rectangle.x = 38 + (index * 168);
		
		MCards_AddRectangle(rectangle, 255, 0, 0, 255);
	}
	
	SDL_RenderPresent(renderer);
	
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void * appstate, SDL_AppResult result)
{
	MCards_CleanUpRegistry();
	MCards_CleanUpLocalization();
}
