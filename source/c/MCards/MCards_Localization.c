#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <MCards/MCards_Localization.h>

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

void MCards_InitializeLocalization(MCards_Language defaultLanguage)
{
	if(localizationRegistry != NULL)
	{
		return;
	}
	
	localizationRegistry = malloc(sizeof(MCards_LocalizationRegistry));
	
	localizationRegistry->entryCount = 0;
	localizationRegistry->maxEntries = 32;
	
	localizationRegistry->entries = malloc(localizationRegistry->maxEntries * sizeof(MCards_LocalizationEntry *));
	
	localizationRegistry->currentLanguage = E_MCards_EnglishNA;
	
	if(!localizationRegistry->entries)
	{
		perror("Houve uma falha ao alocar o registro de localizações na memória R.A.M.");
		free(localizationRegistry);
		
		localizationRegistry = NULL;
	}
}

void MCards_CleanUpLocalization()
{
	if(localizationRegistry == NULL)
	{
		return;
	}
	
	for(size_t index = 0; index < localizationRegistry->entryCount; index++)
	{
		free(localizationRegistry->entries[index]);
	}
	
	localizationRegistry->entryCount = 0;
	
	free(localizationRegistry->entries);
	free(localizationRegistry);
	
	localizationRegistry = NULL;
}

void MCards_SetCurrentLanguage(MCards_Language value)
{
	if(localizationRegistry)
	{
		localizationRegistry->currentLanguage = value;
		
		printf("O idioma foi alterado para %s.\n", languageNames[value]);
	}
}
