#include <stdio.h>
#include <stdlib.h>

int main() // Finding the range between two times.
{
    int s_hour, s_minute, f_hour, f_minute,sh,sm;
    int i = 0, j = 0;

    printf("Enter the start time as hours and minutes separately, please\n");
    do{
        scanf("%d %d", &s_hour,&s_minute);
            }while (s_hour > 23 || s_hour < 0 || s_minute > 59 || s_minute < 0);    // in order to ask again if something goes wrong.

    printf("\nEnter the finish time as hours and minutes separately, please\n");
    do{
        scanf("%d %d", &f_hour,&f_minute);
            }while (f_hour > 23 || f_hour < 0 || f_minute > 59 || f_minute < 0);
    sh=s_hour,sm=s_minute;
    if(s_hour==f_hour && s_minute==f_minute)
    {
        i=24,j=0;
    }

    while((s_hour!=f_hour) || (s_minute!=f_minute))
    {
        while(s_minute!=f_minute)
        {
            s_minute++;
            if(s_minute==60)
            {
                s_minute=0;
                s_hour++;       // Question : Why there is no "i++"?
                if(s_hour==24)
                s_hour=0;
            }
            j++;
        }
        while(s_hour!=f_hour)
        {
            s_hour++;
            if(s_hour==24)
                s_hour=0;
            i++;
        }
    }


    printf("\nThe time range between the values : %d hour(s) , %d minute(s)\n%d:%d -> %d:%d\n", i, j,sh,sm,f_hour,f_minute);
}
