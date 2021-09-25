#include <stdio.h>
#include <stdlib.h>

#include <string.h>

struct member
{
    char name[25];
    char surname[25];
    int age;
    char username[20];
    char password[20];
} mem[100];


int main()
{
    char gs,r;
    int i=0,j;
    char temp_pass[20]; // temporary password
    char temp_usname[20];

    do
    {
        printf("\nPlease enter the 'S' letter to sign in, and the 'R' letter to register : ");
        scanf(" %c",&gs);

        if(gs=='R' || gs=='r')
        {

            printf("\nPlease enter your name : ");
            fflush(stdin);
            gets(mem[i].name);

            printf("\nPlease enter your surname : ");
            gets(mem[i].surname);

            printf("\nPlease enter your age : ");
            scanf(" %d",&mem[i].age);
            while(mem[i].age<0 || mem[i].age>130)
            {
                printf("\n(*)Please enter a valid age : ");
                scanf(" %d",&mem[i].age);
            }

            printf("\nPlease enter your username : ");
            fflush(stdin);
            gets(mem[i].username);

            for(j=0; j<i; j++)
            {
                while(strcmp(mem[i].username,mem[j].username)==0)
                {
                    printf("\n(*)This username is already taken, please choose another one : ");
                    gets(mem[i].username);
                }
            }
            while(strlen(mem[i].username)<7 || strlen(mem[i].username)>20)
            {
                printf("\n(*)Please enter a username between 7-20 : ");
                gets(mem[i].username);
            }

            printf("\nPlease enter your password (7-20): ");
            fflush(stdin);
            gets(mem[i].password);

            while(strlen(mem[i].password)<7 || strlen(mem[i].password)>20)
            {
                printf("\n(*)Please enter a password between 7-20 : ");
                gets(mem[i].password);
            }

            printf("\nRegistration successful!!\n");

            FILE *file;                                     /// File
            file=fopen("records.txt","w");
            if(file!=NULL)
            {
                fprintf(file,"%d.Member\nName : %s\n",i+1,mem[i].name);
                fprintf(file,"Surname : %s\n",mem[i].surname);
                fprintf(file,"Age : %d\n",mem[i].age);
                fprintf(file,"Username : %s\n",mem[i].username);
                fprintf(file,"Password : ");
                int x;
                for(x=0;x<strlen(mem[i].password);x++)
                    fprintf(file,"*");

                fprintf(file,"\n\n\n");
                fclose(file);
                i++;
            }
        }
            else if(gs=='S' || gs=='s')
            {
                fflush(stdin);
                printf("\nPlease enter your username : ");
                gets(temp_usname);
                printf("\nPlease enter your password : ");
                gets(temp_pass);

                int kl=0;
                for(j=0; j<i; j++)
                {
                    if((strcmp(mem[j].username,temp_usname)==0)&&(strcmp(mem[j].password,temp_pass)==0))
                    {
                        printf("****************************");
                        printf("\nName : %s",mem[j].name);
                        printf("\nSurname : %s",mem[j].surname);
                        printf("\nAge : %d\n",mem[j].age);
                        printf("****************************");
                        kl++;
                    }
                }
                if(kl==0)
                    printf("\n(*)Wrong username or password, please try again.\n");
            }
            else
                printf("\nPlease only enter the letters 'G' or 'S'.\n");

            printf("\nEnter the 'R' letter to restart the program : ");
            scanf(" %c",&r);
            system("CLS"); // to clean the screen

    }while(r=='R' || r=='r');
}
