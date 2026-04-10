#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <MCards/UserInterface/MCards_Localization.h>

MCards_LocalizationRegistry * localizationRegistry = NULL;

static const char * languageNames[] =
{
	"North-american English",
	"Português brasileiro",
	"Español europeo",
	"Français europeén",
	"Europäisch",
	"にほんご",
};

void MCards_InitializeLocalization()
{
	if(localizationRegistry != NULL)
	{
		return;
	}
	
	printf("Inicializando o registro de localizações.\n");
	
	localizationRegistry = malloc(sizeof(MCards_LocalizationRegistry));
	
	localizationRegistry->entryCount = 0;
	localizationRegistry->maxEntries = 32;
	
	localizationRegistry->entries = malloc(localizationRegistry->maxEntries * sizeof(MCards_LocalizationEntry *));
	
	if(!localizationRegistry->entries)
	{
		perror("Houve uma falha ao alocar o registro de localizações na memória.\n");
		
		free(localizationRegistry);
		
		localizationRegistry = NULL;
	}
	
	char ** basicTranslations = malloc(E_MCards_LanguageCount * sizeof(char *));
	
	basicTranslations[0] = malloc(strlen("Basic") + 1);
	basicTranslations[1] = malloc(strlen("Básica") + 1);
	basicTranslations[2] = malloc(strlen("Básica") + 1);
	basicTranslations[3] = malloc(strlen("Basique") + 1);
	basicTranslations[4] = malloc(strlen("Basis") + 1);
	basicTranslations[5] = malloc(strlen("ベーシック") + 1);
	
	strcpy(basicTranslations[0], "Basic");
	strcpy(basicTranslations[1], "Básica");
	strcpy(basicTranslations[2], "Básica");
	strcpy(basicTranslations[3], "Basique");
	strcpy(basicTranslations[4], "basis");
	strcpy(basicTranslations[5], "ベーシック");
	
	char ** rareTranslations = malloc(E_MCards_LanguageCount * sizeof(char *));
	
	rareTranslations[0] = malloc(strlen("Rare") + 1);
	rareTranslations[1] = malloc(strlen("Rara") + 1);
	rareTranslations[2] = malloc(strlen("Rara") + 1);
	rareTranslations[3] = malloc(strlen("Rare") + 1);
	rareTranslations[4] = malloc(strlen("Selten") + 1);
	rareTranslations[5] = malloc(strlen("レア") + 1);
	
	strcpy(rareTranslations[0], "Rare");
	strcpy(rareTranslations[1], "Rara");
	strcpy(rareTranslations[2], "Rara");
	strcpy(rareTranslations[3], "Rare");
	strcpy(rareTranslations[4], "Selten");
	strcpy(rareTranslations[5], "レア");
		
	char ** advancedTranslations = malloc(E_MCards_LanguageCount * sizeof(char *));
	
	advancedTranslations[0] = malloc(strlen("Advanced") + 1);
	advancedTranslations[1] = malloc(strlen("Avançada") + 1);
	advancedTranslations[2] = malloc(strlen("Avanzada") + 1);
	advancedTranslations[3] = malloc(strlen("Avanceé") + 1);
	advancedTranslations[4] = malloc(strlen("Fortgeschritten") + 1);
	advancedTranslations[5] = malloc(strlen("アドバンスド") + 1);
	
	strcpy(advancedTranslations[0], "Advanced");
	strcpy(advancedTranslations[1], "Avançada");
	strcpy(advancedTranslations[2], "Avanzada");
	strcpy(advancedTranslations[3], "Avanceé");
	strcpy(advancedTranslations[4], "Fortgeschritten");
	strcpy(advancedTranslations[5], "アドバンスド");
	
	MCards_RegisterLocalizationKey("R_Basic", basicTranslations);
	MCards_RegisterLocalizationKey("R_Rare", rareTranslations);
	MCards_RegisterLocalizationKey("R_Advanced", advancedTranslations);
	
	localizationRegistry->currentLanguage = E_MCards_EnglishNA;
}

void MCards_CleanUpLocalization()
{
	if(localizationRegistry == NULL)
	{
		return;
	}
	
	printf("Limpando o registro de traduções.\n");
	
	for(size_t index = 0; index < localizationRegistry->entryCount; index++)
	{
		MCards_LocalizationEntry * entry = localizationRegistry->entries[index];
		
		printf("Liberando uma chave de tradução no índice %ld da lista registrada (%s)...\n", index, (entry->key != NULL) ? entry->key : "idioma desconhecido");
		free(entry);
	}
	
	localizationRegistry->entryCount = 0;
	
	free(localizationRegistry->entries);
	free(localizationRegistry);
	
	localizationRegistry = NULL;
}

void MCards_SetCurrentLanguage(MCards_Language value)
{
	if(localizationRegistry == NULL)
	{
		printf("For favor, inicialize o registro de localizações.\n");
		
		return;
	}
	
	localizationRegistry->currentLanguage = value;
	
	printf("O idioma foi alterado para %s.\n", languageNames[value]);
}

void MCards_RegisterLocalizationKey(char * key, char ** languages)
{
	if(localizationRegistry == NULL)
	{
		perror("For favor, inicialize o registro de localizações.\n");
		
		return;
	}
	
	for(size_t index = 0; index < localizationRegistry->entryCount; index++)
	{
		MCards_LocalizationEntry * entry = localizationRegistry->entries[index];
		
		if(strcmp(entry->key, key) == 0)
		{
			printf("Já existe uma chave de tradução definida como \"%s\".\n", key);
			
			return;
		}
	}
	
	if(localizationRegistry->entryCount >= localizationRegistry->maxEntries)
	{
		size_t newMaxEntries = localizationRegistry->entryCount * 2;
		MCards_LocalizationEntry ** newEntries = realloc(localizationRegistry->entries, newMaxEntries * sizeof(MCards_LocalizationEntry *));
		
		if(!newEntries)
		{
			perror("Houve uma falha ao tentar redimensionar a lista de entradas de tradução.\n");
			
			return;
		}
		
		localizationRegistry->entries = newEntries;
		localizationRegistry->maxEntries = newMaxEntries;
		
		for(size_t index = 0; index < localizationRegistry->maxEntries; index++)
		{
			localizationRegistry->entries[index] = NULL;
		}
	}
	
	MCards_LocalizationEntry * newEntry = malloc(sizeof(MCards_LocalizationEntry));
	
	if(!newEntry)
	{
		perror("Houve uma falha ao tentar alocar uma nova entrada de tradução.\n");
		
		return;
	}
	
	size_t keyLength = strlen(key) + 1;
	
	newEntry->key = malloc(keyLength);
	
	if(!newEntry->key)
	{
		perror("Houve uma falha ao alocar memória para a chave de entrada.\n");
		
		free(newEntry);
		
		return;
	}
	
	strcpy(newEntry->key, key);
	
	newEntry->translation = malloc(E_MCards_LanguageCount * sizeof(char *));
	
	if(!newEntry->key)
	{
		perror("Houve uma falha ao alocar memória para a lista de traduções.\n");
		
		free(newEntry->key);
		free(newEntry);
		
		return;
	}
	
	for(size_t index = 0; index < E_MCards_LanguageCount; index++)
	{
		size_t translationLength = strlen(languages[index]) + 1;
		
		newEntry->translation[index] = malloc(translationLength);
		
		if(newEntry->translation[index])
		{
			strcpy(newEntry->translation[index], languages[index]);
		}
	}
	
	localizationRegistry->entries[localizationRegistry->entryCount] = newEntry;
	localizationRegistry->entryCount++;
}

char * MCards_TranslateRarityType(MCards_Rarity rarity)
{
	if(localizationRegistry == NULL)
	{
		perror("For favor, inicialize o registro de localizações.\n");
		
		return NULL;
	}
	
	const char * rarityKey = NULL;
	
	switch(rarity)
	{
		case E_MCards_Basic: rarityKey = "R_Basic"; break;
		case E_MCards_Rare: rarityKey = "R_Rare"; break;
		case E_MCards_Advanced: rarityKey = "R_Advanced"; break;
		default: rarityKey = "R_Basic"; break;
	}
	
	for(size_t index = 0; index < localizationRegistry->entryCount; index++)
	{
		MCards_LocalizationEntry * entry = localizationRegistry->entries[index];
		
		if(strcmp(entry->key, rarityKey) == 0)
		{
			return entry->translation[localizationRegistry->currentLanguage];
		}
	}
	
	return "Unknown";
}
