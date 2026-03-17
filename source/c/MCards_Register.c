#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <MCards/Core/Register/MCards_Register.h>
#include <MCards/Core/Register/MCards_Factory.h>

MCards_Registry * registry = NULL;

void MCards_InitializeRegistry()
{
	if(registry != NULL)
	{
		return;
	}
	
	printf("Inicializando o registro principal.\n");
	
	registry = malloc(sizeof(MCards_Registry));
	
	registry->cardCount = 0;
	registry->unitCount = 0;
	registry->leaderCount = 0;
	registry->leaderCardCount = 0;
	registry->maxCards = 8;
	registry->maxUnits = 8;
	registry->maxLeaders = 8;
	registry->maxLeaderCards = 8;
	
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
		
		return;
	}
	
	if(!registry->cardIDs)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para as cartas.");
		
		return;
	}
	
	if(!registry->unitData)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de unidades.");
		
		return;
	}
	
	if(!registry->unitIDs)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para as unidades.");
		
		return;
	}
	
	if(!registry->leaderData)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de líderes.");
		
		return;
	}
	
	if(!registry->leaderIDs)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os líderes.");
		return;
	}
	
	if(!registry->leaderCardData)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de cartas de líderes.");
		
		return;
	}
	
	if(!registry->leaderCardIDs)
	{
		perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para as cartas de líderes.");
		
		return;
	}
}

void MCards_CleanUpRegistry()
{
	if(registry == NULL)
	{
		return;
	}
	
	printf("Limpando o registro principal.\n");
	
	for(size_t index = 0; index < registry->cardCount; index++)
	{
		free(registry->cardData[index]->displayName);
		free(registry->cardData[index]->displayDescription);
		
		for(size_t x = 0; x < registry->cardData[index]->spawnCount; x++)
		{
			free(registry->cardData[index]->spawns[x]->iD);
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
	
	for(size_t index = 0; index < registry->leaderCardCount; index++)
	{
		free(registry->leaderCardData[index]->displayName);
		free(registry->leaderCardData[index]->displayDescription);
		free(registry->leaderCardData[index]->referenceID);
		free(registry->leaderCardData[index]);
	}
	
	registry->cardCount = 0;
	registry->unitCount = 0;
	registry->leaderCount = 0;
	registry->leaderCardCount = 0;
	
	free(registry->cardData);
	free(registry->unitData);
	free(registry->leaderData);
	free(registry->leaderCardData);
	
	free(registry->cardIDs);
	free(registry->unitIDs);
	free(registry->leaderIDs);
	free(registry->leaderCardIDs);
	
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
}

void MCards_RegisterLeaderCard(MCards_LeaderCardBase * leaderCardBase, const char * iD)
{
	if(registry == NULL || registry->leaderCardIDs == NULL || registry->leaderCardData == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	if(leaderCardBase == NULL)
	{
		perror("Por favor, estabeleça uma referência de estrutura válida para o registro da carta.");
		
		return;
	}
	
	for(size_t index = 0; index < registry->leaderCardCount; index++)
	{
		if(strcmp(registry->leaderCardIDs[index], iD) == 0)
		{
			fprintf(stderr, "Já existe um identificador de carta de líder chamado \"%s\".", iD);
			
			return;
		}
	}
	
	if(registry->leaderCardCount >= registry->maxLeaderCards)
	{
		size_t newMaxLeaderCards = registry->leaderCardCount * 2;
		const char ** newLeaderCardIDs = realloc(registry->leaderCardIDs, newMaxLeaderCards * sizeof(const char *));
		
		MCards_LeaderCardBase ** newLeaderCardData = realloc(registry->leaderCardData, newMaxLeaderCards * sizeof(MCards_LeaderCardBase *));
		
		if(!newLeaderCardIDs)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os identificadores de cartas de líder.");
			
			return;
		}
		
		if(!newLeaderCardData)
		{
			perror("Houve uma falha de inicialização do registro principal, principalmente na alocação de memória para os dados de cartas de líder.");
			
			return;
		}
		
		registry->leaderCardIDs = newLeaderCardIDs;
		registry->leaderCardData = newLeaderCardData;
		registry->maxLeaderCards = newMaxLeaderCards;
	}
	
	registry->leaderCardData[registry->leaderCardCount] = leaderCardBase;
	registry->leaderCardIDs[registry->leaderCardCount] = iD;
	
	registry->leaderCardCount++;
}

void MCards_StartUpCards()
{
	if(registry == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	MCards_CardSpawn * cardSpawns[15][DEF_MCards_MaxCardSpawns] =
	{
		NULL
	};
	
	cardSpawns[0][0]  = MCards_CreateCardSpawn("U_Gravedigger",         1);
	cardSpawns[1][0]  = MCards_CreateCardSpawn("U_Tribal",              2);
	cardSpawns[2][0]  = MCards_CreateCardSpawn("U_Pelican",             1);
	cardSpawns[3][0]  = MCards_CreateCardSpawn("U_Bandit",              1);
	cardSpawns[4][0]  = MCards_CreateCardSpawn("U_LRobot",              1);
	cardSpawns[5][0]  = MCards_CreateCardSpawn("U_Capybara",            4);
	cardSpawns[6][0]  = MCards_CreateCardSpawn("U_Seagull",             3);
	cardSpawns[7][0]  = MCards_CreateCardSpawn("U_Crusher",             1);
	cardSpawns[8][0]  = MCards_CreateCardSpawn("U_Theropod",            1);
	cardSpawns[9][0]  = MCards_CreateCardSpawn("U_StrangeWorm",         5);
	cardSpawns[10][0] = MCards_CreateCardSpawn("U_Hallucination",       1);
	cardSpawns[10][1] = MCards_CreateCardSpawn("U_HallucinationReflex", 1);
	cardSpawns[11][0] = MCards_CreateCardSpawn("U_PampaHorseman",       1);
	cardSpawns[12][0] = MCards_CreateCardSpawn("U_GunDealer",           1);
	cardSpawns[13][0] = MCards_CreateCardSpawn("U_PlagueKiller",        1);
	cardSpawns[14][0] = MCards_CreateCardSpawn("U_SkeletalCaptain",     1);
	cardSpawns[14][1] = MCards_CreateCardSpawn("U_CaptainSupporter",    2);
	
	MCards_CardBase * cards[15];
	
	cards[0]  = MCards_CreateCard("T_Gravedigger_Name",   "T_Gravedigger_Flavor",   3, cardSpawns[0],  1);
	cards[1]  = MCards_CreateCard("T_Tribals_Name",       "T_Tribals_Flavor",       2, cardSpawns[1],  1);
	cards[2]  = MCards_CreateCard("T_Pelican_Name",       "T_Pelican_Flavor",       5, cardSpawns[2],  1);
	cards[3]  = MCards_CreateCard("T_Bandit_Name",        "T_Bandit_Flavor",        4, cardSpawns[3],  1);
	cards[4]  = MCards_CreateCard("T_LRobot_Name",        "T_LRobot_Flavor",        4, cardSpawns[4],  1);
	cards[5]  = MCards_CreateCard("T_Capybaras_Name",     "T_Capybaras_Flavor",     5, cardSpawns[5],  1);
	cards[6]  = MCards_CreateCard("T_Seagulls_Name",      "T_Seagulls_Flavor",      2, cardSpawns[6],  1);
	cards[7]  = MCards_CreateCard("T_Crusher_Name",       "T_Crusher_Flavor",       7, cardSpawns[7],  1);
	cards[8]  = MCards_CreateCard("T_Theropod_Name",      "T_Theropod_Flavor",      4, cardSpawns[8],  1);
	cards[9]  = MCards_CreateCard("T_StrangeWorms_Name",  "T_StrangeWorms_Flavor",  5, cardSpawns[9],  1);
	cards[10] = MCards_CreateCard("T_Hallucination_Name", "T_Hallucination_Flavor", 5, cardSpawns[10], 2);
	cards[11] = MCards_CreateCard("T_PampaHorseman_Name", "T_PampaHorseman_Flavor", 5, cardSpawns[11], 1);
	cards[12] = MCards_CreateCard("T_GunDealer_Name",     "T_GunDealer_Flavor",     4, cardSpawns[12], 1);
	cards[13] = MCards_CreateCard("T_PlagueKiller_Name",  "T_PlagueKiller_Flavor",  4, cardSpawns[13], 1);
	cards[14] = MCards_CreateCard("T_TheCaptain_Name",    "T_TheCaptain_Flavor",    4, cardSpawns[14], 2);
	
	const char * cardIDs[15];
	
	cardIDs[0]  = "C_Gravedigger";
	cardIDs[1]  = "C_Tribals";
	cardIDs[2]  = "C_Pelican";
	cardIDs[3]  = "C_Bandit";
	cardIDs[4]  = "C_LRobot";
	cardIDs[5]  = "C_Capybaras";
	cardIDs[6]  = "C_Seagulls";
	cardIDs[7]  = "C_Crusher";
	cardIDs[8]  = "C_Theropod";
	cardIDs[9]  = "C_StrangeWorms";
	cardIDs[10] = "C_Hallucination";
	cardIDs[11] = "C_PampaHorseman";
	cardIDs[12] = "C_GunDealer";
	cardIDs[13] = "C_PlagueKiller";
	cardIDs[14] = "C_TheCaptain";
	
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
	
	MCards_UnitBase * units[18];
	
	units[0]  = MCards_CreateUnit(650,  70,  1.1f, 2.0f, 1.5f);
	units[1]  = MCards_CreateUnit(168,  28,  0.9f, 2.5f, 4.5f);
	units[2]  = MCards_CreateUnit(870,  100, 1.6f, 1.5f, 0.5f);
	units[3]  = MCards_CreateUnit(500,  65,  1.0f, 2.0f, 5.5f);
	units[4]  = MCards_CreateUnit(530,  97,  1.6f, 1.5f, 1.0f);
	units[5]  = MCards_CreateUnit(480,  32,  1.2f, 2.5f, 0.5f);
	units[6]  = MCards_CreateUnit(24,   24,  1.2f, 2.5f, 0.5f);
	units[7]  = MCards_CreateUnit(1100, 144, 1.8f, 1.5f, 1.5f);
	units[8]  = MCards_CreateUnit(600,  66,  1.4f, 2.0f, 1.0f);
	units[9]  = MCards_CreateUnit(320,  32,  1.2f, 2.0f, 1.0f);
	units[10] = MCards_CreateUnit(555,  63,  1.5f, 1.5f, 1.0f);
	units[11] = MCards_CreateUnit(333,  31,  1.5f, 1.5f, 1.0f);
	units[12] = MCards_CreateUnit(775,  70,  1.6f, 2.0f, 1.0f);
	units[13] = MCards_CreateUnit(480,  70,  1.2f, 2.0f, 6.0f);
	units[14] = MCards_CreateUnit(675,  60,  1.0f, 2.5f, 1.0f);
	units[15] = MCards_CreateUnit(500,  50,  1.2f, 2.0f, 1.0f);
	units[16] = MCards_CreateUnit(770,  80,  1.4f, 2.0f, 1.5f);
	units[17] = MCards_CreateUnit(180,  24,  0.9f, 2.0f, 4.0f);
	
	const char * unitIDs[18];
	
	unitIDs[0]  = "U_Gravedigger";
	unitIDs[1]  = "U_Tribal";
	unitIDs[2]  = "U_Pelican";
	unitIDs[3]  = "U_Bandit";
	unitIDs[4]  = "U_LRobot";
	unitIDs[5]  = "U_Capybara";
	unitIDs[6]  = "U_Seagull";
	unitIDs[7]  = "U_Crusher";
	unitIDs[8]  = "U_Theropod";
	unitIDs[9]  = "U_StrangeWorm";
	unitIDs[10] = "U_Hallucination";
	unitIDs[11] = "U_HallucinationReflex";
	unitIDs[12] = "U_PampaHorseman";
	unitIDs[13] = "U_GunDealer";
	unitIDs[14] = "U_PlagueKiller";
	unitIDs[15] = "U_Warrior"; // Esta unidade não será utilizada até a implementação das primeiras construções.
	unitIDs[16] = "U_SkeletalCaptain";
	unitIDs[17] = "U_CaptainSupporter";
	
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
	
	MCards_LeaderBase * leaders[5];
	
	leaders[0] = MCards_CreateLeader(1536, 45, 1.0f, 7.0f);
	leaders[1] = MCards_CreateLeader(1680, 70, 1.6f, 2.0f);
	leaders[2] = MCards_CreateLeader(1600, 56, 0.9f, 2.5f);
	leaders[3] = MCards_CreateLeader(1710, 30, 1.3f, 6.0f);
	leaders[4] = MCards_CreateLeader(1560, 42, 0.9f, 6.5f);
	
	const char * leaderIDs[5];
	
	leaderIDs[0] = "L_Pirate";
	leaderIDs[1] = "L_MightyTribal";
	leaderIDs[2] = "L_Samurai";
	leaderIDs[3] = "L_Executioner";
	leaderIDs[4] = "L_Thief";
	
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

void MCards_StartUpLeaderCards()
{
	if(registry == NULL)
	{
		perror("Por favor, inicialize o registro principal de cartas, unidades e líderes.");
		
		return;
	}
	
	MCards_LeaderCardBase * leaderCards[5];
	
	leaderCards[0] = MCards_CreateLeaderCard("T_Pirate_Name",       "T_Pirate_Flavor",       "L_Pirate");
	leaderCards[1] = MCards_CreateLeaderCard("T_MightyTribal_Name", "T_MightyTribal_Flavor", "L_MightyTribal");
	leaderCards[2] = MCards_CreateLeaderCard("T_Samurai_Name",      "T_Samurai_Flavor",      "L_Samurai");
	leaderCards[3] = MCards_CreateLeaderCard("T_Executioner_Name",  "T_Executioner_Flavor",  "L_Executioner");
	leaderCards[4] = MCards_CreateLeaderCard("T_Thief_Name",        "T_Thief_Flavor",        "L_Thief");
	
	const char * leaderCardIDs[5];
	
	leaderCardIDs[0] = "K_Pirate";
	leaderCardIDs[1] = "K_MightyTribal";
	leaderCardIDs[2] = "K_Samurai";
	leaderCardIDs[3] = "K_Executioner";
	leaderCardIDs[4] = "K_Thief";
	
	size_t leaderCardLength = sizeof(leaderCards) / sizeof(MCards_LeaderCardBase *);
	
	for(size_t x = 0; x < leaderCardLength; x++)
	{
		MCards_LeaderCardBase * leaderCardX = leaderCards[x];
		
		if(leaderCardX)
		{
			MCards_RegisterLeaderCard(leaderCardX, leaderCardIDs[x]);
		}
	}
}

MCards_CardSpawn * MCards_CreateCardSpawn(const char * iD, unsigned int count)
{
	MCards_CardSpawn * cardSpawn = malloc(sizeof(MCards_CardSpawn));
	
	if(!cardSpawn)
	{
		perror("Houve uma falha ao alocar os dados de conjuração da carta na memória.");
		
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

MCards_CardBase * MCards_CreateCard(const char * nk, const char * dk, int dc, MCards_CardSpawn * spawns[], size_t spawnCount)
{
	MCards_CardBase * card = malloc(sizeof(MCards_CardBase) + spawnCount * sizeof(MCards_CardSpawn *));
	
	if(!card)
	{
		perror("Houve uma falha ao alocar a carta na memória.");
		
		return NULL;
	}
	
	size_t nameLength = strlen(nk) + 1;
	size_t descriptionLength = strlen(dk) + 1;
	
	card->displayName = malloc(nameLength);
	card->displayDescription = malloc(descriptionLength);
	
	if(!card->displayName)
	{
		perror("Houve uma falha ao alocar o nome de exibição da carta na memória.");
		
		free(card);
		
		return NULL;
	}
	
	if(!card->displayDescription)
	{
		perror("Houve uma falha ao alocar a descrição da carta na memória.");
		
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
	
	strcpy(card->displayName, nk);
	strcpy(card->displayDescription, dk);
	
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
		
		return NULL;
	}
	
	leader->hitpoints = hp;
	leader->directDamage = dm;
	leader->attackDelay = ad;
	leader->attackRange = ar;
	
	return leader;
}

MCards_LeaderCardBase * MCards_CreateLeaderCard(char * nk, char * dk, char * ri)
{
	MCards_LeaderCardBase * leaderCard = malloc(sizeof(MCards_LeaderCardBase));
	
	if(!leaderCard)
	{
		perror("Houve uma falha ao alocar a carta de líder na memória.");
		
		return NULL;
	}
	
	size_t nameLength = strlen(nk) + 1;
	size_t descriptionLength = strlen(dk) + 1;
	size_t referenceIDLength = strlen(ri) + 1;
	
	leaderCard->displayName = malloc(nameLength);
	leaderCard->displayDescription = malloc(descriptionLength);
	leaderCard->referenceID = malloc(referenceIDLength);
	
	if(!leaderCard->displayName)
	{
		perror("Houve um erro ao alocar o nome de exibição na memória.");
		
		return NULL;
	}
	
	if(!leaderCard->displayDescription)
	{
		perror("Houve um erro ao alocar a descrição na memória.");
		
		free(leaderCard->displayDescription);
		free(leaderCard);
		
		return NULL;
	}
	
	if(!leaderCard->referenceID)
	{
		perror("Houve um erro ao alocar o identificador de referência na memória.");
		
		free(leaderCard->displayName);
		free(leaderCard->displayDescription);
		free(leaderCard);
		
		return NULL;
	}
	
	strcpy(leaderCard->displayName, nk);
	strcpy(leaderCard->displayDescription, dk);
	strcpy(leaderCard->referenceID, ri);
	
	return leaderCard;
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

MCards_CardBase ** MCards_GetAllCardDatas()
{
	if(registry == NULL)
	{
		perror("O registro principal não foi préviamente alocado. Por favor, aloque-o.");
		
		return NULL;
	}
	
	MCards_CardBase ** cardData = malloc(registry->cardCount * sizeof(MCards_CardBase *));
	
	if(cardData == NULL)
	{
		perror("A lista de cartas a serem retornadas foi alocada sem sucesso.");
		
		return NULL;
	}
	
	for(size_t index = 0; index < registry->cardCount; index++)
	{
		cardData[index] = registry->cardData[index];
	}
	
	return cardData;
}

MCards_UnitBase ** MCards_GetAllUnitDatas()
{
	if(registry == NULL)
	{
		perror("O registro principal não foi préviamente alocado. Por favor, aloque-o.");
		
		return NULL;
	}
	
	MCards_UnitBase ** unitData = malloc(registry->unitCount * sizeof(MCards_UnitBase *));
	
	if(unitData == NULL)
	{
		perror("A lista de unidades a serem retornadas foi alocada sem sucesso.");
		
		return NULL;
	}
	
	for(size_t index = 0; index < registry->unitCount; index++)
	{
		unitData[index] = registry->unitData[index];
	}
	
	return unitData;
}
