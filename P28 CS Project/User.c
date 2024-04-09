#include "includeheaders.h"


//checks if user exists
 int userexists()
{
	char checkuser[100];
	char checkpassword[100];
	FILE* readfile;
	readfile = fopen("userinfo.txt", "r");
	while (fscanf(readfile, "%s", checkuser) != EOF)
	{
			fscanf(readfile, "%s", checkpassword);
			if (strcmp(username, checkuser) == 0 && strcmp(userpassword, checkpassword) == 0)
				return 1;
	}
}


 //login page
void checklogin()
{
	system("cls");
	printf("\033[10;50HUSERNAME:%s",brightgreen);
	scanf("%s", username);
	printf("%s\033[11;50HPASSWORD:%s%s",white,brightgreen, save);
	printf("%s\033[0K", reset);
	scanf("%s", userpassword);
	printf("%s", white);
	fflush(stdout);
	if (userexists()!= 1)
		checklogin();
}

//checks for password strength conditions
int checkconditions(char password[])
{
	int checklength = 0;
	int capital = 0;
	int special = 0;
	char confirmpassword[30];

	int length = strlen(password);
	if (length >= 6)
		checklength= 1;

	for (int x = 0; x < length; x++)
	{
		if (password[x] >= 65 && password[x] <= 90)
			capital = 1;
		if (password[x] == 33 || password[x] == 38 || password[x] == 35 || password[x] == 36 || password[x] == 37 || password[x] == 42||password[x]==64)
			special = 1;
	}
	if (checklength + capital + special >= 3)
	{
		printf("%s", reset);
		for (int x = 1; x <= length; x++)
		{
			printf("*");
		}
		printf("\033[12;42H%sCONFIRM PASSWORD:%s%s",brightgreen,white save);
		do 
		{
			printf("%s\033[0K%s", reset,brightyellow);
			scanf("%s", confirmpassword);
			printf("%s", white);
		} while (strcmp(password, confirmpassword) != 0);
		return 1;
	}
	else return 0;
}

//checks password strength
void passwordstrength()
{
	int conditions = 0;
	printf("\033[22;53H%sRULES:\033[23;53H=====%s\033[25;30H1.Password length should be greater than 6 letters.\033[26;30H2.Atleast one letter should be capitalized.\033[27;30H3.Atleast one special character should be present(!,@,#,$,%%,^,&,*,)%s",cyan,brightgreen,white);
	printf("\033[11;50HPASSWORD:%s%s", brightyellow,save);
	do
	{
		printf("%s\033[0K", reset);
		scanf("%s", userpassword);
		printf("%s", white);
		conditions = checkconditions(userpassword);
		fflush(stdout);
	} while (conditions != 1);
}


//asks for username and password
void nameandpassword()
{
	system("cls");
	printf("\033[10;50HUSERNAME:%s",brightyellow);
	scanf("%s", username);
	printf("%s", white);
	passwordstrength();
	
	//Writes username and password to file
	FILE *file;
	file = fopen("userinfo.txt", "a");
	fprintf(file, "%s\n%s\n",username, userpassword);
	fclose(file);
}

//asks for gender(ik lmao)
void genderpage()
{
	system("cls");
	printf("%s\033[4;0H     __oBBBBB8o______oBBBBBBB\n     o8BBBBBBBBBBB__BBBBBBBBB8________o\n     BBBBBB**8BBBB__BBBBBBBBBB_____oBBBBB\n     BBBBB*___ ***___BBBBBBBBBB_____BBBBBBBB\n     BBBBBBBooooo___*BBBBBBB8______ * BB * _8B\n     BBBBBBBBBBBBB8ooBBBBBBB8___________8BBBBB\n     BBBBBBBBBBBBBBBBBBBBBBBBBB8_o88BB88BBBBBB\n     * BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n     _ * *8BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n     ______ * BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n     _______ * BBBBBBBBBBBBBBBBBBBBBBBB888\n     ________BBBBBBBBBBBBBBBBBBBBB\n     ________ * BBBBBBBBBBBBBBBBBBB\n     _________ * BBBBBBBBBBBBBBBB",green);
	printf("\033[4;80H_______o888ooo___\033[5;80H____o8888888888888__\033[6;80H___*888888888888888o_\033[7;80H___o8888888888888__8888\033[8;80H__o8888888888888_  88888\033[9;80H___88888888888     88888\033[10;80H______ * 88888    888888\033[11;80H_______888888__\033[12;80H______o888888888\033[13;80H____o888888888888o\033[14;80H___88888888888888888\033[15;80H_o88888888888888888888\033[16;80H8888888888888888888888\033[17;80H* 8888888888888888888888%s",white);
	printf("%s\033[19;24HBOY\033[19;90HGIRL",yellow);
	printf("\033[20;24H===\033[20;90H====%s", white);
	printf("%s\033[22;44HAre you a boy or girl?(b/g):%s%s",magenta,white,save);
	do
	{
		usergender = getchar();
		printf("%s\033[0K", reset);
	} while (usergender != 'b' && usergender != 'g');
}


//shows user portal
void userportal()
{
	system("cls");
	printf("\033[12;55H%sLogin page%s\n",brightgreen,white);
	printf("\033[14;48H1) Press 1 to login\n");
	printf("\033[15;48H2) Press 2 to sign up\033[17;59H%s",save);
	char enterscreen;
	do
	{
		printf("%s\033[0K%s",reset,brightyellow);
		enterscreen = getchar();
		printf("%s", white);
	} while (enterscreen != '1' && enterscreen != '2');

	if (enterscreen == '2')
	{
		genderpage();
		nameandpassword();
	}
	else if (enterscreen == '1')
		checklogin();
}