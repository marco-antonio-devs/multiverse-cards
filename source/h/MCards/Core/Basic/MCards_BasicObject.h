#ifndef DEF_MCards_BasicObject_Header
#define DEF_MCards_BasicObject_Header

#include <stddef.h>

#include <MCards/Core/Math/MCards_Vector2D.h>

#include <SDL3/SDL_render.h>

/**
 * @brief   Estrutura básica de objeto da cena.
 * @details Contém atributos e métodos de eventos para a manipulação deste objeto.
 */
typedef struct
{
	long objectID;                        /**< Identificador único de objeto da cena.*/
	
	SDL_Texture * surfaceTexture;         /**< Textura para a superfície bidimensional do objeto.*/
	MCards_NormalizedVector2D * position; /**< Posição bidimensional no espaço do <b>Plano-Cartesiano</b> da tela.*/
	
	void (*onTickInitializeEvent)();      /**< Chamada de método customizado para quando inicializar.*/
	void (*onTickUpdateEvent)();          /**< Chamada de método customizado para quando atualizar.*/
	void (*onTickDestroyEvent)();         /**< Chamada de método customizado para quando destruir.*/
}
MCards_ObjectBase;

/**
 * @brief   Inicialização e alocação do objeto na memória.
 * @details O identificador único deste objeto será automaticamente definido com base no índice e tempo de criação.
 * 
 * @param   [in] 
 * 
 */

#endif
