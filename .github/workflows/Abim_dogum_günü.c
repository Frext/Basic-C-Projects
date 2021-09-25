#include <stdio.h>
#include <stdlib.h>
int main()
{ //                :-)
  int i,j;
  char dizi[]="Dogum Gunun Kutlu Olsun , Mutlu Ol Senelerce.";

  for(j=0;j<45;j++)
  {
  for(i=0;i<j;i++)
      printf("  ");
  printf("%c",dizi[j]);
  printf("\n");
  }
  printf("\n\n\n\t\t\t\t\t\t\t\t\t\t           <...>\n\t\t\t\t\t\t\t\t\t\t         EMRE USUL \n\t\t\t\t\t\t\t\t\t\t           <...>\n\n\n");
   for(j=44;j>-1;j--)
  {
  for(i=0;i<j;i++)
      printf("  ");
  printf("%c",dizi[j]);
  printf("\n"); }}
