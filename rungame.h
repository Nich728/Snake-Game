#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <MMsystem.h>
#include "highscore.h"

#define N 25
#define M 50

#define keyUp 72  //arrow keys
#define keyDown 80
#define keyLeft 75
#define keyRight 77
#define keyEnter 13

void gameOver(void);

int Field[N][M], x, y, Gy, Head, Tail, frog, frogX, frogY, Game, score, highScore;
char key = keyRight, dir;

void instruction(void)
{
  for(int i = 0; i <= M + 1; i++){
    if(i == 0){
      printf("%c", 201);
    }
    else if(i == M + 1){
      printf("%c", 187);
    }
    else{
      printf("%c", 205);
    }
  }

  puts("");

  for (int i = 0; i < N; i++)
  {
    printf("%c", char(186));
    if (i == 8)
      printf("             ===== How To Play =====              ");
    else if (i == 9)
      printf("      1. Use the arrow keys on your keyboard      ");
    else if (i == 10)
      printf("           to control the snake's movement        ");
    else if (i == 11)
      printf("      2. A frog will increment your score by 1    ");
    else if (i == 12)
      printf("      3. Frogs will spawn randomly on the map     ");
    else if (i == 13)
      printf("      4. Be careful not to touch the walls        ");
    else if (i == 14)
      printf("      5. Be careful not to eat yourself too       ");
    else if (i == 16)
      printf("              Good Luck And Have Fun              ");
    else if (i == 17)
      printf("            Press Enter To Continue . . .         ");
    else
      printf("                                                  ");
    printf("%c\n", char(186));
  }

  for(int i = 0; i <= M + 1; i++){
    if(i == 0){
      printf("%c", 200);
    }
    else if(i == M + 1){
      printf("%c", 188);
    }
    else{
      printf("%c", 205);
    }
  }
  getchar();
}

void initialSnake(void)
{
  Game = 0;
  for (int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      Field[i][j] = 0;
    }
  }

  x = N / 2; y = M / 2; Gy = y; Head = 5; Tail = 1; frog = 0; score = 0;

  for(int i = 0; i < Head; i++){
    Gy++;
    Field[x][Gy - Head] = i + 1;
  }
}

void printMap(void)
{
  for(int i = 0; i <= M + 1; i++){
    if(i == 0){
      printf("%c", 201);
    }
    else if(i == M + 1){
      printf("%c", 187);
    }
    else{
      printf("%c", 205);
    }
  }

  printf("Current Score: %d", score);
  printf("\n");

  for(int i = 0; i < N; i++){
    printf("%c", 186);

    for(int j = 0; j < M; j++){
      if(Field[i][j] == 0) printf(" ");
      if(Field[i][j] > 0 && Field[i][j] != Head) printf("%c", 176);
      if(Field[i][j] == Head) printf("%c", 219);
      if(Field[i][j] == -1)printf("%c", 234);
      if(j == M - 1)printf("%c\n", 186);
    }
  }


  for(int i = 0; i <= M + 1; i++){
    if(i == 0){
      printf("%c", 200);
    }
    else if(i == M + 1){
      printf("%c", 188);
    }
    else{
      printf("%c", 205);
    }
  }
}

void frogRandom(){
 	srand(time(0));
	frogX = 1 + rand() % 23;
 	frogY = 1 + rand() % 48;


 	if(frog == 0 && Field[frogX][frogY] == 0){
 		Field[frogX][frogY] = -1;
 		frog = 1;
	 }
}

void snakeMovement(void) {
	if (kbhit()) {
		key = getch();
	}
	if ((key == keyUp && dir != keyDown) || (key == keyRight && dir != keyLeft) || (key == keyDown && dir != keyUp) || (key == keyLeft && dir != keyRight)) {
			dir = key;
	}
	if (dir == keyUp) { // move up
		x--; // barisnya kurang 1 jdi naik 1
		if(x==0 || Field[x][y] > 0) {
			Game=1; //nabrak tembok mati
			key = keyRight;
			PlaySound(TEXT(".\\game over.wav"),NULL,SND_ASYNC);
		}
		else if (Field[x][y] == -1){  // kalo snake makan frog, frog=0
			PlaySound(TEXT(".\\get points.wav"),NULL,SND_ASYNC);
			frog = 0;
			score++;
			Tail -= 2; // pertambahan panjang pada tail
		}
		Head++;
		Field[x][y] = Head;
	}
	else if (dir == keyDown) { // move down
		x++; // barisnya tambah 1 jdi turun 1
		if(x==N || Field[x][y] > 0) {
			Game=1; //nabrak tembok mati
			key = keyRight;
			PlaySound(TEXT(".\\game over.wav"),NULL,SND_ASYNC);
		}
		else if (Field[x][y] == -1){
			PlaySound(TEXT(".\\get points.wav"),NULL,SND_ASYNC);
			frog = 0;
			score++;
			Tail -= 2;
		}
		Head++;
		Field[x][y] = Head;
	}
	else if (dir == keyRight) { // move right
		y++; // kolomnya tambah 1 jdi kanan 1
		if(y==M-1 || Field[x][y] > 0) {
			Game=1;//nabrak tembok mati
			key = keyRight;
			PlaySound(TEXT(".\\game over.wav"),NULL,SND_ASYNC);
		}
		else if
		(Field[x][y] == -1){
			PlaySound(TEXT(".\\get points.wav"),NULL,SND_ASYNC);
			frog = 0;
			score++;
			Tail -= 2;
		}
		Head++;
		Field[x][y] = Head;
	}
	else if (dir == keyLeft) { // move left
		y--; // kolomnya kurang 1 jdi kiri 1
		if (y==0 || Field[x][y] > 0) {
			Game=1;//nabrak tembok mati
			dir = keyRight;
			PlaySound(TEXT(".\\game over.wav"),NULL,SND_ASYNC);
		}
		else if (Field[x][y] == -1){
			PlaySound(TEXT(".\\get points.wav"),NULL,SND_ASYNC);
			frog = 0;
			score++;
			Tail -= 2;
		}
		Head++;
		Field[x][y] = Head;
	}
}

void tailRemove(){
	for(int i=0 ; i<N ; i++){
		for(int j=0;j<M;j++){
			if(Field[i][j]==Tail){
				Field[i][j]= 0;
			}
		}
	}
	Tail++;
}

void resetScreenPosition(void)
{
  printf("\e[?25l"); // hide cursor
  COORD cursorPosition; // set cursor ke 0, 0
  cursorPosition.X = 0; // gunanya sebagai alternatif dari clear screen, tapi lebih cepat
  cursorPosition.Y = 0;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void endTitle(int *num)
{
  char gameEnd[7][69] = {{0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0},
                         {0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
                         {0,1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,1,1,1,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
                         {0,1,1,0,1,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0},
                         {0,1,1,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0},
                         {0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0},
                         {0,1,1,1,1,1,1,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,1,0,0,0}};

  resetScreenPosition();
  int status = 0;
  puts(""); // kasih jarak dari pojok atas
  for(int i = 0; i < 7; i++) { // print tulisan hangman
    printf("     ");
    for(int j = 0; j < 69; j++) {
      if(gameEnd[i][j]) { // kalau titleScreen[i][j] = 1 --> merupakan bagian text
        status = (j + *num + 10 * i) % 69;
        if((0 <= status and status <= 9) or (60 <= status and status <= 69)) {
          printf("%c", char(176));
        }
        else if((10 <= status and status <= 19) or (50 <= status and status <= 59)) {
          printf("%c", char(177));
        }
        else if((20 <= status and status <= 29) or (40 <= status and status <= 49)) {
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

void rungame(void)
{
  system ("CLS");
  initialSnake();
  instruction();
  PlaySound(TEXT(".\\start.wav"),NULL,SND_ASYNC);
  while (Game == 0)
  {
	resetScreenPosition();
    frogRandom();
    snakeMovement();
    tailRemove();
    printMap();
    usleep(42000);
  }
  inputUserName(score);
}
