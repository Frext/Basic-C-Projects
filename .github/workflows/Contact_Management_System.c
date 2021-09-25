#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <ctype.h>
#include <string.h>

#define MAX_ 41

struct person
{
    char name_surname[MAX_], p_number[21];
} contact;

char ch; // to read all the contacts

void waitfor(int y)
{
    Sleep(y), system("CLS");
}

void decide(int *x)
{
    fflush(stdin);
    while (1)
    {
        scanf("%d", x);
        if (((*x) < 2) && ((*x) > -1))
            break;
        else
        {
            printf("\n**Please only enter 0 or 1\n");
            waitfor(2000);
            printf(" : ");
        }
    }
}

int control(char *name, FILE *fp, char *buf, int *j)
{
    rewind(fp);
    do
    {
        fgets(buf, MAX_ + 1, fp);
        for ((*j) = 0; (*j) < strlen(buf); (*j)++)
        {
            if (buf[(*j)] == '\n')
            {
                buf[(*j)] = '\0';
                break;
            }
        }
    }
    while ((strcmp(buf, name) != 0) && (!feof(fp)));
    if (strcmp(buf, name) == 0)
        return 0;
    else
        return 1;
}

void save_contact(FILE *fp, char *name)
{
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s\n", name);
    rewind(fp);
}

void copy(FILE *temp,FILE *fp)
{
    fclose(fp),rewind(temp);
    fp=fopen("The Contacts.txt","w");
    if(fp!=NULL)
    {
        while( ( ch = fgetc(temp) ) != EOF )
            fputc(ch, fp);
        fclose(fp);
        fp=fopen("The Contacts.txt","r+");
    }
}

void edit_contact(char *old, char *neww, FILE *fp, FILE *temp, char *buf, int *j)
{
    rewind(fp), rewind(temp);

    fprintf(temp,"%s\n",neww);

    while ((!feof(fp) )&&( !feof(temp)))
    {
        fgets(buf, MAX_ + 1, fp);
        for ((*j) = 0; (*j) < strlen(buf); (*j)++)
        {
            if (buf[(*j)] == '\n')
            {
                buf[(*j)] = '\0';
                break;
            }
        }
        if ((strcmp(buf, old) != 0 ) && (buf[0]!='\n') && (buf[0]!=EOF))
        {
            fprintf(temp,"%s\n",buf);
        }
    }
    copy(temp,fp);
}



int main(void) // save contact, edit, delete
{
    /// declaration of the variables
    int decision, j,z=0;

    char buf[MAX_], buf2[MAX_], filename[MAX_ + 4];

    printf("Welcome to the Contact Management System.\n");
    FILE *fp;
    FILE *temp;
    FILE *ct; // the file of the contact

    while(z==0)
    {
        fp = fopen("The Contacts.txt", "r+");
        temp = fopen("Temp.txt", "w+");
        if (fp != NULL)
        {
            while (1)
            {
                printf("\nPlease press:\n0 -> If you want to save a contact\n1 -> If you want to edit a contact\n2 -> If you want to delete a contact\n3 -> If you want to see all the contacts\n: ");
                scanf("%d", &decision);
                if ((decision==0) || (decision==1) || (decision==2) || (decision==3))
                    break;
                else
                {
                    printf("Please only enter 0,1,2 or 3!\n");
                    waitfor(3000);
                }
            }
            if (decision == 0) /// saving a contact
            {
                fflush(stdin);
                while (1)
                {
                    printf("\nPlease enter the name : ");
                    gets(contact.name_surname);
                    if (strlen(contact.name_surname) < MAX_)
                    {
                        if ((control(contact.name_surname, fp, buf, &j)) == 1)
                            break;
                        else
                        {
                            printf("**There is already a contact named |%s|.  Please try again!\n", contact.name_surname);
                            waitfor(3000);
                        }
                    }
                    else
                        printf("**Please enter a name below 40 characters.\n");
                }

                while (1)
                {
                    fflush(stdin);
                    printf("Please enter the phone number : ");
                    gets(contact.p_number);
                    if ((strlen(contact.p_number) >= 3) && (strlen(contact.p_number) <= 20))
                        break;
                    else
                    {
                        printf("\n**Please enter a phone number between 3 and 20 digits!\n");
                        waitfor(3500);
                    }
                }
                save_contact(fp, contact.name_surname);
                strcpy(filename, contact.name_surname);
                strcat(filename, ".txt");
                ct = fopen(filename, "w");
                if (ct != NULL)
                {
                    fprintf(ct, "%s\n%s", contact.name_surname, contact.p_number);
                    printf("\nSuccessfully saved!\n");
                }
                else
                    printf("**The file of |%s| can't be created!\n", contact.name_surname);
                fclose(ct);
            }

            else if (decision == 1) /// editing a contact
            {
                fflush(stdin);
                printf("\nPlease enter the name of the contact you want to edit : ");
                gets(contact.name_surname);
                rewind(fp);

                if (control(contact.name_surname,fp,buf,&j) == 0)
                {
                    printf("\nWhich information do you want to change? ( 0 = Name, 1 = P. Number ) : ");
                    decide(&decision);
                    fflush(stdin);

                    strcpy(buf, contact.name_surname); // old name = buf
                    strcpy(filename,buf);
                    strcat(filename,".txt");

                    if (decision == 0)
                    {
                        printf("\nPlease enter the new name : ");
                        gets(contact.name_surname);

                        ct=fopen(filename,"r");
                        if(ct!=NULL)
                        {
                            z=0;
                            while(z<2) // getting the phone number
                            {
                                fgets(contact.p_number,MAX_+1,ct);
                                for (j = 0; j < strlen(buf); j++)
                                {
                                    if (buf[j] == '\n')
                                    {
                                        buf[j] = '\0';
                                        break;
                                    }
                                }
                                z++;
                            }
                            z=0; // not to quit automatically
                            fclose(ct);
                            remove(filename); // the file name in brackets
                            strcpy(filename,contact.name_surname);
                            strcat(filename,".txt");
                            ct = fopen(filename, "w");
                            if(ct!=NULL)
                            {
                                edit_contact(buf, contact.name_surname, fp, temp, buf2, &j);
                                fprintf(ct,"%s\n%s",contact.name_surname,contact.p_number);
                                printf("\nSuccessfully edited!\n");
                            }
                            else
                                printf("**Your new file can't be created!\n");
                        }
                        else
                            printf("**Your old file can't be accessed!\n");
                    }

                    else
                    {
                        printf("\nPlease enter the new phone number : ");
                        gets(contact.p_number);

                        strcpy(filename,contact.name_surname);
                        strcat(filename,".txt");
                        ct = fopen(filename, "w");
                        fprintf(ct,"%s\n%s",contact.name_surname,contact.p_number);
                        printf("\nSuccessfully edited!\n");
                    }
                    fclose(ct);
                }
                else
                    printf("**There isn't a person named |%s| in your contacts. Please check all your contacts and try again!\n", contact.name_surname);
            }

            else if (decision == 2) /// deleting a contact
            {
                fflush(stdin);
                printf("\nPlease enter the name of the contact you want to delete : ");
                gets(contact.name_surname);

                if(control(contact.name_surname,fp,buf,&j) == 0)
                {
                    strcpy(filename,contact.name_surname);
                    strcat(filename,".txt");
                    remove(filename);
                    rewind(temp),rewind(fp);
                    buf2[0]='\0';
                    while ( (!feof(fp)) && (!feof(temp)) )
                    {
                        fgets(buf, MAX_ + 1, fp);
                        for (j = 0; j < strlen(buf); j++)
                        {
                            if (buf[j] == '\n')
                            {
                                buf[j] = '\0';
                                break;
                            }
                        }
                        if ((strcmp(buf, contact.name_surname) != 0 ) && (buf[0]!='\0') && (strcmp(buf2,buf) != 0) && (buf[0]!=EOF))
                        {
                            fprintf(temp,"%s\n",buf);
                            strcpy(buf2,buf);
                        }
                    }
                    copy(temp,fp);
                    printf("\nSuccessfully deleted!\n");
                }
                else
                    printf("**There isn't a person named |%s| in your contacts. Please check all your contacts and try again!\n", contact.name_surname);
            }

            else /// showing all the contacts
            {
                rewind(fp);
                contact.name_surname[0]='\0';
                while (!feof(fp))
                {
                    printf("\n-------------------------\n"); // I used an error as an advantage, you'll see if you look carefully ( it interprets the empty line as a contact )
                    fgets(buf, MAX_ + 1, fp);
                    for (j = 0; j < strlen(buf); j++)
                    {
                        if (buf[j] == '\n')
                        {
                            buf[j] = '\0';
                            break;
                        }
                    }
                    if(strcmp(contact.name_surname,buf)!=0)
                    {
                        strcpy(contact.name_surname,buf);
                        strcpy(filename,buf);
                        strcat(filename,".txt");
                        ct=fopen(filename,"r");
                        if(ct!=NULL)
                            while( ( ch = fgetc(ct) ) != EOF )
                                printf("%c",ch);
                        printf("\n");
                        fclose(ct);
                    }
                }
            }
            printf("\n(?) Do you want to quit ( 1 = Yes | 0 = No ) : ");
            decide(&z);
            waitfor(1000);
            fclose(fp),fclose(temp);
        }
        else
            printf("**The Contacts can't be accessed!\n");

    }

//   temp=fopen("Temp.txt","w"); // don't forget to clear the temp file
    //  fclose(temp);
}
