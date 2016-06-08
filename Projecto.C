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
#define DIM 2
#define PMAX 100

typedef enum {FALSE,TRUE} bool;

bool LeftOn(int a[],int b[],int c[]), Between(int a[],int b[],int c[]), Collinear(int a[],int b[],int c[]),
InCone(int i,int j,int n,int [][2]), Diagonal(int i,int j,int n,int [][2]), Diagonalie(int i,int j,int n,int [][2]),
Intersect(int a[],int b[],int c[],int d[]), Left(int a[],int b[],int c[]), IntersectProp(int a[],int b[],int c[],int d[]), Xor(bool x,bool y);

void func_itoa(int x,int y);
void logo();
void muestra_puntos(int num,int [][2]);
void diagonales(int p,int [][2]);

void PointAssign(int [],int []),  Triangulate(int,int [][2]),
TriRecurse(int,int [][2],int []), ClipEar(int,int,int [][2],int []);



long Area2(int [],int [],int []);

void main (void){
	char r,counter[10];
	int adapter=DETECT,modo,t=0,c=320,e=240,men=0,n=0,h,k,c1,e1,mayo=-99999,meno=99999,l=0,P[100][2];
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
	Triangulate(t,P);


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

long Area2(int a[],int b[],int c[])
{
   long area;
   area=((a[0]*b[1])-(a[1]*b[0])+(b[0]*c[1])-(b[1]*c[0])+(c[0]*a[1])-(c[1]*b[0]));
   return(area);
}

bool Left(int a[],int b[],int c[])
{
  return(Area2(a,b,c)>0);
}

bool LeftOn(int a[],int b[],int c[])
{
  return(Area2(a,b,c)>=0);
}

bool Collinear(int a[],int b[],int c[])
{
  return(Area2(a,b,c)==0);
}

bool IntersectProp(int a[],int b[],int c[],int d[])
{
  if(Collinear(a,b,c)||Collinear(a,b,d)||Collinear(c,d,a)||Collinear(c,d,b))
		return(FALSE);
		return(Xor(Left(a,b,c),Left(a,b,d))&&Xor(Left(c,d,a),Left(c,d,b)));
}

bool Between(int a[],int b[],int c[])
{
  if(!Collinear(a,b,c))
	   return FALSE;
  if(a[X]!=b[X])
	   return((a[X]<=c[X])&&(c[X]<=b[X]))||((a[X]>=c[X])&&(c[X]>=b[X]));
  else
	   return((a[Y]<=c[Y])&&(c[Y]<=b[Y]))||((a[Y]>=c[Y])&&(c[Y]>=b[Y]));
}

bool Intersect(int a[],int b[],int c[],int d[])
{
   if(IntersectProp(a,b,c,d))
	   return TRUE;
   else
   if(Between(a,b,c)||Between(a,b,d)||Between(c,d,a)||Between(c,d,b))
	   return TRUE;
   else
	   return FALSE;
}

bool Diagonalie(int i,int j,int n,int P[][2])
{
   int k,k1;
   for(k=0;k<n;k++)
	   {
		 k1=((k+1)%n);
		 if(!((k==i)||(k1==i)||(k==j)||(k1==j)))
			  if(Intersect(P[i],P[j],P[k],P[k1]))
				  return FALSE;
	   }
	   return TRUE;
}

bool InCone(int i,int j,int n,int P[][2])
{
   int i1,in1;
   i1=(i+1)%n;
   in1=(i+n-1)%n;
   if(LeftOn(P[in1],P[i],P[i1]))
	  return(Left(P[i],P[j],P[in1])&& Left(P[j],P[i],P[i1]));
   else
	  return(!(LeftOn(P[i],P[j],P[i1])&& LeftOn(P[j],P[i],P[in1])));
}

bool Diagonal(int i,int j,int n,int P[][2])
{
   return(InCone(i,j,n,P)&& Diagonalie(i,j,n,P));
}

void Triangulate(int n,int P[][2])
{
   int Pt[PMAX][2];
   int labels[PMAX],poly[2*PMAX],i,j=0; 
   
   for(i=0;i<n;i++)
   {
	 PointAssign(Pt[i],P[i]);
		 labels[i]=i;
		 poly[j]=P[i][0];
		 poly[++j]=P[i][1];
		 j++;
   }
   poly[j]=P[0][0];
   poly[j+1]=P[0][1];
   drawpoly(n+1,poly);
   TriRecurse(n,Pt,labels);
   system("PAUSE");
   exit(0);
}

void ClipEar(int i,int n,int P[][2],int labels[])
{
  int k;
  for(k=i;k<(n-1);k++)
   {
	 PointAssign(P[k],P[k+1]);
	 labels[k]=labels[k+1];
   }
}

void TriRecurse(int n,int P[][2],int labels[])
{
  int x,y,x1,y1,i,i1,i2;
  if(n>3)
   for(i=0;i<n;i++)
	 {
	   i1=(i+1)%n;
	   i2=(i+2)%n;
		 if(Diagonal(i,i2,n,P))
		 {
				 x=P[i][0];
				 y=P[i][1];
				 x1=P[i2][0];
				 y1=P[i2][1];
				 setlinestyle(DASHED_LINE,0,1);
				 line(x,y,x1,y1);
				 ClipEar(i1,n,P,labels);
				 TriRecurse(n-1,P,labels);
				 break;
		 }
	  }
}

bool Xor(bool x,bool y)
{
return(!x^!y);
}

void PointAssign(int a[],int b[])
{
   int i;
   for(i=0;i<DIM;i++)
   a[i]=b[i];
} 