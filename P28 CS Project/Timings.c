#include "includeheaders.h"

//Prints mess status
void ismessopen(int day,int hours,int minutes)
{
	printf("\n");
	switch (day)
	{
	case 7:if (hours >= 8 && hours <= 10 || hours >= 12 && minutes >= 30 && hours < 14 || hours >= 20 && hours <= 22)
		printf("%sMess:%s Open%s", magenta, brightgreen, white);
		  else
		printf("%sMess:%s Closed%s", magenta, brightred, white);
		printf("%s (Mess Timings:8:00-10:00, 12:30-14:00, 20:00-22:00)%s",yellow,white);
		break;
	case 5:if (hours >=7&&minutes>=30&&hours<=9|| hours >= 12 && minutes >= 30 && hours < 14 || hours >= 20 && hours <= 22)
		printf("%sMess:%s Open%s", magenta, brightgreen, white);
		  else
		printf("%sMess:%s Closed%s", magenta, brightred, white);
		printf("%s (Mess Timings:7:30-9:30, 12:30-14:00, 20:00-22:00)%s", yellow, white);
		break;
		
	}
}

//checks is clh is open
void iscentrallecturehallopen(int hours,int minutes)
{
	printf("\n");
	if (hours >= 8 && hours <= 20)
		printf("%sCentral Lecture Hall:%sOpen%s", magenta, brightgreen, white);
	else
		printf("%sCentral Lecture Hall:%sClosed%s", magenta, brightred, white);
}



//Prints Banjara status
void isbanjaraopen(int hours, int minutes)
{
	printf("\n");
	if(hours<=2||hours>=20)
		printf("%sBanjara:%s Open%s", magenta, brightgreen, white);
	else
		printf("%sBanjara:%s Closed%s", magenta, brightred, white);
	printf("%s (Banjara Timings:20:00-2:00)%s", yellow, white);
}

//Prints sports complex status
void issportscomplexopen(int hours, int minutes)
{
	printf("\n");
	if(hours<=22&&hours>=8)
		printf("%sSports Complex:%s Open%s", magenta, brightgreen, white);
	else
		printf("%sSports Complex:%s Closed%s", magenta, brightred, white);
	printf("%s (Sports Complex Timings:8:00-22:00)%s", yellow, white);
}



//shows all the timings
void showtimings(char inputday[], char inputtime[], char inputhours[], char inputminutes[])
{
	char returnchoice='m';
	system("cls");
	printf("\n\033[55C%sSTATUS\n\033[55C======%s\n\n", brightgreen, white);
	printf("%s\033[48CCurrent time: %s%s%s\n\n", brightgreen, brightyellow, inputtime, white);
	int hours = ((int)inputhours[0] - 48) * 10 + ((int)inputhours[1] - 48);
	int minutes = ((int)inputminutes[0] - 48) * 10 + ((int)inputminutes[1] - 48);


	//Print academics status
	printf("%s\nACADEMICS:\n=========%s\n",brightblue,white);
	Sleep(400);
	if (strcmp(inputday, "Sun") == 0)
	{
		printf("\n");
		printf("%sCentral Lecture Hall:%sClosed%s", magenta, brightred, white);
	}
	else
	{
		iscentrallecturehallopen(hours,minutes);
	}
	printf("%s (Central Lecture Hall Timings:8:00-20:00)%s\n\n", yellow, white);


	Sleep(400);
	printf("%s\nFOOD:\n====%s\n", brightblue, white);
	Sleep(400);
	//Checks mess status
	if (strcmp(inputday, "Sun") == 0)
		ismessopen(7, hours, minutes);
	else if (strcmp(inputday, "Sat") == 0)
		ismessopen(7, hours, minutes);
	else
		ismessopen(5, hours, minutes);

	//checks banjara status
	Sleep(400);
	isbanjaraopen(hours, minutes);

	//checks sports complex status
	Sleep(400);
	printf("\n\n\n%sSPORTS:\n======%s\n", brightblue, white);
	issportscomplexopen(hours, minutes);

	Sleep(800);
	printf("%s\n\nReturn? (y/n): %s%s", brightyellow, white,save);
	while ((int)returnchoice != (int)'y' && (int)returnchoice != (int)'n')
	{
		printf("%s%s", reset,"\033[0K");
		scanf_s("%c", &returnchoice);
	}


	if (returnchoice == 'y')
	{
		system("cls");
		mainscreen();
	}
	else
	showtimings(inputday, inputtime, inputhours, inputminutes);
}