#include "includeheaders.h"

int currentposition = 1;
int boardstate[] = {0,0,0,0,0,0,0,0,0};
int checkboardstate=0;



//checks bot victory condition
int checkbotvictory()
{
	//Checks rows for user victory
	if (boardstate[0] == 4 && boardstate[1] == 4 && boardstate[2] == 4 || boardstate[3] == 4 && boardstate[4] == 4 && boardstate[5] == 4 || boardstate[6] == 4 && boardstate[7] == 4 && boardstate[8] == 4)
	{
		printf("\n\033[23;0HBot Wins\n");
		printf("========");
		return 1;
	}

	//Checks columns for user victory
	if (boardstate[0] == 4 && boardstate[3] == 4 && boardstate[6] == 4 || boardstate[1] == 4 && boardstate[4] == 4 && boardstate[7] == 4 || boardstate[2] == 4 && boardstate[5] == 4 && boardstate[8] == 4)
	{
		printf("\n\033[23;0HBot Wins\n");
		printf("========");
		return 1;
	}

	//Checks columns for user victory
	if (boardstate[0] == 4 && boardstate[4] == 4 && boardstate[8] == 4 || boardstate[2] == 4 && boardstate[4] == 4 && boardstate[6] == 4)
	{
		printf("\n\033[23;0HBot Wins\n");
		printf("========");
		return 1;
	}

}



//checks if board is full
void isboardfull()
{
	int counter = 0;
	for (int x = 0; x < 9; x++)
	{
		if (boardstate[x] == 1 || boardstate[x] == 4)
			counter += 1;
	}
	if (counter == 9)
		checkboardstate = 1;
}

//Draws X
void drawX(int pos)
{
	switch (pos)
	{
	case 0:printf("\033[0;1H");
		break;
	case 1:printf("\033[0;6H");
		break;
	case 2:printf("\033[0;11H");
		break;
	case 3:printf("\033[5;1H");
		break;
	case 4:printf("\033[5;6H");
		break;
	case 5:printf("\033[5;11H");
		break;
	case 6:printf("\033[9;1H");
		break;
	case 7:printf("\033[9;6H");
		break;
	case 8:printf("\033[9;11H");
		break;
	}
	printf("%s%s*  *\033[1B\033[4D ** \033[1B\033[4D*  *%s%s%s", brightyellow, greenbkg, white, defaultbkg, reset);
	
}


//Opponent turn
void opponentturn()
{


	for (int x = 0; x <= 2; x++)
	{
		if(boardstate[x]+boardstate[x+3]+boardstate[x+6]==8)
		{ 
			if (boardstate[x] == 0)
			{
				drawX(x);
				boardstate[x] = 4;
				return;
			}
			else if (boardstate[x + 3] == 0)
			{
				drawX(x + 3);
				boardstate[x+3] = 4;
				return;
			}
			else if (boardstate[x + 6] == 0)
			{
				drawX(x + 6);
				boardstate[x+6] = 4;
				return;
			}
		}
	}


	for (int x = 0; x <= 6; x += 3)
	{
		if (boardstate[x] + boardstate[x + 1] + boardstate[x + 2] == 8)
		{
			if (boardstate[x] == 0)
			{
				drawX(x);
				boardstate[x] = 4;
				return;
			}
			else if (boardstate[x + 1] == 0)
			{
				drawX(x + 1);
				boardstate[x + 1] = 4;
				return;
			}
			else if (boardstate[x + 2] == 0)
			{
				drawX(x + 2);
				boardstate[x + 2] = 4; 
				return;
			}
		}

	}

		if (boardstate[0] + boardstate[4] + boardstate[8] == 8)
		{
			if (boardstate[0] == 0)
			{
				drawX(0);
				boardstate[0] = 4;
				return;
			}
			else if (boardstate[4] == 0)
			{
				drawX(4);
				boardstate[4] = 4;
				return;
			}
			else if (boardstate[8] == 0)
			{
				drawX(8);
				boardstate[8] = 4;
				return;
			}
		}

		if (boardstate[2] + boardstate[4] + boardstate[6] == 8)
		{
			if (boardstate[2] == 0)
			{
				drawX(2);
				boardstate[2] = 4;
				return;
			}
			else if (boardstate[4] == 0)
			{
				drawX(4);
				boardstate[4] = 4;
				return;
			}
			else if (boardstate[6] == 0)
			{
				drawX(6);
				boardstate[6] = 4;
				return;
			}
		}

		for (int x = 0; x <= 2; x++)
		{
			if (boardstate[x] + boardstate[x + 3] + boardstate[x + 6] == 2)
		 {
			if (boardstate[x] == 0)
			{
				drawX(x);
				boardstate[x] = 4;
				return;
			}
			else if (boardstate[x + 3] == 0)
			{
				drawX(x + 3);
				boardstate[x + 3] = 4;
				return;
			}
			else if (boardstate[x + 6] == 0)
			{
				drawX(x + 6);
				boardstate[x + 6] = 4;
				return;
			}
		 } 
		}

		for (int x = 0; x <= 6; x += 3)
		{
		 if (boardstate[x] + boardstate[x + 1] + boardstate[x + 2] == 2)
		 {
			if (boardstate[x] == 0)
			{
				drawX(x);
				boardstate[x] = 4;
				return;
			}
			else if (boardstate[x + 1] == 0)
			{
				drawX(x + 1);
				boardstate[x + 1] = 4;
				return;
			}
			else if (boardstate[x + 2] == 0)
			{
				drawX(x + 2);
				boardstate[x + 2] = 4;
				return;
			}
		 }
		}


		if (boardstate[0] + boardstate[4] + boardstate[8] == 2)
		{
			if (boardstate[0] == 0)
			{
				drawX(0);
				boardstate[0] = 4;
				return;
			}
			else if (boardstate[4] == 0)
			{
				drawX(4);
				boardstate[4] = 4;
				return;
			}
			else if (boardstate[8] == 0)
			{
				drawX(8);
				boardstate[8] = 4;
				return;
			}
		}

		if (boardstate[2] + boardstate[4] + boardstate[6] == 2)
		{
			if (boardstate[2] == 0)
			{
				drawX(2);
				boardstate[2] = 4;
				return;
			}
			else if (boardstate[4] == 0)
			{
				drawX(4);
				boardstate[4] = 4;
				return;
			}
			else if (boardstate[6] == 0)
			{
				drawX(6);
				boardstate[6] = 4;
				return;
			}
		}

		int random =(int)rand() % 8;
		while (boardstate[random] != 0)
		{
			random =(int)rand() % 8;
		}
		drawX(random);
		boardstate[random] = 4;

}



int checkuservictory()
{
	//Checks rows for user victory
	if (boardstate[0] == 1 && boardstate[1] == 1 && boardstate[2] == 1 || boardstate[3] == 1 && boardstate[4] == 1 && boardstate[5] == 1 || boardstate[6] == 1 && boardstate[7] == 1 && boardstate[8] == 1)
	{
		printf("\n\033[23;0HUser Wins\n");
		printf("=========");
		return 1;
	}

	//Checks columns for user victory
	if (boardstate[0] == 1 && boardstate[3] == 1 && boardstate[6] == 1 || boardstate[1] == 1 && boardstate[4] == 1 && boardstate[7] == 1 || boardstate[2] == 1 && boardstate[5] == 1 && boardstate[8] == 1)
	{
		printf("\n\033[23;0HUser Wins\n");
		printf("=========");
		return 1;
	}

	//Checks columns for user victory
	if (boardstate[0] == 1 && boardstate[4] == 1 && boardstate[8] == 1 || boardstate[2] == 1 && boardstate[4] == 1 && boardstate[6] == 1)
	{
		printf("\n\033[23;0HUser Wins\n");
		printf("=========");
		return 1;
	}
	
}





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
		if (boardstate[x] == 4)
		{
			drawX(x);
		}
	}
}





//Draws the tic tac toe table
void drawtictac()
{
	system("cls");
	printf("    |    |    \n    |    |    \n    |    |    \n====|====|====\n    |    |    \n    |    |    \n    |    |    \n====|====|====\n    |    |    \n    |    |    \n    |    |    \n%s",save);
	restorepreviousboardstate(); 
	printf("\n%sRULES:%s\n1.W or w=>Up\n2.A or a=>Left\n3.D or d=>Right\n4.S or s=>Down\n5.E or e=>Place 0\n6.X or x=>End Game%s\n", brightred, brightgreen, white);
	printf("\n%sEnter an input sequence:%s%s", brightblue, white, save);
}



//Places the user's token

void placetoken()
{
	printf("%s%s\033[2A\033[4D == \033[1B\033[4D|  |\033[1B\033[4D == %s%s", brightyellow,greenbkg, white,defaultbkg);
	boardstate[currentposition-1] = 1;
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
		if (currentposition >= 4)
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
	//Resets board state
	for (int y = 0; y < 9; y++)
		boardstate[y] = 0;


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


		if (userinput == 'e'&&boardstate[currentposition-1]==0 || userinput == 'E' && boardstate[currentposition - 1] == 0)
		{
			draw0(currentposition);
			boardstate[currentposition-1] = 1;
			if (checkuservictory() == 1)
				break;
			else
			{
				isboardfull();
				if (checkboardstate == 1)
				{
					checkboardstate = 0;
					break;
				}
				else
				{
					Sleep(500);
					opponentturn();
					if (checkbotvictory() == 1)
						break;
				}
			}
		}



	} while (userinput != 'x'&&userinput!='X');


	char returnchoice = 'm';
	printf("\033[26;0H%sWould you like to play again?(y/n):%s%s",brightyellow,white,save);
	while ((int)returnchoice != (int)'y' && (int)returnchoice != (int)'n')
	{
		printf("%s%s", reset, "\033[0K");
		scanf_s("%c", &returnchoice);
	}
	if (returnchoice == 'y')
	{
		tictactoe();
	}
	else
		mainscreen();

}