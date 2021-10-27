// I refer the ASCII Art Text Alphabet (or whatever) as "the alphabet".

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Some Characters in ASCII Values
#define SPACE_CHAR ' '
#define ENTER_CHAR '\r'
#define BACKSPACE_CHAR 8
#define ESCAPE_CHAR 27

// Return Values of Some Pressed Keys
#define UNDEFINED_KEY_PRESSED 26 // also the index of question mark in the alphabet
#define SPACE_KEY_PRESSED 27     // also the index of space character in the alphabet
#define ZERO_KEY_PRESSED 28      // also the index of '0' in the alphabet

#define ENTER_KEY_PRESSED -1
#define BACKSPACE_KEY_PRESSED -2
#define ESCAPE_KEY_PRESSED -3

// This is the count of blocks of a character in the alphabet. ( e.g. ASCII Art Letter 'A' contains 25 block of characters.)
// Don't forget to change the PrintXLine functions.
#define BLOCKS_PER_CHARACTER 25 // 25 characters = 5 x 5

int ConvertCharIntoIndexNum(int ch_Input);

// FUNCTIONS

void PrintFirstLineOf(unsigned int indexNumOf_theAlphabetStr);
void PrintSecondLineOf(unsigned int indexNumOf_theAlphabetStr);
void PrintThirdLineOf(unsigned int indexNumOf_theAlphabetStr);
void PrintFourthLineOf(unsigned int indexNumOf_theAlphabetStr);
void PrintFifthLineOf(unsigned int indexNumOf_theAlphabetStr);

int ReturnIndexOf_NextNewlineChar_InConvertedStr(int indexOf_PreviousNewlineChar, int *ConvertedStr);
void PrintConvertedStr(int *ConvertedStr);

// GLOBAL VARIABLES

const char theAlphabetStr[][BLOCKS_PER_CHARACTER + 1] = {
    {" ### "
     "#   #"
     "#####"
     "#   #"
     "#   #"},

    {"#### "
     "#   #"
     "#### "
     "#   #"
     "#### "},

    {" ####"
     "#    "
     "#    "
     "#    "
     " ####"},

    {"#### "
     "#   #"
     "#   #"
     "#   #"
     "#### "},

    {"#####"
     "#    "
     "#####"
     "#    "
     "#####"},

    {"#####"
     "#    "
     "#####"
     "#    "
     "#    "},

    {" ####"
     "#    "
     "# ###"
     "#   #"
     " ### "},

    {"#   #"
     "#   #"
     "#####"
     "#   #"
     "#   #"},

    {"#####"
     "  #  "
     "  #  "
     "  #  "
     "#####"},

    {"    #"
     "    #"
     "#   #"
     "#   #"
     " ### "},

    {"#   #"
     "#  # "
     "###  "
     "#  # "
     "#   #"},

    {"#    "
     "#    "
     "#    "
     "#    "
     "#####"},

    {"#   #"
     "## ##"
     "# # #"
     "#   #"
     "#   #"},

    {"#   #"
     "##  #"
     "# # #"
     "#  ##"
     "#   #"},

    {" ### "
     "#   #"
     "#   #"
     "#   #"
     " ### "},

    {"#### "
     "#   #"
     "#### "
     "#    "
     "#    "},

    {"#####"
     "#   #"
     "# # #"
     "#  ##"
     "#####"},

    {"#### "
     "#   #"
     "#### "
     "#  # "
     "#   #"},

    {" ####"
     "#    "
     " ### "
     "    #"
     "#### "},

    {"#####"
     "  #  "
     "  #  "
     "  #  "
     "  #  "},

    {"#   #"
     "#   #"
     "#   #"
     "#   #"
     " ### "},

    {"#   #"
     "#   #"
     "#   #"
     " # # "
     "  #  "},

    {"# # #"
     "# # #"
     "# # #"
     "# # #"
     " # # "},

    {"#   #"
     " # # "
     "  #  "
     " # # "
     "#   #"},

    {"#   #"
     " # # "
     "  #  "
     "  #  "
     "  #  "},

    {"#####"
     "   # "
     "  #  "
     " #   "
     "#####"},

    {" ### "
     "#   #"
     "   # "
     "     "
     "  #  "},

    {"     "
     "     "
     "     "
     "     "
     "     "},

    {" ### "
     "#  ##"
     "# # #"
     "##  #"
     " ### "},

    {"  #  "
     " ##  "
     "  #  "
     "  #  "
     " ### "},

    {" ### "
     "#   #"
     "   # "
     " #   "
     "#####"},

    {"#### "
     "    #"
     " ### "
     "    #"
     "#### "},

    {"#   #"
     "#   #"
     " ####"
     "    #"
     "    #"},

    {"#####"
     "#    "
     "#### "
     "    #"
     "#### "},

    {"#####"
     "#    "
     "#####"
     "#   #"
     "#####"},

    {"#####"
     "   # "
     "  #  "
     " #   "
     "#    "},

    {" ### "
     "#   #"
     " ### "
     "#   #"
     " ### "},

    {" ### "
     "#   #"
     " ####"
     "    #"
     "#### "}};

unsigned int maxIndexNumOf_ConvertedStr = 0;

int main()
{
    puts(" Please type your input to start\n      (Press ESC to exit)\n :");
    fflush(stdout);

    int returnValueOf_ConvertChar;

    int *ConvertedStr = (int *)malloc(1 * sizeof(int)); // this string contains the indices of the pressed keys by the alphabet, because of that it's an integer array.

    while (1)
    {
        if (kbhit())
        {
            returnValueOf_ConvertChar = ConvertCharIntoIndexNum(getch());

            if (returnValueOf_ConvertChar == ESCAPE_KEY_PRESSED)
            {
                break;
            }

            else if (returnValueOf_ConvertChar == BACKSPACE_KEY_PRESSED)
            {
                if (maxIndexNumOf_ConvertedStr > 0) // if there is something to delete
                {
                    maxIndexNumOf_ConvertedStr--;

                    ConvertedStr[maxIndexNumOf_ConvertedStr] = BACKSPACE_KEY_PRESSED;

            // it prints the actual length as added 1, because it counts backspace character's index as a valid character's index
            // i subtract 1 from it just for now in order to prevent it to happen
                    maxIndexNumOf_ConvertedStr--;
                    PrintConvertedStr(ConvertedStr);
                    maxIndexNumOf_ConvertedStr++;
                }
                
                continue;
            }

            ConvertedStr[maxIndexNumOf_ConvertedStr] = returnValueOf_ConvertChar;

            PrintConvertedStr(ConvertedStr);

            maxIndexNumOf_ConvertedStr++;

            if ((ConvertedStr = (int *)realloc(ConvertedStr, (maxIndexNumOf_ConvertedStr + 1) * sizeof(int))) == NULL) // I'd prefer to expand ConvertedStr, rather than having it as a maximum-sized array.
            {
                printf("\n\nMemory reallocation wasn't successful. Error Code : 1\n");
                fflush(stdout);

                break;
            }
        }
    }

    printf("\n\n");
    free(ConvertedStr);
    return 0;
}

void PrintFirstLineOf(unsigned int indexNumOf_theAlphabetStr)
{
    if (theAlphabetStr[indexNumOf_theAlphabetStr])
        for (unsigned int i = 0; i < 5; i++)
        {
            printf("%c", theAlphabetStr[indexNumOf_theAlphabetStr][i]);
        }
    printf("  ");   // the quantity of spaces between characters
    fflush(stdout);
}

void PrintSecondLineOf(unsigned int indexNumOf_theAlphabetStr)
{
    for (unsigned int i = 5; i < 10; i++)
    {
        printf("%c", theAlphabetStr[indexNumOf_theAlphabetStr][i]);
    }
    printf("  ");
    fflush(stdout);
}

void PrintThirdLineOf(unsigned int indexNumOf_theAlphabetStr)
{
    for (unsigned int i = 10; i < 15; i++)
    {
        printf("%c", theAlphabetStr[indexNumOf_theAlphabetStr][i]);
    }
    printf("  ");
    fflush(stdout);
}

void PrintFourthLineOf(unsigned int indexNumOf_theAlphabetStr)
{
    for (unsigned int i = 15; i < 20; i++)
    {
        printf("%c", theAlphabetStr[indexNumOf_theAlphabetStr][i]);
    }
    printf("  ");
    fflush(stdout);
}

void PrintFifthLineOf(unsigned int indexNumOf_theAlphabetStr)
{
    for (unsigned int i = 20; i < 25; i++)
    {
        printf("%c", theAlphabetStr[indexNumOf_theAlphabetStr][i]);
    }
    printf("  ");
    fflush(stdout);
}

int ConvertCharIntoIndexNum(int ch_Input)
{
    if ((ch_Input >= 'a') && (ch_Input <= 'z'))
    {
        return (int)(ch_Input - 'a');
    }

    else if ((ch_Input >= 'A') && (ch_Input <= 'Z'))
    {
        return (int)(ch_Input - 'A');
    }

    else if ((ch_Input >= '0') && (ch_Input <= '9'))
    {
        return (int)(ch_Input - '0') + ZERO_KEY_PRESSED;
    }

    else if (ch_Input == SPACE_CHAR)
    {
        return SPACE_KEY_PRESSED;
    }

    else if (ch_Input == ENTER_CHAR)
    {
        return ENTER_KEY_PRESSED;
    }

    else if (ch_Input == BACKSPACE_CHAR)
    {
        return BACKSPACE_KEY_PRESSED;
    }

    else if (ch_Input == ESCAPE_CHAR)
    {
        return ESCAPE_KEY_PRESSED;
    }

    else
    {
        return UNDEFINED_KEY_PRESSED;
    }
}

int ReturnIndexOf_NextNewlineChar_InConvertedStr(int indexOf_PreviousNewlineChar, int *ConvertedStr)
{
    for (unsigned int i = indexOf_PreviousNewlineChar + 1; i < (maxIndexNumOf_ConvertedStr + 1); i++)
    {
        if (ConvertedStr[i] == ENTER_KEY_PRESSED)
        {
            return i;
        }
    }
    return (maxIndexNumOf_ConvertedStr + 1); // the length of ConvertedStr
}

void PrintConvertedStr(int *ConvertedStr)
{
    system("CLS");

    unsigned int startIndex = 0;

    unsigned int indexOf_NewlineChar_InConvertedStr = ReturnIndexOf_NextNewlineChar_InConvertedStr(-1, ConvertedStr);
   
    printf("%hu\n", (maxIndexNumOf_ConvertedStr + 1) );

    printf("\n\n\n");
    printf("   ");  // the quantity of spaces between the side of the left border and the first character

    while (1)
    {
        for (unsigned int i = startIndex; i < indexOf_NewlineChar_InConvertedStr; i++)
        {
            if (ConvertedStr[i] == BACKSPACE_KEY_PRESSED)   // don't print backspace (although it's invisible). It would just print the old deleted character instead of a blank character if i didn't assign it to that constant.
            {
                continue;
            }
            PrintFirstLineOf(ConvertedStr[i]);
        }
        printf("\n");

        printf("   ");
        for (unsigned int i = startIndex; i < indexOf_NewlineChar_InConvertedStr; i++)
        {
            if (ConvertedStr[i] == BACKSPACE_KEY_PRESSED)
            {
                continue;
            }
            PrintSecondLineOf(ConvertedStr[i]);
        }
        printf("\n");

        printf("   ");
        for (unsigned int i = startIndex; i < indexOf_NewlineChar_InConvertedStr; i++)
        {
            if (ConvertedStr[i] == BACKSPACE_KEY_PRESSED)
            {
                continue;
            }
            PrintThirdLineOf(ConvertedStr[i]);
        }
        printf("\n");

        printf("   ");
        for (unsigned int i = startIndex; i < indexOf_NewlineChar_InConvertedStr; i++)
        {
            if (ConvertedStr[i] == BACKSPACE_KEY_PRESSED)
            {
                continue;
            }
            PrintFourthLineOf(ConvertedStr[i]);
        }
        printf("\n");

        printf("   ");
        for (unsigned int i = startIndex; i < indexOf_NewlineChar_InConvertedStr; i++)
        {
            if (ConvertedStr[i] == BACKSPACE_KEY_PRESSED)
            {
                continue;
            }
            PrintFifthLineOf(ConvertedStr[i]);
        }

        if (indexOf_NewlineChar_InConvertedStr == (maxIndexNumOf_ConvertedStr + 1)) // i use < , not <= in the for loops above, so I use the length of the string
        {
            break;
        }

        printf("\n\n\n");
        printf("   ");

        startIndex = indexOf_NewlineChar_InConvertedStr + 1; 
        indexOf_NewlineChar_InConvertedStr = ReturnIndexOf_NextNewlineChar_InConvertedStr(indexOf_NewlineChar_InConvertedStr, ConvertedStr);
    }
}