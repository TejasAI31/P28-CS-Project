#include "includeheaders.h"


void mainlibrary();

//searches a book
void searchbook()
{
	FILE* searchfile;
	searchfile = fopen("libbooks.txt", "r");
	char booksearcher[40];
	char userbook[40];
	char bookprinter[40];
	int bookfound = 0;
	system("cls");
	printf("\033[10;35HEnter a keyword of the book you wish to search :%s%s",brightgreen,save);
	do
	{
		printf("\033[11;42H(Word length must be greater then 2)");
		printf("%s\033[0K", reset);
		scanf("%s", userbook);
	} while (strlen(userbook) < 3);
	printf("\n\n");


	for (int x = 0; x < strlen(userbook); x++)
	{
		if (userbook[x] >= 65 || userbook[x] <= 90)
			userbook[x] = tolower(userbook[x]);
	}



	while (fscanf(searchfile, "%s", booksearcher) != EOF)
	{
		char enhancedbooksearcher[40];


		for (int x = 0; x < strlen(booksearcher); x++)
		{
			if (booksearcher[x] >= 65 || booksearcher[x] <= 90)
				booksearcher[x] = tolower(booksearcher[x]);
		}
		




		for (int x = 0; x < strlen(userbook); x++)
		{
			enhancedbooksearcher[x] = booksearcher[x];
			enhancedbooksearcher[strlen(userbook)] = '\0';




			if (strcmp(userbook, enhancedbooksearcher) == 0)
			{
				bookfound = 1;
				printf("%s", brightyellow);
				fseek(searchfile, -1, SEEK_CUR);
				while (getc(searchfile) != '.')
				{
					fseek(searchfile, -2, SEEK_CUR);
				}

				while (enhancedbooksearcher[1] != '.' && enhancedbooksearcher[2] != '.' && enhancedbooksearcher[3] != '.')
				{
					fscanf(searchfile, "%s", enhancedbooksearcher);
					if (enhancedbooksearcher[1] == '.' || enhancedbooksearcher[2] == '.' || enhancedbooksearcher[3] == '.')
						break;
					if (enhancedbooksearcher[0] == '-') 
					{
						printf(" %s", magenta);
					}
					printf("%s ", enhancedbooksearcher);
				}
				printf("\n");
				Sleep(100);
			}
		}
	}

	if (bookfound == 0)
	{
		Sleep(200);
		printf("%s\033[15;54HBook Not Found\033[16;54H==============",brightred);
	}

	char replaychoice='c';
	printf("%s\n\n\n\n\033[31Cr->Return to Library, m->Return to Main Screen, t->Try Again: %s",brightgreen, save);
	do
	{
		printf("%s\033[0K", reset);
		scanf("%c", &replaychoice);
	} while (replaychoice != 'r' && replaychoice != 'm' && replaychoice != 't'&&replaychoice != 'R'&& replaychoice != 'M'&& replaychoice != 'T');
	if (replaychoice == 'r'|| replaychoice == 'R')
		mainlibrary();
	else if (replaychoice == 'm'|| replaychoice == 'M')
		mainscreen();
	else if (replaychoice == 't'|| replaychoice =='T')
	{
		printf("%s", cyan);
		searchbook();
	}
}




//displays library
void mainlibrary()
{
	system("cls");
	printf("%s%s\033[0;106H", yellow, yellowbkg);
	for (int x = 1; x <= 30; x++)
	{
		if (x == 5)
		{
			printf("%s%s", yellow, bluebkg);
			printf("\033[1B");
		}
		printf("||          ||\033[14D\033[1B");
		}
	printf("\033[0;106H");
	printf("\033[0;0H");
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
			else if (userchoice == 's')
			{
				fclose(libfile);
				searchbook();
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
	mainlibrary();
}