#ifndef DEF_MCards_Sprite2D_Header
#define DEF_MCards_Sprite2D_Header

#include <MCards/Core/Math/MCards_Mathematics.h>

typedef struct
{
	MCards_Vector2D * position2D;
}
MCards_Sprite2D;

/**
 * @brief   Criação e alocação de um novo objeto gráfico na memória.
 * @details Requer que o renderizador seja inicializado com sucesso.
 *
 * @param   [in] iD O identificador do objeto gráfico.
 * @param   [in] position2D A posição bidimensional do objeto.
 * 
 * @return  Uma instância de objeto gráfico.
 */
MCards_Sprite2D * MCards_CreateSprite2D(const char * iD, MCards_Vector2D * position2D);

#endif
