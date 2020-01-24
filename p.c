#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#define M 100

char playfiled[M][M] ;	//baraye khondn file
int i=0,j=0, sath=1;    //i mishe tedad satr ha, j mishe tedad soton ha j amodie          j mishe tedad soton ha,      sath ham ke 
int food[M][2];          //??!!??!!
int wall[M][2];          //manee haro neshon mide;
int check[M][M];
int waynum;
int theway[2*M][2];
int numberOfFood;
struct pacman{
	int x;
	int y;
}mypacman;
void gotoxy( int x, int y)
{
	COORD coord; 
	coord.X= x; 
	coord.Y= y; 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleCursorPosition( handle, coord); 
} 
int start()
{
	char r;
	FILE *ptf;
	char address[M];
	printf ("Enter the name and path of a text file: "); 
	scanf("%s" ,address);
	ptf=fopen(address ,"r");
	if(ptf==NULL)
	{
		printf("\nERROR : Cant open the file");
		return 0;
	}
	r=fgetc(ptf);
	if(r!='0')
	{
		sath=3;
	}
	while(r!=EOF)
	{
		if(r=='#')
		{
			sath=2;
			//wall[i][j]=1;
			check[i][j]=2;
		}
		if(r=='*')
			numberOfFood++;	
		if(r=='{' || r=='}' || r==',' || r=='\'')
		{
			continue;
		}	
		else if(r!='\n')
			playfiled[i][j]=r;
		else if(r=='0')
		{
			mypacman.x=i;
			mypacman.y=j;
		}	
		else if(r=='\n')
		{
			j++;
		}
		else
		{
			i++;
		}
		r=fgetc(ptf);
	}  
}
void printfiled()
{
	for(int x=0 ;x<i ;x++)
	{
		for(int y=0 ;y<j ;y++)
		{
			printf("%c" ,playfiled[x][y]);
		}
		printf("\n");
	}
}
int findaway(int satr ,int soton)//mikham bere hame rah haro emtehan kone 
{
	if(numberOfFood==0)//yani ghabli akharie
	{
		return 2;
	}
	if(check[satr][soton]!=0)//ye jaii ke ghablan checkesh kardam yaaa manee
	{
		return 0;
	}
	if(soton==j || satr==i || soton==-1 || satr==-1)//yani kharej shode
	{
		return 0;
	}
	///////// dargheire in sorat waredesh misahm
	check[satr][soton]=1;
	if(playfiled[satr][soton]=='*')
	{
		numberOfFood--;
	}
	int a[4]={0} ,sum=0;
	theway[waynum][0]=satr;
	theway[waynum][0]=soton+1;
	if(a[0]=findaway(satr ,soton+1)==0)
	{
		theway[waynum][0]=satr;
		theway[waynum][0]=soton-1;
		if(a[1]=findaway(satr ,soton-1)==0)
		{
			theway[waynum][0]=satr+1;
			theway[waynum][0]=soton;
			if(a[2]=findaway(satr+1 ,soton)==0)
			{
				theway[waynum][0]=satr-1;
				theway[waynum][0]=soton;
				a[3]=findaway(satr-1 ,soton);
			}
		}
	}
	for(int v=0 ;v<4 ;v++);
		sum+=a[i];
				
	if(sum>1)//masir peida shode wa alan to khone akharam
	{
//		gotoxy(soton+1 ,satr)
//		printf("\b%c" ,0)
//		return 1;
		check[i][j]=4;
		waynum++;
		return 1;
	}
	else if(sum==1)//masir peida shode wa alan to khone gheirrrrrrre akharam
	{
		check[i][j]=3;
		waynum++;
		return 1;
	}
	else
	{
		check[i][j]=0;
		return 0;
	}
	//0kardan dobare check!!
}
void showpath()
{
	printfiled();
	for(int l=waynum-2 ;l>0 ;l++)
	{
		gotoxy(theway[l][1]+1 , theway[l][0]);
		printf("\b%c" ,'1');
		sleep(1);
	}
	gotoxy(theway[0][1]+1 , theway[0][0]);
	printf("\b%c" ,'0');
	gotoxy(0,i+1);
	printf("Pacman finished eating:)");
	sleep(1);
	system("cls");
	printf("The Game Has End");
	
}
void sath1()
{
	printfiled();
	mypacman.x=0;
	mypacman.y=0;
	int eaten=0;
	for(int x=0; x<i ;x++){
		for(int y=0 ;y<j ;y++){
			if(playfiled[x][y]=='*')
			{
				eaten++;
				if(x==mypacman.x)
				{
					for(int a=mypacman.y; a<y ;a++)
					{
						gotoxy(a+1 , mypacman.x);
						printf("\b%c" ,'1');
						mypacman.y++;
						sleep(1);
					}	
					gotoxy(mypacman.y+1 , mypacman.x);
					printf("\b%c" ,'0');
					mypacman.y++;
					sleep(1);	
				}
				else{
					for(int z=mypacman.x ;z<x ;z++)
					{
						gotoxy(mypacman.y+1 ,mypacman.x);
						printf("\b%c" ,'1');
						sleep(1);
						mypacman.x++;
					}
					gotoxy(mypacman.y+1 ,++mypacman.x);
					printf("\b%c" ,'0');
					for(int a=mypacman.y; a<y ;a++)
					{
						gotoxy(a+1 , mypacman.x);
						printf("\b%c" ,'1');
						mypacman.y++;
						sleep(1);
					}	
					gotoxy(mypacman.y+1 , mypacman.x);
					printf("\b%c" ,'0');
					mypacman.y++;
					sleep(1);
				}
				if(eaten==numberOfFood)
				{
					gotoxy(0 ,6);
					printf("Pacman finished eating:)");
					sleep(1);
					system("cls");
					printf("The Game Has End");
				}
			}		
		}
	}
}
//void sath2()
//{
//	//miyonam for bezanam ke tamam khone haro bere baraye faz 2 wa 3 wali rah zibaii(!) nist:((((
//	
//}
int main()
{
	if(start()==0)
	{
		return 0;
	}
	if(sath==1)
	{
		sath1();
	}
	if(sath>=2)
	{
		findaway(mypacman.x , mypacman.y);
	}
}
/////////////////////////////////////////////////////////////////////////tamaom kardan sath 2 wa 3  wa behtar kardan sath yekam
/////////////////////////////////////////////////////////////////////////dibag kardan


