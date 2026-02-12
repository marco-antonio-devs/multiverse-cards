#include <stdlib.h>
#include <stdio.h>

#include <MCards/MCards_Register.h>
#include <MCards/MCards_Factory.h>

int main()
{
	MCards_InitializeRegistry();
	MCards_StartUpCards();
	
	printf("\n");
	
	MCards_StartUpUnits();
	
	printf("\n");
	
	MCards_StartUpLeaders();
	MCards_CleanUpRegistry();
	
	return 0;
}
