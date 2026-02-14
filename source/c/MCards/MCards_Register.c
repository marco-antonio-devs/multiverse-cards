#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <MCards/MCards_Register.h>
#include <MCards/MCards_Factory.h>

MCards_Registry * registry = NULL;

void MCards_InitializeRegistry()
{
	if(registry != NULL)
	{
		return;
	}
	
	registry = malloc(sizeof(MCards_Registry));
	
	registry->cardCount = 0;
	registry->unitCount = 0;
	registry->leaderCount = 0;
	
	registry->maxCards = 8;
	registry->maxUnits = 8;
	registry->maxLeaders = 8;
	
	registry->cardData = malloc(registry->maxCards * sizeof(MCards_CardBase *));
	registry->unitData = malloc(registry->maxUnits * sizeof(MCards_UnitBase *));
	registry->leaderData = malloc(registry->maxLeaders * sizeof(MCards_LeaderBase *));
	registry->leaderCardData = malloc(registry->maxLeaderCards * sizeof(MCards_LeaderCardBase *));
	
	registry->cardIDs = malloc(registry->maxCards * sizeof(const char *));
	registry->unitIDs = malloc(registry->maxUnits * sizeof(const char *));
	registry->leaderIDs = malloc(registry->maxLeaders * sizeof(const char *));
	registry->leaderCardIDs = malloc(registry->maxLeaderCards * sizeof(const char *));
	
	if(!registry->cardData)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de cartas.");
		free(registry->cardData);
		
		return;
	}
	
	if(!registry->cardIDs)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para as cartas.");
		free(registry->cardIDs);
		
		return;
	}
	
	if(!registry->unitData)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de unidades.");
		free(registry->unitData);
		
		return;
	}
	
	if(!registry->unitIDs)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para as unidades.");
		free(registry->unitIDs);
		
		return;
	}
	
	if(!registry->leaderData)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de líderes.");
		free(registry->leaderData);
		
		return;
	}
	
	if(!registry->leaderIDs)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os líderes.");
		free(registry->leaderIDs);
		
		return;
	}
}

void MCards_CleanUpRegistry()
{
	if(registry == NULL)
	{
		return;
	}
	
	for(size_t index = 0; index < registry->cardCount; index++)
	{
		free(registry->cardData[index]->displayName);
		
		for(size_t x = 0; x < registry->cardData[index]->spawnCount; x++)
		{
    		free(registry->cardData[index]->spawns[x]);
		}
		
		free(registry->cardData[index]);
	}
	
	for(size_t index = 0; index < registry->unitCount; index++)
	{
		free(registry->unitData[index]);
	}
	
	for(size_t index = 0; index < registry->leaderCount; index++)
	{
		free(registry->leaderData[index]);
	}
	
	registry->cardCount = 0;
	registry->unitCount = 0;
	registry->leaderCount = 0;
	
	free(registry->cardData);
	free(registry->unitData);
	free(registry->leaderData);
	
	free(registry->cardIDs);
	free(registry->unitIDs);
	free(registry->leaderIDs);
	
	free(registry);
	
	registry = NULL;
}

void MCards_RegisterCard(MCards_CardBase * cardBase, const char * iD)
{
	if(registry == NULL || registry->cardIDs == NULL || registry->cardData == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	if(cardBase == NULL)
	{
		perror("Por favor, estabeleça uma referência de estrutura válida para o registro da carta.");
		
		return;
	}
	
	for(size_t index = 0; index < registry->cardCount; index++)
	{
		if(strcmp(registry->cardIDs[index], iD) == 0)
		{
			fprintf(stderr, "Já existe um identificador de carta chamado \"%s\".", iD);
			
			return;
		}
	}
	
	if(registry->cardCount >= registry->maxCards)
	{
		size_t newMaxCards = registry->cardCount * 2;
		
		const char ** newCardIDs = realloc(registry->cardIDs, newMaxCards * sizeof(const char *));
		MCards_CardBase ** newCardData = realloc(registry->cardData, newMaxCards * sizeof(MCards_CardBase *));
		
		if(!newCardIDs)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os identificadores de cartas.");
			
			return;
		}
		
		if(!newCardData)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de cartas.");
			
			return;
		}
		
		registry->cardIDs = newCardIDs;
		registry->cardData = newCardData;
		registry->maxCards = newMaxCards;
	}
	
	registry->cardData[registry->cardCount] = cardBase;
	registry->cardIDs[registry->cardCount] = iD;
	registry->cardCount++;
	
	printf("O identificador %s corresponde a uma carta denominada %s (custando %d unidades de energia).\n", iD, cardBase->displayName, cardBase->deployCost);
}

void MCards_RegisterUnit(MCards_UnitBase * unitBase, const char * iD)
{
	if(registry == NULL || registry->unitIDs == NULL || registry->unitData == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	if(unitBase == NULL)
	{
		perror("Por favor, estabeleça uma referência de estrutura válida para o registro da unidade.");
		
		return;
	}
	
	for(size_t index = 0; index < registry->unitCount; index++)
	{
		if(strcmp(registry->unitIDs[index], iD) == 0)
		{
			fprintf(stderr, "Já existe um identificador de unidade chamado \"%s\".", iD);
			
			return;
		}
	}
	
	if(registry->unitCount >= registry->maxUnits)
	{
		size_t newMaxUnits = registry->unitCount * 2;
		
		const char ** newUnitIDs = realloc(registry->unitIDs, newMaxUnits * sizeof(const char *));
		MCards_UnitBase ** newUnitData = realloc(registry->unitData, newMaxUnits * sizeof(MCards_UnitBase *));
		
		if(!newUnitIDs)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para identificadores de unidades.");
			
			return;
		}
		
		if(!newUnitData)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de unidades.");
			
			return;
		}
		
		registry->unitIDs = newUnitIDs;
		registry->unitData = newUnitData;
		registry->maxUnits = newMaxUnits;
	}
	
	registry->unitData[registry->unitCount] = unitBase;
	registry->unitIDs[registry->unitCount] = iD;
	registry->unitCount++;
	
	printf("O identificador %s corresponde a uma unidade com %d pontos de vida, %d pontos de dano-direto, %1.2f segundos entre ataques sequenciais, percorrendo %1.2f ladrilhos por segundo e %1.2f ladrilhos de alcance de ataque.\n", iD, unitBase->hitpoints, unitBase->directDamage, unitBase->attackDelay, unitBase->movementSpeed, unitBase->attackRange);
}

void MCards_RegisterLeader(MCards_LeaderBase * leaderBase, const char * iD)
{
	if(registry == NULL || registry->leaderIDs == NULL || registry->leaderData == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	if(leaderBase == NULL)
	{
		perror("Por favor, estabeleça uma referência de estrutura válida para o registro do líder.");
		
		return;
	}
	
	for(size_t index = 0; index < registry->leaderCount; index++)
	{
		if(strcmp(registry->leaderIDs[index], iD) == 0)
		{
			fprintf(stderr, "Já existe um identificador de líder chamado \"%s\".", iD);
			
			return;
		}
	}
	
	if(registry->leaderCount >= registry->maxLeaders)
	{
		size_t newMaxLeaders = registry->leaderCount * 2;
		
		const char ** newLeaderIDs = realloc(registry->leaderIDs, newMaxLeaders * sizeof(const char *));
		MCards_LeaderBase ** newLeaderData = realloc(registry->leaderData, newMaxLeaders * sizeof(MCards_LeaderBase *));
		
		if(!newLeaderIDs)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os líderes.");
			
			return;
		}
		
		if(!newLeaderData)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de líderes.");
			
			return;
		}
		
		registry->leaderIDs = newLeaderIDs;
		registry->leaderData = newLeaderData;
		registry->maxLeaders = newMaxLeaders;
	}
	
	registry->leaderData[registry->leaderCount] = leaderBase;
	registry->leaderIDs[registry->leaderCount] = iD;
	registry->leaderCount++;
	
	printf("O identificador %s corresponde a um líder com %d pontos de vida, %d pontos de dano-direto, %1.2f segundos entre ataques sequenciais e %1.2f ladrilhos de alcance de ataque.\n", iD, leaderBase->hitpoints, leaderBase->directDamage, leaderBase->attackDelay, leaderBase->attackRange);
}

void MCards_StartUpCards()
{
	if(registry == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	MCards_CardSpawn * cardSpawns[8][1] =
	{
		{MCards_CreateCardSpawn("U_Gravedigger", 1)},
		{MCards_CreateCardSpawn("U_Tribal", 2)},
		{MCards_CreateCardSpawn("U_Pelican", 1)},
		{MCards_CreateCardSpawn("U_Bandit", 1)},
		{MCards_CreateCardSpawn("U_LRobot", 1)},
		{MCards_CreateCardSpawn("U_Capybara", 4)},
		{MCards_CreateCardSpawn("U_Seagull", 3)},
		{MCards_CreateCardSpawn("U_Crusher", 1)},
	};
	
	MCards_CardBase * cards[8];
	
	cards[0] = MCards_CreateCard("Local_GravediggerName", "Gravedigger", 3, cardSpawns[0], 1);
	cards[1] = MCards_CreateCard("Local_TribalsName", "Tribals", 2, cardSpawns[1], 1);
	cards[2] = MCards_CreateCard("Local_PelicanName", "Pelican", 5, cardSpawns[2], 1);
	cards[3] = MCards_CreateCard("Local_BanditName", "Bandit", 4, cardSpawns[3], 1);
	cards[4] = MCards_CreateCard("Local_LRobotName", "L-Robot", 4, cardSpawns[4], 1);
	cards[5] = MCards_CreateCard("Local_CapybarasName", "Capybaras", 5, cardSpawns[5], 1);
	cards[6] = MCards_CreateCard("Local_SeagullsName", "Seagulls", 2, cardSpawns[6], 1);
	cards[7] = MCards_CreateCard("Local_CrusherName", "Crusher", 7, cardSpawns[7], 1);
	
	const char * cardIDs[8];
	
	cardIDs[0] = "C_Gravedigger";
	cardIDs[1] = "C_Tribals";
	cardIDs[2] = "C_Pelican";
	cardIDs[3] = "C_Bandit";
	cardIDs[4] = "C_LRobot";
	cardIDs[5] = "C_Capybaras";
	cardIDs[6] = "C_Seagulls";
	cardIDs[7] = "C_Crusher";
	
	size_t cardLength = sizeof(cards) / sizeof(MCards_CardBase *);
	
	for(size_t x = 0; x < cardLength; x++)
	{
		MCards_CardBase * cardX = cards[x];
		
		if(cardX)
		{
			MCards_RegisterCard(cardX, cardIDs[x]);
		}
	}
}

void MCards_StartUpUnits()
{
	if(registry == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	MCards_UnitBase * units[8];
	
	units[0] = MCards_CreateUnit(650,  70,  1.1f, 2.0f, 1.5f);
	units[1] = MCards_CreateUnit(168,  26,  0.9f, 2.5f, 4.0f);
	units[2] = MCards_CreateUnit(870,  100, 1.6f, 1.5f, 0.5f);
	units[3] = MCards_CreateUnit(500,  65,  1.0f, 2.0f, 5.5f);
	units[4] = MCards_CreateUnit(700,  300, 1.4f, 2.0f, 1.0f);
	units[5] = MCards_CreateUnit(480,  32,  1.2f, 2.5f, 0.5f);
	units[6] = MCards_CreateUnit(24,   24,  1.2f, 2.5f, 0.5f);
	units[7] = MCards_CreateUnit(1100, 144, 1.8f, 1.5f, 1.5f);
	
	const char * unitIDs[8];
	
	unitIDs[0] = "U_Gravedigger";
	unitIDs[1] = "U_Tribal";
	unitIDs[2] = "U_Pelican";
	unitIDs[3] = "U_Bandit";
	unitIDs[4] = "U_LRobot";
	unitIDs[5] = "U_Capybara";
	unitIDs[6] = "U_Seagull";
	unitIDs[7] = "U_Crusher";
	
	size_t unitLength = sizeof(units) / sizeof(MCards_UnitBase *);
	
	for(size_t x = 0; x < unitLength; x++)
	{
		MCards_UnitBase * unitX = units[x];
		
		if(unitX)
		{
			MCards_RegisterUnit(unitX, unitIDs[x]);
		}
	}
}

void MCards_StartUpLeaders()
{
	if(registry == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	MCards_LeaderBase * leaders[3];
	
	leaders[0] = MCards_CreateLeader(1536, 45, 1.0f, 7.0f);
	leaders[1] = MCards_CreateLeader(1700, 90, 1.5f, 1.0f);
	leaders[2] = MCards_CreateLeader(1600, 56, 0.9f, 1.5f);
	
	const char * leaderIDs[3];
	
	leaderIDs[0] = "L_Pirate";
	leaderIDs[1] = "L_MightyTribal";
	leaderIDs[2] = "L_Samurai";
	
	size_t leaderLength = sizeof(leaders) / sizeof(MCards_LeaderBase *);
	
	for(size_t x = 0; x < leaderLength; x++)
	{
		MCards_LeaderBase * leaderX = leaders[x];
		
		if(leaderX)
		{
			MCards_RegisterLeader(leaderX, leaderIDs[x]);
		}
	}
}

MCards_CardSpawn * MCards_CreateCardSpawn(const char * iD, unsigned int count)
{
	MCards_CardSpawn * cardSpawn = malloc(sizeof(MCards_CardSpawn));
	
	if(!cardSpawn)
	{
		perror("Houve uma falha ao alocar os dados de conjuração da carta na memória.");
		free(cardSpawn);
		
		return NULL;
	}
	
	size_t iDLength = strlen(iD) + 1;
	
	cardSpawn->iD = malloc(iDLength);
	
	if(!cardSpawn->iD)
	{
		perror("Houve uma falha ao alocar o identificador de conjuração da carta na memória.");
		free(cardSpawn);
		
		return NULL;
	}
	
	strcpy(cardSpawn->iD, iD);
	
	cardSpawn->count = count;
	
	return cardSpawn;
}

MCards_CardBase * MCards_CreateCard(const char * lk, const char * dn, int dc, MCards_CardSpawn * spawns[], size_t spawnCount)
{
	MCards_CardBase * card = malloc(sizeof(MCards_CardBase));
	
	if(!card)
	{
		perror("Houve uma falha ao alocar a carta na memória.");
		free(card);
		
		return NULL;
	}
	
	size_t languageKeyLength = strlen(lk) + 1;
	size_t nameLength = strlen(dn) + 1;
	
	card->localizationKey = malloc(languageKeyLength);
	card->displayName = malloc(nameLength);
	
	if(!card->localizationKey)
	{
		perror("Houve uma falha ao alocar a chave de tradução da carta na memória.");
		free(card->localizationKey);
		free(card);
		
		return NULL;
	}
	
	if(!card->displayName)
	{
		perror("Houve uma falha ao alocar o nome de exibição da carta na memória.");
		free(card->displayName);
		free(card);
		
		return NULL;
	}
	
	if(dc <= 0 || dc > 10)
	{
		perror("Você atribuiu um valor incorreto no custo de conjuração da carta. O valor não pode ser menor ou igual a zero (0) e maior que dez (10).");
		free(card->displayName);
		free(card);
		
		return NULL;
	}
	
	strcpy(card->localizationKey, lk);
	strcpy(card->displayName, dn);
	
	card->deployCost = dc;
	
	for(size_t index = 0; index < spawnCount; index++)
	{
		if(spawns[index] != NULL)
		{
			card->spawns[index] = spawns[index];
		}
		else
		{
			continue;
		}
	}
	
	card->spawnCount = spawnCount;
	
	return card;
}

MCards_UnitBase * MCards_CreateUnit(int hp, int dm, float ad, float ms, float ar)
{
	MCards_UnitBase * unit = malloc(sizeof(MCards_UnitBase));
	
	if(!unit)
	{
		perror("Houve uma falha ao alocar a unidade na memória.");
		free(unit);
		
		return NULL;
	}
	
	unit->hitpoints = hp;
	unit->directDamage = dm;
	unit->attackDelay = ad;
	unit->movementSpeed = ms;
	unit->attackRange = ar;
	
	return unit;
}

MCards_LeaderBase * MCards_CreateLeader(int hp, int dm, float ad, float ar)
{
	MCards_LeaderBase * leader = malloc(sizeof(MCards_LeaderBase));
	
	if(!leader)
	{
		perror("Houve uma falha ao alocar o líder na memória.");
		free(leader);
		
		return NULL;
	}
	
	leader->hitpoints = hp;
	leader->directDamage = dm;
	leader->attackDelay = ad;
	leader->attackRange = ar;
	
	return leader;
}

bool MCards_ContainsCard(const char * iD)
{
	for(size_t index = 0; index < registry->cardCount; index++)
	{
		if(strcmp(registry->cardIDs[index], iD) == 0)
		{
			return true;
		}
		else
		{
			continue;
		}
	}
	
	return false;
}

bool MCards_ContainsUnit(const char * iD)
{
	for(size_t index = 0; index < registry->unitCount; index++)
	{
		if(strcmp(registry->unitIDs[index], iD) == 0)
		{
			return true;
		}
		else
		{
			continue;
		}
	}
	
	return false;
}

bool MCards_ContainsLeader(const char * iD)
{
	for(size_t index = 0; index < registry->leaderCount; index++)
	{
		if(strcmp(registry->leaderIDs[index], iD) == 0)
		{
			return true;
		}
		else
		{
			continue;
		}
	}
	
	return false;
}
