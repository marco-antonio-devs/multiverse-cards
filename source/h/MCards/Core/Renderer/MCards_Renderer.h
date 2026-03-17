#ifndef DEF_MCards_Renderer_Header
#define DEF_MCards_Renderer_Header

#include <stddef.h>

#include <SDL3/SDL.h>

#define DEF_MCards_CardRectangleWidth 128
#define DEF_MCards_CardRectangleHeight 192

extern SDL_Window * window;
extern SDL_Renderer * renderer;

/**
 * @brief   Carregamento e alocação de um retângulo na janela gráfica.
 * @details Deve ser chamada após a inicialização gráfica.
 * 
 * @param   [in] rectangle O retângulo a ser adicionado ao renderizador selecionado.
 * @param   [in] redChannel A intensidade do canal vermelho da cor do retângulo.
 * @param   [in] greenChannel A intensidade do canal verde da cor do retângulo.
 * @param   [in] blueChannel A intensidade do canal azul da cor do retângulo.
 * @param   [in] alphaChannel A intensidade do canal alfa da cor do retângulo.
 */
void MCards_AddRectangle(SDL_FRect rectangle, unsigned int redChannel, unsigned int greenChannel, unsigned int blueChannel, unsigned int alphaChannel);

#endif
