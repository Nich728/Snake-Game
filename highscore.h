#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char name[20];
	int score;
}highscore;

highscore leaderboard[100];
int Idx;

void swap(highscore *a, highscore *b) {
	highscore temp = *a;
	*a = *b;
	*b = temp;
}

void listNameAndScore() {
	FILE *fp;
	fp = fopen("highscore_name_score.txt", "r");

	Idx = 0;
	while(fscanf(fp, "%s %d", leaderboard[Idx].name, &leaderboard[Idx].score) != EOF) {
		Idx++;
	}

	fclose(fp);
}

void processScore(highscore a) {
	FILE *fp;

	listNameAndScore();
	leaderboard[Idx] = a;

	for(int i = 1; i < Idx + 1; i++) {
		for(int j = 1; j < Idx + 1; j++) {
			if(leaderboard[j].score > leaderboard[j - 1].score) {
				swap(&leaderboard[j - 1], &leaderboard[j]);
			}
		}
	}

	fp = fopen("highscore_name_score.txt", "w");

	for(int i = 0; i < Idx + 1; i++) {
		fprintf(fp, "%s  %d\n", leaderboard[i].name, leaderboard[i].score);
	}

	fclose(fp);
}

void printLeaderBoard()
{
	listNameAndScore();
	system("CLS");
	for(int i = 0; i < 29; i++)
	{
	   	if(i == 0){
	     	printf("%c", 201);
	   	}
	   	else if(i == 28){
	     	printf("%c", 187);
	   	}
	   	else{
	     	printf("%c", 205);
	  	}
	}
	puts("");

	for (int i = 0; i < 6; i++)
	{
		printf("%c", char(186));
		if (i == 0)
			printf("  ===== LeaderBoard =====  ");
		if (i > 0 && i < 6)
		{
			for (int j = 0; j < 26; j++)
			{
				int n = strlen(leaderboard[i - 1].name);
				if (j == 1)
					printf("%d. ", i);
				else if (j == 2)
					printf("%s", leaderboard[i - 1].name);
				else if (j == 23)
					printf("%03d  ", leaderboard[i - 1].score);
				else if (j < 21 - n)
					printf(" ");
			}
		}
		printf("%c", char(186));
		puts("");
	}

	for(int i = 0; i < 29; i++)
	{
	   	if(i == 0){
	     	printf("%c", 200);
	   	}
	   	else if(i == 28){
	     	printf("%c", 188);
	   	}
	   	else{
	     	printf("%c", 205);
	  	}
	}
	printf("\nPress Enter to go back to Main menu...\n");
	getchar();
	system("CLS");
}

void inputUserName(int score) {
		char username[20];
		int len;
		do 
		{
			printf("\nPlease input username (2 - 15 characters) : ");
			scanf("%s", username);
			getchar();
			len = strlen(username);

			if(len < 2 || len > 15) {
				printf("Please Try Again!\n");
			}
		}
		while(len < 2 || len > 15);

		highscore player;
		strcpy(player.name,username);
		player.score = score;
		processScore(player);
	}
