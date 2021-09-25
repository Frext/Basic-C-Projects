#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <windows.h>

unsigned short int dikeyEkranaBasma,yatayEkranaBasma;
unsigned short int BirinciOyuncuPuan,IkinciOyuncuPuan;
char  OyunAlani[101], oyuncu1ad[21], oyuncu2ad[21];

void OyunAlaniniEkranaBastir()
{
    system("CLS");
    printf("---1.Oyuncu ( %s ): %d\n---2.Oyuncu ( %s ): %d\n",oyuncu1ad,BirinciOyuncuPuan,oyuncu2ad,IkinciOyuncuPuan);
    printf("\n**********************************************\n     1   2   3   4   5   6   7   8   9   10");
    dikeyEkranaBasma=1;
    for(yatayEkranaBasma=0; yatayEkranaBasma<=90; yatayEkranaBasma+=10)
    {
        printf("\n%2hu   %c   %c   %c   %c   %c   %c   %c   %c   %c   %c",dikeyEkranaBasma,OyunAlani[yatayEkranaBasma],OyunAlani[yatayEkranaBasma+1],OyunAlani[yatayEkranaBasma+2],OyunAlani[yatayEkranaBasma+3],OyunAlani[yatayEkranaBasma+4],OyunAlani[yatayEkranaBasma+5],OyunAlani[yatayEkranaBasma+6],OyunAlani[yatayEkranaBasma+7],OyunAlani[yatayEkranaBasma+8],OyunAlani[yatayEkranaBasma+9]);
        dikeyEkranaBasma++;
    }
    printf("\n\n**********************************************\n");
}

int main(void)
{
    /// DEGISKEN TANIMLAMA

    unsigned short int sutunNo, satirNo,ProgramSonKontrol, KareNo, OyuncuSira, siraDegisimKontrol;       // a=puan eklemek icin
    unsigned short int yukarikontrol[100]= {0},yankontrol[100]= {0},ters1[100]= {0},ters2[100]= {0}; // kontrolsuz puan artisini engellemek icin 4 tane dizi
    unsigned short int HarfGirisiKontrol[100]= {0};
    char karar;


    /// OYUNCULARIN ADLARINI ALMA

    printf("1. oyuncunun adi : ");
    gets(oyuncu1ad);
    fflush(stdin);
    printf("2. oyuncunun adi : ");
    gets(oyuncu2ad);
    fflush(stdin);

    OyuncuSira=1;
    BirinciOyuncuPuan=0,IkinciOyuncuPuan=0;
    ProgramSonKontrol=0;

    for(KareNo=0; KareNo<100; KareNo++)
        OyunAlani[KareNo]='.';

    while(ProgramSonKontrol<100)
    {
        /// HARF ALMA, HARFI YERLESTIRME ve OYUNCULARIN SIRASINI AYARLAMA

        while(1)
        {
            OyunAlaniniEkranaBastir();
            printf("\n\n[ Sira %hu. oyuncuda ",OyuncuSira);
            if(OyuncuSira==1)
            {
                printf("( %s ) ] Hangi harfi yazacaksiniz? : ",oyuncu1ad);
            }
            else
            {
                printf("( %s ) ] Hangi harfi yazacaksiniz? : ",oyuncu2ad);
            }
            scanf("%1c",&karar);
            fflush(stdin);
            if(karar=='s')
                karar='S';
            else if(karar=='o')
                karar='O';

            if((karar!='S') && (karar!='O'))
            {
                printf("\n()()Lutfen sadece 'S' veya 'O' harfini giriniz.()()\n");
                Sleep(2500);
                system("CLS");
            }
            else
            {
                break;
            }
        }
        while(1)
        {
            printf("\nLutfen once sutun, sonra satir numarasini giriniz.\n");
            scanf("%hu%hu",&sutunNo,&satirNo);	// sutun yatay, satir dikey
            fflush(stdin);

            if( (sutunNo<11) && (sutunNo>0) && (satirNo<11) && (satirNo>0) )
            {
                KareNo=(satirNo-1)*10;

                KareNo += (sutunNo-1);
                if (HarfGirisiKontrol[KareNo]==0) // kilitleme
                {
                    OyunAlani[KareNo] = karar;
                    HarfGirisiKontrol[KareNo] = 1;
                    ProgramSonKontrol++;

                    if(OyuncuSira==1)
                        OyuncuSira=2;
                    else
                        OyuncuSira=1;

                    break;
                }
                else if ( HarfGirisiKontrol[KareNo]!=0 )
                {
                    printf("\n()()()Lutfen onceden girilen bir karenin uzerine yeniden bir sey girmeye calismayin!()()()\n\n");

                    Sleep(2500);
                    system("CLS");

                    OyunAlaniniEkranaBastir();
                }
            }
            /// SATIN VE SUTUN NO ALIRKEN SORUN CIKARSA VERILECEK HATALAR
            else
            {
                if((sutunNo>10) || (sutunNo<1))
                {
                    printf("\n()Lutfen 1 ile 10 arasinda bir sutun degeri giriniz.()\n");
                }
                if((satirNo<1) || (satirNo>10))
                {
                    printf("\n()Lutfen 1 ile 10 arasinda bir satir degeri giriniz.()\n");
                }
                Sleep(2500);
                system("CLS");
            }
        }
        /// PUAN ARTISI
        siraDegisimKontrol=0;
        for(KareNo=0; KareNo<100; KareNo++)
        {
            if((OyunAlani[KareNo]=='S') && (OyunAlani[KareNo+10]=='O') && (OyunAlani[KareNo+20]=='S') && (yukarikontrol[KareNo]==0)) // Yukaridan asagi
            {
                if(OyuncuSira==1)
                    IkinciOyuncuPuan++;
                else
                    BirinciOyuncuPuan++;

                siraDegisimKontrol=1;
                yukarikontrol[KareNo]=1;
            }

            if((OyunAlani[KareNo]=='S') && (OyunAlani[KareNo+1]=='O') && (OyunAlani[KareNo+2]=='S') && ( (KareNo/10) == ((KareNo+1)/10) ) && ( (KareNo/10) == ((KareNo+2)/10) ) && (yankontrol[KareNo]==0)) // Yan yana
            {
                if(OyuncuSira==1)
                    IkinciOyuncuPuan++;

                else
                    BirinciOyuncuPuan++;

                siraDegisimKontrol=1;
                yankontrol[KareNo]=1;
            }

            if((OyunAlani[KareNo]=='S') && (OyunAlani[KareNo+9]=='O') && (OyunAlani[KareNo+18]=='S') && ((KareNo/10)+1 == (KareNo+9)/10) && ( (KareNo/10)+2==(KareNo+18)/10) && (ters1[KareNo]==0))  //   Ters  / seklinde
            {
                if(OyuncuSira==1)
                    IkinciOyuncuPuan++;

                else
                    BirinciOyuncuPuan++;

                siraDegisimKontrol=1;;
                ters1[KareNo]=1;
            }

            if((OyunAlani[KareNo]=='S') && (OyunAlani[KareNo+11]=='O') && (OyunAlani[KareNo+22]=='S') && ( (KareNo/10)+1 == (KareNo+11)/10 ) && ( (KareNo/10)+2==(KareNo+22)/10 )  && (ters2[KareNo]==0)) //     Ters  \ seklinde
            {
                if(OyuncuSira==1)
                    IkinciOyuncuPuan++;
                else
                    BirinciOyuncuPuan++;

                siraDegisimKontrol=1;
                ters2[KareNo]=1;
                if((OyunAlani[KareNo+2]=='S') && (OyunAlani[KareNo+11]=='O') && (OyunAlani[KareNo+20]=='S') && ( (KareNo/10)+1 == (KareNo+11)/10) && ( (KareNo/10)+2 == (KareNo+20)/10) && (ters1[KareNo]==0)) //    /\ seklinde olursa diye
                {
                    ters1[KareNo+2]=1;

                    if(OyuncuSira==1)
                        IkinciOyuncuPuan++;
                    else
                        BirinciOyuncuPuan++;
                }
            }
        }
        if(siraDegisimKontrol != 0)
        {
            if(OyuncuSira==1)
                OyuncuSira=2;
            else
                OyuncuSira=1;
        }
    }

/// OYUN SONU BILGILERI
	Sleep(350);
	system("CLS");
    printf("\n\n Sonuclar\n ------------\n 1.Oyuncu (%s) = %d\n 2.Oyuncu (%s)= %d\n ------------\n",oyuncu1ad,BirinciOyuncuPuan,oyuncu2ad,IkinciOyuncuPuan);
    if(BirinciOyuncuPuan < IkinciOyuncuPuan) printf("\n |Kazanan 2. Oyuncu (%s)!\n",oyuncu2ad);
    else if(IkinciOyuncuPuan < BirinciOyuncuPuan) printf("\n |Kazanan 1. Oyuncu (%s)!\n",oyuncu1ad);
    else printf("\n\n |Berabere!\n");

/// HATA BILDIRME

    printf("\n\n Oyunda herhangi bir hata ile karsilastiniz mi? ( Evet = 1 , Hayir = 0 ) : ");
    scanf("%1c",&karar);
    fflush(stdin);
    if(karar=='1')
    {
        char hatametin[250];
        FILE *hatadosya;
        hatadosya=fopen("SOS_hata.txt","a");
        if(hatadosya!=NULL)
        {
            time_t t;
            time(&t);
            printf("\n Lutfen karsilastiginiz hatayi giriniz ( max. 500 kelime ) : ");
            gets(hatametin);
            fprintf(hatadosya,"%s-------------------------\nOyuncular : %s / %s\nHata : %s\n\n\n",ctime(&t),oyuncu1ad,oyuncu2ad,hatametin);
        }
        else
            printf("\n**Hatayi yazdiracak dosya acilamadi!");
        fclose(hatadosya);
    }
    printf("\n Geribildiriminiz icin tesekkur ederim.\n\n");
}
