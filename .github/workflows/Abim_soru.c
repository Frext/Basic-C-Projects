#include <stdio.h>
#include <stdlib.h>

int main()
{
  int maksimum,i,kat;
  printf("Maksimum sayiyi giriniz : ");
  scanf("%d",&maksimum);

  int dizi[maksimum];

  for(i=0;i<maksimum;i++)
  {
      dizi[i]=i+1;
  }

  i=0;
            while(i<10)
          {
              kat=0;
              while(dizi[i+(kat*10)]<=maksimum && i+(kat*10)<maksimum)
                {
                    printf("%d\t",dizi[i+(kat*10)]);
                    kat++;
                }
                printf("\n");
                i++;
          }
}
