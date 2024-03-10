#include <stdio.h>
#include <stdlib.h>
#include "altscreen.h"
#include "colors.h"
#include "Cursorposition.h"

//shows the main hub
void mainscreen()
{
	int n;
	printf("%s					----------------------\n",blue);
	printf("					|Welcome to IIT Patna|\n");
	printf("					----------------------\n%s",white);
	printf("%s\n\nWhat do you wish to do?\n%s",green,white);
	printf("%s-----------------------\n%s",green,white);
	scanf_s("%d", &n);
	system("cls");
	printf("\033[1;0");
	printf("%s					----------------------\n", green);
	printf("					|Welcome to IIT Patna|\n");
	printf("					----------------------\n%s", white);
	printf("%s\n\nWhat do you wish to do?\n%s", green, white);
	printf("%s-----------------------\n%s", green, white);
	printf("Successful");
}



int main(void)
{
	mainscreen();
}