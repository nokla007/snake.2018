
#include "stdafx.h"
# include "iGraphics.h"
#include "variable.h"

void menu()
{
	hover = 1;
	state = 0;

}


void restart()
{
	playing = true;
	state = 1;
	score = 0;
	direction = 2;
	len = 5;
	for (i = 0; i < len; i++)
	{
		snake[i].dx = 305 + i*size;
		snake[i].dy = 305;
	}
	iResumeTimer(t);

}	

void highScore()
{
	fopen_s(&high, "high.txt", "w+");
	for (j = 0; j < 5; j++)
	{
		if (score > hs[j])
		{
			
			for (k = 4; k >j; k--)
			{
				hs[k] = hs[k-1];
			}
			hs[j] = score;
			break;
		}
	}

	for (j = 0; j < 5; j++)
		fprintf_s(high, "%d\n", hs[j]);
	fclose(high);
	played = false;
}

void over()
{
	hover = 0;
	playing = false;
	state = 2;
	if (played)
		highScore();

}


void move()
{


	for (i = len - 1; i >0; i--)
	{
		snake[i].dx = snake[i - 1].dx;
		snake[i].dy = snake[i - 1].dy;
	}

	if (direction == 0)
		snake[0].dx += size;
	if (direction == 1)
		snake[0].dy -= size;
	if (direction == 2)
		snake[0].dx -= size;
	if (direction == 3)
		snake[0].dy += size;

	if (snake[0].dx < border)
		snake[0].dx = width - border - size;
	if (snake[0].dx > width - border - size)
		snake[0].dx = border;
	if (snake[0].dy < border)
		snake[0].dy = height - border - size - scrboard;
	if (snake[0].dy > height - border - size - scrboard)
		snake[0].dy = border;


}

void colision()
{
	for (i = len - 1; i > 3; i--)
	{
		if (snake[i].dx == snake[0].dx && snake[i].dy == snake[0].dy)
		{
			iPauseTimer(t);
			played = true;
			if (playing)
				over();
			break;
		}
	}
}


void generateFood()
{
	foodx = 5 + (size * rand()) % 600;
	foody = 5 + (size * rand()) % 600;

	for (j = 1; j < len; j++)
	{
		if (foodx == snake[j].dx && foody == snake[j].dy)
			generateFood();
	}
}

void foodEat()
{
	if (snake[0].dx == foodx && snake[0].dy == foody)		//check food and score increment 
	{
		generateFood();
		score += (8 + rand() % 5);
		len++;
		foodcnt++;
		snake[len - 1].dx = snake[len - 2].dx;
		snake[len - 1].dy = snake[len - 2].dy;
	}
}





void game()		//game drawing function
{
	iSetColor(0, 100, 100);
	iFilledRectangle(0, 0, width, height);

	iSetColor(38, 38, 38);	//playzone
	iFilledRectangle(border, border, width - 2 * border, height - 2 * border - scrboard);

	iSetColor(colors[foodcnt % 7][0], colors[foodcnt % 7][1], colors[foodcnt % 7][2]);
		//food drawing
	iFilledRectangle(foodx, foody, size, size);



	iSetColor(colors[(foodcnt - 1) % 7][0], colors[(foodcnt - 1) % 7][1], colors[(foodcnt - 1) % 7][2]);		//print snake
	for (i = 0; i < len; i++)
	{
		iFilledRectangle(snake[i].dx, snake[i].dy, size, size);

	}

	iSetColor(195, 195, 225);		//printing the score
	sprintf_s(scor, "%4d", score);
	iText(width - 50, height - 25, scor, GLUT_BITMAP_HELVETICA_18);
	
}

void gameOver()		//game over page drawing.
{
	
	iSetColor(38, 38, 38);
	iFilledRectangle(0, 0, width, height);
	iShowBMP2(0, 44, "pics\\over.bmp", 38);
	iSetColor(180, 194, 223);
	sprintf_s(scor, "%d", score);
	iText(135, 113, scor, GLUT_BITMAP_TIMES_ROMAN_24);
	
	for (i = 0; i < 2; i++)
	{
		if (hover == i)
			iShowBMP(buttonx, buttony[i + 2], button2[i + 2]);
		else
			iShowBMP(buttonx, buttony[i + 2], button2[i]);
	}
}

void highScorr()
{
	iShowBMP(0, 0, "pics//hiscore.bmp");
	for (j = 0; j < 5; j++)
	{
		sprintf_s(scores[j], "1. %d", hs[j]);
	}
	int pos = 100;
	for (j = 4; j >= 0; j--)
	{
		iText(250, pos, scores[j], GLUT_BITMAP_TIMES_ROMAN_24);
		pos += 40;
	}
}

void menuDraw()
{
	iShowBMP(0, 0, "pics/main.bmp");

	for (i = 1; i < 4; i++)
	{
		if (hover==i)
			iShowBMP(buttonx, buttony[i], button[i+4]);
		else
			iShowBMP(buttonx, buttony[i], button[i]);
	}

}


/* 
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
	//place your drawing codes here	
	iClear();

	if (state == 0)
	{
		iClear();
		menuDraw();
	}
	
	if (state == 1)
	{
		iClear();
		playing = true;
		game();
	}

	if (state == 2)
	{
		iClear();
		gameOver();
	}

	if (state == 3)
	{
		iClear();
		highScorr();
	}
	

}


/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if (state == 0 && key == '\r')
	{
		if (hover == 1)
			restart();
		if (hover == 3)
			exit(0);
		if (hover == 2)
			state = 3;
	}

	if (state == 2 && key == '\r')
	{
		if (hover == 0)
		{
			
			state = 0;
		}
		if (hover == 1)
			exit(0);
	}

	if (state == 3 && key == 27)
		menu();

	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}

	if (state == 1)
	{
		if (key == GLUT_KEY_DOWN  && direction != 3)
		{
			direction = 1;
		}
		if (key == GLUT_KEY_LEFT  && direction != 0)
		{
			direction = 2;
		
		}
		if (key == GLUT_KEY_UP  && direction != 1)
		{
			direction = 3;
		
		}
		if (key == GLUT_KEY_RIGHT  && direction != 2)
		{
			direction = 0;
	
		}
	}

	if (state == 0)
	{
		if (key == GLUT_KEY_DOWN  && hover<3)
		{
			hover++;
		}
		if (key == GLUT_KEY_UP  && hover>1)
		{
			hover--;
		}
		
	}

	if (state == 2)
	{
		if (key == GLUT_KEY_DOWN  && hover<1)
		{
			hover++;
		}
		if (key == GLUT_KEY_UP  && hover>0)
		{
			hover--;
		}
	}
	
	//place your codes for other keys here
}


int main()
{
	//place your own initialization codes here. 
	
	for (i = 0; i < len; i++)
	{
		snake[i].dx = 305 + i*size;
		snake[i].dy = 305;
	}

	generateFood();

	
	fopen_s(&high, "high.txt", "r");
	
	for (j = 0; j < 5; j++)
		fscanf_s(high, "%d", &hs[j]);

	fclose(high);

	t= iSetTimer(spd, move);
	iSetTimer(spd, colision);
	iSetTimer(spd, foodEat);

	iInitialize(width, height, "Snake");
	return 0;
}	