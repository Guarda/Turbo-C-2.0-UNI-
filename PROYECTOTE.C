#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<process.h>
#include<mouse.h>
#include<alloc.h>
#include<dos.h>
#include<math.h>

#define X 0
#define Y 1
#define DIM 2  /*dimension de los puntos*/
#define TRI 3	/*numero de vertices de un triangulo*/
#define CORD 4	/*numero de coordenadas de 2 puntos*/
#define PMAX 50 /*numero maximo de puntos para poligono*/

typedef enum {FALSE,TRUE} bool;
typedef int tPointi[DIM];  /*puntos de tipo entero*/
typedef tPointi tPolygoni[PMAX];  /*poligono de enteros*/

bool Left(tPointi a, tPointi b, tPointi c), LeftOn(tPointi a,tPointi b,tPointi c), Collinear(tPointi a, tPointi b, tPointi c),Between(tPointi a, tPointi b, tPointi c),
Xor(bool x, bool y),Diagonalie(int i,int j,int n,tPolygoni P),InCone(int i,int j,int n,tPolygoni P),Diagonal(int i, int j, int n, tPolygoni P),
extreme(tPolygoni P,int s,int i,int j),IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d),concavo(int i,int n,tPolygoni P),Imply(tPointi q,tPolygoni P,int n),antihorario(tPolygoni P,int n,int labels[]);

int Area2(tPointi a, tPointi b, tPointi c), aris_ext(tPolygoni P,int s,int aris[][CORD]), punt_ext(tPolygoni P,int labels[],int n),
ReadPoints(tPolygoni P), Border(tPointi q,tPolygoni P,int n);

void etiquetar(int labels[],int n);
void PointAssign(tPointi a,tPointi b);
void ClipEar1(int i,int n,tPolygoni P,int labels[]);
void Triangulate1(int n, tPolygoni P,int vertex[][TRI]);

void func_itoa(int x,int y);
void logo();
void muestra_puntos(int num,int [][2]);
void diagonales(int p,int [][2]);




void main (void){
	char r,counter[10];
	int adapter=DETECT,modo,t=0,c=320,e=240,n=0,h,k,c1,e1,P[100][2];
	initgraph (&adapter,&modo,"C:\\tc20\\bin");
	setbkcolor(BLACK);
	logo();
	mver();
	msituar(1,320,240);

	while(!kbhit()){
		n=0;
		c=mxpos(1);
		e=mypos(1);

		func_itoa(c,e);

			if(mclick()==1&&n!=1){
			delay(100);
			if(t==0){

				P[t][0]=mxpos(1);
				P[t][1]=mypos(1);
			  	mocultar();
				putpixel(P[t][0],P[t][1],YELLOW);
				mver();
				c1=h=P[t][0];
				e1=k=P[t][1];
				itoa(t,counter,10);
				outtextxy(0,0,counter);
				n=1;
				t++;
			}
			else if(t==1){
				P[t][0]=mxpos(1);
				P[t][1]=mypos(1);
				setcolor(YELLOW);
				line(h,k,P[t][0],P[t][1]);

				h=P[t][0];
				k=P[t][1];
				itoa(t,counter,10);
				setfillstyle(1,BLACK);
				bar(0,0,20,20);
				outtextxy(0,0,counter);

				t++;

				n=1;
			}else if(t>=2){
			P[t][0]=mxpos(1);
			P[t][1]=mypos(1);
			setcolor(YELLOW);
			mocultar();
			line(h,k,P[t][0],P[t][1]);
			mver();
			h=mxpos(1);
			k=mypos(1);
				itoa(t,counter,10);
				setfillstyle(1,BLACK);
				bar(0,0,20,20);
				outtextxy(0,0,counter);

			t++;
			n=1;
			}
		} else if(mclick()==2){
			setcolor(YELLOW);
			line(h,k,c1,e1);

			muestra_puntos(t,P);


			n=1;
		}
	}


	do{
	r=getch();
	switch(r)
	case 13:{

	itoa(t,counter,10);
	outtextxy(290,440,"n� puntos");
	outtextxy(290,450,counter);
	Triangulate1(t,P,P);


	}

	}while(r!=27);
	getch();
	closegraph();
}

void func_itoa(int x, int y){
   char x1[10],x2[10];
   delay(100);
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

void muestra_puntos(int num,int P[][2]){
int ini,g=50,oc=0;

char equis[10],ye[10],oie[100];
setfillstyle(1,BLUE);
bar(460,0,640,440);
outtextxy(490,50,"x");
outtextxy(530,50,"y");

for(ini=0;ini<num;ini++){
	setcolor(YELLOW);
	itoa(P[ini][0],equis,10);
	itoa(P[ini][1],ye,10);

	outtextxy(490,g=g+15,equis);
	outtextxy(530,g,ye);

	setcolor(RED);
	itoa(oc,oie,10);
	outtextxy(470,g,oie);
	outtextxy(P[ini][0]-15,P[ini][1],oie);
	oc++;
}

}
void diagonales(int p,int P[][2]){
int n,l;
char m[10],h[10];
setcolor(RED);
	for(n=0;n<=p-1;n++){
		for(l=0;l<=p-1;l++){
		if((n-l)==1){
		setcolor(BLUE);
		line(P[n][0],P[n][1],P[l][0],P[l][1]);
		delay(1000);
		}else if((n-l)<=0){
		setcolor(RED);
		line(P[n][0],P[n][1],P[l][0],P[l][1]);
		itoa(n,m,10);
		itoa(l,h,10);
		setfillstyle(1,BLACK);
		bar(0,0,30,25);
		outtextxy(0,0,m);
		outtextxy(0,10,h);
		delay(1000);
		}else if((n-l)==(p-1)){
			delay(1000);
			setcolor(BLUE);
			line(P[n][0],P[n][1],P[l][0],P[l][1]);
		}
		}
	}
}
void logo(){
	setfillstyle(1,GREEN);
	bar(0,440,640,480);
	setfillstyle(1,BLUE);
	bar(460,0,640,440);
}
int Area2(tPointi a, tPointi b, tPointi c)

/*retorna dos veces el area del triangulo formado por a,b,c*/

{
	return((a[0] * b[1]) - (a[1] * b[0]) + (a[1] * c[0]) - (a[0] * c[1]) + (b[0] * c[1]) - (c[0] * b[1]));
}

bool Left(tPointi a, tPointi b, tPointi c)

/*retorna verdadero si c esta a la izquierda del segmento ab*/

{
 return Area2(a,b,c)>0;
}

bool LeftOn(tPointi a,tPointi b,tPointi c)

/*retorna verdadero si c esta a la izquierda o sobre el segmento ab*/

{
 return Area2(a,b,c)>=0;
}

bool Collinear(tPointi a, tPointi b, tPointi c)

/* retorna verdadero si los puntos a,b,c son colineales*/

{
 return Area2(a,b,c)==0;
}

bool Xor(bool x, bool y)

/*o exclusivo. Retorna verdadero si exactamente uno de los argumentos es
verdadero. Los argumentos son negados para asegurar que tienen valores 0/1*/

{
	return !x^!y;
}

bool IntersectProp(tPointi a, tPointi b, tPointi c, tPointi d)

{

 if(Collinear(a, b, c)||Collinear(a, b, d)||Collinear(c, d, a)||Collinear(c, d, b))
	 return (FALSE);
 return Xor(Left(a, b, c), Left(a, b, d)) && Xor(Left(c, d, a), Left(c, d, b));
}

bool Between(tPointi a, tPointi b, tPointi c)

/*retorna verdadero si a,b y c son colineales y el punto c yace sobre el
segmento cerrado ab*/

{
 if(!Collinear(a, b, c))
	return FALSE;
 if(a[X] != b[X])
	return((a[X] <= c[X]) && (c[X] <= b[X])) || ((a[X] >= c[X]) && (c[X] >= b[X]));
 else
	return((a[Y] <= c[Y]) && (c[Y] <= b[Y])) || ((a[Y] >= c[Y]) && (c[Y] >= b[Y]));
}

bool Intersect(tPointi a, tPointi b, tPointi c, tPointi d)

/*retorna verdadero if los segmentos ab y cd se intersectan propia o
impropiamente*/

{
 if(IntersectProp(a, b, c, d))
	return TRUE;
 else
	if(Between(a, b, c)||Between(a, b, d)||Between(c, d, a)||Between(c, d, b))
		return TRUE;
	else
		return FALSE;
}

bool Diagonalie(int i,int j,int n,tPolygoni P)

/*retorna verdadero si vi,vj una diagonal interna o externa propia de P*/

{
	int k, k1;
	for(k=0;k<n;k++)
	{
		k1 = (k + 1)%n;
		if(!((k == i) || (k1 == i) || (k == j) || (k1 == j)))
			if(Intersect(P[i], P[j], P[k], P[k1]))
				return FALSE;
	}
	return TRUE;
}

bool InCone(int i,int j,int n,tPolygoni P)

/*retorna verdadero si la diagonal i,j es estrictamente interna al poligono P
en la vecindad del punto final i*/

{
	int i1, in1;
	i1 = (i + 1)%n;
	in1 = (i + n - 1)%n;
	if(LeftOn(P[in1], P[i],P[i1]))
		return Left(P[i], P[j], P[in1]) && Left(P[j], P[i], P[i1]);
	else
		return !(LeftOn(P[i], P[j], P[i1]) && LeftOn(P[j], P[i], P[in1]));
}

bool Diagonal(int i, int j, int n, tPolygoni P)

/*retorna verdadero si i,j es una diagonal propia interna de P*/

{
	return(InCone(i, j, n, P) && Diagonalie(i, j, n, P));
}

void PointAssign(tPointi a,tPointi b)

/*asigna los puntos de la coordenada a a b*/

{
	int i;
	for(i=0;i<DIM;i++)
		a[i] = b[i];
}

void ClipEar1(int i,int n,tPolygoni P,int labels[])

/*remueve P[i] al copiar p[i+1]. Actualiza los vertices del poligono una
vez hecha una triangulacion*/

{
	int k;
	for(k=i;k<(n-1);k++)
	{
		PointAssign(P[k],P[k+1]);
		labels[k] = labels[k+1];
	}
}


void TriRecurse(int n,tPolygoni P,int labels[],int vertex[][TRI],int *cont)
{
	int i,i1,i2,x,y,x1,y1;
	if(n>3)
		for(i=0;i<n;i++)
		{
			i1 = (i + 1)%n;
			i2 = (i + 2)%n;

			/*analiza si diagonal i es i2 es interna y si su interseccion con
			el poligono es apropiada*/

			if(Diagonal(i,i2,n,P))
			{
				x=P[i][0];
				 y=P[i][1];
				 x1=P[i2][0];
				 y1=P[i2][1];
				vertex[*cont][0]=labels[i];
				vertex[*cont][1]=labels[i1];
				vertex[*cont][2]=labels[2];
				line(x,y,x1,y1);
				*cont++;
				ClipEar1(i1,n,P,labels);
				TriRecurse(n-1,P,labels,vertex,cont);
				break;
			}
		}
}


void Triangulate1(int n, tPolygoni P,int vertex[][TRI])

/*triangula el poligono P, imprime las coordenadas de los puntos finales*/


{
	tPolygoni Pt;


	int labels[PMAX],cont=0,poly[2*PMAX],i;
	for(i=0;i<n;i++)
	{
		PointAssign(Pt[i],P[i]);
		labels[i]=i;
		poly[cont]=P[i][0];
		poly[++cont]=P[i][1];
		cont++;
	 }
	/* printf("Diagonales de la triangulaci¢n : \n");*/
	 poly[cont]=P[0][0];
	 poly[cont+1]=P[0][1];
	 setcolor(BLUE);
	 mocultar();
     drawpoly(n+1,poly);
	 setcolor(RED);
	 TriRecurse(n,Pt,labels,vertex,&cont);
	 mver();
	 system("PAUSE");
   exit(0);
}







bool concavo(int i,int n,tPolygoni P)

/*retorna  verdadero si el vertice es concavo. En otro caso retorna falso*/

{
	int i1,in1;
	i1=(i+1)%n;
	in1=(i+n-1)%n;
	if(!(LeftOn(P[in1],P[i],P[i1])))
		return TRUE;
	else
		return FALSE;
}

bool antihorario(tPolygoni P,int n,int labels[])

/*Encuentra el punto mas bajo(p) en Y y mas a la derecha en X.Luego calcula su
 punto anterior(p-) y posterior(p+) y calcula el area formada por p-,p,p+.
 Si esta es positiva los puntos estan en sentido antihorario y la funcion
 retorna TRUE, en otro caso retorna FALSE.*/

{
	int i,v,vplus,vless,low;
	low=P[0][1];
	v=labels[0];
	for(i=1;i<n;i++)
	{
		if(low>P[i][1])  /*comparando las coordenadas en y*/
		{
			low=P[i][1];    /*asignando el de menor coordenada en y*/
			v=labels[i];
		}
		if(low==P[i][1])      /*comparando la coordenada en x*/
		/*asignando el y de coordenada mayor en x*/
			v=(P[v][0]<P[i][0])?labels[i]:labels[v];
	 }
	vplus=(v+1)%n;    /*calculando el v+*/
	vless=(v+n-1)%n;  /*calculando el v-*/
	if(Area2(P[vless],P[v],P[vplus])>0)   /*calculando el area */
		return TRUE; /*si el area es positiva return TRUE*/
	else
		return FALSE;   /*en otro caso return FALSE*/
}

bool Imply(tPointi q,tPolygoni P,int n)

/*retorna True si el punto q es interno al poligono P y False en otro caso*/

{
	int i,i1,d,cruce=0;
	tPolygoni Pt; /*se declara Pt para evitar errores al pedir un nuevo
					punto de consulta para el mismo poligono P*/
	double x;
	for(i=0;i<n;i++)
		for(d=0;d<DIM;d++)
			Pt[i][d]=P[i][d]-q[d];  /*trasladando el poligono al eje x*/
	for(i=0;i<n;i++)
	{
		i1=(i+n-1)%n;  /*el vertice anterior del poligono*/
		if(((Pt[i][Y]>0)&&(Pt[i1][Y]<=0))||((Pt[i1][Y]>0)&&(Pt[i][Y]<=0)))

		/*compara si uno de los puntos finales de la arista esta estrictamente
		arriba de la recta r (q) y el otro punto final esta abajo o sobre r*/

		{
			x=(Pt[i][X]*Pt[i1][Y]-Pt[i1][X]*Pt[i][Y])/(double)(Pt[i1][Y]-Pt[i][Y]);
			if(x>0)
				cruce++;
		}
	}
	if((cruce%2)==1)  /*si el numero de cruces es impar q es interno*/
		return TRUE;
	else
		return FALSE;
}

int Border(tPointi q,tPolygoni P,int n)
{
	int i,i1;
	for(i=0;i<n;i++)
	{
		i1=(i+n-1)%n;
		if(Between(P[i1],P[i],q)) /*si el punto q esta entre i,i1 esta en la frontera*/
			return(0);   /*el 1 indica que el punto q esta en la frontera de P*/
	}
	if(Imply(q,P,n))
		return(1); /*el 2 indica que el punto q es interno al poligono P*/
	else
		return(-1); /*el 0 indica que el punto q no pertenece al poligono P*/
}

void etiquetar(int labels[],int n)
{
int i;
for(i=0;i<n;i++)
	labels[i]=i;
}

bool extreme(tPolygoni P,int s,int i,int j)

/*Determina si una arista es extrema o no.Si P[k] no esta a la izquierda o
	en P[i],P[j](se utilizo la negacion de la funcion LeftOn),entonces, no
	es extrema(retornando FALSE).Retorna TRUE cuando la arista es extrema,
	es decir que todos los puntos estan a la izquierda de ella*/

{
int k;
for(k=0;k<s;k++)
	if((k!=i)&&(k!=j))
		if(!LeftOn(P[i],P[j],P[k]))
			return FALSE; /*retorna TRUE si todos los puntos
				      estan a la izquierda*/
return TRUE;
}

int punt_ext(tPolygoni P,int labels[],int n)

/*Encuentra los puntos extremos que determinan el cierre convexo y
reasigna los puntos y sus coordenadas en labels y P respectivamente, ademas
retorna el numero de puntos extremos. La tecnica usada en la determinacion
de los puntos extremos es que si estos son no extremos se les asigna -1 en
labels, siendo los puntos extremos los que no tiene -1 en labels. */

{
	int i,j,k,l,s=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
				if(j!=i)
					for(k=0;k<n;k++)
						if((k!=i)&&(k!=j))
							for(l=0;l<n;l++)
								if((l!=i)&&(l!=j)&&(l!=k))
									if(LeftOn(P[i],P[j],P[l]))
										if(LeftOn(P[j],P[k],P[l]))
											if(LeftOn(P[k],P[i],P[l]))
												labels[l]=-1;
/*se le asigna -1 a los puntos no extremos*/
 printf("\n\nPuntos\t\tCoordenadas");
	for(i=0;i<n;i++)
		if(labels[i]!=-1)
		{     /*reasignando el arreglo de etiquetas y el P con
		     las etiquetas y puntos extremos respectivamente*/

			printf("\n%d\t\t[%d,%d]",labels[i],P[i][0],P[i][1]);
			labels[s]=i;
			P[s][0]=P[i][0];
			P[s][1]=P[i][1];
			s+=1;
		}
	return s;
}

int aris_ext(tPolygoni P,int s,int aris[][CORD])

/*Encuentra las aristas extremas utilizando los puntos extremos almacenados
	en labels(labels y P ya fueron reasignados en la funcion punt_ext,
	conteniendo	los puntos extremos y sus coordenadas respectivamente).
	Si la funcion extreme retorna TRUE	entonces imprime : el listado	de
	aristas extremas y su conexion.*/

{
int i,j,k=0;
printf("\n\nAristas\t\tCoordenadas\n\n");
for(i=0;i<s;i++)
	for(j=0;j<s;j++)
		if(j!=i)
		{
			if(extreme(P,s,i,j))
			{
				aris[k][0]=P[i][X];
				aris[k][1]=P[i][Y];
				aris[k][2]=P[j][X];
				aris[k][3]=P[j][Y];
				k++;
			}
		}
return(k);
}
