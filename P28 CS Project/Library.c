#include "includeheaders.h"



void mainlibrary()
{
	system("cls");
	FILE* libfile;
	libfile = fopen("libbooks.txt", "r");
	char book[100];
	printf("\033[2;50H%sAvailable Books:\033[3;50H===============\n\n\n%s", brightgreen, white);
	int counter = 1;
	int bookcounter =1;
	while (bookcounter!=546)
	{
		fscanf(libfile, "%s", book);
		for (int x = 0; x <= 9; x++)
		{
			if (book[0] == 49+x)
				if (book[1] == '.' || book[2] == '.' || book[3] == '.' || book[4] == '.')
				{
					printf("\n\n%s",brightyellow);
					bookcounter += 1;
				}
		}

		if (bookcounter % 12 == 0)
		{
			char userchoice;
			do
			{
				printf("\033[5;2H%sEnter Choice: %s\033[0K", cyan,save);
				printf("%s       ('n'->Next Page, 's'->Search book, 'r'->Return to Mainscreen)\n%s ============%s",blue,brightred,reset);
				userchoice = getchar();
			} while (userchoice != 'n' && userchoice != 's' && userchoice != 'r');
			if (userchoice == 'n')
			{
				system("cls");
				printf("\033[2;50H%sAvailable Books:\033[3;50H===============\n\n\n\n\n%s", brightgreen, brightyellow);
				bookcounter += 1;
			}
			else if (userchoice == 'r')
			{
				fclose(libfile);
				mainscreen();
			}
		}

		if (bookcounter != 546)
		{
			if (book[0] == '-')
				printf("  %s", magenta);
			printf(" %s", book);
		}
		counter++;

	}
}