#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#define maxsize 100
#define keychar '\n'

char *filename="File.sc";

void selectOption(unsigned short int *option);
void obtainStr(char *str);
void encryptStr(char *str);
void appendStr(FILE *fbin,char *str);
void showAllFile(FILE *fbin,char *str);

int main(void)
{
    FILE *fbin = NULL;
    char str[101];
    unsigned short int option;

    selectOption(&option);

    switch (option)
    {
    case 1:
        obtainStr(str);
        encryptStr(str);
        appendStr(fbin,str);
        break;
    case 2:
        showAllFile(fbin,str);
        break;
    }

}

void selectOption(unsigned short int *option)
{
    while(1)
    {
        printf("1 : Add | 2 : Show All\n -> ");
        scanf("%1hu", option);
        fflush(stdin);
        if( ( (*option) == 1) || ( (*option) == 2) )
            break;
        else
            printf("\n | Please only enter 1 or 2. |\n\n");
    }
}

void obtainStr(char *str)
{
    while(1)
    {
        printf("\nPlease enter your text ( max. 100 characters ) : ");
        gets(str);
        if(strlen(str)<=maxsize)
            break;
        else
            printf("\n| Please only enter 100 characters or below. |\n");
    }
}

void encryptStr(char *str)
{
    unsigned short int i;
    for(i=0; i<=maxsize; i++)
    {
        if((str[i]>='A') && (str[i]<='M'))
        {
            str[i]+=13;
        }

        else if((str[i]>='a') && (str[i]<='m'))
        {
            str[i]+=13;
        }

        else if((str[i]>='N') && (str[i]<='Z'))
        {
            str[i]-=13;
        }

        else if((str[i]>='n') && (str[i]<='z'))
        {
            str[i]-=13;
        }
    }
}

void appendStr(FILE *fbin,char *str)
{
    unsigned short int i=0;

    fbin=fopen(filename,"ab");
    if(fbin!=NULL)
    {
        while( str[i]!='\0' )
        {
            fputc(str[i],fbin);
            i++;
        }
        fputc(keychar,fbin);  // 	'\n' = line feed, but it doesn't work. So, i'll use it as a trigger to put a new line character.
        fclose(fbin);
    }
    else
    {
        printf("\n*%s can't be accessed ! \n Error Code : 1",filename);
        exit(0);
    }
}

void showAllFile (FILE *fbin, char *str)
{
    unsigned short int i=0;
    fbin = fopen(filename,"rb");
    if ( fbin != NULL )
    {
        while( !feof(fbin) )
        {
            str[i] = fgetc(fbin);

            /*     		 if( str[i] == EOF )		There is a space at the end of the file mysteriously. In order to destroy it, use this statement.
            				str[i]='\0'; 		*/
            i++;
        }
        fclose(fbin);


        printf("\n******************************************************************************************\n\n");
        i=0;
        encryptStr(str);

        while(str[i] != '\0')
        {
            if(str[i] == keychar)
                printf("\n");
            else
                printf("%c", str[i]);
            i++;
        }
        printf("\n******************************************************************************************\n\n");
    }
    else
    {
        printf("\n*%s can't be accessed ! \n Error Code : 2", filename);
        exit(0);
    }
}
