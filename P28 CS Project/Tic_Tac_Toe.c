#include "includeheaders.h"

int currentposition = 1;


void drawtictac()
{
	system("cls");
	printf("    |    |    \n    |    |    \n    |    |    \n====|====|====\n    |    |    \n    |    |    \n    |    |    \n====|====|====\n    |    |    \n    |    |    \n    |    |    \n");
	printf("\n%sRULES:%s\n1. W or w=>Up\n2.A or a=>Left\n3.D or d=>Right\n4.S or s=>Down%s\n",brightred,brightgreen,white);
	printf("\n%sEnter an input:%s%s", brightblue, white, save);
}



void shiftbkg(int position)
{
	switch (position)
	{
	case 1:printf("\033[0;1H");
		break;
	case 2:printf("\033[0;6H");
		break;
	case 3:printf("\033[0;11H");
		break;
	case 4:printf("\033[5;1H");
		break;
	case 5:printf("\033[5;6H");
		break;
	case 6:printf("\033[5;11H");
		break;
	case 7:printf("\033[9;1H");
		break;
	case 8:printf("\033[9;6H");
		break;
	case 9:printf("\033[9;11H");
		break;
	}
	printf("%s    \033[1B\033[4D    \033[1B\033[4D    ", magentabkg);
}




void placetoken()
{


}






//Shifts Position based on user input
void shiftpos(char input)
{
	if (input == 'w' || input == 'W')
	{
		if (currentposition >= 3)
			currentposition -= 3;
		return;
	}
	if (input == 'a' || input == 'A')
	{
		if (currentposition % 3 != 1)
			currentposition -= 1;
		return;
	}
	if (input == 's' || input == 'S')
	{
		if (currentposition <= 6)
			currentposition += 3;
		return;
	}
	if (input == 'd' || input == 'D')
	{
		if (currentposition % 3 != 0)
			currentposition += 1;
	}
	if (input == 'e' || input == 'E')
	{
		placetoken();
	}
}



//Play Tic Tac Toe
void tictactoe()
{
	int positions[3][3] = { 1,2,3,4,5,6,7,8,9 };
	char userinput;
	int movescounter = 0; 
	drawtictac();
	do
	{
		do 
		{
			printf("%s\033[0K",reset);
			userinput = getchar();
		} while (userinput!='a'&&userinput!='A'&&userinput != 'w'&& userinput != 'W'&& userinput != 's'&& userinput != 'S'&& userinput != 'd'&& userinput != 'D'&&userinput!='e'&&userinput!='E');
		shiftpos(userinput);
		drawtictac();
		shiftbkg(currentposition);
	} while (userinput != 'x'&&userinput!='X');
}