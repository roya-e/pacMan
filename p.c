#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#define M 100

char playfiled[M][M] ;	//baraye khondn file
int i=0,j=0, sath=1;
int food[M][2];
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
		sath=3;
	while(r!=EOF)
	{
		if(r='#')
			sath=2;
		if(r=='*')
			numberOfFood++;	
		if(r!='\n')
			playfiled[i][j]=r;
		if(r=='\n')
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
					system("cls");
					printf("The Game Has End");
				}
			}		
		}
	}
}
void sath2()
{
	//miyonam for bezanam ke tamam khone haro bere baraye faz 2 wa 3 wali rah zibaii(!) nist:((((
}
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
	if(sath==2)
	{
		sath2();
	}
}

