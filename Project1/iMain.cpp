# include <iostream>
# include "iGraphics.h"
using namespace std;
#define screenWidth 1200
#define screenHight 800
#define bricks 50

struct bricksturcture
{
	int x;
	int y;
	int dx;
	int dy;
	bool show;
	int red;
	int green;
	int blue;
};

struct bricksturcture brickk[bricks];

struct balllocation
{
	int x;
	int y;
};

struct balllocation bl[2];


struct score{
	int sc;
	char sc_char[10];
};

struct score p[100];


int playingstage = 2;
int st = 20;
int cc = 0;
//int score = 0;
//char sc[100];

int index=0;

int xback = 1100;
int yback = 0;

int red = 255;
int green = 255;
int blue = 255;

int xmahin = screenWidth/2;
int ymahin = 100;
int radius = 10;
int dxmahin = 3;
int dymahin = 2;

int xstick = xmahin - 50;
int ystick = ymahin - 20;
int dxstick = 100;
int dystick = 10;

bool start = false;
bool playmusic = false;

void restartmahin();
void mahinbounce();
void thebricks();
void icon();

char buttonfigure[30][500] = {"pic\\play.bmp", "pic\\score.bmp"};

void save(){
	FILE *fp;
	fp=fopen("data.dat","wb");
	fwrite(&p,sizeof(p),1,fp);
	fwrite(&index,sizeof(index),1,fp);
	fclose(fp);
}
void read(){
	FILE *fp;
	fp=fopen("data.dat","rb");
	fread(&p,sizeof(p),1,fp);
	fread(&index,sizeof(index),1,fp);
	fclose(fp);
}
void iDraw()
{
	iClear();

	if(playingstage == 2)
	{
		iShowBMP(0, 0, "pic\\gm.bmp");
		iText(100, 600, "Press B or Backspace for back",GLUT_BITMAP_TIMES_ROMAN_24);
		int j = 0;
	    for(j = 0; j<2; j++)
	    {
			iShowBMP(bl[j].x, bl[j].y, buttonfigure[j]);
	    }
		iShowBMP(xback, yback, "pic\\back.bmp");
	}

    else if(playingstage == 0)
	{
		iShowBMP(0, 0, "pic\\ga.bmp");
	    p[index].sc = cc * 5;
	    _itoa_s(p[index].sc, p[index].sc_char, 10);
	    iSetColor(255, 255, 255);
	    iText(1200-40, 800-40, p[index].sc_char,GLUT_BITMAP_HELVETICA_18);
	    iSetColor(red, green, blue);
	    iFilledCircle(xmahin, ymahin, radius, 100);
	    iFilledRectangle(xstick, ystick, dxstick, dystick);
		iShowBMP(xback, yback, "pic\\back.bmp");

	    int i = 0;
	    for(i=0 ; i < bricks ; i++)
	    {
		    if(brickk[i].show)
		    {
			   iSetColor(brickk[i].red, brickk[i].green, brickk[i].blue);
			   iFilledRectangle(brickk[i].x , brickk[i].y , brickk[i].dx , brickk[i].dy);
		    }
	    }

	    if(cc == 50)
	   {
		   iShowBMP(0, 0, "pic\\gameover.bmp");
	   }
	 }

	else if(playingstage == 1)
	{
		iShowBMP(0, 0, "pic\\highscorepage.bmp");
		iShowBMP(xback, yback, "pic\\back.bmp");
		int max=0, i;
		char max_char[10];
		for(i = 0; i<index; i++){
			if(p[i].sc > max){
				max = p[i].sc;
			}
		}
		_itoa_s(max, max_char,10);
		iText(screenWidth/2-50, screenHight-50,"HighScore: ", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(screenWidth/2+80, screenHight-50, max_char, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(screenWidth/2-90, screenHight-100, "------Scores-----", GLUT_BITMAP_TIMES_ROMAN_24);
		int j;
		for(i=index-1, j=0; i>=0; i--, j++){
			iText(screenWidth/2, screenHight-(120+(j*20)), p[i].sc_char);
			if(j == 10)
			{
				break;
			}
		}
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
		int i;
		for(i = 0; i < 2; i++)
		{
			if(mx >= bl[i].x && mx<=bl[i].x+260 && my >= bl[i].y && my<=bl[i].y+94)
			{
					playingstage = i;
			}
		}
		if(mx >= xback && mx <= xback+100 && my >= yback && my <= yback+50)
		{
			playingstage = 2;
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

void iKeyboard(unsigned char key)
{
	if(key == 'a')
	{
		if(xstick > 0)
		{
		 xstick -= 10;
		 if(!start)
		 {
			xmahin -= 10;
		 }
		}
	}
	if(key == 'd')
	{
		if(xstick < screenWidth - dxstick)
		{
		 xstick += 10;
		 if(!start)
		 {
			xmahin += 10;
		 }
		}
	}
	if(key == 'w')
	{
		if(!start)
		{
			start = true;
		}
	}
	if(key == ' ')
	{
		restartmahin();
    }
	if(key == 'b')
	{
		playingstage = 2;
	}
	if(key == 8)
	{
		playingstage=2;
	}
}

void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_LEFT)
	{
		if(xstick > 0)
		{
		 xstick -= 10;
		 if(!start)
		 {
			xmahin -= 10;
		 }
		}
	}
	else if(key == GLUT_KEY_RIGHT)
	{
		if(xstick < screenWidth - dxstick)
		{
		 xstick += 10;
		 if(!start)
		 {
			xmahin += 10;
		 }
		}
	}
	else if(key == GLUT_KEY_UP)
	{
		if(!start)
		{
			start = true;
		}
	}

}

void restartmahin()
{
	index++;
	save();
	xmahin = screenWidth/2;
    ymahin = 100;
	dxmahin = 3;
    dymahin = 2;
	cc=0;
    xstick = xmahin - 50;
    ystick = ymahin - 20;

	start = false;

	int i;
	for(i=0 ; i<bricks ; i++)
	{
		brickk[i].show = true;
	}

}

void mahinbounce()
{
	if(start)
	{
	  xmahin += dxmahin;
	  ymahin += dymahin;
	  if(xmahin >= screenWidth || xmahin <= 0)
	 {
		dxmahin*=(-1);
	 }
	  if(ymahin >= screenHight || ymahin <= 0)
	 {
		dymahin*=(-1);
	 }
	}

	if(xmahin>=xstick && xmahin<=xstick+dxstick && ymahin>=ystick && ymahin<=ystick+dystick)
	{
		dymahin*=(-1);
	}
	else
	{
		if(ymahin < ystick)
	    {
			cc = 50;
	    }
	}

	//brickbreaker
	int i;
	for(i=0 ; i<bricks ; i++)
	{
		if(brickk[i].show)
		{
			if(xmahin>=brickk[i].x && (xmahin<=brickk[i].x+brickk[i].dx))
			{
				if(ymahin>=brickk[i].y && (ymahin<=brickk[i].y+brickk[i].dy))
				{
			       dymahin*=(-1);
				   brickk[i].show = false;
				   cc++;
				   printf("\a");
				   playmusic = true;
				}
			}
			else if(ymahin>=brickk[i].y && (ymahin<=brickk[i].y+brickk[i].dy))
			{
			     if(xmahin>=brickk[i].x && (xmahin<=brickk[i].x+brickk[i].dx))
			     {
				    dxmahin*=(-1);
				    brickk[i].show = false;
					cc++;
				    printf("\a");
					playmusic = true;
			     }
		    }
		}
	}

}

void thebricks()
{
	int sx = 100;
	int sy = 650;
	int i;
	for(i=0 ; i<bricks ; i++)
	{
		brickk[i].x = sx;
		brickk[i].y = sy;
		brickk[i].dx = 100;
		brickk[i].dy = 20;
		brickk[i].show = true;
		brickk[i].red = rand() % 255;
		brickk[i].green = rand() % 255;
		brickk[i].blue = rand() % 255;
		sx += 100;
		if(sx > 1000)
		{
			sx = 100;
			sy += 20;
		}
	}
}

void icon()
{
	int i = 0, plus = 250;
	for(i = 1; i>=0; i--)
	{
		bl[i].x = 100;
		bl[i].y	= plus;
		plus += 150;
	}
}

int main()
{
	thebricks();
	icon();
	read();
	iSetTimer(5,mahinbounce);
	if(playmusic)
	{
		PlaySound("music\\gamemusic.wav", NULL, SND_ASYNC);
		playmusic = false;
	}
	iInitialize(screenWidth, screenHight, "dxball");

	return 0;
}
