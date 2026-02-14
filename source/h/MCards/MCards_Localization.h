#ifndef DEF_MCards_Localization_Header
#define DEF_MCards_Localization_Header

typedef enum
{
	E_MCards_EnglishNA = 0,
	E_MCards_PortugueseSA,
	E_MCards_EspanishEU,
	E_MCards_FrenchEU,
	E_MCards_DeutschEU,
	E_MCards_JapaneseAS,
	
	E_MCards_LanguageCount,
}
MCards_Language;

typedef struct
{
	const char * key;
	const char * translation[E_MCards_LanguageCount];
}
MCards_LocalizationEntry;

typedef struct
{
	MCards_LocalizationEntry ** entries;
	size_t entryCount;
	size_t maxEntries;
	MCards_Language currentLanguage;
}
MCards_LocalizationRegistry;

extern MCards_LocalizationRegistry * localizationRegistry;

/**
 * @brief   Inicialização do registro de localizações.
 * @details Deve ser chamado uma única vez no começo de chamadas para previnir problemas de consulta.
 * @param   [in] defaultLanguage A linguagem padrão ao inicializar.
 */
void MCards_InitializeLocalization(MCards_Language defaultLanguage);

/**
 * @brief   Limpeza e desativação do registro de localizações.
 * @details Deve ser chamada uma única vez no final para liberação de memória R.A.M.
 */
void MCards_CleanUpLocalization();

/**
 * @brief   Mudança e atualização da linguagem selecionada.
 * @details Deve ser chamada <b>após</b> a chamada de inicialização do registro de localizações.
 * @param   [in] value A linguagem selecionada.
 */
void MCards_SetCurrentLanguage(MCards_Language value);

/**
 * @brief   Adição de uma chave a ser traduzida.
 * @details Deve ser chamada <b>após</b> a chamada de inicialização do registro de localizações.
 * @param   [in] key A chave cuja será traduzida de acordo com o idioma selecionado.
 * @param   [in] translations O conjunto de traduções relacionadas com a chave, com cada elemento representando uma versão textual correspondente ao idioma selecionado.
 */
void MCards_RegisterLocalizationKey(const char * key, const char * languages[E_MCards_LanguageCount]);

#endif
