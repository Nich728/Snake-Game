#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <MMsystem.h>
#include "rungame.h"

#define keyUp 72  //arrow keys
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13

void titleScreen(int *num);
void printmenu(void);

int main(void)
{
  printmenu();
  return 0;
}

void titleScreen(int *num)
{
  int screentitle[12][60] = {{1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1},
                             {1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0},
                             {1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
                             {1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
                             {1,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
                             {0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
                             {0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
                             {0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0},
                             {1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1},
                             {1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1}};


    printf("\e[?25l"); // hide cursor
    COORD cursorPosition; // set cursor ke 0, 0
    cursorPosition.X = 0; // gunanya sebagai alternatif dari clear screen, tapi lebih cepat
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    int status = 0;
    puts(""); // kasih jarak dari pojok atas
    for(int i = 0; i < 12; i++) { // print tulisan hangman
      printf("     ");
      for(int j = 0; j < 60; j++) {
        if(screentitle[i][j]) { // kalau titleScreen[i][j] = 1 --> merupakan bagian text
          status = (j + *num + 5 * i) % 60;
          if((0 <= status && status <= 9) or (50 <= status && status <= 59)) {
            printf("%c", char(176));
          }
          else if((10 <= status && status <= 19) or (40 <= status && status <= 49)) {
            printf("%c", char(177));
          }
          else if((20 <= status && status <= 29) or (30 <= status && status <= 39)) {
            printf("%c", char(178));
          }
          else {
            printf("%c", char(219));
          }
        }
        else printf(" ");
      }
      puts("");
    }

    puts("");
    puts("");
}

void printmenu(void)
{
  int num = 0, currentPos = 0;
  int terminated = 0;
  char key;
  char options[3][12] = {"   Play","LeaderBoard","   Quit"};

  system("CLS"); // Clear Screen
  do
  {
    titleScreen(&num); // Title Screen
    num += 59;

    printf("     ");

    for (int i = 0; i < 60; i++)
    {
      if (i == 59)
      {
        printf("%c", char(187));
      }
      else if (i == 0)
      {
        printf("%c", char(201));
      }
      else
      {
        printf("%c", char(205));
      }
    }

    puts("");

    for (int i = 0; i < 3; i++)
    {
      printf("     ");
      for (int j = 0; j < 60; j++)
      {
        if (j == 0 || j == 59)
        {
          printf("%c", char(186));
        }
        else
        {
          printf(" ");
        }
      }
      puts("");
    }

    for(int i = 0; i < 3; i++) {
			printf("     %c  ", char(186));
      for (int j = 0; j < 15; j++)
      {
        printf(" ");
      }
			if(currentPos == i) printf(">>   ");
			else printf("     ");

			printf("%s", options[i]); // print option
			for(int j = strlen(options[i]); j < 11; j++) printf(" ");

			if(currentPos == i) printf("   <<");
			else printf("     ");
      for (int j = 0; j < 17; j++)
      {
        printf(" ");
      }
			printf("   %c", char(186));
			puts("");

		}

    for (int i = 0; i < 3; i++)
    {
      printf("     ");
      for (int j = 0; j < 60; j++)
      {
        if (j == 0 || j == 59)
        {
          printf("%c", char(186));
        }
        else
        {
          printf(" ");
        }
      }
      puts("");
    }

    printf("     ");

    for (int i = 0; i < 60; i++)
    {
      if (i == 59)
      {
        printf("%c", char(188));
      }
      else if (i == 0)
      {
        printf("%c", char(200));
      }
      else
      {
        printf("%c", char(205));
      }
    }

    if(kbhit())
    {
			key = getch();
			if((key == keyUp or key == keyLeft) && currentPos != 0) currentPos--;
			else if((key == keyDown or key == keyRight) && currentPos != 2) currentPos++;
      else if(key == keyEnter)
      {
        switch(currentPos)
        {
          case 0:
            rungame();
            gameOver();
            break;
          case 1:
            printLeaderBoard();
            break;
          case 2:
            terminated = 1;
            break;
        }
      }
    }
  }
  while (!terminated);
}

void gameOver(void)
{
  int num = 0;
  int currentPos = 0;
  int end = 1;
  char key;
  char options[2][10] = {"Try Again", "Main Menu"};
  system("CLS");
  do
  {
    endTitle(&num);
    num += 68;
    printf("     ");

    for (int i = 0; i < 60; i++)
    {
      if (i == 59)
      {
        printf("%c", char(187));
      }
      else if (i == 0)
      {
        printf("%c", char(201));
      }
      else
      {
        printf("%c", char(205));
      }
    }

    puts("");

    for (int i = 0; i < 3; i++)
    {
      printf("     ");
      for (int j = 0; j < 60; j++)
      {
        if (j == 0 || j == 59)
        {
          printf("%c", char(186));
        }
        else
        {
          printf(" ");
        }
      }
      puts("");
    }

    for(int i = 0; i < 2; i++) {
			printf("     %c  ", char(186));
      for (int j = 0; j < 15; j++)
      {
        printf(" ");
      }
			if(currentPos == i) printf(">>   ");
			else printf("     ");

			printf("%s", options[i]); // print option
			for(int j = strlen(options[i]); j < 9; j++) printf(" ");

			if(currentPos == i) printf("   <<");
			else printf("     ");
      for (int j = 0; j < 19; j++)
      {
        printf(" ");
      }
			printf("   %c", char(186));
			puts("");

		}

    for (int i = 0; i < 3; i++)
    {
      printf("     ");
      for (int j = 0; j < 60; j++)
      {
        if (j == 0 || j == 59)
        {
          printf("%c", char(186));
        }
        else
        {
          printf(" ");
        }
      }
      puts("");
    }

    printf("     ");

    for (int i = 0; i < 60; i++)
    {
      if (i == 59)
      {
        printf("%c", char(188));
      }
      else if (i == 0)
      {
        printf("%c", char(200));
      }
      else
      {
        printf("%c", char(205));
      }
    }

    if(kbhit())
    {
			key = getch();
			if((key == keyUp or key == keyLeft) && currentPos != 0) currentPos--;
			else if((key == keyDown or key == keyRight) && currentPos != 1) currentPos++;
      else if(key == keyEnter)
      {
        switch(currentPos)
        {
          case 0:
            rungame();
            gameOver();
            end = 0;
            break;
          case 1:
            end = 0;
            system("CLS");
            break;
        }
      }
    }
  }
  while(end);
}
