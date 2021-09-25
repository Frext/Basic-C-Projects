#include <stdio.h>
#include <stdlib.h>


int main()
{
 int a,b,c=1,num;
 printf("Please enter a number : ");
 scanf("%d",&num);

 for(a=1;a<=num;a++)
 {
     for(b=0;b<a;b++) // satirdaki sayilarin sayisini sayar 1 , 2 , 3... tane sayi yazdirir.
     {
         if(c>num)
     {
         break;
     }
     printf("%d ",c);
     c++;
     }

        if(c<=num) // zevk meselesi
      printf("\n");
 }
 printf("\n");
}
