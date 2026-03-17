#include <stdlib.h>
#include <stdio.h>

#include <MCards/Core/Register/MCards_Register.h>
#include <MCards/Core/Register/MCards_Factory.h>
#include <MCards/Core/Renderer/MCards_Renderer.h>

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
	
	if(!SDL_CreateWindowAndRenderer("Multiverse Cards", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Houve uma falha ao tentar inicializar a biblioteca de áudio da SDL3. Erro específico: %s;", SDL_GetError());
		
		return SDL_APP_FAILURE;
	}
	
	SDL_SetRenderLogicalPresentation(renderer, 800, 600, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	
	MCards_InitializeRegistry();
	MCards_StartUpCards();
	MCards_StartUpUnits();
	MCards_StartUpLeaders();
	MCards_StartUpLeaderCards();
	
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
	
	SDL_FRect rectangle = {255, 255, 128, 192};
	
	MCards_AddRectangle(rectangle, 255, 0, 0, 255);
	
	SDL_RenderPresent(renderer);
	
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void * appstate, SDL_AppResult result)
{
	MCards_CleanUpRegistry();
}
