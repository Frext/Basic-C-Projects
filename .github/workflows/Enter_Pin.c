#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define EndOfStr 4
char pin[5] ;

void PrintAsterisks( )
{
    system("CLS");

    for( unsigned short int i = 0 ; pin[i] ; i ++ )
    {
        printf("*");
    }
}

int main( void )
{
    char tempChar ;
    unsigned short int  currentDigit = 0 ;

    while ( currentDigit < EndOfStr )	// keyboard hit = kbhit
    {
        while( !kbhit() )
        {
        }

        tempChar = getch();	// get the character without pressing enter

        if( ( ( tempChar >= '0' ) && ( tempChar <= '9' ) ) && ( currentDigit < EndOfStr ) )
        {
            pin [currentDigit] = tempChar ;
            currentDigit ++ ;
        }
        else if( (tempChar == 8) && ( currentDigit != 0 ) && ( currentDigit < EndOfStr ) )	// backspace
        {
            pin [ currentDigit - 1 ] = '\0';
            currentDigit -- ;
        }

        PrintAsterisks( );
    }
    printf("\nYour pin is |%s|.", pin );
}
