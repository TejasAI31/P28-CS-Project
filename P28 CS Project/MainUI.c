#include "includeheaders.h"

char choice, dateandmonth[11], day[4], currenttime[7],hours[4], minutes[4];
int check;

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
	system("cls");
	updatetime();
	//mainscreen
	printf("		%s---------------------------------\n", brightyellow);
	printf("		!%sWELCOME TO THE IIT PATNA PORTAL%s!\n", brightblue, brightyellow);
	printf("		---------------------------------\n%s", white);
	printf("\n\nWhat do you wish to do?\n");
	printf("%s----------------------\n%s", brightyellow,white);
	printf("\n\n%sCatalogue:%s\n", cyan, white);
	printf("%s-----------------------\n%s", magenta, white);
	printf("%s1:%sTimetable%s\n", magenta, cyan, white);
	printf("%s2:%sClubs%s\n", magenta, cyan, white);
	printf("%s3:%sTimings%s\n", magenta, cyan, white);
	printf("%s4:%sSWB%s\n", magenta, cyan, white);
	printf("%s5:%sContacts%s\n", magenta, cyan, white);
	printf("%s6:%sComplaints%s\n", magenta, cyan, white);
	printf("%s7:%sWeekly Quiz%s\n", magenta, cyan, white);
	printf("%s8:%sTic Tac Toe%s\n", magenta, cyan, white);
	printf("%s-----------------------\n\n%s%s", magenta, white, save);

	//prints date
	printf("\033[6;50H--%s%s%s--", brightgreen, dateandmonth, white);


	//checks for valid input and turns red if wrong
	int anger = 0;
	do {
		printf("%s\033[0K", reset);
		if (anger == 0)
			printf("%sEnter a valid choice(1-8):%s", brightgreen, white);
		else
			printf("%sEnter a valid choice(1-8):%s", brightred, white);
		scanf_s("%c", &choice);
		anger += 1;
	} while (choice < 49 || choice>56);
	
	switch (choice)
	{
	case 51:
		updatetime();
		loadingscreen(minutes);
		showtimings(day, currenttime, hours, minutes);
		break;
	case 56:
		updatetime();
		loadingscreen(minutes);
		tictactoe();
		break;
	}
}


int main(void)
{
	mainscreen();
}