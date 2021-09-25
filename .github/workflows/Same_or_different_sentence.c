#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void equal(char c[],char d[])
{
  int i=0,s,s2,sonuc;
  s=strlen(c);
  s2=strlen(d);

   for(i=0;i<s;i++) // Kucuk harfe cevirme
    {
     if((c[i]>='A') && (c[i]<='Z'))
     {
         c[i]=(int)c[i]+32;
     }
    }
       for(i=0;i<s2;i++) // Kucuk harfe cevirme
    {
     if((d[i]>='A') && (d[i]<='Z'))
     {
         d[i]=(int)d[i]+32;
     }
    }

  i=0;
  if(s==s2)
  {
    sonuc=strcmp(c,d);
    if(sonuc==0)
    printf("\nThey are same.\n");

    else
    printf("\nThey are different.\n");
  }
  else
  printf("\nThey are different.\n");
}

int main()
{
   char c[100],d[100];
   printf("Please enter the first sentence.\n");
   scanf("%s",c);
   printf("Please enter the second sentence.\n");
   scanf("%s",d);

   equal(c,d);
}

