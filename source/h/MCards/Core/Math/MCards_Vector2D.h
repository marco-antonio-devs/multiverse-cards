#ifndef DEF_MCards_Vector2D_Header
#define DEF_MCards_Vector2D_Header

/**
 * @brief   Vetor bidimensional.
 * @details Representa um ponto lívre da qual não é normalizado e portanto é baseada exclusivamente em <b>Pixels</b> (pontos da tela).
 * @note    Não confunda esta estrutura com {@code MCards_NormalizedVector2D}. Ambas possuem implementação diferente.
 */
typedef struct
{
	float xCoordinate; /**< Coordenada horizontal deste vetor bidimensional.*/
	float yCoordinate; /**< Coordenada vertical deste vetor bidimensional.*/
}
MCards_Vector2D;

/**
 * @brief   Vetor bidimensional normalizado.
 * @details Representa um ponto normalizado dentro do <b>Plano-Cartesiano</b> em uma faixa de zero (0.0f) representando a extremidade esquerda da tela e vice-versa para dois (2.0f).
 * @note    Não confunda esta estrutura com {@code MCards_Vector2D}. Ambas possuem implementação diferente.
 */
typedef struct
{
	float yCoordinate; /**< Coordenada horizontal deste vetor bidimensional.*/
	float xCoordinate; /**< Coordenada vertical deste vetor bidimensional.*/
}
MCards_NormalizedVector2D;

/**
 * @brief   Criação e alocalçao uma instância de vetor bidimensional na memória.
 * @details Usada para definir uma coordenada no Plano-Cartesiano de duas dimensões.
 *
 * @param   [in] xc A coordenada horizontal do vetor.
 * @param   [in] yc A coordenada vertical do vetor.
 *
 * @return  Uma estrutura básica de vetor bidimensional.
 */
MCards_Vector2D * MCards_CreateVector2D(float xc, float yc);

/**
 * @brief   Criação e alocalçao uma instância de vetor bidimensional na memória.
 * @details Usada para definir uma coordenada no Plano-Cartesiano de duas dimensões.
 *
 * @param   [in] xc A coordenada horizontal relativa à tela, com o valor entre zero (0.0f) até dois (2.0f).
 * @param   [in] yc A coordenada vertical relativa à tela, com o valor entre zero (0.0f) até dois (2.0f).
 *
 * @return  Uma estrutura básica de vetor bidimensional.
 */
MCards_NormalizedVector2D * MCards_CreateVector2D(float cx, float cy);

/**
 * @brief   Obtenção e retorno do valor de coordenada horizontal do vetor.
 * @details Requer que o vetor solicitado já esteja alocado na memória.
 *
 * @param   [in] vector2D O vetor solicitado para consulta e retorno da coordenada desejada.
 *
 * @return  O valor de coordenada horizontal do vetor.
 */
float MCards_GetVectorXCoordinate(MCards_Vector2D * vector2D);

/**
 * @brief   Obtenção e retorno do valor de coordenada vertical do vetor.
 * @details Requer que o vetor solicitado já esteja alocado na memória.
 *
 * @param   [in] vector2D O vetor solicitado para consulta e retorno da coordenada desejada.
 *
 * @return  O valor de coordenada vertical do vetor.
 */
float MCards_GetVectorYCoordinate(MCards_Vector2D * vector2D);

/**
 * @brief   Obtenção e retorno do valor de coordenada horizontal do vetor normalizado.
 * @details Requer que o vetor solicitado já esteja alocado na memória.
 *
 * @param   [in] normalizedVector2D O vetor solicitado para consulta e retorno da coordenada desejada.
 *
 * @return  O valor de coordenada horizontal do vetor normalizado, que esteja dentro da faixa de zero (0.0f) e dois (2.0f).
 */
float MCards_GetNormalizedVectorXCoordinate(MCards_NormalizedVector2D * normalizedVector2D);

/**
 * @brief   Obtenção e retorno do valor de coordenada vertical do vetor normalizado.
 * @details Requer que o vetor solicitado já esteja alocado na memória.
 *
 * @param   [in] normalizedVector2D O vetor solicitado para consulta e retorno da coordenada desejada.
 *
 * @return  O valor de coordenada vertical do vetor normalizado, que esteja dentro da faixa de zero (0.0f) e dois (2.0f).
 */
float MCards_GetNormalizedVectorYCoordinate(MCards_NormalizedVector2D * normalizedVector2D);

/**
 * @brief   Mistura entre dois vetores bidimensional.
 * @details Requer que ambos os vetores selecionados estejam préviamente alocados na memória.
 *
 * @param   [in] firstVector2D O primeiro vetor a ser selecionado, como referência para a mistura.
 * @param   [in, out] secondVector2D O segundo vetor a ser selecionado, como o valor a ser misturado com base na referência.
 * @param   [in] blendFactor O fator de mistura entre ambos os vetores.
 */
void MCards_SmoothBlendVector2D(MCards_Vector2D * firstVector2D, MCards_Vector2D * secondVector2D, float blendFactor);

/**
 * @brief   Mistura entre dois vetores bidimensional.
 * @details Requer que ambos os vetores selecionados estejam préviamente alocados na memória.
 *
 * @param   [in] firstNormalizedVector2D O primeiro vetor normalizado a ser selecionado, como referência para a mistura.
 * @param   [in, out] secondNormalizedVector2D O segundo vetor normalizado a ser selecionado, como o valor a ser misturado com base na referência.
 * @param   [in] blendFactor O fator de mistura entre ambos os vetores.
 */
void MCards_SmoothBlendNormalizedVector2D(MCards_NormalizedVector2D * firstVector2D, MCards_NormalizedVector2D * secondVector2D, float blendFactor);

#endif
