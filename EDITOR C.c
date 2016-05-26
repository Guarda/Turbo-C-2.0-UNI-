#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<process.h>
#include<mouse.h>
#include<alloc.h>
#include<dos.h>
#include<math.h>

#define arriba 72
#define abajo 80
#define izquierda 75
#define derecha 77
#define ENTER 13
#define COLCURS 8
#define TAM_CURS 5
#define select 97
#define poner_cursor(x,y) dib_cursor(x,y);
#define borrar cursor(x,y) dib_cursor(x,y);
int color=0;

double elipse(int x,int y,int h,int k,int r1,int r2);
void menu();
void menu11();
void menu2();
void menu3();
void menu4();
void lineabuena(void);
void rectanguloteclado(void);
void xor(int x, int y);
void LineaXor(int X, int Y, int XF, int YF);
void muestraBMP();
void xor_pixel(int x, int y);
void area(int x, int y,int radio);
void dib_cursor(int x, int y);
void logo(void);
void func_itoa(int x, int y);
int seleccion(int x, int y,int t);
typedef struct /*estructura*/
/*campos de la estructura*/
{
  char Type[2];           /*Tipo de archivo. establecido en "BM".*/
  unsigned long Size;     /*Tamano en BYTES del archivo*/
  unsigned long Reserved;      /*Reservado. establecido en cero*/
  unsigned long OffSet;   /*Desplazamiento hacia datos*/
  unsigned long headsize; /*Tamaño de la cabecera del bitmap. establecido en 40.*/
  unsigned long Width;     /*Anchura en  pixeles.*/
  unsigned long Height;     /* Altura en pixeles.*/
  unsigned int  Planes;    /*Numero de Planos. establecido en 1.*/
  unsigned int  BitsPerPixel;       /*Numero de Bits por pixeles.*/
  unsigned long Compression;   /*Compresion. Usually establecido en 0.*/
  unsigned long SizeImage;  /*Tamano en BYTES del bitmap.*/
  unsigned long XPixelsPreMeter;     /*Pixeles Horizontales por metro.*/
  unsigned long YPixelsPreMeter;     /*Pixeles Verticales por metro.*/
  unsigned long ColorsUsed;   /*Numero de colores utilizados.*/
  unsigned long ColorsImportant;  /*Numero de colores "Importantes".*/
}BMP;
void ProBMP(int x, int y, char* NomArchivo) /*cuerpo de la funcion para dibujar imagen*/
{
    int b,a;
    BMP Obj;

    unsigned char* Datas;
	int in=0;
    unsigned char c=0;
	FILE * fp;  /*declaracion de fichero*/

	fp = fopen(NomArchivo,"rb");      /*apertura de fichero*/
    if(!fp){
    printf("Error : No se puede abrir el archivo ...");
	getch();
    exit(0);
    }

	fread(&Obj, sizeof(Obj), 1, fp); /*comprobacion del formato de la imagen*/
    if(Obj.BitsPerPixel!=4)  /* Este NO es un bmp de 16 colores que podamos leer*/
    {
     fclose(fp);
     printf("Error : Formato de archivo no soportado...");
	 getch();
     exit(0);
    };
    fseek(fp,Obj.OffSet,SEEK_SET);
    Datas=(unsigned char*) calloc(Obj.Width/2+1, sizeof(unsigned char));
    for(b=Obj.Height;b>=0;b--)
    {
     fread(Datas, sizeof(unsigned char), Obj.Width/2, fp);
     c=0;
     in=0;
     for(a=0;a<=Obj.Width;a+=2)
     {
		 c = (Datas[in]| 0xF0) & 0x0F; 
		 putpixel(a+1+x,b+y,c);  /*dubujar imagen*/
		
         c = (Datas[in] | 0x00) >>4;
		 putpixel(a+x,b+y,c); /*dibujar imagen*/
		 
         in++;
     }
    }

	free (Datas);   /*liberar memoria*/
	fclose(fp);     /*cerrar fichero*/
}


void main(void)
{
	char r;
	int van=0;
	int adapter=DETECT,modo,c=320,e=240;
	initgraph (&adapter,&modo,"C:\\tc20\\bin");

	logo();
	mver();
	msituar(1,200,200);
	mlimit(1,1,1,630,470);
	do{
		c=mxpos(1);
		e=mypos(1);
		delay(100);
		func_itoa(c,e); /*mostrar en pantalla la posicion (x,y) del cursor mouse o teclado*/
		if(kbhit()){
		
			do{
				if(mclick()==1)
				{
				
					msituar(1,c,e);
					van=seleccion(c,e,van);
				}

				r=getch();
				switch(r)     /*dibujo del cursor del teclado mediante el uso de los valores ascii de las direccionales */
				{
				case arriba:
				func_itoa(c,e);
				dib_cursor(c, e);
				e=e-1;
				dib_cursor(c,e);
				mver();
				break;

				case abajo:

				func_itoa(c,e);
				dib_cursor(c, e);
				e=e+1;
				dib_cursor(c, e);
				mver();
				break;

				case derecha:
				func_itoa(c,e);
				dib_cursor(c, e);
				c=c+1;
				dib_cursor(c, e);
				break;	
				
				case izquierda:
					
				func_itoa(c,e);
				dib_cursor(c, e);
				c=c-1;
				dib_cursor(c, e);
				break;

				case ENTER:

				van=seleccion(c,e,van); /*seleccion de un punto, validado de los menus*/
				break;
					


			}
		if(r==27)
			exit(0);
		}while(r!=27);
	}
	mver();
		if(mclick()==1){

			c=mxpos(1);
			e=mypos(1);
			if(mclick()==1)
				van=seleccion(c,e,van);
				if(kbhit()){
					van=1;
					mocultar();
				}
		}
	}while(van>=0);
		getch();
		closegraph();
}
/*dibujamos el cursor dado por las direccionales del teclado*/
  	void dib_cursor(int x, int y)
	{
	int i;
	for (i=0; i<TAM_CURS; i++){
		xor_pixel(x-i,y);
		xor_pixel(x+i,y);
		xor_pixel(x,y-i);
		xor_pixel(x,y+i);
	}
	xor_pixel(x,y);
}
/*funcion que restaura el color detras del cursor del teclado*/
void xor_pixel(int x, int y)   
{
	putpixel(x,y,COLCURS^getpixel(x,y));
}
void rec(){
		int rectagulo[90] = {
		115, 103
		,115, 378
		,117, 378
		,117, 380
		,118, 381
		,119, 382
		,120, 383
		,121, 384
		,123, 387
		,124, 387	
		,126, 388
		,128, 389
		,130, 390
		,505, 390
		,508, 386	
		,509, 385
		,511, 382
		,515, 379
		,516, 376
		,517, 376
		,518, 375
		,518, 103
		,516, 102
		,515, 100
		,514, 98
		,513, 98
		,513, 97
		,512, 97
		,511, 96
		,510, 95
		,509, 94
		,507, 93
		,506, 92
		,504, 90
		,503, 91
		,500, 89
		,130, 90
		,129, 91
		,126, 92
		,122, 94
		,121, 98
		,118, 98
		,118, 100
		,117, 101
		,115, 103

	};	
	setfillstyle(1,BLUE);
	fillpoly(45,rectagulo);
}
void logo(void)
{






	setfillstyle(1,GREEN);
	bar(1,1,640,480);
	setfillstyle(1,BLUE);
	rec();
	setfillstyle(1,RED);
	fillellipse(4,240,35,120);
	fillellipse(320,480,120,35);
	fillellipse(640,240,35,120);
	fillellipse(320,1,120,35);
	 
	/*fillellipse(300,480,150,50);
	fillellipse(0,240,50,150);
	fillellipse(639,240,50,150);
	fillellipse(300,0,150,50);*/

	/*setfillstyle(1,GREEN);
	fillpoly(10,esq1); */

	/*setfillstyle(1,YELLOW);
	bar(190,450,430,480);
	bar(190,0,430,50);
	bar(0,120,50,430);
	bar(590,120,640,430); */
}

/*esta funcion pone en pantalla la posicion del cursor del mouse y el del teclado*/
void func_itoa(int x, int y){
	char x1[10],x2[10];
   	settextstyle(11,0,1);
  	itoa(x,x1,10);
  	itoa(y,x2,10);
  	setfillstyle(1,GREEN);
  	bar(40,450,100,460);
  	outtextxy(40,450,"X=");
  	outtextxy(60,450,x1);
  	bar(580,450,640,460);
  	outtextxy(580,450,"Y=");
  	outtextxy(600,450,x2);
}
int seleccion(int x, int y,int t){
	int n=0,e=0,k=0,l=0,imagentam;
 
	void *imagen,*imagen2,*imagen3,*imagen4,*m11;  /*void para almacenar la imagen  dada por el raster*/

	if((elipse(x,y,320,1,120,35)<1)){       /*boton de archivos, parte superior, funcion elipse si el punto dado resulta en <1 ese punto estara o pertenece a la elipse*/
		t=1; /*esta variable se emplea como bandera para que no se pueda presionar ningun otro menu sino se ha abierto el menu de archivo primero*/
		mocultar();
		imagentam = imagesize(160,0,461,148);   /*uso de raster para guardar lo que esta detras del menu, se asigna el tamaño del raster a una variable int*/
		imagen=malloc(imagentam);       /*reserva de memoria dinamica con el tamaño del raster*/
		getimage(160,0,461,148,imagen); /*obtencion de la imagen y almacenamiento en una variable void*/
		menu();
		mver();

		while(n!=1){                /*este while se utiliza para evitar que el valor de mclick dado anteriormente valide automaticamente los otros menus y para detectar que si se presiona*/
			e=mclick();				/*asignacion del retorno del click del mouse a la variable si es ==1 es el click izquierdo*/
			if(e==1&&mxpos(1)>=160&&mypos(1)>=118&&mxpos(1)<=461&&mypos(1)<=148){          /*boton cerrar menu, posicion dada entre los limites del boton*/

				mocultar();  /*oculto el mouse para que no pase ningun problema al guardar el raster y que no guarde el cursor*/
				putimage(160,0,imagen, COPY_PUT);  /*poner la imagen que estaba detras del menu para reescribirlo, en la misma posicion*/
				mver();            /*volvemos a mostrar el mouse debido a un problema que deja un cuadro sin color*/
				msituar(1,x,y);  /*situamos el mouse*/
				free(imagen);		/*liberamos la memoria dinamica */
				n=1;         /*rompemos el ciclo*/
						
			} else if(e==1&&mxpos(1)>=160&&mypos(1)>=0&&mxpos(1)<=461&&mypos(1)<=29){	
							
					mocultar();
			     	putimage(160,0,imagen,COPY_PUT);
			     	rec();
			     	logo();
			     	mver();
				    msituar(1,x,y);
				    free(imagen);
			     	n=1; 
			     	
			} else if(e==1&&mxpos(1)>=160&&mypos(1)>=30&&mxpos(1)<=461&&mypos(1)<58){
				exit(0);
			} 
			else if(e==1&&mxpos(1)>=160&&mypos(1)>=58&&mxpos(1)<=461&&mypos(1)<=87){
				mocultar();
				imagentam=imagesize(461,58,610,148);
				m11=malloc(imagentam);
				getimage(461,58,610,148,m11);
				menu11();
				mver();
				while(k!=1){
					l=mclick();
					 if(l==1&&mxpos(1)>=461&&mypos(1)>=58&&mxpos(1)<=610&&mypos(1)<87){
						mocultar();
						putimage(461,58,m11,COPY_PUT);
						putimage(160,0,imagen, COPY_PUT); 
						ProBMP(115,89,"oie.bmp");
						setfillstyle(1,color);
						bar(115,89,145,130);
						free(m11);
						free(imagen);
						mver();
						k=1;
						
					} else if(l==1&&mxpos(1)>=461&&mypos(1)>=87&&mxpos(1)<=610&&mypos(1)<118){
						mocultar();
						putimage(461,58,m11,COPY_PUT);
						putimage(160,0,imagen, COPY_PUT); 
						ProBMP(115,89,"nel.bmp");
						mver();
						free(m11);
						free(imagen);
						k=1;
						
					} else if(l==1&&mxpos(1)>=461&&mypos(1)>=118&&mxpos(1)<=610&&mypos(1)<=148){
						mocultar();
						putimage(461,58,m11,COPY_PUT);
						putimage(160,0,imagen, COPY_PUT); 
						ProBMP(115,89,"zimon.bmp");
						mver();
						free(m11);
						free(imagen);
						k=1;						
					}
					n=1;
				} 
			}
		}n=e=k=l=0;
	}else if(t==1&&(elipse(x,y,4,240,35,120)<1)){
		mocultar();
		imagentam = imagesize(0,120,148,400);
		imagen=malloc(imagentam);
		getimage(0,120,148,400,imagen);
		menu2();
		mver();

		while(n!=1){

			if(mclick()==1&&mxpos(1)>=118&&mypos(1)>=120&&mxpos(1)<=148&&mypos(1)<=400){

				mocultar();
				putimage(0,120,imagen, COPY_PUT);
				mver();
				msituar(1,x,y);
				free(imagen);
				n=1;

			}
		}
	}else if(t==1&&(elipse(x,y,640,240,35,120)<1)){
		mocultar();
		imagentam = imagesize(499,124,639,399);
		imagen4=malloc(imagentam);
		getimage(499,124,639,399,imagen4);
		menu4();
		mver();


		while(n!=1){

			if(mclick()==1&&mxpos(1)>=500&&mypos(1)>=124&&mxpos(1)<=530&&mypos(1)<=324){

				mocultar();
				putimage(499,124,imagen4, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen4);
				n=1;

			} else if(mclick()==1&&mxpos(1)>=530&&mypos(1)>=308&&mxpos(1)<=639&&mypos(1)<=353){

				mocultar();
				putimage(499,124,imagen4, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen4);
				n=1;
				while(mclick()!=2){
				 if(mclick()==1)
				rectanguloteclado();
				
			 }
			} else if(mclick()==1&&mxpos(1)>=530&&mypos(1)>=125&&mxpos(1)<=640&&mypos(1)<=170){
				mocultar();
				putimage(499,124,imagen4, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen4);
				n=1;
					while(mclick()!=2){
				 if(mclick()==1)				
				 lineabuena();
			    }
			}
		}n=0;
	}else if(t==1&&((elipse(x,y,320,480,120,35)<1))){
	
		mocultar();
		imagentam = imagesize(118,370,503,479);
		imagen3=malloc(imagentam);
		getimage(118,370,503,479,imagen3);
		menu3();
		mver();


		while(n!=1){

			if(mclick()==1&&mxpos(1)>=118&&mypos(1)>=370&&mxpos(1)<=503&&mypos(1)<=402){

				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=130&&mypos(1)>=405&&mxpos(1)<=165&&mypos(1)<=435){
				color=0;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=175&&mypos(1)>=405&&mxpos(1)<=210&&mypos(1)<=435){
				color=1;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=220&&mypos(1)>=405&&mxpos(1)<=255&&mypos(1)<=435){
				color=2;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=265&&mypos(1)>=405&&mxpos(1)<=300&&mypos(1)<=435){
				color=3;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=310&&mypos(1)>=405&&mxpos(1)<=345&&mypos(1)<=435){
				color=4;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=355&&mypos(1)>=405&&mxpos(1)<=390&&mypos(1)<=435){
				color=5;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=400&&mypos(1)>=405&&mxpos(1)<=435&&mypos(1)<=435){
				color=6;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} else if(mclick()==1&&mxpos(1)>=445&&mypos(1)>=405&&mxpos(1)<=480&&mypos(1)<=435){
				color=7;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=130&&mypos(1)>=440&&mxpos(1)<=165&&mypos(1)<=470){
				color=8;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=175&&mypos(1)>=440&&mxpos(1)<=210&&mypos(1)<=470){
				color=9;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=220&&mypos(1)>=440&&mxpos(1)<=255&&mypos(1)<=470){
				color=10;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=265&&mypos(1)>=440&&mxpos(1)<=300&&mypos(1)<=470){
				color=11;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=310&&mypos(1)>=440&&mxpos(1)<=345&&mypos(1)<=470){
				color=12;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=310&&mypos(1)>=440&&mxpos(1)<=345&&mypos(1)<=470){
				color=13;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=355&&mypos(1)>=440&&mxpos(1)<=390&&mypos(1)<=470){
				color=14;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			}  else if(mclick()==1&&mxpos(1)>=400&&mypos(1)>=440&&mxpos(1)<=480&&mypos(1)<=470){
				color=15;
				mocultar();
				putimage(118,370,imagen3, COPY_PUT);
				mver();
				msituar(1,200,200);
				free(imagen3);
				n=1;
			} 
		}
		msituar(1,x,y);
	}else if(x>=630&&x<=640&&y>=470&&y<=480){
		cleardevice();
		outtextxy(0,240,"denunciado papu, despidete de tu cuenta rufian");
	}

	return(t);
}
/*dibujo de los menus*/
void menu(){
setfillstyle(1,15);
bar(160,0,461,117);
setcolor(4);
setfillstyle(1,YELLOW);
bar(160,118,461,148);
rectangle(160 ,118,461,148);
settextstyle(1,0,3);
outtextxy(265,120,"CERRAR");
setcolor(0);
settextstyle(1,0,3);
outtextxy(170,0,"Nuevo");
line(160,29,461,29);
outtextxy(170,29,"Salir");
line(160,58,461,58);
outtextxy(170,58,"Cargar Imagen");
line(160,87,461,87);
outtextxy(170,87,"Guardar Imagen");
rectangle(170,10,190,30);
}

void menu11(){
	setfillstyle(1,WHITE);
	bar(461,58,610,148);
	line(461,87,610,87);
	line(461,118,610,118);
	rectangle(461,58,610,148);
	outtextxy(470,60,"imagen 1");
	outtextxy(470,90,"imagen 2");
	outtextxy(470,120,"imagen 3");
}
void menu2(){
setfillstyle(1,15);
bar(0,120,118,400);
setfillstyle(1,YELLOW);
bar(118,120,148,400);
rectangle(118,120,148,400);
settextstyle(1,1,3);
outtextxy(120,210,"CERRAR");
setcolor(0);
settextstyle(1,0,3);
outtextxy(10,130,"Texto");
line(0,166,118,166);
outtextxy(10,175,"Estilo");
line(0,212,118,212);
outtextxy(10,222,"Mover");
line(0,258,118,258);
outtextxy(10,268,"Eliminar");
line(0,305,118,305);
outtextxy(10,315,"Editar");
line(0,351,118,351);
outtextxy(10,361,"Copiar");

}
void menu3(){
int x,y,x1,x2,x3,i,color;
setfillstyle(1,15);
bar(118,403,503,478);
setfillstyle(1,YELLOW);
bar(118,370,503,402);
settextstyle(1,0,3);
rectangle(118,370,503,402);
outtextxy(254,376,"CERRAR");
x=118;
x1=178;
color=0;
for(i=1;i<=8;i++){
setfillstyle(1,color);
x2=x+9;
x3=x2+38;
bar(x2,408,x3,435);
setcolor(0);
rectangle(x2,408,x3,435);
x=x3;
color++;
}
x=118;
x1=178;
for(i=1;i<=8;i++){
setfillstyle(1,color);
x2=x+9;
x3=x2+38;
bar(x2,440,x3,467);
setcolor(0);
rectangle(x2,440,x3,467);
x=x3;
color++;
}



}
void menu4(){
setfillstyle(1,15);
bar(499,124,640,399);
setcolor(0);
settextstyle(1,0,3);
line(499,169,639,169);
outtextxy(535,133,"Linea");
line(499,215,639,215);
outtextxy(535,178,"Pixel");
line(499,261,639,261);
outtextxy(535,223,"Circulo");
line(499,307,639,307);
outtextxy(535,268,"Poligono");
setlinestyle(1,1,3);
line(499,353,639,353);
outtextxy(535,313,"Cuadrado");
outtextxy(535,358,"Seleccionar");
setfillstyle(1,14);
setlinestyle(0,1,2);
bar(499,124,530,399);
setcolor(RED);
rectangle(499,124,530,399);
settextstyle(1,1,3);
outtextxy(505,220,"CERRAR");


}
/* validacion de que si un punto esta dentro de una elipse para activar el evento que muestra los botones (los menus) */
double elipse(int x,int y,int h,int k,int r1,int r2){  /*esta funcion recibe 6 parametros posicion (x,y) del punto, (h,k) centro de la elipse (r1,r2) los radios mayores y menores*/
	double valor;
	char a[10];
	valor=abs(((pow((x-h),2)/(r1*r1))+(pow((y-k),2)/(r2*r2))));

	/*muestra el resultado en pantalla del procedimiento
	itoa(valor,a,10);
	setfillstyle(1,GREEN);
	bar(1,1,30,30);
	outtextxy(10,10,a);
	*/

	return(valor); /*retornamos el valor del procedimiento si es <=1 el punto esta dentro de la elipse*/
}

void muestraBMP()
{
	BMP Obj;
	int X=115,Y=89,X1=435,Y1=329;
	int tam;
	void *Raster;
	FILE *FO;
	setfillstyle(1,GREEN);
	bar(120,100,150,170);
	tam=imagesize(X,Y,X1,Y1);
	Raster=malloc(tam);
	getimage(X,Y,X1,Y1,Raster);
	FO=fopen("o.BMP","wb");
	Obj.Type[0] = 66;
	Obj.Type[1] = 77;
	Obj.Size = sizeof(Raster);
	Obj.Reserved = 0;
	Obj.OffSet=0;
	Obj.headsize=40;
	Obj.Width=X1;
	Obj.Height=Y1;
	Obj.Planes=1;
	Obj.BitsPerPixel=4;
	Obj.Compression=0;
	Obj.SizeImage=tam;
	Obj.XPixelsPreMeter = X1;
	Obj.YPixelsPreMeter = Y1;
	Obj.ColorsUsed=16;
	Obj.ColorsImportant=0;

fwrite(&Obj.Type,sizeof(char),2,FO);
fwrite(&Obj.Size,sizeof(Obj),1,FO);
fwrite(&Obj.Reserved,sizeof(unsigned long),1,FO);
fwrite(&Obj.OffSet,sizeof(unsigned long),1,FO);
fwrite(&Obj.headsize,sizeof(unsigned long),1,FO);
fwrite(&Obj.Width,sizeof(unsigned long),1,FO);
fwrite(&Obj.Height,sizeof(unsigned long),1,FO);
fwrite(&Obj.Planes,sizeof(unsigned int),1,FO);
fwrite(&Obj.BitsPerPixel,sizeof(unsigned int),1,FO);
fwrite(&Obj.Compression,sizeof(unsigned long),1,FO);
fwrite(&Obj.SizeImage,sizeof(unsigned long),1,FO);
fwrite(&Obj.XPixelsPreMeter,sizeof(unsigned long),1,FO);
fwrite(&Obj.YPixelsPreMeter,sizeof(unsigned long),1,FO);
fwrite(&Obj.ColorsUsed,sizeof(unsigned long),1,FO);
fwrite(&Obj.ColorsImportant,sizeof(unsigned long),1,FO);
fwrite(Raster,tam,1,FO);

	fclose(FO);
	free(Raster);

	getch();
	closegraph();

}
void rectanguloteclado()
{
	int a,b,c,d;
	
	a=mxpos(1);
	b=mypos(1);
	mocultar();
	mlimit(1,115,89,515,389);
	while(mclick()==1){
		c=mxpos(1);
		d=mypos(1);
		LineaXor(a,b,c,b);
		LineaXor(c,b,c,d);
		LineaXor(c,d,a,d);
		LineaXor(a,d,a,b);
		delay(50);
		LineaXor(a,b,c,b);
		LineaXor(c,b,c,d);
		LineaXor(c,d,a,d);
		LineaXor(a,d,a,b);
	}
	setfillstyle(1,color);
	bar(a,b,c,d);
	mver();
	mlimit(1,1,1,640,480);
}


void xor(int x, int y)
{
putpixel(x,y,COLCURS^getpixel(x,y));
}
void LineaXor(int X,int Y, int XF, int YF)
{
	int DX,DY,Pasos,k;
	float XInc,YInc;
	double Xi,Yi;

	DX=XF-X;
	DY=YF-Y;
	Xi=X;
	Yi=Y;

	if(abs(DX)>abs(DY))
		Pasos=abs(DX);
	else
		Pasos=abs(DY);

	if(Pasos==0)
		xor(X,Y);
	else{
		XInc=(float)DX/Pasos;
		YInc=(float)DY/Pasos;
			for(k=1; k<=Pasos; k++){
				xor(ceil(Xi),ceil(Yi));
				Xi=Xi+XInc;
				Yi=Yi+YInc;

			  }
	 }
}
void lineabuena()
{
	int X,Y,X2,Y2;
	X=mxpos(1);
	Y=mypos(1);
	mocultar();
	mlimit(1,115,89,515,389);
	while(mclick()==1){
		X2=mxpos(1);
		Y2=mypos(1);
		LineaXor(X,Y,X2,Y2);
		delay(50);
		LineaXor(X,Y,X2,Y2);
	}
	mlimit(1,1,1,640,480);
	setcolor(color);
	setlinestyle(1,0,3);
	line(X,Y,X2,Y2);
	mver();
	
}
