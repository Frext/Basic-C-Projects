#include <stdio.h>
#include <stdlib.h>

int main( void ) // 10 bit binary counter
{
    unsigned short int number, arrayIndex = 0 ;

    do
    {
        printf("Enter a number from 0 to 1023 , please : ");
        scanf("%hu", &number );
    }
    while( (number >= 1024) || (number < 0) );


    unsigned short int binaryForm [10] ;

    for( arrayIndex = 0 ; arrayIndex <=9 ; arrayIndex++) {
        binaryForm [ arrayIndex ] = 0;
    }

    arrayIndex = 9 ;

    while(number >= 1)
    {
        binaryForm[ arrayIndex ] = (number % 2) ;
        arrayIndex --;
        number = number / 2;
    }

	printf("\n\n");

    for( arrayIndex = 0 ; arrayIndex <= 9 ; arrayIndex ++)
    {
        printf("%hu ", binaryForm[ arrayIndex ] );
    }

    printf("\n\n");
}
