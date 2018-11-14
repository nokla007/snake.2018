#include "stdafx.h"

#define width  610
#define height 640
#define border  5
#define scrboard  30

int spd = 65;
int len = 5;
int direction = 2;		// 0=right	1=up	2=left	3=down //

int foodx, foody;	//food coordinate.
int foodcnt = 1;	//counting food.

bool playing = false;
bool played = false;

typedef struct block{
	int dx;
	int dy;
};
block snake[5000];

int colors[][3] = {
	{ 255, 51, 51 }, { 255, 255, 77 }, { 136, 77, 255 }, { 0, 235, 171 }, { 51, 132, 255 }, { 0, 255, 85 }, { 255, 175, 51 }
};	//colorset for foods and snake.

int size = 20;
int i , j , k;		
int t;		//timer variable.
int score = 0;	//scorecount.

char scor[10];	//score string.

int state = 0;	//game state.
/*
0=main menu
1=classic game
2=game over page
3=pause menu
4=high score
*/

char button[9][100] = {
	"pics\\buttons\\a.bmp",
	"pics\\buttons\\b.bmp",
	"pics\\buttons\\c.bmp",
	"pics\\buttons\\d.bmp",
	"pics\\buttons\\e.bmp",
	"pics\\buttons\\f.bmp",
	"pics\\buttons\\g.bmp",
	"pics\\buttons\\h.bmp"
};		//buttons in main menu.

char button2[5][100] = {
	"pics\\over buttons\\a.bmp",
	"pics\\over buttons\\b.bmp",
	"pics\\over buttons\\c.bmp",
	"pics\\over buttons\\d.bmp",
};

int buttonx = 300;
int buttony[4] = { 350, 250, 150, 50 };
int hover = 1;

FILE *high;
int hs[6];
int write=0;

char scores[6][20];

bool paused = false;
