#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<ctype.h>
#include<stdlib.h>

void frontPage();
void ButtonBox(int,int,int,int);
void TowerA(int);
void TowerB(int);
void TowerC(int);
void inputPage();
void disc(int,int, int ,int ,int);
void discMove(int, int ,int);
void towerOfHanoi(int,char,char,char);
void fromTo(char,char);

int A,B,C;

struct node
{
	int x[20];
	int y[20];
	int color[20];
}T1,T2,T3;

///******************************** MOUSE *********************************///
void mouse_reset()
{
	union REGS r;
	r.x.ax=0;
	int86(0x33,&r,&r);
	if(int(r.x.ax)!=-1)
	{
		printf("Hardware failure!");
		exit(1);
	}
}
void mouse_on()
{
	union REGS r;
	r.x.ax=1;
	int86(0x33,&r,&r);
}
void mouse_off()
{
	union REGS r;
	r.x.ax=2;
	int86(0x33,&r,&r);
}
void get_position(int *x,int *y)
{
	union REGS r;
	r.x.ax=3;
	int86(0x33,&r,&r);
	*x=r.x.cx;
	*y=r.x.dx;
}
int left_button_pressed()
{
	union REGS r;
	r.x.ax=3;
	int86(0x33,&r,&r);
	return(r.x.bx & 1);
}

int right_button_pressed()
{
	union REGS r;
	r.x.ax=3;
	int86(0x33,&r,&r);
	return(r.x.bx & 2);
}
///**************************** END OF MOUSE ******************************///

void main()
{
	int driver=DETECT,mode;
	int x,y,input;

	initgraph(&driver,&mode,"c:\\tc\\bgi");

	frontPage();
	mouse_reset();
	mouse_on();

	first:
	while(1)
	{
		if(left_button_pressed())
		{
			get_position(&x,&y);

			if(x>=590&&y>=5&&x<=635&&y<=25)
			exit(1);

			if(x>=250&&y>=250&&x<=380&&y<=300)
			{
				mouse_off();
				cleardevice();

				again:

				inputPage();
				gotoxy(46,15);
				scanf("%d",&input);
				A=input; B=0; C=0;

				for(int i=1,a=105,b=60;i<=A;i++,a-=8,b-=5)
				{
					T1.x[i]=a;
					T1.y[i]=b;
					T1.color[i]=i;
				}

				for(i=1;i<=A;i++)
				{
					T2.x[i]=0;
					T3.x[i]=0;
					T2.y[i]=0;
					T3.y[i]=0;
					T2.color[i]=0;
					T3.color[i]=0;
				}

				mouse_reset();
				mouse_on();
				goto second;
			}
		}
	}

	second:

	while(1)
	{
		mouse_on();
		if(left_button_pressed())
		{
			get_position(&x,&y);

			if(x>=590&&y>=5&&x<=635&&y<=25)
			exit(1);

			if(x>=250&&y>=280&&x<=380&&y<=330)
			{
				mouse_off();
				discMove(A,B,C);
				towerOfHanoi(input,'A','B','C');
				mouse_on();
			}

			if(x>=10&&y>=430&&x<=105&&y<=465)
			goto again;
		}
	}
}

void discMove(int A,int B,int C)
{
	int a,b,i,x,y,midx,midy;
	setfillstyle(1,1);
	bar(0,0,getmaxx(),getmaxy());

	TowerA(A);
	TowerB(B);
	TowerC(C);
	delay(5000);
}

void towerOfHanoi(int n,char frompeg,char auxpeg,char topeg)
{
	int x,y;

	if(n!=0)       //for(i=1,a=105,b=60;i<=A;i++,a-=8,b-=5,midy-=5)
	{
		towerOfHanoi(n-1,frompeg,topeg,auxpeg);

		fromTo(frompeg,topeg);
		discMove(A,B,C);

		towerOfHanoi(n-1,auxpeg,frompeg,topeg);
	}
}

void fromTo(char frompeg,char topeg)
{
	if(frompeg=='A'&&topeg=='B')
	{
		B++;
		T2.x[B]=T1.x[A];
		T2.y[B]=T1.y[A];
		T2.color[B]=T1.color[A];

		T1.x[A]=0;
		T1.y[A]=0;
		T1.color[A]=0;
		A--;
	}

	if(frompeg=='A'&&topeg=='C')
	{
		C++;
		T3.x[C]=T1.x[A];
		T3.y[C]=T1.y[A];
		T3.color[C]=T1.color[A];

		T1.x[A]=0;
		T1.y[A]=0;
		T1.color[A]=0;
		A--;
	}

	if(frompeg=='B'&&topeg=='C')
	{
		C++;
		T3.x[C]=T2.x[B];
		T3.y[C]=T2.y[B];
		T3.color[C]=T2.color[B];

		T2.x[B]=0;
		T2.y[B]=0;
		T2.color[B]=0;
		B--;
	}

	if(frompeg=='B'&&topeg=='A')
	{
		A++;
		T1.x[A]=T2.x[B];
		T1.y[A]=T2.y[B];
		T1.color[A]=T2.color[B];

		T2.x[B]=0;
		T2.y[B]=0;
		T2.color[B]=0;
		B--;
	}

	if(frompeg=='C'&&topeg=='A')
	{
		A++;
		T1.x[A]=T3.x[C];
		T1.y[A]=T3.y[C];
		T1.color[A]=T3.color[C];

		T3.x[C]=0;
		T3.y[C]=0;
		T3.color[C]=0;
		C--;
	}

	if(frompeg=='C'&&topeg=='B')
	{
		B++;
		T2.x[B]=T3.x[C];
		T2.y[B]=T3.y[C];
		T2.color[B]=T3.color[C];

		T3.x[C]=0;
		T3.y[C]=0;
		T3.color[C]=0;
		C--;
	}
}

void frontPage()
{
	setfillstyle(3,5);                    //page style and color
	bar(0,0,getmaxx(),getmaxy());
	rectangle(0,0,getmaxx(),getmaxy());
	setfillstyle(7,10);                   //text background style and color
	bar(150,160,530,200);
	setcolor(9);                          //Text color
	settextstyle(0,0,3);
	outtextxy(160,170,"TOWERS OF HANOI");
	ButtonBox(250,250,380,300);
	settextstyle(0,0,2);                   // button text style and color
	outtextxy(280,268,"SHOW");
}

void ButtonBox(int x1,int y1,int x2,int y2)
{
	int thick=10,pattern=1,color=1;
	int i,left,right,top,bottom;

	setfillstyle(1,0);			// button Outside color
	bar(x1-1,y1-1,x2+1,y2+1);

	left = top = WHITE;
	right =bottom = DARKGRAY;

	setfillstyle(pattern,color); 		// Inside bar
	bar(x1,y1,x2,y2);

	setcolor(top);
	for(i=0;i<=thick;i++)
	line(x1+i-1,y1+i-1,x2-i-1,y1+i-1);	// TOP

	setcolor(left);
	for(i=0;i<=thick;i++)
	line(x1+i-1,y1+i-1,x1+i-1,y2-i-1);	//LEFT

	setcolor(right);
	for(i=0;i<=thick;i++)
	line(x2-i+1,y1+i-2,x2-i+1,y2-i+1);	// RIGHT

	setcolor(bottom);
	for(i=0;i<=thick;i++)
	line(x1+i-2,y2-i+1,x2-i+1,y2-i+1);	// BOTTOM
}

void TowerA(int A)
{
	int a,b,midy=350,i,less=0;
	rectangle(0,0,getmaxx(),getmaxy());

	less=less+A*5;

	setfillstyle(1,2);
	bar(590,5,635,25);
	rectangle(590,5,635,25);
	settextstyle(0,0,1);
	outtextxy(598,12,"EXIT");


	for(i=1;i<=A;i++,midy-=5)
	disc(110,midy,T1.x[i],T1.y[i],T1.color[i]);

	setcolor(6);
	for(i=1;i<=20;i++)
	line(100+i,200,100+i,346-less);

	setfillstyle(1,2);
	bar(10,430,105,465);
	rectangle(10,430,105,465);
	settextstyle(0,0,2);
	outtextxy(20,440,"AGAIN");
}

void TowerB(int B)
{
	int i,midy=350,less=0;
	rectangle(0,0,getmaxx(),getmaxy());

	less=less+B*5;

	setfillstyle(1,2);
	bar(590,5,635,25);
	rectangle(590,5,635,25);
	settextstyle(0,0,1);
	outtextxy(598,12,"EXIT");


	for(i=1;i<=B;i++,midy-=5)
	disc(320,midy,T2.x[i],T2.y[i],T2.color[i]);

	setcolor(6);
	for(i=1;i<=20;i++)
	line(310+i,200,310+i,346-less);

	setfillstyle(1,2);
	bar(10,430,105,465);
	rectangle(10,430,105,465);
	settextstyle(0,0,2);
	outtextxy(20,440,"AGAIN");
}

void TowerC(int C)
{
	int i,midy=350,less=0;
	rectangle(0,0,getmaxx(),getmaxy());

	less=less+C*5;

	setfillstyle(1,2);
	bar(590,5,635,25);
	rectangle(590,5,635,25);
	settextstyle(0,0,1);
	outtextxy(598,12,"EXIT");

	for(i=1;i<=C;i++,midy-=5)
	disc(530,midy,T3.x[i],T3.y[i],T3.color[i]);    //100,50

	setcolor(6);                 //Towers Color
	for(i=1;i<=20;i++)
	line(520+i,200,520+i,346-less);

	setfillstyle(1,2);
	bar(10,430,105,465);
	rectangle(10,430,105,465);
	settextstyle(0,0,2);
	outtextxy(20,440,"AGAIN");
}

void disc(int midx,int midy,int xradius,int yradius,int i)
{
	setfillstyle(1, 2+i);
	/* draw a filled ellipse */
	fillellipse(midx, midy-5, xradius, yradius-10);
	setfillstyle(9,3+i);
	fillellipse(midx,midy-12,xradius,yradius-10);
	setfillstyle(0,1+i);
	fillellipse(midx, midy-15, 20,7);
}

void inputPage()
{
	int input;

	setfillstyle(10,10);
	bar(0,0,getmaxx(),getmaxy());
	setcolor(3);
	rectangle(0,0,getmaxx(),getmaxy());
	setcolor(3);
	rectangle(590,5,635,25);
	settextstyle(0,0,1);
	outtextxy(598,12,"EXIT");

	settextstyle(1,0,2);
	outtextxy(150,215,"HOW MANY DISCS : ");

	setfillstyle(9,8);                 //input box style and color
	bar(346,215,386,242);
	rectangle(345,215,387,242);

	ButtonBox(250,280,380,330);
	settextstyle(0,0,2);
	outtextxy(275,300,"ENTER");
}
