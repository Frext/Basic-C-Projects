#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <string.h>
int main(void) // if you don't pass any arguments, then use (void)
{
    char output[50],buf[12];
    printf("Welcome to the Mini Calendar program. The format is : ( DD / MM / YY) \n");
    struct tm *present;     /// https://linux.die.net/man/3/ctime
    time_t now = time(NULL);
    // or time(&now);

    present=localtime(&now);
    sprintf(output,"| %d.%d.%d |", present->tm_mday , present->tm_mon + 1 , present->tm_year+1900 );
    // to understand this visit the website

         switch(present->tm_mon)
    {
        case 0:strcpy(buf,"January");
        break;
        case 1:strcpy(buf,"February");
        break;
        case 2:strcpy(buf,"March");
        break;
        case 3:strcpy(buf,"April");
        break;
        case 4:strcpy(buf,"May");
        break;
        case 5:strcpy(buf,"June");
        break;
        case 6:strcpy(buf,"July");
        break;
        case 7:strcpy(buf,"August");
        break;
        case 8:strcpy(buf,"September");
        break;
        case 9:strcpy(buf,"October");
        break;
        case 10:strcpy(buf,"November");
        break;
        case 11:strcpy(buf,"December");
        break;
    }
    printf("\nThe month is | %s |.\n",buf);

    switch(present->tm_wday)
    {
        case 0:strcpy(buf,"Sunday");
        break;
        case 1:strcpy(buf,"Monday");
        break;
        case 2:strcpy(buf,"Tuesday");
        break;
        case 3:strcpy(buf,"Wednesday");
        break;
        case 4:strcpy(buf,"Thursday");
        break;
        case 5:strcpy(buf,"Friday");
        break;
        case 6:strcpy(buf,"Saturday");
        break;
    }
    printf("\nThe day is | %s |.\n",buf);

    printf("\nThere are | %d | day(s) left till the end of %d.\n",365- present->tm_yday , present->tm_year+1900); // this might be some unsatifying, you can add the info of hours and minutes too.

    if(present->tm_min) {
    printf("\nThere are | %d | day(s) , | %d | hours(s) and | %d | minute(s) left till the end of the week.\n", 6-present->tm_wday , 23-present->tm_hour , 60-present->tm_min);
    printf("\nThere are | %d | hour(s) and | %d | minute(s) left till the end of %s.\n",23-present->tm_hour , 60-present->tm_min, buf);
    }
    else {
    printf("\nThere are | %d | day(s) , | %d | hours(s) and | %d | minute(s) left till the end of the week.\n", 6-present->tm_wday , 24-present->tm_hour , 0);
    printf("\nThere are | %d | hour(s) and | %d | minute(s) left till the end of %s.\n",24-present->tm_hour , 0 , buf);
    }
    printf("\nThe date is = %s\n",output);
    return 0;
}
