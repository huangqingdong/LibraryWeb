#define N 200
#include <process.h>
#include <dos.h>
#include <conio.h>
#include<graphics.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define Key_DOWN 0x5000
#define Key_UP 0x4800
#define Key_ESC 0x011b
#define Key_ALT_F 0x2100
#define Key_ALT_X 0x2d00
#define Key_ENTER 0x1c0d
#define IMAGE_SIZE 10
/*��Ϸ*/
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define DOWN 0x5000
#define UP 0x4800
#define ESC 0x011b
#define filename "c:\\tc\\save.txt"
int i,key;
int score=0;/*�÷�*/
int gamespeed=50;/*��Ϸ�ٶ��Լ�����*/
int start=1;
int Level=1;
char y;

struct Food
{
   int x;/*ʳ��ĺ�����*/
   int y;/*ʳ���������*/
   int x1;
   int y1;

   int yes;/*yes=1:��Ҫ��ʾʳ�yes=0:��Ļ�Ѿ���ʳ����ڡ�yes�ж��Ƿ�Ҫ����ʳ��ı���*/
}food;/*ʳ��Ľṹ��*/

struct Snake
{
   int x[N];/*X����*/
   int y[N];/*y����*/
   int node;/*�ߵĽ���*/
   int direction;/*���ƶ�����*/
   int life;/* �ߵ�����,0����,1����*/
}snake;
/*������Ϸ*/
struct person
{
	int score;
	char name[20];

}per[5];

void box(int startx,int starty,int high,int width);
int menuslist();
void putstar(void);
void win1();
void startpage();

void autoPlay();
void autoPlayGame();
void voice();

/*��Ϸ����*/

void Init(void);/*ͼ������*/
void Close(void);/*ͼ�ν���*/
void DrawK(void);/*��ʼ����*/
void GameOver(void);/*������Ϸ*/
void GamePlay(void);/*����Ϸ�������*/
void PrScore(void);/*����ɼ�*/
void save(void);/*������Ϸ��¼*/
void readfile(void);/*��ȡ��Ϸ��¼*/
void startplay(void);/*��ʼ*/
void newstart(void);/*��ʼ����Ϸ*/
void paihb();/*���а�*/
void comparescore(struct person des);/*�Ƚ����а����*/
void initscorefiles();/*��ʼ������*/
void writefiles(struct person *tmp);/*������д���ļ���*/
void readfiles();/*���ļ��ж�ȡ����*/

main()
{
startpage();
menuslist();/*���˵�*/
getch();
}

int menuslist()
{
int i,key,x,y,l;


char *menu[] = {"Play","Level","Rank","Continu","Auto"};
/* ���˵����� */
char *menu1[] = {"Play","","Level","","Rank","","Continue","","Auto"};
char *red[] = { "P","L","R","C","A"}; /* ���Ϻ�ɫ�ȼ� */
/*char *f[] = {"Load file", "Save file", "Print", "Modify ", "Quit"};*/
/* File ����Ӳ˵� */
char *level[]={"Low","Midum","High"};

char buf[16*10*2],buf1[16*10*2]; /* ���屣���ı��Ļ����� */
l=0;

while(1)
			{
			textbackground(BLUE);
			clrscr();
			textmode(C80);
			window(25,5,35,20);/* ������ʾ���˵��Ĵ��� */
			textbackground(LIGHTGRAY);
			textcolor(BLACK);
			clrscr();

			gotoxy(5,5);
					for(i=0,l=0;i<5;i++)
					{
					x=wherex(); /* �õ���ǰ�������� */
					y=wherey();
					cprintf("%s",menu[i]); /* ��ʾ���˵��� */
					 /*l=strlen(menu[i]); �õ��˵���ĳ��� */
					gotoxy(x,y);
					textcolor(RED);
					cprintf("%s",red[i]); /* �����˵����ͷ�ַ�д�Ϻ��ַ� */
					y=y+2;
					gotoxy(x,y);
					textcolor(BLACK); /* Ϊ��ʾ��һ���˵����ƶ���� */
					}
					gettext(29,9,45,11,buf);
			gotoxy(5,5);
			key=bioskey(0);
y=5;

					while ((key=bioskey(0))!=Key_ALT_X) /* �ȴ�ѡ�������˵���*/
								{

								if ((key==Key_UP)||(key==Key_DOWN))
											{
												puttext(29,y+4,45,y+6,buf); /* �ָ�ԭ�ȵ��� */
												if (key==Key_UP)
												y=y==5?13:y-2;
												else
												y=y==13?5:y+2;
												gettext(29,y+4,45,y+6,buf);/*����Ҫѹ�Ϲ������Ӳ˵���*/
												textbackground(BLACK);
												textcolor(WHITE);
												gotoxy(5,y);
												cprintf("%s",menu1[y-5]); /* ��������ѹ����ѡ���� */


												gotoxy(5,y);

											}
								else

								if (key==Key_ENTER)/* ���ǻس���,�ж�����һ�Ӳ˵����Ļ�
								�����ڴ�û����Ӧ�����⴦��*/
										{
													switch ( y )
															{
														case 5: /* ���Ӳ˵����һ��:Play */
														
													i=1;
													startplay();
													
														break;

														case 7: /* Level */
														textbackground(BLACK);
														textcolor(WHITE);
														gotoxy(29,45);
														cprintf("%s",menu[1]);
														window(36,9,43,14);
														textbackground(LIGHTGRAY);
														textcolor(BLACK);
														clrscr();
														for(i=0;i<3;i++)
															{
															l=l+2;
															gotoxy(2,l);
															cprintf("%s",level[i]);
															}
														gettext(36,10,43,11,buf1);
														gotoxy(2,2);


															y=2;
															while ((key=bioskey(0))!=Key_ALT_X) /* �ȴ�ѡ�������˵���*/
																	{
																	if ((key==Key_UP)||(key==Key_DOWN))
																			{
																			puttext(36,y+8,43,y+9,buf1); /* �ָ�ԭ�ȵ��� */
																			if (key==Key_UP)
																			y=y==2?6:y-2;
																			else
																			y=y==6?2:y+2;
																			gettext(36,y+8,43,y+9,buf1);/*����Ҫѹ�Ϲ������Ӳ˵���*/
																			textbackground(BLACK);
																			textcolor(WHITE);
																			gotoxy(2,y);
																			cprintf("%s",level[y/2-1]); /* ��������ѹ����ѡ���� */
																			gotoxy(2,y);
																			}									
																	else
																	if (key==Key_ENTER)
																			{
																					switch(y)
																					{
																							case 2:
																								Level=1;
																						
																								break;
																							case 4:
																								Level=2;
																								break;
																							case 6:
																								Level=3;
																								break;
																							default:
																								break;
																					}
																			}
																
																else
																if (key==Key_ESC)
																break; /* ��Esc ��,�������˵� */
																}
														case 9: /*Rank*/
														paihb();
														break;
														case 11: /* Continue��Ϸ��¼ */
														start=0;
														startplay();
														getch();
														break;
														case 13:/*�Զ���Ϸ*/
														autoPlayGame();
												default:
													break;
															}


									    }
								else
								if (key==Key_ESC)
								break; /* ��Esc ��,�������˵�   */
								}
							/*if (key==Key_ALT_X) exit(0);
							break;*/
							}
							return;

}
/*��ʼҳ��*/
void startpage()
{int driver=DETECT;
int mode,color;
void *pt_addr;
int x,y,maxy,maxx,midy,midx,i;
unsigned size;
initgraph(&driver,&mode,"c:\\tc\\bgi");
maxx=getmaxx();
maxy=getmaxy();
midx=maxx/2;
x=0;
midy=y=maxy/2;
win1();
settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
settextjustify(CENTER_TEXT,CENTER_TEXT);
outtextxy(midx,400,"WELCONME TO SNAKE WORLD");
setbkcolor(BLACK);
setcolor(RED);
setlinestyle(SOLID_LINE,0,THICK_WIDTH);
ellipse(midx,midy,130,50,160,30);
setlinestyle(SOLID_LINE,0,NORM_WIDTH);
size=imagesize(x,y-IMAGE_SIZE,x+(4*IMAGE_SIZE),y+IMAGE_SIZE);
pt_addr=malloc(size);
getimage(x,y-IMAGE_SIZE,x+(4*IMAGE_SIZE),y+IMAGE_SIZE,pt_addr);
putstar();
setcolor(BLUE);
setlinestyle(SOLID_LINE,0,NORM_WIDTH);
rectangle(0,0,maxx,maxy);
while(!kbhit())
{
putstar();
setcolor(RED);
setlinestyle(SOLID_LINE,0,THICK_WIDTH);
ellipse(midx,midy,130,50,160,30);
setcolor(BLACK);
ellipse(midx,midy,130,50,160,30);
for(i=0;i<=13;i++)
{
setcolor(i%2==0?LIGHTBLUE:BLACK);
ellipse(midx,midy,0,360,100-8*i,100);
setcolor(LIGHTBLUE);
ellipse(midx,midy,0,360,100,100-8*i);
}
}



free(pt_addr);
closegraph();
return;
}
void win1()
{
	setcolor(8);
	setfillstyle(SOLID_FILL,8);
	bar3d(0,0,639,479,0,0);
	setcolor(0);
	setfillstyle(SOLID_FILL,0);
	bar3d(189,44,494,214,0,0);
	setcolor(1);
	setfillstyle(SOLID_FILL,1);
	bar3d(159,59,479,239,0,0);
	setcolor(14);
   settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,8);
	outtextxy(216,64,"SNAKE");
}
void putstar(void)/*������*/
{
int seed=1858;
int i,dotx,doty,h,w,color,maxcolor;
maxcolor=getmaxcolor();/*�õ���ǰģʽ�������ɫ��*/
w=getmaxx();
h=getmaxy();
srand(seed);
for(i=0;i<250;++i)
{
dotx=i+random(w-1);
doty=i+random(h-1);
color=random(maxcolor);
setcolor(color);
putpixel(dotx,doty,color);/*�õ��ʾС��*/
circle(dotx+1,doty+1,1);/*��Բ��ʾ����*/
}
srand(seed);
}
/*��ʼҳ�����*/


/*ͼ������*/
void Init(void)
{
   int gd=DETECT,gm;
   initgraph(&gd,&gm,"c:\\tc\\bgi");
   cleardevice();/*���ͼ����Ļ*/
}
/*��ʼ���棬���Ͻ�����Ϊ��50��40�������½�����Ϊ��610��460����Χǽ*/
void DrawK(void)
{
   setbkcolor(LIGHTBLUE);/*���ñ���ɫ��ɫ*/
   setcolor(11);/*����ǰ����ɫ*/
   setlinestyle(SOLID_LINE,0,THICK_WIDTH);/*�������ͣ����õ�ǰ���߿�Ⱥ�����*/
   for(i=0;i<=640;i+=10)/*��Χǽ*/
   {
      rectangle(i,40,i+10,49); /*�ϱߣ�rectangle��һ������*/
   }

}

/*����Ϸ�������*/
void GamePlay(void)
{
	if(start==1)
   newstart();
else
	{
   readfile();
   score=(snake.node-2)*10;
   PrScore();
	}
   randomize();/*�����������*/
   PrScore();

   while(1)/*�����ظ�����Ϸ,ѹESC������*/
   {
			  while(!kbhit())/*kbhit��һ������������������鵱ǰ�Ƿ��м�������,��û�а����������,���Լ��ƶ�����*/
			  {
						  if(food.yes==1)/*��Ҫ������ʳ��*/
						  {
							  food.x=rand()%400+60;
							  food.y=rand()%350+60;
							  /* food.x1=rand()%400+60;
							  food.y1=rand()%350+60;*/
							  while(food.x%10!=0)/*ʳ��������ֺ������ʳ���ܹ���������,�����ſ������߳Ե�*/
						  food.x++;
							  while(food.y%10!=0)
						  food.y++;
						  food.yes=0;/*��������ʳ����,��Ҫ��yes��0*/
						  }
							  if(food.yes==0)/*��������ʳ���˾�Ҫ��ʾ*/
							  {
								           voice();
										  setcolor(GREEN);/*����ʳ��ǰ��ɫ��*/
										  rectangle(food.x,food.y,food.x+10,food.y-10);/*����ʳ����ɫ*/
										 /* rectangle(food.x1,food.y1,food.x1+10,food.y1-10);����ʳ����ɫ*/
							  }
						 for(i=snake.node-1;i>0;i--)/*�ߵ�ÿ��������ǰ�ƶ�,Ҳ����̰���ߵĹؼ��㷨*/
						 {
							snake.x[i]=snake.x[i-1];
							snake.y[i]=snake.y[i-1];
						 }
			   /*1,2,3,4��ʾ��,��,��,���ĸ�����,ͨ������ж����ƶ���ͷ*/
					  switch(snake.direction)
					  {
						 case 1:
							 if(snake.x[0]==630)
							  snake.x[0]=0;
						     else
							 snake.x[0]+=10;
						 break;/*��*/
						 case 2:
							  if(snake.x[0]==0)
							  snake.x[0]=630;
						     else
							 snake.x[0]-=10;
							 break;/*��*/
						 case 3:
							  if(snake.y[0]==60)
							 snake.y[0]=480;/*��*/
                          else
							   snake.y[0]-=10;
						 break;
						 case 4:
							 if(snake.y[0]==470)
							 snake.y[0]=60;
						 else
						 snake.y[0]+=10;break;/*��*/
					  }


				  for(i=3;i<snake.node;i++)/*���ߵĵ��Ľڿ�ʼ�ж��Ƿ�ײ���Լ��ˣ���Ϊ��ͷΪ���ڣ������ڲ����ܹչ���*/
				  {
					 if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0])
					 {
							   GameOver();/*��ʾʧ��*/
							   snake.life=1;/*0Ϊ���ţ�1Ϊ�ҵ�*/
							   break;
					 }
				   }
				 if(snake.x[0]==food.x&&snake.y[0]==food.y)/*�Ե�ʳ���Ժ�*/
					 {
							   setcolor(0);/*�ѻ����ϵ�ʳ�ﶫ��ȥ��*/
							   rectangle(food.x,food.y,food.x+10,food.y-10);
						snake.x[snake.node]=-20;snake.y[snake.node]=-20;
							  /*�µ�һ���ȷ��ڿ�������λ��,�´�ѭ����ȡǰһ�ڵ�λ��*/
						snake.node++;/*�ߵ����峤һ��*/
						food.yes=1;/*��������Ҫ�����µ�ʳ��*/
						score+=10;
						PrScore();/*����µ÷�*/
					 }
				 setcolor(4);/*������*/
				 for(i=0;i<snake.node;i++)
					rectangle(snake.x[i],snake.y[i],snake.x[i]+10,
							   snake.y[i]-10);
				 delay(gamespeed);
				 setcolor(0);/*�ú�ɫȥ���ߵĵ����һ��*/
				 rectangle(snake.x[snake.node-1],snake.y[snake.node-1],
				 snake.x[snake.node-1]+10,snake.y[snake.node-1]-10);
		      }  /*endwhile����kbhit��*/




		if(snake.life==1)/*�������������ѭ��*/
			break;
		key=bioskey(0);/*���հ�����bioskeyֱ��ʹ��BIOS����ļ��̽ӿڡ�*/
		if(key==ESC)/*��ESC���������˵�*/
	   {
		   window(36,5,60,20);
		   gotoxy(0,10);
		   printf("Save Game?(Y/N)");
		   scanf("%s",&y);
		   clrscr();
			   if(y=='Y'||y=='y')
				   save();
			   else
				   exit(0);
	   }
		else
		   if(key==UP&&snake.direction!=4)
	/*�ж��Ƿ����෴�ķ����ƶ�*/
			snake.direction=3;
		   else
	   if(key==RIGHT&&snake.direction!=2)
		  snake.direction=1;
	   else
		  if(key==LEFT&&snake.direction!=1)
	  snake.direction=2;
		  else
	  if(key==DOWN&&snake.direction!=3)
		 snake.direction=4;
	   }/*endwhile(1)*/
}

void newstart()
{
	   food.yes=1;/*1��ʾ��Ҫ������ʳ��,0��ʾ�Ѿ�����ʳ��*/
  /*����*/
   snake.direction=1;/*��������*/
   snake.x[0]=100;/*��ͷ*/
   snake.y[0]=100;
   snake.x[1]=110;/*�ڶ���*/
   snake.y[1]=100;
   snake.node=2;/*����*/
    snake.life=0;
   PrScore();/*����÷�*/
}

/*��Ϸ����*/
void GameOver(void)
{
	struct person curperson;
    cleardevice();
    PrScore();
   setcolor(RED);
   settextstyle(0,0,4);
   outtextxy(200,200,"GAME OVER");


/*��������*/

	readfiles();
	if(score>per[4].score)
	{
		setfillstyle(1,9);
		bar(14,14,447,419);
		 settextstyle(0,0,2);
		outtextxy(5,5,"refueling! you score enter the board!");
		outtextxy(5,20,"please enter your name");
		gotoxy(5,100);
		printf(":                  ");
		gotoxy(5,100);
		scanf("%s",curperson.name);
		curperson.score=score;
		comparescore(curperson);
		writefiles(per);
	}
	else outtextxy(100,100,"you score is not enough on the board!");
	paihb();



   getch();
}

/*����ɼ�*/
void PrScore(void)
{
   char str[100];

   setfillstyle(SOLID_FILL,YELLOW);
   bar(50,15,500,35);
   setcolor(6);
   settextstyle(0,0,2);

   if(Level==1)
	   sprintf(str,"score:%d LEVEL:LOW",score);
   else if(Level==2)
		sprintf(str,"score:%d LEVEL:MID",score);
   else if(Level==3)
		sprintf(str,"score:%d LEVEL:HIG",score);
   outtextxy(55,20,str);
}



void readfiles()
{
	FILE *fpread;
	if((fpread=fopen(filename,"ab+"))==NULL)
	{printf("can't open the file person.txt!");

	exit(0);

	}
	getch();
	if(fgetc(fpread)==EOF)
		initscorefiles();
         rewind(fpread);
		 fread(per,sizeof(struct person),5,fpread);
		 fclose(fpread);
}
void writefiles(struct person *tmp)
{
	FILE *fpwrite;
	if((fpwrite=fopen(filename,"wb+"))==NULL)
	{
		printf("can't open the file person.txt!");
	exit(0);

	}
	fwrite(tmp,sizeof(struct person),5,fpwrite);
	fclose(fpwrite);
}
void initscorefiles()
{
	int i;
	struct person a[5];
	for(i=0;i<5;i++)
	{
		a[i].score=0;
		strcpy(a[i].name,"nobody");
	}
	writefiles(a);
}


void comparescore(struct person des)
{
	int i,j;
	for(i=0;i<5;i++)
	{
		if(des.score>=per[i].score)
		{
			if(i<5)
			{for(j=4;j>=i+1;j--)
				per[j]=per[j-1];
			}
			per[i]=des;
			break;
		}
	}
}
void paihb()/*���а�*/
{
	int i;
	char string[10];
	readfiles();
	 settextstyle(0,0,2);
	setfillstyle(1,9);
	bar(200,150,405,300);
	outtextxy(200,100,"highest board");

	outtextxy(200,150,"name    score");
	for(i=0;i<5;i++)
	{
		setcolor(4);
	outtextxy(200,200+i*30,per[i].name);/*����*/
	itoa(per[i].score,string,10);
	setcolor(14);
	outtextxy(350,200+i*30,string);/*����*/
	}
	getch();
}



/****************************������Ϸ��¼*****************************************/
void save()
{
	FILE *fpwrite;
	if((fpwrite=fopen(filename,"w"))==NULL)
	{
		printf("can't save the file save.txt!");
	exit(0);

	}

	fprintf(fpwrite,"%d %d %d %d %d\n",food.yes,food.x,food.y,snake.node,snake.direction);
	for(i=0;i<=snake.node;i++)
	fprintf(fpwrite,"%d %d\n",snake.x[i],snake.y[i]);
	fclose(fpwrite);

}
/****************************��ȡ��Ϸ��¼*****************************************/
void readfile()
{
	FILE *fpread;
	if((fpread=fopen(filename,"r"))==NULL)
	{
    printf("can't read the file person.txt!");
	exit(0);
	}
	fscanf(fpread,"%d %d %d %d %d\n",&food.yes,&food.x,&food.y,&snake.node,&snake.direction);
	/*printf("%d %d %d %d %d\n",&food.yes,&food.x,&food.y,&snake.node,&snake.direction);*/
	for(i=0;i<snake.node;i++)
	fscanf(fpread,"%d%d\n",&snake.x[i],&snake.y[i]);
	fclose(fpread);
}


/*ͼ�ν���*/
void Close(void)
{
    getch();
    closegraph();
}
void startplay()
{
	  Init();/*ͼ������*/
   DrawK();/*��ʼ����*/
   GamePlay();/*����Ϸ�������*/
   Close();/*ͼ�ν���*/
}


void autoPlayGame()
{
	  Init();/*ͼ������*/
   DrawK();/*��ʼ����*/
   autoPlay();/*����Ϸ�������*/
   Close();/*ͼ�ν���*/
}

/**************�Զ���Ϸ******************/
void autoPlay(void)
{
   randomize();/*�����������*/
   food.yes=1;/*1��ʾ��Ҫ������ʳ��,0��ʾ�Ѿ�����ʳ��*/
   snake.life=0;/*����*/
   snake.direction=1;/*��������*/
   snake.x[0]=100;/*��ͷ*/
   snake.y[0]=100;
   snake.x[1]=110;/*�ڶ���*/
   snake.y[1]=100;
   snake.node=2;/*����*/
   PrScore();/*����÷�*/
   while(1)/*�����ظ�����Ϸ,ѹESC������*/
   {
			  while(!kbhit())/*kbhit��һ������������������鵱ǰ�Ƿ��м�������,��û�а����������,���Լ��ƶ�����*/
			  {

				  if(snake.x[0]-food.x<0)
					snake.direction=1;
				  else if(snake.x[0]-food.x>0)
					  snake.direction=2;
					if(snake.y[0]-food.y<0)
					snake.direction=4;
				  else if(snake.y[0]-food.y>0)
					  snake.direction=3;

						  if(food.yes==1)/*��Ҫ������ʳ��*/
						  {
							  food.x=rand()%400+60;
							  food.y=rand()%350+60;
							  /* food.x1=rand()%400+60;
							  food.y1=rand()%350+60;
							  */
							  while(food.x%10!=0)/*ʳ��������ֺ������ʳ���ܹ���������,�����ſ������߳Ե�*/
						  food.x++;
							  while(food.y%10!=0)
						  food.y++;
						  food.yes=0;/*��������ʳ����,��Ҫ��yes��0*/
						  }
							  if(food.yes==0)/*��������ʳ���˾�Ҫ��ʾ*/
							  {
										  setcolor(GREEN);/*����ʳ��ǰ��ɫ��*/
										  rectangle(food.x,food.y,food.x+10,food.y-10);/*����ʳ����ɫ*/
							  }
						 for(i=snake.node-1;i>0;i--)/*�ߵ�ÿ��������ǰ�ƶ�,Ҳ����̰���ߵĹؼ��㷨*/
						 {
							snake.x[i]=snake.x[i-1];
							snake.y[i]=snake.y[i-1];
						 }
			   /*1,2,3,4��ʾ��,��,��,���ĸ�����,ͨ������ж����ƶ���ͷ*/
					  switch(snake.direction)
					  {
						 case 1:
							 if(snake.x[0]==630)
							  snake.x[0]=0;
						     else
							 snake.x[0]+=10;
						 break;/*��*/
						 case 2:
							  if(snake.x[0]==0)
							  snake.x[0]=630;
						     else
							 snake.x[0]-=10;
							 break;/*��*/
						 case 3:
							  if(snake.y[0]==60)
							 snake.y[0]=480;/*��*/
                          else
							   snake.y[0]-=10;
						 break;
						 case 4:
							 if(snake.y[0]==470)
							 snake.y[0]=60;
						 else
						 snake.y[0]+=10;break;/*��*/
					  }
				  for(i=3;i<snake.node;i++)/*���ߵĵ��Ľڿ�ʼ�ж��Ƿ�ײ���Լ��ˣ���Ϊ��ͷΪ���ڣ������ڲ����ܹչ���*/
				  {
					 if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0])
					 {
							   GameOver();/*��ʾʧ��*/
							   snake.life=1;/*0Ϊ���ţ�1Ϊ�ҵ�*/
							   break;
					 }
				   }
				 if(snake.x[0]==food.x&&snake.y[0]==food.y)/*�Ե�ʳ���Ժ�*/
					 {
							   setcolor(0);/*�ѻ����ϵ�ʳ�ﶫ��ȥ��*/
							   rectangle(food.x,food.y,food.x+10,food.y-10);
						snake.x[snake.node]=-20;snake.y[snake.node]=-20;
							  /*�µ�һ���ȷ��ڿ�������λ��,�´�ѭ����ȡǰһ�ڵ�λ��*/
						snake.node++;/*�ߵ����峤һ��*/
						food.yes=1;/*��������Ҫ�����µ�ʳ��*/
						score+=10;
						PrScore();/*����µ÷�*/
					 }
				 setcolor(4);/*������*/
				 for(i=0;i<snake.node;i++)
					rectangle(snake.x[i],snake.y[i],snake.x[i]+10,
							   snake.y[i]-10);
				 delay(gamespeed);
				 setcolor(0);/*�ú�ɫȥ���ߵĵ����һ��*/
				 rectangle(snake.x[snake.node-1],snake.y[snake.node-1],
				 snake.x[snake.node-1]+10,snake.y[snake.node-1]-10);
		      }  /*endwhile����kbhit��*/




		if(snake.life==1)/*�������������ѭ��*/
			break;
		key=bioskey(0);/*���հ�����bioskeyֱ��ʹ��BIOS����ļ��̽ӿڡ�*/
		if(key==ESC)/*��ESC���˳�*/
		   break;


	   }/*endwhile(1)*/
}



void voice(void)
{
	int freq;
for(freq=50;freq<5000;freq+=50)
{
sound(freq);
delay(1);
}
}


void saveGame()
{

}
void playBack()
{


}




