#include<conio.h>
#include<graphics.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>
#include<mouse.h>

#define arriba 72
#define abajo 80
#define derecha 77
#define izquierda 75
#define NEGRO 0
#define BLANCO 15
#define array[100]
#define gresult

#define PonerCursor(x,y) dib_cursor(x,y,BLANCO);
#define BorrarCursor(x,y) dib_cursor(x,y,NEGRO);
#define TAM_CURS 5

void dib_cursor(int x, int y, int color);
void logo(void);
void mouse(void);
void rectanguloteclado(void);int leercar(void);
void CirculoDeHule(int x,int y,int radio);
void lineahule(void);

void main()
{
 char c;
 int driver=DETECT,modo,n=100,b=200;
 initgraph(&driver,&modo,"C:\\tc20\\bin");
 logo();
 setbkcolor(BLACK);
 mouse();
 do{
	c=getch();
	switch(c)
	{
	  case arriba:
	  dib_cursor(n, b, BLANCO);
	  dib_cursor(n,b,NEGRO);
	  b=b-5;
	  if (b==25)
	  {
		b=b+5;
	  }
	  dib_cursor(n, b, BLANCO);
	  break;

	  case abajo:
	  dib_cursor(n, b,BLANCO);
	  dib_cursor(n,b,NEGRO);
	  b=b+5;
	 if (b==325)
	 {
	   b=b-5;
	 }
	 dib_cursor(n,b,BLANCO);
	 break;

	 case derecha:
	 dib_cursor(n, b, BLANCO);
	 dib_cursor(n,b,NEGRO);
	 n=n+5;
	 if(n==615)
	 {
	   n=n-5;
	 }
	dib_cursor(n, b, BLANCO);
	break;

	case izquierda:
	dib_cursor(n, b, BLANCO);
	dib_cursor(n,b,NEGRO);
	n=n-5;
	if(n==40)
	{
	 n=n+5;
	}
	dib_cursor(n, b, BLANCO);
	break;

	default:
	/*settextstyle(2,0,4);
	outtextxy(30,30,"Cursor destructivo");
	outtextxy(30,40,"presione ESC para salir");*/
	break;
  }
  if(c==27)
  exit(0);
 }while(c!=27);
getch();
}

void dib_cursor(int x, int y, int color)
{
 int col_ant;
 /*col_ant= getcolor();   */
 setcolor(color);
 line(x- TAM_CURS, y, x + TAM_CURS, y);
 line(x, y - TAM_CURS, x, y + TAM_CURS);
 /*setcolor(col_ant); */
}

void logo(void)
{
	int gresult;
	/*Cuerpo*/
	rectangle(30,15,620,330);
	rectangle(30,350,620,470);
	rectangle(40,380,110,450);
		line(130,380,150,460);
		circle(550,410,35);
}

void mouse(void)
{
	mver();
	do{
	   if(mclick()==1 && minlimit(1,40,380,110,450))
		   rectanguloteclado();
	   if(mclick()==1 && minlimit(1,500,380,600,450))
		 CirculoDeHule(getmaxx()/2,getmaxy()/2,30);
	   if(mclick()==1 && minlimit(1,120,380,170,450))
		   lineahule();
	}while(1);
}

void rectanguloteclado(void)
	{
	  char a;
	  int x2=60,y2=80;
	  setlinestyle(1,1,2);
	  setcolor(BLUE);
	  rectangle(320,240,x2,y2);
	  do{
		  logo();
		  a=getch();
		  switch(a)
		  {
			case 77:    cleardevice();
			x2=x2+5;
			setcolor(BLUE);
			rectangle(320,240,x2,y2);
			if(x2>600)
			 x2=600;
			break;

			case 75:   cleardevice();
			x2=x2-5;
			setcolor(BLUE);
			rectangle(320,240,x2,y2);
			if(x2<60)
			 x2=60;
			break;

			case 80:   cleardevice();
			y2=y2+5;
			setcolor(BLUE);
			rectangle(320,240,x2,y2);
			if(y2>460)
			 y2=460;
			if(y2==325)
			{
			 y2=y2-5;
			}
			break;

			case 72:   cleardevice();
			y2=y2-5;
			setcolor(BLUE);
			rectangle(320,240,x2,y2);
			if(y2<80)
			 y2=80;
			 if(y2==25)
			 {
			   y2=y2+5;
			 }
			break;
	  }
	}while(a!=27);
	cleardevice();
}

int leercar()
{
	int tecla;
	while((tecla=getch())!=0)
	if(tecla==13)
	return(tecla);
	return(getch());
}

void CirculoDeHule(int x,int y,int radio)
	{
		int direccion,caracter;
	   do
	           {
		setcolor(GREEN);
		circle(x,y,abs(radio));
		direccion=0;

		switch(caracter=leercar())
		{
			case arriba:
				direccion++;
				break;
			case abajo:
				direccion--;
				break;
			case derecha:
				direccion++;
				break;
			case izquierda:
				direccion--;
				break;
		}
		setcolor(0);
		circle(x,y,abs(radio));
		radio+=direccion;

	      }while(direccion);

	radio=abs(radio);
	return(caracter);

	}

void lineahule(void)
	{
		char a;
		int x2=getmaxx()/2, y2=getmaxy()/2;
		/*cleardevice();*/

	do
		{
		a=getch();

		switch(a)
			{

			case 77:  setcolor(BLACK);

				  line(290,240,x2,y2);
				  setcolor(WHITE);
				  x2=x2+5;
				  line(290,240,x2,y2);
				  break;

			case 75:  setcolor(BLACK);
				  line(290,240,x2,y2);
				  setcolor(WHITE);
				  x2=x2-5;
                                  if (x2==325)
	                           {
	                             x2=x2+5;
	                           }
				  line(290,240,x2,y2);
				  break;

			case 72:  setcolor(BLACK);
				  line(290,240,x2,y2);
				  setcolor(WHITE);
				  y2--;

				  if(y2==615){
							y2=y2-5;
	                          }  
				  line(290,240,x2,y2);
				  break;

			case 80: setcolor(BLACK);
				 line(290,240,x2,y2);
				 setcolor(WHITE);
				 y2++;
				 line(290,240,x2,y2);
				 break;

			}

		}while(a!=27);
	}
