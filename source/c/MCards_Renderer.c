#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <MCards/Core/Renderer/MCards_Renderer.h>

#include <SDL3/SDL.h>

void MCards_AddRectangle(SDL_FRect rectangle, unsigned int redChannel, unsigned int greenChannel, unsigned int blueChannel, unsigned int alphaChannel)
{
	if(renderer == NULL)
	{
		perror("O renderizador requirido para desenhar um retângulo não foi inicializado. Por favor, defina-o.");
		
		return;
	}
	
	SDL_SetRenderDrawColor(renderer, redChannel, greenChannel, blueChannel, alphaChannel);
	SDL_RenderFillRect(renderer, &rectangle);
	SDL_RenderRect(renderer, &rectangle);
}
