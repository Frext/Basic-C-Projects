#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int i,j,k;
  char dizi[1000]="";     char f;
  char birinci[13]={"abcdefghijklm"};
  char ikinci[13]={"nopqrstuvwxyz"};

  printf("Lutfen metni giriniz.\n");
  gets(dizi);
  for(i=0;i<1000;i++)
  if(dizi[i]>='A' && dizi[i]<='Z')
  dizi[i]=dizi[i]+32;

  printf("Sifreleme yapilacak ise S , sifre cozulecek ise C harfini giriniz.\n");
  scanf("%c",&f);
 if(f=='C' || f=='c' || f=='S' || f=='s')
  {
  if(f=='S' || f=='s')
  printf("Sifrelenmis hali : ");
    else if(f=='C' || f=='c')
    printf("Cozulmus hali : ");

  for(i=0;i<strlen(dizi);i++)
{
  k=0;
  for(j=0;j<13;j++)
  {

  if(dizi[i]==birinci[j])
      k++;
  else if(dizi[i]==ikinci[j])
      k--;

  if(k==1)
  {
    dizi[i]=ikinci[j]; k++;
  }

  else if(k==-1)
  {
    dizi[i]=birinci[j]; k--;
  }}
  printf("%c",dizi[i]);
}}}
