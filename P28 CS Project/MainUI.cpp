#include <stdio.h>
#include <stdlib.h>

//shows the main hub
void mainscreen()
{
	int n;
	printf("\033[0;34m");
	printf("					----------------------\n");
	printf("					|Welcome to IIT Patna|\n");
	printf("					----------------------\n");
	printf("\033[0;32m");
	printf("\n\nWhat do you wish to do?\n");
	printf("-----------------------\n");
	scanf_s("%d", &n);
	system("cls");
}



int main(void)
{
	mainscreen();
}