#include "includeheaders.h"


void load(int progress)
{
	for (int x = 1; x <= progress; x++)
		printf("%s#%s",green,white);
}


void loadingscreen(int seed)
{
	int loading = 0;
	int progress;
	system("cls");
	printf("\033[14;55HLOADING\033[15;43H");
	printf("[%s______________________________]%s", save,reset);
	srand(seed);
	while (loading < 30)
	{
		Sleep(100);
		progress = rand() % 4;
		load(progress);
		loading += progress;
	}
}