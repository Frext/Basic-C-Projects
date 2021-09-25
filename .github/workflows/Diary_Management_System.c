#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <windows.h>

void sign_up(char *username, char *password, FILE *fp)
{
    while (1)
    {
        printf("Username (between 6-20): ");
        scanf("%s", username);
        if (strlen(username) > 20)
            printf("This username is too long. Please try again\n");
        else if (strlen(username) < 6)
            printf("This username is too short. Please try again\n");
        else
            break;
    }
    while (1)
    {
        printf("Password (between 8-21): ");
        scanf("%s", password);
        if (strlen(password) > 21)
            printf("This password is too long. Please try again\n");
        else if (strlen(password) < 8)
            printf("This password is too short. Please try again\n");
        else
            break;
    }
}

int control(char username[], char password[], FILE *fp, unsigned short int *decision)
{
    rewind(fp);
    char temp[22];
    int k = 0, j, same = 0;
    /// username control
    do
    {
        j = -1;
        do
        {
            temp[++j] = fgetc(fp);
        }
        while ((temp[j] != '\n') && !feof(fp));
        temp[j] = '\0';
    }
    while ((strcmp(temp, username) != 0) && !feof(fp));

    if (strcmp(temp, username) == 0)
    {
        k++;
        if (!(*decision))
            same++;
    }
    else
    {
        if ((*decision))
            return k;
    }
    /// password control
    temp[0] = '\0';
    j = -1;
    do
    {
        temp[++j] = fgetc(fp);
    }
    while ((temp[j] != '\n') && !feof(fp));
    temp[j] = '\0';

    if (strcmp(temp, password) == 0)
    {
        k++;
        if ((!(*decision)) && (same > 0))
            same++;
    }

    if (!(*decision))
        return same;
    else
        return k;
}

void sign_in(char *username, char *password)
{
    printf("Username : ");
    scanf("%s", username);
    printf("Password : ");
    scanf("%s", password);
}

void decide(unsigned short int *decision)
{
    while (1)
    {
        scanf("%hu", decision);
        if (*decision < 0 || *decision > 1)
            printf("\n**Please only enter 0 or 1!\n : ");
        else
            break;
    }
}

void wait(unsigned short int i)
{
    Sleep(i), system("CLS");
}

void encrpyt(char *str,unsigned short int Length)	// this part is added later
{
    unsigned short int i;
    for(i=0; i<=Length; i++)
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

int main()
{
    FILE *fp = fopen("The Diary Accounts.txt", "a+");
    if (fp != NULL)
    {
        char *username = (char *)malloc(25 * sizeof(char)); // .bin
        char *password = (char *)malloc(22 * sizeof(char));
        char *to_write = (char *)malloc(156 * sizeof(char));
        username[0] = '\0'; // Don't assign a string pointer to NULL! Instead assign its first character to '\0'(the null character)
        *password = '\0';
        unsigned short int decision, ctrl, j = 0;

        printf("Welcome to the diary management system, press 0 if you want to sign up or 1 if you want to sign in : ");
        decide(&decision);
        if (decision)
        {
            while (1)
            {
                sign_in(username, password);
                ctrl = control(username, password, fp, &decision);
                if (ctrl != 2)
                {
                    printf("**Your username or password was wrong, please try again.\n");
                    wait(2000);
                }
                else
                    break;
            }
            printf("\nSuccessfully signed in!\n");
            wait(2000);
        }

        else
        {
            while (1)
            {
                sign_up(username, password, fp);
                ctrl = control(username, password, fp, &decision);
                if (ctrl == 1)
                    printf("This username is already taken! Please try again.\n");

                else if (ctrl == 2)
                {
                    printf("This account is already created! Please try again.\n");
                    return 0;
                }

                else
                    break;
            }
            fprintf(fp, "\n%s\n%s\n", username, password);
            printf("\nSuccessfully signed up!\n");
            wait(2000);
        }

        fclose(fp);
        /// Opening binary file
        strcat(username, ".bin");
        FILE *the_diary = fopen(username, "ab+");

        if (the_diary != NULL)
        {
            while (j == 0)
            {
                printf("Please press 0 if you want to see your diary, 1 if you want to write on it or 2 in order to clear it: ");
                while (1)
                {
                    scanf("%hu", &decision);
                    fflush(stdin);
                    if (decision < 0 || decision > 2)
                        printf("\n**Please only enter 0 , 1 or 2!\n : ");
                    else
                        break;
                }
                unsigned short int fileLength;
                size_t elements_written;
                if (decision == 0)
                {
                    fseek(the_diary, 0, SEEK_END);
                    fileLength = ftell(the_diary);
                    fseek(the_diary, 0, SEEK_SET);
                    char *buffer = (char *)malloc((fileLength+1 )* sizeof(char)); // +1 for '\0'

                    fread(buffer, sizeof(char), fileLength, the_diary);
                    encrpyt(buffer,fileLength);
                    printf("\n\nThe contents of '%s'\n----------------------------------------------------------------------\n", username);
                    for (j = 0; j < fileLength; j++)
                        printf("%c", buffer[j]);
                    printf("\n----------------------------------------------------------------------\n");
                    j = 0;
                    free(buffer);
                }
                else if (decision == 1)
                {
                    while (1)
                    {
                        printf("\nPlease enter your text here (max. 150 words) : ");
                        fflush(stdin);
                        gets(to_write);
                        encrpyt(to_write,155);
                        if (strlen(to_write) > 150)
                            printf("Please enter the number of your words less than or equal to 150!\n");
                        else
                        {
                            strcat(to_write," | ");
                            break;
                        }
                    }
                    fclose(the_diary);
                    the_diary = fopen(username, "ab+");
                    elements_written = fwrite(to_write, sizeof(char), strlen(to_write), the_diary); // visit programiz.com

                    if (elements_written)
                    {
                        printf("\nSuccessfully wrote!\n");
                    }
                    else
                        printf("\n**The writing process wasn't successful! Please try again.\n");
                    to_write[0]='\0'; // assigning it to the null character
                }
                else
                {
                    the_diary = fopen(username, "wb");
                    the_diary = fopen(username, "ab+");
                    if (the_diary != NULL)
                    {
                        printf("\nSuccesfully cleared!\n");
                    }
                    else
                        printf("\n**Clearing process wasn't successful! Please try again.\n");
                }
                printf("\n|?| Do you want to quit? (1 = Yes | 0 = No ) : ");
                decide(&j);
                printf("\n\n");
            }
            for(j=0; j<5; j++)
            {
                printf("\nThe data on the screen will be removed in %hu second(s).",j+1);
                wait(950);
            }
        }
        else
            printf("Your diary file can't be accessed!\n");

        fclose(the_diary);
        free(username), free(password), free(to_write);
    }
    else
        printf("The Diary Accounts can't be accessed!\n");

    return 0;
}
