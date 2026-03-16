#ifndef DEF_MCards_Mathematics_Header
#define DEF_MCards_Mathematics_Header

/**
 * @brief   Vetor bidimensional.
 * @details Representa um ponto dentro do Plano-Cartesiano zero (0.0f) representando a extremidade esquerda da tela e vice-versa para dois (2.0f).
 */
typedef struct
{
	float coordinateX; /**< Coordenada horizontal deste vetor bidimensional.*/
	float coordinateY; /**< Coordenada vertical deste vetor bidimensional.*/
}
MCards_Vector2D;

/**
 * @brief   Criação e alocalçao uma instância de vetor bidimensional na memória.
 * @details Usada para definir uma coordenada no Plano-Cartesiano de duas dimensões.
 *
 * @param   [in] cx A coordenada horizontal relativa à tela, com o valor entre zero (0.0f) até dois (2.0f).
 * @param   [in] cy A coordenada vertical relativa à tela, com o valor entre zero (0.0f) até dois (2.0f).
 *
 * @return  Uma estrutura básica de vetor bidimensional.
 */
MCards_Vector2D * MCards_CreateVector2D(float cx, float cy);

/**
 * @brief   Obtenção e retorno do valor de coordenada horizontal do vetor.
 * @details Requer que o vetor solicitado já esteja alocado na memória.
 *
 * @param   [in] vector2D O vetor solicitado para consulta e retorno da coordenada desejada.
 *
 * @return  O valor de coordenada horizontal cujo o vetor tenha entre zero (0.0f) e dois (2.0f).
 */
float MCards_GetVectorXCoordinate(MCards_Vector2D * vector2D);

/**
 * @brief   Obtenção e retorno do valor de coordenada vertical do vetor.
 * @details Requer que o vetor solicitado já esteja alocado na memória.
 *
 * @param   [in] vector2D O vetor solicitado para consulta e retorno da coordenada desejada.
 *
 * @return  O valor de coordenada vertical do vetor, que tenha entre zero (0.0f) e dois (2.0f).
 */
float MCards_GetVectorYCoordinate(MCards_Vector2D * vector2D);

/**
 * @brief   Mistura entre dois vetores bidimensional.
 * @details Requer que ambos os vetores selecionados estejam préviamente alocados na memória.
 *
 * @param   [in] firstVector2D O primeiro vetor a ser selecionado, como referência para a mistura.
 * @param   [in, out] secondVector2D O segundo vetor a ser selecionado, como o valor a ser misturado com base na referência.
 * @param   [in] blendFactor O fator de mistura entre ambos os vetores.
 */
void MCards_SmoothBlendVector2D(MCards_Vector2D * firstVector2D, MCards_Vector2D * secondVector2D, float blendFactor);

#endif
