#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "crypt.h"

void crypt(char* crypt,int touche)
{
int i;
system("date +%s%N > .date");
FILE * fic;
fic=fopen(".date","r");
char cle[128];
fgets(cle,128,fic);
for (i=0;i<strlen(cle);i++)
{
	if (cle[i+1]=='\n')
		cle[i]=touche+48;
	if (cle[i]=='\n')
		cle[i]='\0';
}
printf("%s\n",cle);
int seed=141000000;
long long div,num,reste;
num=atoll(cle);
//printf("%lli\n",num);
seed=num%seed;
srand(seed);
int alea=1+(rand()%9);
//char crypt[128];
i=0;
while (num!=1)
{
	div=num/alea;
	reste=num%alea;
	if (div==0)
		alea=1+rand()%9;
	else
	{
		//printf("%lli/%i =%lli\n",num,alea,div);
		crypt[i]=alea+48;
		i++;
		crypt[i]=reste+48;
		num=div;
		alea=1+rand()%9;
		i++;
	}
}
crypt[i]='\0';
printf("%s %i\n",crypt,i);
//decrypt (crypt);
printf("%s\n",cle);
}

long long decrypt (char *m)
{
int i;
long long num;
num=1;
for (i=strlen(m)-1;i>=0;i--)
{
	//printf("q=%i r=%i\n",m[i-1]-48,(int)m[i]-48);
	num=num*(m[i-1]-48);
	num=num+(m[i]-48);
	i--;
}
printf("%lli\n",num);
return num;
}

void epoch (char *cle)
{
int i;
system("date +%s%N > .date");
FILE * fic;
fic=fopen(".date","r");
fgets(cle,128,fic);
for (i=0;i<strlen(cle);i++)
{
	if (cle[i]=='\n')
		cle[i]='\0';
}
}	
