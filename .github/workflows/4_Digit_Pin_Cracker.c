#include <stdio.h>
#include <stdlib.h>

#define NINE 9
int main(void)
{
    int ones,tens,hundreds,thousands;
    char password[5] ;
    for(thousands = 0 ; thousands <= NINE ; thousands ++)
    {
        for(hundreds = 0 ; hundreds <= NINE ; hundreds ++)
        {
            for(tens = 0 ; tens <= NINE ; tens ++)
            {
                for(ones = 0 ; ones <= NINE ; ones ++)
                {
                    sprintf(password,"%hu%hu%hu%hu",thousands,hundreds,tens,ones);
                    printf("%s\n",password);
                }
            }
        }
    }
}
