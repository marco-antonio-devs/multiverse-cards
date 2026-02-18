#ifndef DEF_MCards_Mathematics_Header
#define DEF_MCards_Mathematics_Header

typedef struct
{
	float coordinateX;
	float coordinateY;
}
MCards_Vector2D;

/**
 * @brief   Criação e alocalçao uma instância de vetor bidimensional na memória.
 * @details Usada para definir uma coordenada no Plano-Cartesiano de duas dimensões.
 * @param   [in] cx A coordenada horizontal relativa à tela, com o valor entre zero (0.0f) até dois (2.0f).
 * @param   [in] cy A coordenada vertical relativa à tela, com o valor entre zero (0.0f) até dois (2.0f).
 * @return  Uma estrutura básica de vetor bidimensional.
 */
MCards_Vector2D * MCards_CreateVector2D(float cx, float cy);

/**
 * @brief   Obtenção e retorno do valor de coordenada horizontal do vetor.
 * @details Requer que o vetor solicitado já esteja alocado na memória.
 * @param   [in] vector2D O vetor solicitado para consulta e retorno da coordenada desejada.
 * @return  O valor de coordenada horizontal cujo o vetor tenha entre zero (0.0f) e dois (2.0f).
 */
float MCards_GetVectorXCoordinate(MCards_Vector2D * vector2D);

#endif
