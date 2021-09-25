#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <windows.h>
#define MAXX 9
char SudokuTable[ MAXX ] [ 10 ] =
{
    {' ','3','1',' ','9',' ',' ',' ',' ','\0'},
    {' ',' ','4',' ','8','7',' ','1',' ','\0'},
    {' ',' ','9',' ','3',' ','4',' ',' ','\0'},
    {' ',' ',' ',' ',' ',' ','3',' ','2','\0'},
    {' ',' ','5','6','3',' ',' ',' ',' ','\0'},
    {' ',' ','3','5','1',' ','7',' ',' ','\0'},
    {' ',' ',' ','8',' ',' ',' ',' ','7','\0'},
    {' ','5',' ',' ',' ','6',' ',' ',' ','\0'},
    {'6',' ',' ',' ','7','1','2',' ',' ','\0'},
} ;
unsigned short int arrayNum, elementNum ;
unsigned short int LeastUsedNumbers [ MAXX ] ; // index 0 = first most used number, index 1 = second most used number ...


void AssignEveryCellToUnderscore() ;

void PrintSudokuTable( ) ;
void PrintFirstLine( unsigned short int *temp_ArrayNum ) ;
void PrintSecondLine( unsigned short int *temp_ArrayNum ) ;
void PrintThirdLine( unsigned short int *temp_ArrayNum ) ;

void GetEveryCellFromUser ( ) ;
int ControlInputValidity(char *decision) ;
void WaitAndClearOutput() ;

void ControlTableValidity ( ) ;
void ControlAll3x3BlocksValidity ( ) ;
int Single3x3BlockSearch( unsigned short int *willGetCheckedNum );	// arrayNum is needed, elementNum isn't.

void ControlAll1x9RowsValidity ( ) ;
void SelectValidValueForwillGetCheckedNum_Rows ( unsigned short int *willGetCheckedNum, unsigned short int *validValueCheckingCounter ) ;
void RoundUpTheNumbersToStandards_Rows( unsigned short int *temp_ElementNum, unsigned short int *temp_ArrayNum, unsigned short int *constant_TempArrayNum, unsigned short int *constant_TempElementNum) ;
int Single1x9RowSearch ( unsigned short int *willGetCheckedNum ) ;

void ControlAll9x1ColumnsValidity ( ) ;
void SelectValidValueForwillGetCheckedNum_Columns ( unsigned short int *willGetCheckedNum, unsigned short int *validValueCheckingCounter ) ;
void RoundUpTheNumbersToStandards_Columns( unsigned short int *temp_ElementNum, unsigned short int *temp_ArrayNum, unsigned short int *constant_TempArrayNum, unsigned short int *constant_TempElementNum ) ;
int Single9x1ColumnSearch ( unsigned short int *willGetCheckedNum ) ;


void FindLeastUsedNumbers( ) ;
void NoSolutionFound() ;
void FindOccurences( unsigned short int *howManyTimesUsed_EachNum ) ;
void CompareOccurencesAndGetLeastUsedNumbers( unsigned short int *howManyTimesUsed_EachNum ) ;
void SortEqualTimesUsedOccurences( unsigned short int *howManyTimesUsed_EachNum, unsigned short int *currentLeast_Times_Used, unsigned short int *currentLeastUsed_Num, unsigned short int *sortingArray_ElementNum ) ;

void FillMissingCells( ) ;

void FillTheCellwithTheRightNumber ( unsigned short int *willGetCheckedNum) ;
int CheckOtherPossibilities ( unsigned short int *willGetCheckedNum ) ;
int HorizontalSearch( unsigned short int *willGetCheckedNum, unsigned short int *before_ElementNum, unsigned short int *before_ArrayNum ) ;
int VerticalSearch ( unsigned short int *willGetCheckedNum, unsigned short int *before_ElementNum, unsigned short int *before_ArrayNum ) ;

void GoToNextCell ( unsigned short int *sortingArray_ElementNum, unsigned short int *willGetCheckedNum ) ;
void Change_willGetCheckedNum ( unsigned short int *sortingArray_ElementNum, unsigned short int *willGetCheckedNum ) ;
int LookIfThereIsAnyEmptyCell( ) ;

void PrintSolvedSudokuTable( ) ;

int main( void )
{
    printf("\nWelcome to the Sudoku Solver Program.\n\n\n");

    //AssignEveryCellToUnderscore( &arrayNum );

    //GetEveryCellFromUser( &arrayNum, &elementNum );

    ControlTableValidity( ) ;

    FindLeastUsedNumbers ( ) ;

    FillMissingCells ( ) ;

    PrintSolvedSudokuTable( ) ;
}

void AssignEveryCellToUnderscore()
{
    for( arrayNum = 0 ; arrayNum != MAXX ; arrayNum ++)
    {
        strcpy ( SudokuTable [ arrayNum ], "---------" ) ;
    }
}

void PrintSudokuTable()
{
    unsigned short int temp_ArrayNum;
    for( temp_ArrayNum = 0 ; temp_ArrayNum <= 6 ; temp_ArrayNum +=3 )
    {
        PrintFirstLine( &temp_ArrayNum );

        PrintSecondLine( &temp_ArrayNum );

        PrintThirdLine( &temp_ArrayNum );

        printf("\n");
    }
}

void PrintFirstLine( unsigned short int *temp_ArrayNum )
{
    printf(" %c %c %c   ", SudokuTable[ (*temp_ArrayNum) ] [ 0 ], SudokuTable[ (*temp_ArrayNum) ] [ 1 ], SudokuTable[ (*temp_ArrayNum) ] [ 2 ] );
    printf(" %c %c %c   ", SudokuTable[ (*temp_ArrayNum) + 1 ] [ 0 ], SudokuTable[ (*temp_ArrayNum) + 1 ] [ 1 ], SudokuTable[ (*temp_ArrayNum) +1 ] [ 2 ] );
    printf(" %c %c %c   \n", SudokuTable[ (*temp_ArrayNum) + 2 ] [ 0 ], SudokuTable[ (*temp_ArrayNum) +2 ] [ 1 ], SudokuTable[ (*temp_ArrayNum) + 2 ] [ 2 ] );
}

void PrintSecondLine( unsigned short int *temp_ArrayNum )
{
    printf(" %c %c %c   ", SudokuTable[ (*temp_ArrayNum) ] [ 3 ], SudokuTable[ (*temp_ArrayNum) ] [ 4 ], SudokuTable[ (*temp_ArrayNum) ] [ 5 ] );
    printf(" %c %c %c   ", SudokuTable[ (*temp_ArrayNum) + 1 ] [ 3 ], SudokuTable[ (*temp_ArrayNum) + 1 ] [ 4 ], SudokuTable[ (*temp_ArrayNum) +1 ] [ 5 ] );
    printf(" %c %c %c   \n", SudokuTable[ (*temp_ArrayNum) + 2 ] [ 3 ], SudokuTable[ (*temp_ArrayNum) +2 ] [ 4 ], SudokuTable[ (*temp_ArrayNum) + 2 ] [ 5 ] );
}

void PrintThirdLine( unsigned short int *temp_ArrayNum )
{
    printf(" %c %c %c   ", SudokuTable[ (*temp_ArrayNum) ] [ 6 ], SudokuTable[ (*temp_ArrayNum) ] [ 7 ], SudokuTable[ (*temp_ArrayNum) ] [ 8 ] );
    printf(" %c %c %c   ", SudokuTable[ (*temp_ArrayNum) + 1 ] [ 6 ], SudokuTable[ (*temp_ArrayNum) + 1 ] [ 7 ], SudokuTable[ (*temp_ArrayNum) +1 ] [ 8 ] );
    printf(" %c %c %c   \n", SudokuTable[ (*temp_ArrayNum) + 2 ] [ 6 ], SudokuTable[ (*temp_ArrayNum) +2 ] [ 7 ], SudokuTable[ (*temp_ArrayNum) + 2 ] [ 8 ] );
}

void GetEveryCellFromUser ()
{
    char decision;
    arrayNum = 0, elementNum = 0 ;

    while( arrayNum != MAXX )
    {
        SudokuTable [ arrayNum ] [ elementNum ] = 'X' ;

        while(1)
        {
            PrintSudokuTable( ) ;

            printf("\nPlease type the number where the X letter stands ( type a space if the cell is empty ) : ");
            decision = getchar() ;
            fflush(stdin);

            if( ControlInputValidity ( &decision ) == 1 )
            {
                system("CLS");
                break;
            }
            else
            {
                printf("\n**Please only type values between 1 and 9, or a space!\n\n");
                WaitAndClearOutput();
            }
        }

        SudokuTable [ arrayNum ] [ elementNum ] = decision ;

        elementNum ++ ;

        if( elementNum  == MAXX)
        {
            elementNum  = 0 ;
            arrayNum  ++ ;
        }
    }
}

int ControlInputValidity(char *decision)
{
    if(  ( ( (*decision) >='1' )  && ( (*decision) <='9' ) )  ||  ( (*decision) == ' ')  )
        return 1;

    else
        return 0;
}

void WaitAndClearOutput()
{
    Sleep(2500);
    system("CLS");
}

void ControlTableValidity ( )
{
    ControlAll3x3BlocksValidity( );
    ControlAll1x9RowsValidity( );
    ControlAll9x1ColumnsValidity( );
}

void ControlAll3x3BlocksValidity ( )
{
    unsigned short int willGetCheckedNum ;

    arrayNum = 0, elementNum = 0;

    while( arrayNum < MAXX )
    {
        if( SudokuTable [ arrayNum ] [ elementNum ] != ' ')
        {
            willGetCheckedNum = SudokuTable [ arrayNum ] [ elementNum ] - '0' ;

            if ( Single3x3BlockSearch( &willGetCheckedNum ) == -1 )
            {
                NoSolutionFound();
            }
        }

        elementNum ++ ;
        if( elementNum == MAXX )
        {
            arrayNum ++;
            elementNum = 0 ;
        }
    }
}

int Single3x3BlockSearch( unsigned short int *willGetCheckedNum )
{
    unsigned short int sameNumOccurenceCounter = 0, temp_ElementNum ;

    for( temp_ElementNum = 0 ; temp_ElementNum != MAXX ; temp_ElementNum ++ )
    {
        if( SudokuTable [ arrayNum ] [ temp_ElementNum ] == ( (*willGetCheckedNum) + '0' ) )
        {
            sameNumOccurenceCounter ++ ;
        }
    }
    if( sameNumOccurenceCounter == 1 )
    {
        return 1;
    }
    else if ( sameNumOccurenceCounter == 0 )
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void ControlAll1x9RowsValidity( )
{
    unsigned short int willGetCheckedNum, validValueCheckingCounter ;

    arrayNum = 0, elementNum = 0;

    while( 1 )
    {
        // printf("[%hu][%hu]\n", *arrayNum, *elementNum);  use this if you want to find out what the '-3' thing below does

        validValueCheckingCounter = 0;
        do
        {
            SelectValidValueForwillGetCheckedNum_Rows( &willGetCheckedNum, &validValueCheckingCounter ) ;

            if  ( validValueCheckingCounter != 10)
            {
                if ( Single1x9RowSearch( &willGetCheckedNum ) == -1 )
                {
                    NoSolutionFound();
                }
            }
        }
        while( validValueCheckingCounter != 10) ;


        elementNum += 3 ;
        if( ( ( elementNum - 3 ) == 6 ) && ( arrayNum == 6 ) )		// some unsigned type problems
        {
            break;
        }

        else if( ( elementNum - 3 ) == 6 )
        {
            arrayNum += 3;
            elementNum = 0;
        }
    }
}

void SelectValidValueForwillGetCheckedNum_Rows ( unsigned short int *willGetCheckedNum, unsigned short int *validValueCheckingCounter  )	// don't laugh, I really need this 70 lines of code to decrease the compilation time
{
    (*validValueCheckingCounter) ++ ;

    switch( (*validValueCheckingCounter) )
    {
    case 1:
        if( SudokuTable [ arrayNum ] [ elementNum ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum ] [ elementNum ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 2 ;
        }

    case 2:
        if( SudokuTable [ arrayNum ] [ elementNum + 1 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum ] [ elementNum + 3 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 3 ;
        }

    case 3:
        if( SudokuTable [ arrayNum ] [ elementNum + 2 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum ] [ elementNum + 6] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 4 ;
        }

    case 4:
        if( SudokuTable [ arrayNum + 1 ] [ elementNum ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 3 ] [ elementNum ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 5 ;
        }

    case 5:
        if( SudokuTable [ arrayNum + 1 ] [ elementNum + 1 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 3 ] [ elementNum + 3 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 6 ;
        }

    case 6:
        if( SudokuTable [ arrayNum + 1 ] [ elementNum + 2 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 3 ] [ elementNum + 6 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 7 ;
        }

    case 7:
        if( SudokuTable [ arrayNum + 2 ] [ elementNum ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 6 ] [ elementNum ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 8 ;
        }
    case 8:
        if( SudokuTable [ arrayNum + 2 ] [ elementNum + 1 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 6 ] [ elementNum + 3 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 9 ;
        }

    case 9:
        if( SudokuTable [ arrayNum + 2 ] [ elementNum + 2 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 6 ] [ elementNum + 6 ] - '0'  ;
        }
        else
        {
            (*validValueCheckingCounter) = 10 ;
        }
        break;
    }
}

void RoundUpTheNumbersToStandards_Rows( unsigned short int *temp_ElementNum, unsigned short int *temp_ArrayNum, unsigned short int *constant_TempArrayNum, unsigned short int *constant_TempElementNum)
{
    (*temp_ArrayNum) = arrayNum 	, 	(*temp_ElementNum) = elementNum ;
    ( *constant_TempArrayNum ) = arrayNum 	, 	(*constant_TempElementNum) = elementNum ;

    if( ( (*temp_ElementNum) >= 0 ) && ( (*temp_ElementNum) <= 2 ) )
    {
        (*temp_ElementNum) = 0 ;
        (*constant_TempElementNum) = 0;
    }
    else if( ( (*temp_ElementNum) >= 3 ) && ( (*temp_ElementNum) <= 5 ) )
    {
        (*temp_ElementNum) = 3 ;
        (*constant_TempElementNum) = 3;
    }

    else if( ( (*temp_ElementNum) >= 6 ) && ( (*temp_ElementNum) <= 8 ) )
    {
        (*temp_ElementNum) = 6 ;
        (*constant_TempElementNum) = 6;
    }

    switch( (*constant_TempArrayNum) )
    {
    case 1:
    case 2:
        (*temp_ArrayNum) = 0 ;
        (*constant_TempArrayNum) = 0 ;
        break;
    case 4:
    case 5:
        (*temp_ArrayNum) = 3 ;
        (*constant_TempArrayNum) = 3 ;
        break;
    case 7:
    case 8:
        (*temp_ArrayNum) = 6 ;
        (*constant_TempArrayNum) = 6 ;
        break;
    }
}

int Single1x9RowSearch( unsigned short int *willGetCheckedNum )   // I can't add 1 to elementNum, and use it in a for loop. Because I mustn't change its value.
{
    unsigned short int temp_ElementNum, temp_ArrayNum, constant_TempArrayNum, constant_TempElementNum, sameNumOccurenceCounter;
    sameNumOccurenceCounter = 0;

    RoundUpTheNumbersToStandards_Rows( &temp_ElementNum, &temp_ArrayNum, &constant_TempArrayNum, &constant_TempElementNum ) ;

    for( ; temp_ArrayNum <= ( constant_TempArrayNum + 2 ) ; temp_ArrayNum ++)
    {

        for ( temp_ElementNum = constant_TempElementNum ; temp_ElementNum <= ( constant_TempElementNum + 2 ) ; temp_ElementNum ++ )
        {
            if( SudokuTable [ temp_ArrayNum ] [ temp_ElementNum ] 		==		 ( (*willGetCheckedNum) + '0' ) )
                sameNumOccurenceCounter ++ ;
        }
    }

    if( sameNumOccurenceCounter == 1)
    {
        return 1;
    }
    else if ( sameNumOccurenceCounter == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void ControlAll9x1ColumnsValidity ( )
{
    unsigned short int willGetCheckedNum, validValueCheckingCounter ;

    arrayNum = 0, elementNum = 0;

    while( 1 )
    {
        validValueCheckingCounter = 0 ;
        do
        {
            SelectValidValueForwillGetCheckedNum_Columns( &willGetCheckedNum, &validValueCheckingCounter );

            if ( validValueCheckingCounter != 10)
            {
                if ( Single9x1ColumnSearch( &willGetCheckedNum ) == -1 )
                {
                    NoSolutionFound();
                }
            }
        }
        while ( validValueCheckingCounter != 10 );


        elementNum ++  ;	// same goes for this little one

        if ( ( ( elementNum - 1 ) == 2 ) && ( arrayNum == 2 ) )
        {
            break;
        }

        else if( ( elementNum - 1) == 2)
        {
            arrayNum ++ ;
            elementNum = 0;
        }
    }
}

void SelectValidValueForwillGetCheckedNum_Columns ( unsigned short int *willGetCheckedNum, unsigned short int *validValueCheckingCounter )
{
    (*validValueCheckingCounter) ++ ;

    switch( (*validValueCheckingCounter) )
    {
    case 1:
        if( SudokuTable [ arrayNum ] [ elementNum ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum ] [ elementNum ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 2 ;
        }

    case 2:
        if( SudokuTable [ arrayNum ] [ elementNum + 3 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum ] [ elementNum + 3 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 3 ;
        }

    case 3:
        if( SudokuTable [ arrayNum ] [ elementNum + 6 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum ] [ elementNum + 6] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 4 ;
        }

    case 4:
        if( SudokuTable [ arrayNum + 3 ] [elementNum] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 3 ] [ elementNum ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 5 ;
        }

    case 5:
        if( SudokuTable [ arrayNum + 3 ] [ elementNum + 3 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 3 ] [ elementNum + 3 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 6 ;
        }

    case 6:
        if( SudokuTable [ arrayNum + 3 ] [ elementNum + 6 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 3 ] [ elementNum + 6 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 7 ;
        }

    case 7:
        if( SudokuTable [ arrayNum + 6 ] [elementNum] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 6 ] [ elementNum ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 8 ;
        }
    case 8:
        if( SudokuTable [ arrayNum + 6 ] [ elementNum + 3 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 6 ] [ elementNum + 3 ] - '0'  ;
            break;
        }
        else
        {
            (*validValueCheckingCounter) = 9 ;
        }

    case 9:
        if( SudokuTable [ arrayNum + 6 ] [ elementNum + 6 ] != ' ')
        {
            (*willGetCheckedNum) = SudokuTable [ arrayNum + 6 ] [ elementNum + 6 ] - '0'  ;
        }
        else
        {
            (*validValueCheckingCounter) = 10 ;
        }
        break;
    }

}

void RoundUpTheNumbersToStandards_Columns( unsigned short int *temp_ElementNum, unsigned short int *temp_ArrayNum, unsigned short int *constant_TempArrayNum, unsigned short int *constant_TempElementNum)
{
    (*temp_ArrayNum) = arrayNum, (*temp_ElementNum) = elementNum ;
    ( *constant_TempArrayNum ) = arrayNum, (*constant_TempElementNum) = elementNum ;

    if( ( (*temp_ElementNum) == 3 ) || ( (*temp_ElementNum) == 6 ) )
    {
        (*temp_ElementNum) = 0 ;
        (*constant_TempElementNum) = 0;
    }
    else if( ( (*temp_ElementNum) == 4 ) || ( (*temp_ElementNum) == 7 ) )
    {
        (*temp_ElementNum) = 1 ;
        (*constant_TempElementNum) = 1;
    }

    else if( ( (*temp_ElementNum) == 5 ) || ( (*temp_ElementNum) == 8 ) )
    {
        (*temp_ElementNum) = 2 ;
        (*constant_TempElementNum) = 2;
    }

    switch( (*constant_TempArrayNum) )
    {
    case 3:
    case 6:
        (*temp_ArrayNum) = 0 ;
        (*constant_TempArrayNum) = 0 ;
        break;
    case 4:
    case 7:
        (*temp_ArrayNum) = 1 ;
        (*constant_TempArrayNum) = 1 ;
        break;
    case 5:
    case 8:
        (*temp_ArrayNum) = 2 ;
        (*constant_TempArrayNum) = 2 ;
        break;
    }
}

int Single9x1ColumnSearch ( unsigned short int *willGetCheckedNum )
{
    unsigned short int temp_ElementNum, temp_ArrayNum, constant_TempArrayNum, constant_TempElementNum, sameNumOccurenceCounter;
    sameNumOccurenceCounter = 0;

    RoundUpTheNumbersToStandards_Columns( &temp_ElementNum, &temp_ArrayNum, &constant_TempArrayNum, &constant_TempElementNum ) ;

    while( temp_ArrayNum <= ( constant_TempArrayNum + 6 ) )
    {
        for( temp_ElementNum = constant_TempElementNum  ; temp_ElementNum <= ( constant_TempElementNum + 6 ) ; temp_ElementNum += 3 )
        {

            if( SudokuTable [ temp_ArrayNum ] [ temp_ElementNum ] 		==		 ( (*willGetCheckedNum) + '0' ) )
                sameNumOccurenceCounter ++ ;
        }

        temp_ArrayNum += 3 ;
    }


    if ( sameNumOccurenceCounter == 1)
    {
        return 1;
    }
    else if ( sameNumOccurenceCounter == 0 )
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void FindLeastUsedNumbers( )
{
    unsigned short int howManyTimesUsed_EachNum [ MAXX ] = { 0 } ;

    FindOccurences( howManyTimesUsed_EachNum ) ;
    CompareOccurencesAndGetLeastUsedNumbers ( howManyTimesUsed_EachNum ) ;
}

void FindOccurences( unsigned short int *howManyTimesUsed_EachNum )
{
    unsigned short int currentNum;

    for ( arrayNum = 0 ; arrayNum != MAXX ; arrayNum ++ )
    {
        for( elementNum = 0 ; elementNum != MAXX ; elementNum ++ )
        {
            if ( SudokuTable [ arrayNum ] [ elementNum ] != ' ' )
            {
                currentNum = ( SudokuTable [ arrayNum ] [ elementNum ] - '0' ) ;

                howManyTimesUsed_EachNum [ currentNum - 1 ] ++ ;

                if( howManyTimesUsed_EachNum [ currentNum - 1 ] == MAXX )
                {
                    NoSolutionFound( ) ;
                }
            }
        }
    }

    for( elementNum = 0 ; elementNum != MAXX ; elementNum ++ )
    {
        if( howManyTimesUsed_EachNum [ currentNum - 1 ] == 0 )
        {
            NoSolutionFound( ) ;
        }
    }
}

void NoSolutionFound()
{
    printf("\n\n*** No solutions were found. Please make sure you typed every cell correctly. ***\n\n");
    exit(0);
}

void CompareOccurencesAndGetLeastUsedNumbers( unsigned short int *howManyTimesUsed_EachNum )
{
    unsigned short int currentLeastUsed_Num, currentLeast_Times_Used, sortingArray_ElementNum ;
    sortingArray_ElementNum = 0 ;

    do
    {
        currentLeastUsed_Num = 1 ;
        currentLeast_Times_Used = howManyTimesUsed_EachNum [ 0 ] ;

        for ( elementNum = 1 ; elementNum != MAXX ; elementNum ++ )
        {
            if ( howManyTimesUsed_EachNum[ elementNum ] < currentLeast_Times_Used )
            {
                currentLeast_Times_Used = howManyTimesUsed_EachNum[ elementNum ] ;
                currentLeastUsed_Num = ( elementNum + 1 ) ;
            }
        }

        LeastUsedNumbers [ sortingArray_ElementNum ] = currentLeastUsed_Num ;
        sortingArray_ElementNum ++ ;

        if( sortingArray_ElementNum < MAXX )
        {
            SortEqualTimesUsedOccurences( howManyTimesUsed_EachNum, &currentLeast_Times_Used, &currentLeastUsed_Num, &sortingArray_ElementNum ) ;

            howManyTimesUsed_EachNum [ currentLeastUsed_Num - 1 ] = 10 ;	// why is it 10?  Because it has to be larger than any valid occurence ( from 0 to 9 )
        }

    }
    while ( sortingArray_ElementNum < 9 );
}

void SortEqualTimesUsedOccurences( unsigned short int *howManyTimesUsed_EachNum, unsigned short int *currentLeast_Times_Used, unsigned short int *currentLeastUsed_Num, unsigned short int *sortingArray_ElementNum )
{
    for ( elementNum = 0 ; elementNum != MAXX ; elementNum ++ )
    {
        if ( elementNum != ( (*currentLeastUsed_Num) - 1 ) )
        {
            if ( howManyTimesUsed_EachNum[ elementNum ] == (*currentLeast_Times_Used) )
            {
                // currentLeast_Times_Used and currentLeastUsed_Num is still the same, don't touch them

                if( (*sortingArray_ElementNum) < MAXX )
                {
                    LeastUsedNumbers [ (*sortingArray_ElementNum) ] = ( elementNum + 1 ) ;
                    howManyTimesUsed_EachNum[ elementNum ] = 10 ;

                    (*sortingArray_ElementNum) ++ ;
                }
            }
        }
    }
    howManyTimesUsed_EachNum [ (*currentLeastUsed_Num) - 1 ] = 0 ;
}

void FillMissingCells( )
{
    unsigned short int willGetCheckedNum, sortingArray_ElementNum ;

    sortingArray_ElementNum = 0 ;
    willGetCheckedNum = LeastUsedNumbers [ sortingArray_ElementNum ] ;
    arrayNum = 0, elementNum = 0 ;

    while( LookIfThereIsAnyEmptyCell( ) == 1 )
    {

        FillTheCellwithTheRightNumber( &willGetCheckedNum ) ;

        GoToNextCell ( &sortingArray_ElementNum, &willGetCheckedNum ) ;

    }

}

void FillTheCellwithTheRightNumber ( unsigned short int *willGetCheckedNum)
{
    if( SudokuTable [ arrayNum ] [ elementNum ] == ' ' )
    {
        if ( Single3x3BlockSearch( willGetCheckedNum ) == 0 )
        {
            if( Single1x9RowSearch( willGetCheckedNum ) == 0 )
            {
                if( Single9x1ColumnSearch( willGetCheckedNum ) == 0 )
                {
                    if( CheckOtherPossibilities( willGetCheckedNum ) == 0 )
                    {
						PrintSudokuTable();
                        SudokuTable [ arrayNum ] [ elementNum ] = ( (*willGetCheckedNum) + '0' ) ;
                    }
                }
            }
        }
    }
}

int CheckOtherPossibilities ( unsigned short int *willGetCheckedNum )
{
    unsigned short int before_ElementNum = elementNum, before_ArrayNum = arrayNum ;

    // we re in the top in front of the line

    if( ( HorizontalSearch ( willGetCheckedNum, &before_ElementNum, &before_ArrayNum ) == 1 )  ||  ( VerticalSearch ( willGetCheckedNum, &before_ElementNum, &before_ArrayNum ) == 1) )
    {
        arrayNum = before_ArrayNum ;
        elementNum = before_ElementNum ;
        return 1 ;
    }

    arrayNum = before_ArrayNum ;
    elementNum = before_ElementNum ;

    return 0 ;
}

int HorizontalSearch( unsigned short int *willGetCheckedNum, unsigned short int *before_ElementNum, unsigned short int *before_ArrayNum )	// --- --- ---
{
    unsigned short int temp_ElementNum, temp_ArrayNum, constant_TempArrayNum, constant_TempElementNum ;

    RoundUpTheNumbersToStandards_Rows( &temp_ElementNum, &temp_ArrayNum, &constant_TempArrayNum, &constant_TempElementNum ) ;
    arrayNum = constant_TempArrayNum ;
    elementNum = constant_TempElementNum ;

    while( 1 )
    {
        if( ( SudokuTable [ arrayNum ] [ elementNum ] == ' ' ) && ( arrayNum != (*before_ArrayNum) ) && ( elementNum != (*before_ElementNum) ) )
        {
            if ( Single3x3BlockSearch( willGetCheckedNum ) == 0 )
            {
                if( Single9x1ColumnSearch( willGetCheckedNum ) == 0 )
                {
                    if( Single1x9RowSearch ( willGetCheckedNum ) == 0 )
                    {
                        return 1;
                    }
                }
            }
        }

        if( ( arrayNum == (constant_TempArrayNum + 2) ) && ( elementNum ==  (constant_TempElementNum + 2)) )
        {
            break ;
        }

        elementNum ++ ;

        if ( elementNum > ( constant_TempElementNum + 2) )
        {
            elementNum = constant_TempElementNum ;
            arrayNum ++ ;
        }
    }

    return 0 ;
}

int VerticalSearch ( unsigned short int *willGetCheckedNum, unsigned short int *before_ElementNum, unsigned short int *before_ArrayNum ) // ||| ||| |||
{
    unsigned short int temp_ElementNum, temp_ArrayNum, constant_TempArrayNum, constant_TempElementNum ;

    RoundUpTheNumbersToStandards_Columns( &temp_ElementNum, &temp_ArrayNum, &constant_TempArrayNum, &constant_TempElementNum ) ;
    arrayNum = constant_TempArrayNum ;
    elementNum = constant_TempElementNum ;

    while( 1 )
    {
        if( ( SudokuTable [ arrayNum ] [ elementNum ] == ' ' ) && ( arrayNum != (*before_ArrayNum) ) && ( elementNum != (*before_ElementNum) ) )
        {
            if ( Single3x3BlockSearch( willGetCheckedNum ) == 0 )
            {
                if( Single9x1ColumnSearch( willGetCheckedNum ) == 0 )
                {
                    if( Single1x9RowSearch ( willGetCheckedNum ) == 0 )
                    {
                        return 1;
                    }
                }
            }
        }

        if( ( arrayNum == (constant_TempArrayNum + 6) ) && ( elementNum ==  (constant_TempElementNum + 6) ) )
        {
            break ;
        }

        elementNum += 3 ;

        if ( elementNum > ( constant_TempElementNum + 6 ) )
        {
            elementNum = constant_TempElementNum ;
            arrayNum += 3 ;
        }
    }

    return 0 ;
}

void GoToNextCell ( unsigned short int *sortingArray_ElementNum, unsigned short int *willGetCheckedNum )
{
    elementNum ++ ;

    if( elementNum == MAXX )
    {
        elementNum = 0 ;
        arrayNum ++ ;

        if( arrayNum == MAXX )
        {
            arrayNum = 0 ;

            Change_willGetCheckedNum ( sortingArray_ElementNum, willGetCheckedNum) ;

        }
    }
}

void Change_willGetCheckedNum ( unsigned short int *sortingArray_ElementNum, unsigned short int *willGetCheckedNum )
{
    (*sortingArray_ElementNum) ++ ;

    if( (*sortingArray_ElementNum) == MAXX )
    {
        (*sortingArray_ElementNum) = 0 ;
    }

    (*willGetCheckedNum) = LeastUsedNumbers [ (*sortingArray_ElementNum) ] ;
}

int LookIfThereIsAnyEmptyCell()
{
    unsigned short int temp_ArrayNum ;

    for( temp_ArrayNum = 0 ; temp_ArrayNum != MAXX ; temp_ArrayNum ++ )
    {
        if( strchr( SudokuTable [ temp_ArrayNum ], ' ') != NULL)
        {
            return 1 ;
        }
    }
    return 0 ;
}

void PrintSolvedSudokuTable( )
{
    system("CLS") ;
    printf("\n*************************\n\n") ;
    PrintSudokuTable() ;
    printf("*************************\n") ;
}
