#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <time.h>
#include <windows.h>

#define WAITING_TIME 30.0 // seconds
#define MAX_SELECTABLE_ITEMS 4
#define USER_DESCRIPTION_FOR_ITEMS "Choose one of the things below."

#define INVALID_KEY_RETURN_VALUE 0
#define UP_ARROW_KEY_RETURN_VALUE 1
#define DOWN_ARROW_KEY_RETURN_VALUE 2
#define ENTER_KEY_RETURN_VALUE 3

// ASCII Codes
#define SPECIAL_KEY_PRESSED 0XE0
#define ENTER_KEY_PRESSED '\r'

#define UP_ARROW_KEY_PRESSED 72
#define DOWN_ARROW_KEY_PRESSED 80

char ITEMS_STRING[MAX_SELECTABLE_ITEMS] [101] = {"Emre", "Usul", "Blue", "Furkan"};

unsigned short int SelectionPosition = 0;
unsigned short int InterpretKbHit_ReturnValue;

void PrintSelectionScreen(time_t InitialTime);
int InterpretKbHit();
void UptadeSelectionScreen();
void PrintTheSelectedOneAndTerminate();

int main(void)
{
  time_t InitialTime = time(NULL);
  time_t a_secondCounterBeginning;
  time_t a_secondCounterFinish;

  while (1)
  {
    system("CLS");
    fflush(stdout);

    PrintSelectionScreen(InitialTime);

    if (difftime(time(NULL), InitialTime) >= WAITING_TIME)
    {
      break;
    }

    a_secondCounterBeginning = time(NULL);

    do
    {
      if (kbhit())
      {
        InterpretKbHit_ReturnValue = InterpretKbHit();

        if (InterpretKbHit_ReturnValue == ENTER_KEY_RETURN_VALUE)
        {
          goto FinishPoint_GOTO;
        }

        else if (InterpretKbHit_ReturnValue != INVALID_KEY_RETURN_VALUE)
        {
          UptadeSelectionScreen();
          continue;
        }
      }

      a_secondCounterFinish = time(NULL);

    } while (difftime(a_secondCounterBeginning, a_secondCounterFinish) >= 1.0); // until a second has passed
  }

FinishPoint_GOTO:

  PrintTheSelectedOneAndTerminate();
}

int InterpretKbHit()
{
  int charInput, arrowKey = 0;

  charInput = getch();

  if (charInput != SPECIAL_KEY_PRESSED)
  {
    if (charInput == ENTER_KEY_PRESSED)
    {
      return ENTER_KEY_RETURN_VALUE;
    }

    return INVALID_KEY_RETURN_VALUE;
  }

  arrowKey = getch();

  switch (arrowKey)
  {
  case UP_ARROW_KEY_PRESSED:
    return UP_ARROW_KEY_RETURN_VALUE;

  case DOWN_ARROW_KEY_PRESSED:
    return DOWN_ARROW_KEY_RETURN_VALUE;

  default:
    return INVALID_KEY_RETURN_VALUE;
  }
}

void UptadeSelectionScreen()
{
  if (InterpretKbHit_ReturnValue == UP_ARROW_KEY_RETURN_VALUE)
  {
    if (SelectionPosition > 0)
    {
      SelectionPosition--;
    }
  }
  else
  {
    if (SelectionPosition < MAX_SELECTABLE_ITEMS - 1)
    {
      SelectionPosition++;
    }
  }
}

void PrintSelectionScreen(time_t InitialTime)
{
  printf(" %s\n",USER_DESCRIPTION_FOR_ITEMS);
  puts(" ( Use arrow keys. )\n");

  fflush(stdout);

  for (unsigned short int i = 0; i < MAX_SELECTABLE_ITEMS; i++)
  {
    if (i == SelectionPosition)
    {
      printf("-> ");
    }
    else
    {
      printf("   ");
    }

    puts(ITEMS_STRING[i]);

    fflush(stdout);
  }
  printf("\n %0.lf\n", WAITING_TIME - difftime(time(NULL), InitialTime));

  fflush(stdout);
}

void PrintTheSelectedOneAndTerminate()
{
  system("CLS");
  printf("You chose \"%s\"\n", ITEMS_STRING[SelectionPosition]);
  fflush(stdout);
}