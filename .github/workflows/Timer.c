#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

int main( void )
{
    unsigned short int st,dk,sn;

    do
    {
        printf("Lutfen ne kadar surecegini saat,dakika,saniye sekilde giriniz (HH:MM:SS) : ");
        scanf("%hu%hu%hu",&st,&dk,&sn);
		fflush(stdin);
    }
    while( ( (st<0) || (dk<0) || (sn<0) || (dk>59) || (sn>59) ) 	|| 		( (st == 0) && (dk == 0) && (sn == 0) ) );


    while( 1 )
    {
        printf("%hu : %hu : %hu\n",st,dk,sn) ;
        sn-- ;


        if( ( dk==0 ) && ( sn == 0 ) )
        {
            if( st > 0 )
            {
            	Sleep(975);
                system("CLS");
                printf("%hu : %hu : %hu\n",st,dk,sn) ;


                st--;
                dk=59 ;
                sn=59 ;
            }
        }

        else if( sn == 0 )
        {
            if( dk > 0 )
            {
            	Sleep(975);
                system("CLS");
                printf("%hu : %hu : %hu\n",st,dk,sn) ;


                dk-- ;
                sn=59 ;
            }
        }

        if( (st == 0) && (dk == 0) && (sn == 0) )
        {
            Sleep(975);
            break;
        }

        Sleep(975);
        system("CLS");
    }

    system("CLS");
    for( unsigned short int i=0 ; i < 10 ; i++)
    {
        MessageBeep(MB_OK); // windows.h
        printf("Vakit dolmustur!\n\n\n\n");
        Sleep(1500);
    }
}