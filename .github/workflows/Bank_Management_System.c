#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

int decision, cvv, j = 0, actualmoney = 0;
unsigned long long cardnumber;
char name_surname[50], ns[50];

void uptade(FILE *f, FILE *temp)
{
    unsigned long long i2;
    int cvv2, actualmoney2, j;
    rewind(f), rewind(temp);
    fprintf(temp, "%s\n%llu\n%d\n%d\n", name_surname, cardnumber, cvv, actualmoney);
    while (!feof(f) && !feof(temp))
    {
        fgets(ns,50,f);
        if ((ns[0] <= 90 && ns[0] >= 65) || (ns[0] <= 122 && ns[0] >= 97))// if ns[0] isn't a letter, don't continue.
        {
            for (j = 1; j <= 50; j++)
                if (((ns[j] >= 48) && (ns[j] <= 58)) || (ns[j] == '\n')) // if it's a number or a new line
                {
                    ns[j] = '\0';
                    break;
                }
            fscanf(f, "%llu", &i2);
            fscanf(f, "%d", &cvv2);
            fscanf(f, "%d", &actualmoney2);

            if ((i2 != cardnumber))
                fprintf(temp, "\n%s\n%llu\n%d\n%d\n", ns, i2, cvv2, actualmoney2);
        }
    }
    rewind(f), rewind(temp);
  
}
void name_formatter()
{
    int i = 1;

    name_surname[0] = toupper(name_surname[0]);
    while (name_surname[i] != '\0')
    {
        if (name_surname[i - 1] != ' ')
            name_surname[i] = tolower(name_surname[i]);
        else
            name_surname[i] = toupper(name_surname[i]);
        i++;
    }
}
int sign_in(FILE *f)
{
    int r = 0;
    long long int i;
    fflush(stdin);
    printf("\nPlease enter your name and surname with a space between them : ");
    gets(name_surname);
    name_formatter();
    rewind(f);
    do
    {
        fgets(ns, strlen(name_surname) + 1, f);
    }
    while ((strcmp(ns, name_surname) != 0) && !feof(f));

    if (strcmp(ns, name_surname) == 0)
    {
        r++;
        printf("\nPlease enter your 16 digit card number without a space : ");
        scanf("%llu", &cardnumber);
        fscanf(f, "%lld", &i);
        if (i == cardnumber)
            r++;

        printf("\nPlease enter your CVV : ");
        scanf("%d", &cvv);
        fscanf(f, "%lld", &i);
        if (i == cvv)
            r++;
    }

    if (r == 3)
        return 1;
    else
        return 0;
}

int money(FILE *f, FILE *temp, int decision)
{
    int money, number, i = 0;
    printf("\nThere are | %d | dollars in your account.\n", actualmoney);
    if (!decision)
        printf("\nHow much money do you want to withdraw? (max. 100.000 dollars): ");
    else
        printf("\nHow much money do you want to pay in? (max. 100.000 dollars): ");

    scanf("%d", &money);

    if (money > actualmoney && !decision)
    {
        printf("\n**There isn't that much money in your account!\n");
        return 0;
    }
    else if (money <= 100000 && money > 0)
    {
        if (!decision)
            actualmoney -= money;
        else
            actualmoney += money;

        printf("\nThe amount of money in your account is | %d | dollar(s) now.\n", actualmoney);
        uptade(f, temp);
        return 1;
    }
    else if (money > 100000)
    {
        printf("\n**Please enter the amount of money less than 100.000 dollars.\n");
        return 0;
    }

    else if (money <= 0)
    {
        printf("\n**Please enter the amount of money more than 0 dollar.");
        return 0;
    }
}

void generate_card_number() // Stack Overflow :-)
{
    int i;
    // Ensure most significant digit is not 0
    cardnumber = rand() % 9 + 1;

    // Add 15 more digits (which can also be 0)
    for (i = 0; i < 15; i++)
    {
        cardnumber *= 10;
        cardnumber += rand() % 10;
    }
}

void generate_cvv()
{
    cvv = 100 + (rand() % 900);
}

int main()
{
    srand(time(0));
    FILE *f = fopen("The Bank Accounts.txt", "r"), *temp = fopen("Temp.txt", "w+");
    if (f != NULL && temp != NULL)
    {

        while (1)
        {
            printf("Press 0 if you want to register or 1 if you want to sign in, please: ");
            scanf("%d", &decision);
            if (decision != 0 && decision != 1)
                printf("\n**Please only enter 0 or 1!\n");
            else
                break;
        }

        if (decision)
        {
            if (!sign_in(f))
                do
                {
                    printf("\n***Some of your information was inaccurate, please enter your information again.\n");
                    Sleep(2000), system("CLS");
                }
                while (sign_in(f) == 0);

            printf("\nSuccessfully signed in!\n");
            fscanf(f, "%d", &actualmoney);
            Sleep(2000), system("CLS");
        }
        else
        {
            while(1){
            printf("\nPlease enter your name and surname with a space between them : ");
            fflush(stdin);
            gets(name_surname);
            if(name_surname[0]==' ') printf("\n**Please enter the space just between your name and surname!\n");
            else break;
            }
            name_formatter();

            generate_cvv();
            generate_card_number();

            printf("\nSuccessfully registered!\n");
            printf("\nYour card number : %llu\nYour CVV : %d\n", cardnumber, cvv);

            uptade(f, temp);
            Sleep(2500), system("CLS");
        }
        while (j == 0)
        {
            do
            {
                printf("\nPress 0 if you want to withdraw money or 1 if you want to pay money in : ");
                scanf("%d", &decision);
                if (decision > 1 || decision < 0)
                    printf("\n**Please only enter 0 or 1!\n");
                else if (actualmoney == 0 && decision == 0)
                {
                    printf("\n**There is no money in your account to withdraw!\n"), Sleep(2000), system("CLS");
                }
            }
            while ((decision > 1 || decision < 0) || (decision == 0 && actualmoney == 0));

            if (!money(f, temp, decision))
            {
                do
                {
                    if (!decision)
                        printf("\n***Withdrawing wasn't successful, please try again.\n");
                    else
                        printf("\n***Paying in wasn't successful, please try again.\n");
                    Sleep(3000), system("CLS");
                }
                while (money(f, temp, decision) == 0);
            }

            if (!decision)
                printf("\nSuccessfully withdrew!\n");
            else
                printf("\nSuccessfully paid in!\n");
            Sleep(3000), system("CLS");

            printf("\nDo you want to quit? ( 1 = Yes , 0 = No ) : ");
            scanf("%d", &j);
            printf("\n\n");
        }
    }
    else
        printf("\nThe required files can't be accessed.\n");
    fclose(f),fclose(temp);
    FILE *temp_erase=fopen("Temp.txt","w");
    fclose(temp_erase);
}
