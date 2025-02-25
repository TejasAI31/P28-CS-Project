﻿#include "includeheaders.h"

char dateandmonth[11], day[4], currenttime[7],hours[4], minutes[4];


//updates date and time
void updatetime()
{
	time_t now = time(NULL);
	char* time = ctime(&now);
	strncpy(dateandmonth, time, 10);
	dateandmonth[10] = 0;
	strncpy(day, time, 3);
	day[3] = 0;
	for (int x = 11; x < 16; x++)
		currenttime[x - 11] = time[x];
	currenttime[6] = 0;
	strncpy(hours, currenttime, 2);
	hours[2] = 0;
	for (int x = 3; x <= 4; x++)
		minutes[x - 3] =currenttime[x];
	minutes[2] = 0;
}



//shows the main hub
void mainscreen()
{
	char choice;
	system("cls");
	updatetime();

	//mainscreen
	for (int y = 1; y <= 2; y++)
	{
		printf("%s%s", yellow, magentabkg);
		for (int x = 1; x <= 30; x++)
		{
			if (x == 23)
			{
				printf("%s%s", yellow, cyanbkg);
				if (y == 1)
					printf("\033[14D\033[1B");
				else
					printf("\033[1B");
			}
			printf("||          ||\033[14D\033[1B");
		}
		printf("\033[0;106H");
	}
	printf("\033[0;0H");
	printf("\033[41C%s---------------------------------\n", brightyellow);
	printf("\033[41C!%sWELCOME TO THE IIT PATNA PORTAL%s!\n", brightblue, brightyellow);
	printf("\033[41C---------------------------------\n%s", white);
	printf("\n\n\033[45CWhat do you wish to do?\n");
	printf("%s\033[45C----------------------\n%s", brightyellow,white);
	printf("\n%s\033[51CCatalogue:%s\n", cyan, white);
	printf("%s\n\033[44C------------------------\n%s", magenta, white);
	printf("%s\033[44C1:%sLibrary%s\n", magenta, cyan, white);
	printf("%s\033[44C2:%sTimings%s\n", magenta, cyan, white);
	printf("%s\033[44C3:%sSWB%s\n", magenta, cyan, white);
	printf("%s\033[44C-----------------------%s", magenta, white);
	printf("\n\n\n\n%s\033[51CMinigames:%s\n\n", cyan, white);
	printf("%s\033[44C-----------------------%s\n", magenta, white);
	printf("%s\033[44C4:%sTic Tac Toe%s\n", magenta, cyan, white);
	printf("%s\033[44C5:%sVolleyball%s\n", magenta, cyan, white);
	printf("%s\033[44C6:%sBot Defense%s\n", magenta, cyan, white);
	printf("%s\033[44C-----------------------\n\n%s\033[44C%s", magenta, white, save);

	//prints date
	printf("\033[6;85H--%s%s%s--", brightgreen, dateandmonth, white);
	

	//checks for valid input and turns red if wrong
	int anger = 0;
	do {
		printf("%s\033[0K", reset);
		if (anger == 0)
			printf("%sEnter a valid choice(1-6):%s", brightgreen, white);
		else
			printf("%sEnter a valid choice(1-6):%s", brightred, white);
		choice = getchar();
		anger = 1;
	} while (choice < 49 || choice>54);
	anger =0;
	
	switch (choice)
	{
	case 50:
		updatetime();
		showtimings(day, currenttime, hours, minutes);
		break;
	case 51:
		updatetime();
		swb();
		break;
	case 49:
		mainlibrary();
		break;
	case 52:
		updatetime();
		loadingscreen(minutes);
		tictactoe();
		break;
	case 53:
		game();
		break;
	case 54:
		game2();
		break;
	}
}


int main(void)
{
	userportal();
	mainscreen();
}