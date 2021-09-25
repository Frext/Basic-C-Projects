#include <stdio.h>
#include <stdlib.h>

// Good to see you again, this code is a bit hard to read.So, try to take it slow if you don't understand. I tried my best to make it look clean.

#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAXX 43
#define MAXSEATS 32
#define thebusestxt "The Buses.txt"

char copy_char; // it's just for copy_to function
unsigned short int TillNewLineV;

struct info
{
    char name[MAXX-2],surname[MAXX-2],id[12];
};

void obtain_user_info(struct info *person,unsigned short int *temp_int);

void obtain_name(char *name,unsigned short int *temp_int);

void obtain_surname(char *surname,unsigned short int *temp_int);

void obtain_id(char *id,unsigned short int *temp_int);

void list_all_buses(FILE *fbuses,unsigned short int *order_var,char *ShowInfoStr);

void choose_a_bus( FILE *fbuses, unsigned short int *control_var, unsigned short int *the_bus_num,char *the_bus_plate, char *temp_str );

void list_all_the_seats(FILE *fseats,unsigned short int *control_var,unsigned short int *order_var,unsigned short int *seat_num,char *the_bus_filename,char *temp1,char *temp2);

void control_the_existence_of_TheSeatNum(FILE *fseats,unsigned short int *temp_int,unsigned short int *seat_num,unsigned short int *control_var,char *temp1_str,char *temp2_str);

void choose_a_seat(FILE *fseats,unsigned short int *control_var,unsigned short int *temp_int,unsigned short int *the_seat_num,char *the_bus_plate,char *temp1_str,char *temp2_str,char *name,char *surname);

void ListAllReservationsOfThePerson(struct info *person,char *person_filename,char *temp1,char *temp2,FILE *fpeople,FILE *fbuses,unsigned short int *order_var);

void choose_a_reservation(char *person_filename,char *bus_plate,char *str_reservation_num,unsigned short int *control_var,unsigned short int *decision_num,FILE *fpeople);

void delete_a_reservation(char *PersonFilename,char *bus_plate,char *the_seat_num,char *temp1_str,char *temp2_str,unsigned short int decision,FILE *fpeople,FILE *fbuses,FILE *ftemp,FILE *ftemp2);

void remove_the_seat_number_from_the_bus_file(char *bus_filename,char *seat_number,char *temp1,char *temp2,FILE *fbuses,FILE *ftemp2);

void get_a_bus_plate(char *the_plate,unsigned short int *temp);

void get_DateTime(char *date,char *temp_str,unsigned short int *temp_int);

void get_DepartDest_points(char *destination,char *temp_str,unsigned short int *temp_int);

void get_bus_info(char *the_plate,char *destination,char *date,char *temp_str,unsigned short int *temp_int);

void plate_formatter(char *the_plate,unsigned short int *temp);

void add_new_bus_to_thebusestxt(FILE *fbuses,char *the_plate,char *destination,char *date);

void create_new_bus_file(FILE *fbuses,char *the_plate);

void delete_the_bus_from_thebusestxt(char *bus_plate,char *temp1,char *temp2,char *temp3,FILE *fbuses,FILE *ftemp);

void delete_the_SeatNum_from_each_passanger(char *bus_filename,char *person_filename,char *seat_num,char *temp1,char *temp2,unsigned short int *temp_int,FILE *fpeople,FILE *fbuses,FILE *ftemp,FILE *ftemp2);

void create_a_new_person_file(FILE *fpeople,char *person_filename,char *id);

void save_the_reservation_info(unsigned short int *the_seat_num,char *the_bus_plate,char *person_filename,FILE *fpeople);

void edit_thebusestxt(char *bus_plate,char *new_info,char *tempStr,unsigned short int mod,FILE *fbuses,FILE *ftemp);

void ChangeOldPlateIntoNewForEachPassenger(char *OldBusPlate,char *NewBusPlate,char *SeatNum,char *PersonFilenameorTemp1,char *temp2,FILE *fseats,FILE *fpeople,FILE *fbuses,FILE *ftemp,FILE *ftemp2);

void show_all_passengers_of_the_bus(char *bus_filename,char *temp1,char *temp2,FILE *fbuses,unsigned short int *order_var,unsigned short int *seat_num);

int ControlTheExistenceOfTheReservations(struct info *person,char *person_filename,char *temp_str,unsigned short int *control_var,FILE *fpeople);

/// Short ones

void decide(unsigned short int *decision,unsigned short int min,unsigned short int max);

void AsktoGoBacktoStart(unsigned short int *temp_int);

void waitfor(unsigned short int time);

void name_formatter(char *name,char *surname,unsigned short int *i);

void until_newline(char *str,unsigned short int *temp_int);

void copy_to(FILE *source,FILE *dest,char *ch);

void generate_person_filename(char *filename,struct info *person);

void ask_to_log_in(struct info *person,unsigned short int *decision,unsigned short int *temp_int,unsigned short int *log_in_val,char *person_filename,char *temp_str,FILE *fpeople);

int id_check(char *id,char *temp_str,char *person_filename,FILE *fpeople);

///

int main(void)
{
    struct info person;
    unsigned short int decision, common1, common2, seat_num, log_in_val=0;
    char BusPlatesOrFilenames[MAXX],PersonFilenames[MAXX],temp1[MAXX],temp2[MAXX],temp3[MAXX];
    // you can understand the aim of the variable by looking at its function variable names

    FILE *fbuses,*fseats,*fpeople,*ftemp,*ftemp2;

start:

    if(log_in_val==0)
    {
        ask_to_log_in(&person,&decision,&common1,&log_in_val,PersonFilenames,temp1,fpeople);
    }
    if(log_in_val==1) // don't turn this into an else statement
    {
        printf(" | %s %s | \n",person.name,person.surname);
    }
    printf("Welcome to the Main Menu.\n--------------------------------------\n");
    printf("\nPlease press\n1 : To reserve a seat\n2 : To see the available seats of a particular bus\n3 : To see your reservation info\n4 : To delete a reservation\n5 : To access the advanced  options\n6 : To log out\n7 : To terminate the program\n : ");

    switch(log_in_val)
    {
    case 1:
        decide(&decision,1,7);
        break;
    default:
        while(1)
        {
            scanf("%hu",&decision);
            fflush(stdin);
            if((decision==2) || (decision == 7))
                break;
            else
                printf("\n**Please only enter 2 or 7 because you are not logged in.\n");
        }
        break;
    }


    BusPlatesOrFilenames[0]='\0',PersonFilenames[0]='\0',temp1[0]='\0',temp2[0]='\0',temp3[0]='\0';      // cleaning the variables
    fbuses=NULL,fseats=NULL,fpeople=NULL,ftemp=NULL,ftemp2=NULL;        // Assigning them to NULL will solute the "may be uninitialized" problem of the file pointers

    switch(decision)
    {
/*reserve a seat*/    case 1:
        /// choosing an available bus
        list_all_buses(fbuses,&common1,temp1);
        choose_a_bus(fbuses,&common1,&seat_num, BusPlatesOrFilenames, temp1);

        strcat(BusPlatesOrFilenames,".txt");
        list_all_the_seats(fseats,&common1,&common2,&seat_num,BusPlatesOrFilenames,temp1,temp2);
        choose_a_seat(fseats,&common1,&common2,&seat_num,BusPlatesOrFilenames,temp1,temp2,person.name,person.surname);

        strtok(BusPlatesOrFilenames,".txt");         /// I just need the bus plate. So, I took the ".txt" part of it.
        generate_person_filename(PersonFilenames,&person);

        if( access(PersonFilenames, F_OK) !=0 )    // if the file doesn't exist, create.
        {
            create_a_new_person_file(fpeople,PersonFilenames,person.id);
        }

        if(id_check(person.id,temp1,PersonFilenames,fpeople)==1)	// for people who have the same name and surname
        {
            save_the_reservation_info(&seat_num,BusPlatesOrFilenames,PersonFilenames,fpeople);
            printf("\nSuccessfully reserved.\n");
        }
        break;


/*getting the bus number and showing all of its seats*/    case 2:
        while(1)
        {
            list_all_buses(fbuses,&common1,temp1);
            choose_a_bus(fbuses,&common1,&seat_num, BusPlatesOrFilenames, temp1);

            strcat(BusPlatesOrFilenames,".txt");
            list_all_the_seats(fseats,&common1,&common2,&seat_num,BusPlatesOrFilenames,temp1,temp2);

            AsktoGoBacktoStart(&common1);
            if(common1==1)
            {
                goto start;
            }
        }
        break;


/*showing all the reservations of a particular person*/   case 3:
    /* deleting a reservation */
    case 4:
        if(ControlTheExistenceOfTheReservations(&person,PersonFilenames,temp1,&common1,fpeople)==1)    // if there is no file that has the person filename, skip.
        {
            ListAllReservationsOfThePerson(&person,PersonFilenames,temp1,temp2,fpeople,fbuses,&common1);
            if(decision==4)
            {
                choose_a_reservation(PersonFilenames,BusPlatesOrFilenames,temp1,&common1,&common2,fpeople);
                // BusPlatesOrFilenames = The Bus plate | temp1 = the seat num

                delete_a_reservation(PersonFilenames,BusPlatesOrFilenames,temp1,temp2,temp3,1,fpeople,fbuses,ftemp,ftemp2);	// it has another function in it. 1 makes it work, 0 doesn't.
                printf("\nSuccessfully deleted.\n");
            }
        }
        else
            goto start;
        break;


/*the advanced bus menu*/   case 5:
        waitfor(200);
        printf("\nWelcome to the Advanced Menu.\n---------------------------------------------\nPlease press\n1 : To add a bus journey\n2 : To delete a bus journey\n3 : To edit a bus journey\n4 : To see all the passengers of a particular bus\n5 : To go to the main menu\n : ");

        decide(&decision,1,5);
        switch(decision)
        {
        case 1:
            get_bus_info(BusPlatesOrFilenames,temp1,temp2,temp3,&common1);
            add_new_bus_to_thebusestxt(fbuses,BusPlatesOrFilenames,temp1,temp2);

            strcat(BusPlatesOrFilenames,".txt");
            create_new_bus_file(fbuses,BusPlatesOrFilenames);

            printf("\nSuccessfully added.\n");
            break;

        case 2:
            list_all_buses(fbuses,&common1,temp1);
            choose_a_bus(fbuses,&common1,&decision, BusPlatesOrFilenames, temp1);

            delete_the_bus_from_thebusestxt(BusPlatesOrFilenames,temp1,temp2,temp3,fbuses,ftemp);

            strcat(BusPlatesOrFilenames,".txt");
            delete_the_SeatNum_from_each_passanger(BusPlatesOrFilenames,PersonFilenames,temp1,temp2,temp3,&common1,fpeople,fbuses,ftemp,ftemp2);

            printf("\nSuccessfully deleted.\n");
            break;

        case 3:
            list_all_buses(fbuses,&common1,temp1);
            choose_a_bus(fbuses,&common1,&decision, BusPlatesOrFilenames, temp1);

            printf("\nWhich information do you want to edit? ( 1 = Bus Plate | 2 = Departure and Destination Points | 3 = Date & Time ) : ");
            decide(&decision,1,3);
            switch(decision)
            {
            case 1:
                get_a_bus_plate(temp1,&common1);
                edit_thebusestxt(BusPlatesOrFilenames,temp1,temp2,1,fbuses,ftemp);
                ChangeOldPlateIntoNewForEachPassenger(BusPlatesOrFilenames,temp1,temp2,PersonFilenames,temp3,fseats,fpeople,fbuses,ftemp,ftemp2);

                strcat(BusPlatesOrFilenames,".txt");	// the old bus plate
                strcat(temp1,".txt");
                if(rename(BusPlatesOrFilenames,temp1)==0)
                {
                    printf("\nFile renamed successfully!\n");
                }
                else
                {
                    printf("\nUnable to rename the file!\n");
                    exit(0);
                }

                break;
            case 2:
                get_DepartDest_points(temp1,temp2,&common1);
                edit_thebusestxt(BusPlatesOrFilenames,temp1,temp2,2,fbuses,ftemp);
                break;
            case 3:
                get_DateTime(temp1,temp2,&common1);
                edit_thebusestxt(BusPlatesOrFilenames,temp1,temp2,3,fbuses,ftemp);
                break;
            }

            printf("\nSuccessfully edited.\n");
            break;

        case 4:
            list_all_buses(fbuses,&common1,temp1);
            choose_a_bus(fbuses,&common1,&decision,BusPlatesOrFilenames,temp1);

            strcat(BusPlatesOrFilenames,".txt");
            show_all_passengers_of_the_bus(BusPlatesOrFilenames,temp1,temp2,fbuses,&common1,&common2);
            break;
        case 5:
            waitfor(250);
            goto start;
        }
        break;


/*log out*/    case 6:
        log_in_val=0;
        printf("\nSuccessfully logged out!\n");
        break;
/* terminate */  case 7:
        remove("Temp.txt");
        remove("Temp2.txt");
        exit(0);
        break;
    }

    printf("\n(?) Do you want to terminate the program? ( 1 = Yes | 0 = No ) : ");
    decide(&decision,0,1);

    if(decision==0)
    {
        system("CLS");
        goto start;
    }
    else
    {
        remove("Temp.txt");
        remove("Temp2.txt");
        exit(0);
    }
}

void decide(unsigned short int *decision,unsigned short int min,unsigned short int max)
{
    while(1)
    {
        scanf("%hu",decision);    // I get the first digit, and don't know why.
        fflush(stdin);

        if( ( (*decision) >= min ) && ( (*decision) <= max) )
        {
            break;
        }
        else
        {
            printf("\n**Please enter a valid decision number!\n");
            Sleep(2000);
            printf("\n : ");
        }
    }
}

void waitfor(unsigned short int time)
{
    Sleep(time);
    system("CLS");
}

void AsktoGoBacktoStart(unsigned short int *temp_int)
{
    printf("\n(?) Do you want to go back to the beginning or stay in this menu? ( 1 = Go back | 0 = Stay here ) : ");
    decide(temp_int,0,1);
    waitfor(500);
}

void name_formatter(char *name,char *surname,unsigned short int *i)
{
    name[0] = toupper(name[0]);
    (*i)=1;
    while (name[(*i)] != '\0')
    {
        if (name[(*i) - 1] != ' ')
            name[(*i)] = tolower(name[(*i)]);
        else
            name[(*i)] = toupper(name[(*i)]);
        (*i)++;
    }

    (*i)=0;
    while (surname[(*i)] != '\0')
    {
        surname[(*i)] = toupper(surname[(*i)]);
        (*i)++;
    }
}

void until_newline(char *str,unsigned short int *temp_int)
{
    for((*temp_int)=0 ; (*temp_int)<strlen(str) ; (*temp_int)++ )
    {
        if(str[(*temp_int)]=='\n')
        {
            str[(*temp_int)]='\0';
            break;
        }
    }
}

void generate_person_filename(char *person_filename,struct info *person)
{
    strcpy(person_filename,person->name);
    strcat(person_filename," ");
    strcat(person_filename,person->surname);
    strcat(person_filename,".txt");
}

void plate_formatter(char *the_plate,unsigned short int *temp)
{
    for((*temp)=0; the_plate[(*temp)]; (*temp)++)
    {
        the_plate[(*temp)]=toupper(the_plate[(*temp)]);
    }
}

void copy_to(FILE *source,FILE *dest,char *ch)
{
    rewind(dest),rewind(source);
    while((*ch=getc(source))!=EOF)
    {
        putc(*ch,dest);
    }
    rewind(dest);
}

int id_check(char *id,char *temp_str,char *person_filename,FILE *fpeople)
{
    fpeople=fopen(person_filename,"r");
    if(fpeople!=NULL)
    {
        fgets(temp_str,MAXX,fpeople);
        until_newline(temp_str,&TillNewLineV);

        fclose(fpeople);
        if(strcmp(id,temp_str)==0)
            return 1;
        else
            return 0;
    }
    else
    {
        fclose(fpeople);
        return 1;
    }
}

void ask_to_log_in(struct info *person,unsigned short int *decision,unsigned short int *temp_int,unsigned short int *log_in_val,char *person_filename,char *temp_str,FILE *fpeople)
{
    printf("\n(?) Do you want to log in to access the main functions? (1 = Yes | 0 = No ) : ");
    decide(decision,0,1);
    if((*decision)==1)
    {
        obtain_user_info(person,temp_int);
        (*log_in_val)=1;

        generate_person_filename(person_filename,person);
        while(id_check(person->id,temp_str,person_filename,fpeople)==0)
        {
            printf("\n**Please make sure your ID is correct!\n");
            waitfor(2500);
            obtain_id(person->id,temp_int);
        }
        printf("\nSuccessfully logged in!\n");
        waitfor(750);
    }
    else
    {
        printf("\n***Please log in to access the main functions. Without logging in, you can only choose option 2 or 7.\n");
        waitfor(3000);
    }

}

void obtain_user_info(struct info *person,unsigned short int *temp_int)
{
    obtain_name(person->name,temp_int);
    obtain_surname(person->surname,temp_int);
    obtain_id(person->id,temp_int);
    name_formatter(person->name,person->surname,temp_int);
}

void obtain_name(char *name,unsigned short int *temp_int)
{
    while(1)
    {
        printf("\nPlease enter your name : ");
        fflush(stdin);
        gets(name);
        for( (*temp_int)=0 ; ((name[(*temp_int)]>='a' && name[(*temp_int)]<='z') || (name[(*temp_int)]>='A' && name[(*temp_int)]<='Z') || (name[(*temp_int)]==' ')) ; (*temp_int)++ );
        // if it contains something except alphabet or a blank

        if( ((*temp_int)==strlen(name)) && (strlen(name)<=MAXX-3))
            break;
        else
        {
            printf("\n**Please only enter letters or enter the number of your characters below 41!\n");
            waitfor(3000);
        }
    }
}

void obtain_surname(char *surname,unsigned short int *temp_int)
{
    while(1)
    {
        printf("\nPlease enter your surname : ");
        scanf("%s",surname);
        fflush(stdin);
        for( (*temp_int)=0 ;    ((surname[(*temp_int)]>='a' && surname[(*temp_int)]<='z') || (surname[(*temp_int)]>='A' && surname[(*temp_int)]<='Z'))     ; (*temp_int)++ );

        if( ((*temp_int)==strlen(surname)) && (strlen(surname)<=MAXX-3) )
            break;
        else
        {
            printf("\n**Please only enter letters or enter the number of your characters below 41!\n");
            waitfor(3000);
        }
    }
}

void obtain_id(char *id,unsigned short int *temp_int)
{
    while(1)
    {
        printf("\nPlease enter your ID : ");
        scanf("%s",id);
        fflush(stdin);
        for( (*temp_int)=0  ;    ((id[(*temp_int)]>='0') && (id[(*temp_int)]<='9'))   ;  (*temp_int)++ );
        if((*temp_int)==11)
            break;
        else
        {
            printf("\n**Please enter a valid ID!\n");
            waitfor(2500);
        }
    }
}

void list_all_buses(FILE *fbuses,unsigned short int *order_var,char *ShowInfoStr)
{
    fbuses=fopen(thebusestxt,"r");
    if(fbuses!=NULL)
    {
        printf("\n\n     Bus Plate\t\tDepart. -> Dest.\tDate & Time\n------------------------------------------------------------------\n");

        for((*order_var)=1 ; !feof(fbuses)  ; (*order_var)++)
        {
            ShowInfoStr[0]='\0';  // to prevent displaying some ghost data

            fgets(ShowInfoStr,MAXX,fbuses);
            until_newline(ShowInfoStr,&TillNewLineV);

            if(ShowInfoStr[0]!='\0')
            {
                printf("%hu ->  %s      ",(*order_var),ShowInfoStr);  //  order -> bus plate

                fgets(ShowInfoStr,MAXX,fbuses);
                until_newline(ShowInfoStr,&TillNewLineV);
                printf("%s     ",ShowInfoStr);         // depart. -> dest.

                fgets(ShowInfoStr,MAXX,fbuses);
                until_newline(ShowInfoStr,&TillNewLineV);
                printf(" %s\n",ShowInfoStr);       // date & time
            }
        }
        fclose(fbuses);
        printf("------------------------------------------------------------------\n\n");
    }
    else
    {
        printf("\n**The Buses.txt can't be accessed. Error code : 1\n");
        exit(0);
    }
}

void choose_a_bus( FILE *fbuses, unsigned short int *control_var, unsigned short int *the_bus_num,char *the_bus_plate, char *temp_str )
{
    fbuses=fopen(thebusestxt,"r");
    if(fbuses!=NULL)
    {
        while(1)
        {
            printf("\nWhich bus do you want to choose? ( by the number on the left ) : ");
            decide(the_bus_num,1,MAXSEATS);

            (*control_var)=0;
            while(( (*control_var)!=(*the_bus_num) ) && (!feof(fbuses) ))
            {
                fgets(the_bus_plate,MAXX,fbuses);    // the bus plate
                until_newline(the_bus_plate,&TillNewLineV);

                fgets(temp_str,MAXX,fbuses);     // the departure and destination point
                until_newline(temp_str,&TillNewLineV);

                fgets(temp_str,MAXX,fbuses);      // the date & time
                until_newline(temp_str,&TillNewLineV);

                if((temp_str[0]!='\0'))    /// to prevent counting the new line which is at the end of the file
                {
                    (*control_var)++;
                }
                temp_str[0]='\0';
            }

            if((*control_var)==(*the_bus_num))
                break;
            else
            {
                printf("\n**Please enter a valid bus number!\n");
                Sleep(1000);
            }
            rewind(fbuses);
        }
        fclose(fbuses);
    }
    else
    {
        printf("\n**The Buses.txt can't be accessed. Error code : 2\n");
        exit(0);
    }
}

void list_all_the_seats(FILE *fseats,unsigned short int *control_var,unsigned short int *order_var,unsigned short int *seat_num,char *the_bus_filename,char *temp1,char *temp2)
{
    unsigned short int f_length;
    fseats=fopen(the_bus_filename,"r");
    if(fseats!=NULL)
    {
        printf("\n All The Seats ( The ones with '**' are reserved )\n-------------------------------\n");

        fseek(fseats,0,SEEK_END);
        f_length=ftell(fseats);

        for((*order_var)=1; (*order_var)<=MAXSEATS; (*order_var)++)
        {
            (*control_var)=0;
            if((f_length)!=0)
            {
                rewind(fseats);
                while(!feof(fseats))
                {
                    fscanf(fseats,"%hu",seat_num);
                    fscanf(fseats,"%s %s",temp1,temp2);
                    if((*order_var)==(*seat_num))
                        (*control_var)++;
                }
            }

            // some things to make it look good
            if((*control_var) > 0)
            {
                printf("**  ");
                if((*order_var) > 10)
                    printf(" ");
            }
            else
                printf("%hu   ",(*order_var));

            if((*order_var) < 10)
                printf(" ");

            if((*order_var) %4 == 0)
                printf("\n");

        }
        fclose(fseats);
        printf("-------------------------------\n");
    }
    else
    {
        printf("\n**The Particular Bus File can't be accessed. Error code : 3\n");
        exit(0);
    }
}

void control_the_existence_of_TheSeatNum(FILE *fseats,unsigned short int *temp_int,unsigned short int *the_seat_num,unsigned short int *control_var,char *temp1_str,char *temp2_str)
{
    rewind(fseats);
    (*control_var)=0;
    while(!feof(fseats))
    {
        fscanf(fseats,"%hu",temp_int);
        fscanf(fseats,"%s %s",temp1_str,temp2_str);
        if((*temp_int)==(*the_seat_num))
            (*control_var)++;
    }
}

void choose_a_seat(FILE *fseats,unsigned short int *control_var,unsigned short int *temp_int,unsigned short int *the_seat_num,char *the_bus_plate,char *temp1_str,char *temp2_str,char *name,char *surname)
{
    fseats=fopen(the_bus_plate,"a+");
    if(fseats!=NULL)
    {
        while(1)
        {
            printf("\nPlease enter the number of the seat you want : ");
            decide(the_seat_num,1,32);

            control_the_existence_of_TheSeatNum(fseats,temp_int,the_seat_num,control_var,temp1_str,temp2_str);
            if((*control_var)==0)
            {
                break;
            }
            else
            {
                printf("\n**Sorry, that seat is already taken!\n");
            }
        }
        fprintf(fseats,"%hu\n%s %s\n",(*the_seat_num),name,surname);
        fclose(fseats);
    }
    else
    {
        printf("\n**The Particular Bus file can't be accessed. Error code : 4\n");
        exit(0);
    }
}

void create_a_new_person_file(FILE *fpeople,char *person_filename,char *id)
{
    fpeople=fopen(person_filename,"w");
    if(fpeople!=NULL)
    {
        fprintf(fpeople,"%s", id);
        fclose(fpeople);
    }
    else
    {
        printf("\n**The Person File can't be accessed. Error code : 5\n");
        exit(0);
    }
}

void save_the_reservation_info(unsigned short int *the_seat_num,char *the_bus_plate,char *person_filename,FILE *fpeople)
{
    fpeople=fopen(person_filename,"a");
    if(fpeople!=NULL)
    {
        fprintf(fpeople,"\n%s\n%hu",the_bus_plate,*the_seat_num);   // if there was a new line in the end, that would be a problem for "copy_to" function.
        fclose(fpeople);
    }
    else
    {
        printf("\n**The Person File can't be accessed. Error code : 6\n");
        exit(0);
    }
}

void ListAllReservationsOfThePerson(struct info *person,char *person_filename,char *temp1,char *temp2,FILE *fpeople,FILE *fbuses,unsigned short int *order_var)
{
    fpeople=fopen(person_filename,"r");
    fbuses=fopen(thebusestxt,"r");
    (*order_var)=0;

    if((fpeople!=NULL) & (fbuses!=NULL))
    {
        fgets(temp2,MAXX,fpeople);  // id
        until_newline(temp2,&TillNewLineV);

        printf("\n\n\n     Bus Plate\tSeat Number\tDepart. -> Dest.\tDate & Time\n---------------------------------------------------------------------------\n");
        while(!feof(fpeople))
        {
            temp2[0]='\0';  // to prevent repeating

            fgets(temp2,MAXX,fpeople);    /// the bus plate
            until_newline(temp2,&TillNewLineV);

            if(temp2[0]!='\0')
            {
                while(strcmp(temp1,temp2)!=0)
                {
                    fgets(temp1,MAXX,fbuses);
                    until_newline(temp1,&TillNewLineV);
                }

                (*order_var)++;
                printf("%hu -) %s\t   ",*order_var,temp2);

                temp2[0]='\0';
                fgets(temp2,3,fpeople);      /// the seat number
                until_newline(temp2,&TillNewLineV);

                if(temp2[0]!='\0')
                {
                    printf("%s\t\t",temp2);

                    fgets(temp1,MAXX,fbuses); /// the departure and destination point
                    until_newline(temp1,&TillNewLineV);
                    printf("%s\t",temp1);

                    fgets(temp1,MAXX,fbuses); /// the date & time
                    until_newline(temp1,&TillNewLineV);
                    printf("%s\n",temp1);
                }
            }
            rewind(fbuses);
        }
        fclose(fpeople),fclose(fbuses);
        printf("---------------------------------------------------------------------------\n\n\n\n");
    }
    else
    {
        printf("\n**The Buses.txt or The Person File can't be accessed. Error code : 7\n");
        exit(0);
    }
}

void get_a_bus_plate(char *the_plate,unsigned short int *temp)
{
    while(1)    // bus plate
    {
        printf("\nPlease enter the bus plate : ");
        fflush(stdin);
        gets(the_plate);

        (*temp)=strlen(the_plate);

        strcat(the_plate,".txt");
        if( (((*temp)>6) && ((*temp)<12)) && (access(the_plate,F_OK)!=0) )
        {
            break;
        }
        else if(access(the_plate,F_OK)==0)
        {
            printf("\n**There is already a bus which has this plate. Please enter the bus plate again.\n");
            waitfor(2500);
        }
        else
        {
            printf("\nPlease enter a valid bus plate!\n");
            waitfor(2500);
        }
    }
    strtok(the_plate,".txt");
    plate_formatter(the_plate,temp);
}

void get_DepartDest_points(char *destination,char *temp_str,unsigned short int *temp_int)
{
    while(1)
    {
        printf("\nPlease enter the departure point : ");
        fflush(stdin);
        gets(destination);
        for( (*temp_int)=0 ;   ((destination[(*temp_int)]>='a') && (destination[(*temp_int)]<='z')) || (destination[(*temp_int)]==' ') || ((destination[(*temp_int)]>='A') && (destination[(*temp_int)]<='Z')) ; (*temp_int)++);
        if((*temp_int)!=strlen(destination))
        {
            printf("\n**Please enter the departure point correctly!");
            waitfor(2500);
        }
        else
            break;
    }
    destination[0]=toupper(destination[0]);
    strcat(destination," -> ");

    while(1)
    {
        printf("\nPlease enter the destination point : ");
        fflush(stdin);
        gets(temp_str);
        for( (*temp_int)=0 ;   ((temp_str[(*temp_int)]>='a') && (temp_str[(*temp_int)]<='z')) || (temp_str[(*temp_int)]==' ') || ((temp_str[(*temp_int)]>='A') && (temp_str[(*temp_int)]<='Z')) ; (*temp_int)++);

        if((*temp_int)!=strlen(temp_str))
        {
            printf("\n**Please enter the destination point correctly!");
            waitfor(2500);
        }
        else
            break;
    }
    temp_str[0]=toupper(temp_str[0]);
    strcat(destination,temp_str);
}

void get_DateTime(char *date,char *temp_str,unsigned short int *temp_int)
{
    while(1)    // date
    {
        printf("\nPlease enter the departure date (DD.MM.YY) : ");
        scanf("%010s",date);    // to get the zero in front of the number
        fflush(stdin);

        for ( (*temp_int)=0 ;    ((date[(*temp_int)]>='0') && (date[(*temp_int)]<='9')) || (date[(*temp_int)]=='.') ; (*temp_int)++);

        if ( ((*temp_int)==10))
            break;
        else
        {
            printf("\n**Please enter the date in this format (03.05.2021)!\n");
            waitfor(2500);
        }
    }
    while(1)    // time
    {
        printf("\nPlease enter the departure time (HH:MM) : ");
        scanf("%05s",temp_str);
        fflush(stdin);

        for( (*temp_int)=0 ;    ((temp_str[(*temp_int)]>='0') && (temp_str[(*temp_int)]<='9')) || (temp_str[(*temp_int)]==':') ; (*temp_int)++);

        if( ((*temp_int)==5) )
            break;
        else
        {
            printf("\n**Please enter the time in this format (09:05)!\n");
            waitfor(2500);
        }
    }
    strcat(date,"  ");
    strcat(date,temp_str);
}

void get_bus_info(char *the_plate,char *destination,char *date,char *temp_str,unsigned short int *temp_int)
{
    get_a_bus_plate(the_plate,temp_int);
    get_DepartDest_points(destination,temp_str,temp_int);
    get_DateTime(date,temp_str,temp_int);
}

void add_new_bus_to_thebusestxt(FILE *fbuses,char *the_plate,char *destination,char *date)
{
    fbuses=fopen(thebusestxt,"a");
    if(fbuses!=NULL)
    {
        fprintf(fbuses,"%s\n%s\n%s\n",the_plate,destination,date);
        fclose(fbuses);
    }
    else
    {
        printf("\n**The Buses.txt can't be accessed. Error code : 8\n");
        exit(0);
    }
}

void create_new_bus_file(FILE *fbuses,char *the_plate)
{
    fbuses=fopen(the_plate,"a");
    fclose(fbuses);
}

int ControlTheExistenceOfTheReservations(struct info *person,char *person_filename,char *temp_str,unsigned short int *control_var,FILE *fpeople)
{
    generate_person_filename(person_filename,person); // check the existence of the person
    if( access(person_filename, F_OK) !=0 )
    {
        printf("\n**Looks like there aren't any reservations related to you. Please try to make reservations first.\nDirecting to the Main Menu...");
        waitfor(4000);
        return 0;
    }
    else
    {
        fpeople=fopen(person_filename,"r");
        if(fpeople!=NULL)
        {
            (*control_var)=0;
            while(!feof(fpeople))
            {
                fgets(temp_str,MAXX,fpeople);
                until_newline(temp_str,&TillNewLineV);
                (*control_var)++;
            }
            fclose(fpeople);
            if((*control_var)>1)
            {
                return 1;
            }
            else
            {
                printf("\n**Looks like there aren't any reservations related to you. Please try to make reservations first.\nDirecting to the Main Menu...");
                waitfor(4000);
            }
        }
        else
        {
            printf("\n**The Person File can't be accessed. Error code : 9\n");
            exit(0);
        }
        return 0;
    }
}

void choose_a_reservation(char *person_filename,char *bus_plate,char *str_reservation_num,unsigned short int *control_var,unsigned short int *decision_num,FILE *fpeople)
{
    fpeople=fopen(person_filename,"r");
    if(fpeople!=NULL)
    {
        while(1)
        {
            printf("\nWhich reservation do you want to delete? ( by the number on the left ) : ");
            scanf("%hu",decision_num);
            fflush(stdin);
            if((*decision_num)>0)
            {
                fgets(str_reservation_num,13,fpeople);      // id
                until_newline(str_reservation_num,&TillNewLineV);

                (*control_var)=0;
                while(( (*control_var)!=(*decision_num) ) && (!feof(fpeople) ))
                {
                    fgets(bus_plate,MAXX,fpeople);    // the bus plate
                    until_newline(bus_plate,&TillNewLineV);

                    fgets(str_reservation_num,4,fpeople);       // the seat number
                    until_newline(str_reservation_num,&TillNewLineV);

                    // there is no need an if statement like this if(temp[0]!='\0') because of the file scheme ( there is no new line at the end of the file )
                    (*control_var)++;
                }

                if((*control_var)==(*decision_num))
                    break;
                else
                    printf("\n**Please enter a valid reservation number!\n");

                rewind(fpeople);
            }
            else
            {
                printf("\n**Please enter a valid reservation number!\n");
            }
        }
        fclose(fpeople);
    }
    else
    {
        printf("\n**The Person File can't be accessed. Error code : 10\n");
        exit(0);
    }
}

void remove_the_seat_number_from_the_bus_file(char *bus_filename,char *seat_number,char *temp1,char *temp2,FILE *fbuses,FILE *ftemp2)
{
    strcat(bus_filename,".txt");
    fbuses=fopen(bus_filename,"r");
    ftemp2=fopen("Temp2.txt","w+");

    if( (fbuses!=NULL) && (ftemp2!=NULL) )
    {
        copy_to(fbuses,ftemp2,&copy_char);

        fclose(fbuses);
        fbuses=fopen(bus_filename,"w");

        if(fbuses!=NULL)
        {
            while (!feof(ftemp2))
            {
                fgets(temp1,4,ftemp2);   // the seat number
                until_newline(temp1,&TillNewLineV);

                fgets(temp2,MAXX,ftemp2);   // name & surname
                until_newline(temp2,&TillNewLineV);

                if ((strcmp(temp1,seat_number)!=0) && (temp1[0]!='\0'))
                    fprintf(fbuses,"%s\n%s\n",temp1,temp2);
                temp1[0]='\0';
            }

            fclose(fbuses),fclose(ftemp2);
            strtok(bus_filename,".txt");
        }
        else
        {
            printf("\n**The Particular Bus file can't be accessed. Error code : 11\n");
            exit(0);
        }
    }
    else
    {
        printf("\n**The Particular Bus file or Temp file can't be accessed. Error code : 12\n");
        exit(0);
    }
}

void delete_a_reservation(char *PersonFilename,char *bus_plate,char *the_seat_num,char *temp1_str,char *temp2_str,unsigned short int decision,FILE *fpeople,FILE *fbuses,FILE *ftemp,FILE *ftemp2)
{
    fpeople=fopen(PersonFilename,"r");
    ftemp=fopen("Temp.txt","w+");
    if((fpeople!=NULL) && (ftemp!=NULL))
    {
        copy_to(fpeople,ftemp,&copy_char);

        fclose(fpeople);
        fpeople=fopen(PersonFilename,"w");

        if(fpeople!=NULL)
        {
            fgets(temp1_str,MAXX,ftemp);		// ID
            until_newline(temp1_str,&TillNewLineV);
            fprintf(fpeople,"%s",temp1_str);

            while(!feof(ftemp))
            {
                fgets(temp1_str,MAXX,ftemp);    // the bus plate
                until_newline(temp1_str,&TillNewLineV);

                fgets(temp2_str,4,ftemp);
                until_newline(temp2_str,&TillNewLineV);   // the seat number

                if( (strcmp(temp1_str,bus_plate)!=0) || ((strcmp(temp1_str,bus_plate)==0) && (strcmp(temp2_str,the_seat_num)!=0)))	// rewriting the reservations except the deleted one
                    fprintf(fpeople,"\n%s\n%s",temp1_str,temp2_str);

                else if(decision == 1)
                    remove_the_seat_number_from_the_bus_file(bus_plate,the_seat_num,temp1_str,temp2_str,fbuses,ftemp2);
            }
            fclose(fpeople),fclose(ftemp);
        }
        else
        {
            printf("\n**The Person File can't be accessed. Error code : 13\n");
            exit(0);
        }
    }
    else
    {
        printf("\n**The Person File or Temp File can't be accessed. Error code : 14\n");
        exit(0);
    }

}

void delete_the_bus_from_thebusestxt(char *bus_plate,char *temp1,char *temp2,char *temp3,FILE *fbuses,FILE *ftemp)
{
    fbuses=fopen(thebusestxt,"r");
    ftemp=fopen("Temp.txt","w+");

    if((fbuses!=NULL) && (ftemp!=NULL))
    {
        copy_to(fbuses,ftemp,&copy_char);
        fclose(fbuses);

        fbuses=fopen(thebusestxt,"w");
        if(fbuses!=NULL)
        {
            while(!feof(ftemp))
            {
                temp1[0]='\0';

                fgets(temp1,MAXX,ftemp);    // the bus plate
                until_newline(temp1,&TillNewLineV);

                fgets(temp2,MAXX,ftemp);    // the departure and destination points
                until_newline(temp2,&TillNewLineV);

                fgets(temp3,MAXX,ftemp);    // the departure date and time
                until_newline(temp3,&TillNewLineV);

                if( (strcmp(temp1,bus_plate)!=0 ) && (temp1[0]!='\0') )
                {
                    fprintf(fbuses,"%s\n%s\n%s\n",temp1,temp2,temp3);
                }
            }
            fclose(fbuses),fclose(ftemp);
        }
        else
        {
            printf("\n**The Buses.txt can't be accessed. Error code : 15\n");
            exit(0);
        }
    }
    else
    {
        printf("\n**The Buses.txt or Temp File can't be accessed. Error code : 16\n");
        exit(0);
    }
}

void delete_the_SeatNum_from_each_passanger(char *bus_filename,char *person_filename,char *seat_num,char *temp1,char *temp2,unsigned short int *temp_int,FILE *fpeople,FILE *fbuses,FILE *ftemp,FILE *ftemp2)
{
    fbuses=fopen(bus_filename,"r");

    if(fbuses!=NULL)
    {
        strtok(bus_filename,".txt");		// delete_a_reservation needs a bus plate, not a bus filename
        while(!feof(fbuses))
        {
            fgets(seat_num,MAXX,fbuses);       // the seat number
            until_newline(seat_num,temp_int);

            fgets(person_filename,MAXX,fbuses);     // name & surname
            until_newline(person_filename,temp_int);

            strcat(person_filename,".txt");

            if( (seat_num[0]!='\0') )
            {
                delete_a_reservation(person_filename,bus_filename,seat_num,temp1,temp2,0,fpeople,fbuses,ftemp,ftemp2);
                // "decision=0" because I'm already going to delete the bus file
            }
            seat_num[0]='\0';
        }

        // removing the bus file
        strcat(bus_filename,".txt");

        fclose(fbuses);
        remove(bus_filename);
    }
    else
    {
        printf("\n**The Buses.txt can't be accessed. Error code : 17\n");
        exit(0);
    }
}

void edit_thebusestxt(char *bus_plate,char *new_info,char *tempStr,unsigned short int mod,FILE *fbuses,FILE *ftemp)
{
    fbuses=fopen(thebusestxt,"r");
    ftemp=fopen("Temp.txt","w+");
    if((fbuses!=NULL) && (ftemp!=NULL))
    {
        copy_to(fbuses,ftemp,&copy_char);
        fclose(fbuses);

        fbuses=fopen(thebusestxt,"w");
        if(fbuses!=NULL)
        {
            while(!feof(ftemp))
            {
                fgets(tempStr,MAXX,ftemp);
                until_newline(tempStr,&TillNewLineV);

                if((strcmp(bus_plate,tempStr)==0) && (tempStr[0]!='\0'))
                {
                    switch(mod)
                    {
                    case 1:		// the bus plate
                        fprintf(fbuses,"%s\n",new_info);

                        break;

                    case 2:		// the depart. and dest. points
                    case 3:		// the date & time info
                        fprintf(fbuses,"%s\n",bus_plate);
                        fgets(tempStr,MAXX,ftemp);
                        until_newline(tempStr,&TillNewLineV);

                        if(mod==3)
                        {
                            fprintf(fbuses,"%s\n",tempStr);
                            fgets(tempStr,MAXX,ftemp);
                            until_newline(tempStr,&TillNewLineV);
                        }
                        fprintf(fbuses,"%s\n",new_info);

                        break;
                    }
                }
                else if(tempStr[0]!='\0')
                {
                    fprintf(fbuses,"%s\n",tempStr);
                }
                tempStr[0]='\0';
            }
            fclose(ftemp),fclose(fbuses);
        }
        else
        {
            printf("\n**The Buses.txt can't be accessed. Error code : 18\n");
            exit(0);
        }
    }
    else
    {
        printf("\n**The Buses.txt or Temp File can't be accessed. Error code : 19\n");
        exit(0);
    }
}

void ChangeOldPlateIntoNewForEachPassenger(char *OldBusPlate,char *NewBusPlate,char *SeatNum,char *PersonFilenameorTemp1,char *temp2,FILE *fseats,FILE *fpeople,FILE *fbuses,FILE *ftemp,FILE *ftemp2)
{
    strcat(OldBusPlate,".txt");
    fseats=fopen(OldBusPlate,"r");
    strtok(OldBusPlate,".txt");

    if(fseats!=NULL)
    {
        while(!feof(fseats))
        {
            fgets(SeatNum,MAXX,fseats);
            until_newline(SeatNum,&TillNewLineV);

            fgets(PersonFilenameorTemp1,MAXX,fseats);
            until_newline(PersonFilenameorTemp1,&TillNewLineV);

            strcat(PersonFilenameorTemp1,".txt");	// delete a reservation, and append

            if(access(PersonFilenameorTemp1,F_OK)==0)
            {
                fpeople=fopen(PersonFilenameorTemp1,"a");
                if(fpeople!=NULL)
                {
                    fprintf(fpeople,"\n%s\n%s",NewBusPlate,SeatNum);
                }
                else
                {
                    printf("\n**The new bus plate can't be saved into one of the person files. Error code : 20\n");
                    exit(0);
                }
                fclose(fpeople);

                delete_a_reservation(PersonFilenameorTemp1,OldBusPlate,SeatNum,PersonFilenameorTemp1,temp2,0,fpeople,fbuses,ftemp,ftemp2);
            }
        }
        fclose(fseats);
    }
    else
    {
        printf("\n**The old bus file can't be accessed. Error code : 21\n");
        exit(0);
    }
}

void show_all_passengers_of_the_bus(char *bus_filename,char *temp1,char *temp2,FILE *fbuses,unsigned short int *order_var,unsigned short int *seat_num)
{
    fbuses=fopen(bus_filename,"r");
    if(fbuses!=NULL)
    {
        printf("\n\n   All of Its Passengers (The ones with '-' are empty)\n----------------------------------------");
        for((*order_var)=1; (*order_var)<=MAXSEATS; (*order_var)++)
        {
            printf("\n%hu = ",(*order_var));
            while(( !feof(fbuses) ) && ( (*order_var)!=(*seat_num)) )
            {
                fgets(temp1,4,fbuses);
                until_newline(temp1,&TillNewLineV);

                fgets(temp2,MAXX,fbuses);
                until_newline(temp2,&TillNewLineV);

                if(temp1[1]=='\0')  // 1 digit
                {
                    (*seat_num)=(temp1[0]-'0');
                }
                else // 2 digits
                {
                    (*seat_num)=10*(temp1[0]-'0');
                    (*seat_num)+=(temp1[1]-'0');
                }
            }
            if( (*order_var)==(*seat_num) )
                printf("%s",temp2);
            else
                printf(" -");
            rewind(fbuses);
        }
        printf("\n----------------------------------------\n\n");
        fclose(fbuses);
    }
    else
    {
		printf("\n**The particular bus file can't be accessed. Error code : 22\n");
        exit(0);
    }
}
