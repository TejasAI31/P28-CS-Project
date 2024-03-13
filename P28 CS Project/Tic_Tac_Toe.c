#include "includeheaders.h"

int currentposition = 1;
int boardstate[] = { 0,0,0,0,0,0,0,0,0 };

//Draws 0's in previous game state
void draw0(int pos)
{
	switch (pos)
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
	printf("%s%s == \033[1B\033[4D|  |\033[1B\033[4D == %s%s%s", brightyellow, greenbkg, white, defaultbkg,reset);
}



//Restores the previous game state
void restorepreviousboardstate()
{
	for (int x = 0; x < 9; x++)
	{
		if (boardstate[x] == 1)
		{
			draw0(x+1);
		}
	}
}





//Draws the tic tac toe table
void drawtictac()
{
	system("cls");
	printf("    |    |    \n    |    |    \n    |    |    \n====|====|====\n    |    |    \n    |    |    \n    |    |    \n====|====|====\n    |    |    \n    |    |    \n    |    |    \n%s",save);
	restorepreviousboardstate(); 
	printf("\n%sRULES:%s\n1.W or w=>Up\n2.A or a=>Left\n3.D or d=>Right\n4.S or s=>Down%s\n", brightred, brightgreen, white);
	printf("\n%sEnter an input:%s%s", brightblue, white, save);
}



//Places the user's token

void placetoken()
{
	printf("%s%s\033[2A\033[4D == \033[1B\033[4D|  |\033[1B\033[4D == %s%s", brightyellow,greenbkg, white,defaultbkg);
	boardstate[currentposition - 1] = 1;
}


//Shifts the Green Background
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
	printf("%s    \033[1B\033[4D    \033[1B\033[4D    ", greenbkg);
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
}



//Play Tic Tac Toe
void tictactoe()
{
	int positions[3][3] = { 1,2,3,4,5,6,7,8,9 };
	char userinput;
	drawtictac();
	do
	{
		do 
		{
			printf("%s\033[0K",reset);
			userinput = getchar();
		} while (userinput!='x'&&userinput!='X'&&userinput != 'a' && userinput != 'A' && userinput != 'w' && userinput != 'W' && userinput != 's' && userinput != 'S' && userinput != 'd' && userinput != 'D' && userinput != 'e' && userinput != 'E');
		
		
		if (userinput == 'x' || userinput == 'X')
			break;


		drawtictac();
		shiftpos(userinput);
		shiftbkg(currentposition);


		if (userinput == 'e' || userinput == 'E')
			placetoken();


	} while (userinput != 'x'&&userinput!='X');

	//Resets board state
	for (int x = 0; x < 9; x++)
		boardstate[x] = 0;

	//Returns to mainscreen
	mainscreen();
}