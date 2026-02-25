#include <stdlib.h>
#include <stdio.h>

#include <MCards/Core/Register/MCards_Register.h>
#include <MCards/Core/Register/MCards_Factory.h>

int main()
{
	MCards_InitializeRegistry();
	MCards_StartUpCards();
	MCards_StartUpUnits();
	MCards_StartUpLeaders();
	MCards_StartUpLeaderCards();
	MCards_CleanUpRegistry();

	return 0;
}
