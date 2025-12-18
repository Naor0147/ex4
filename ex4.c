/******************
Name:Naor Biton
ID:329218416
Assignment:ex4
*******************/

#include <stdio.h>
#include <string.h>

/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6

/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3




/******************************
******* CUSTOM DEFINE*********
*******************************/

#define SUDOKU_MAX_NUMBER 9


/***************************
 * USER INTEFACE PROTOTYPES *
 ****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();

/****************************
 * IMPLEMENTATION PROTOTYPES *
 *****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM + 1], int, char[][LONGEST_TERM + 1], int,
                                          char[][LONGEST_TERM + 1], int);
int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);

/******************************
 * HELPER FUNCTIONS PROTOTYPES *
 *******************************/

int readTerms(char[][LONGEST_TERM + 1], int, char[]);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);

/******************************
*********** CUSTOM ************
*******************************/
int task2HelpCheck(int length, int index);
void clearBuffer();

// task3 helpers
void task3GenerateSentencesHelperSubject(char subjects[][LONGEST_TERM + 1], int subjectsCount, int subjectIndex,
                                         char verbs[][LONGEST_TERM + 1], int verbsCount, int vebvIndex,
                                         char objects[][LONGEST_TERM + 1], int objectsCount, int objectIndex);

void task3GenerateSentencesHelperVerb(char subjects[][LONGEST_TERM + 1], int subjectsCount, int subjectIndex,
                                      char verbs[][LONGEST_TERM + 1], int verbsCount, int vebvIndex,
                                      char objects[][LONGEST_TERM + 1], int objectsCount, int objectIndex);

void task3GenerateSentencesHelperObject(char subjects[][LONGEST_TERM + 1], int subjectsCount, int subjectIndex,
                                        char verbs[][LONGEST_TERM + 1], int verbsCount, int vebvIndex,
                                        char objects[][LONGEST_TERM + 1], int objectsCount, int objectIndex);

// task 4 helpers

int task4SolveZipBoardHelper(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                             char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                             int size, int currentTurn, int target, int posR, int posC, int highest);
/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}

/***************************
****** USER INTERFACE ******
****************************/

void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}

void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    // scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}

void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM + 1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM + 1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM + 1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount = readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount = readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount = readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}

void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest = 0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if (board[i][j] > highest)
            {
                highest = board[i][j];
            }
        }
    }
    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}

void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board))
    {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }
}

/***************************
********* HELPERS **********
****************************/

int readTerms(char terms[][LONGEST_TERM + 1], int maxNumOfTerms, char type[])
{
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if (termsCount < 1 || termsCount > maxNumOfTerms)
    {
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for (int i = 0; i < termsCount; i++)
    {
        printf("%d. ", i + 1);
        scanf(" %[^\n]", terms[i]);
    }
    return termsCount;
}

void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+-------+\n");
    }
}

/***************************
*********** TODO ***********
****************************/

void task1ReversePhraseImplementation()
{
    char s = getchar(); // saves one char at a time
    if (s != '\n')      // if player press enter the task 1 stops
    {
        task1ReversePhraseImplementation();
    }
    printf("%c", s); // print the char
}

int task2CheckPalindromeImplementation(int length)
{
    clearBuffer(); // clear the buffer
    return task2HelpCheck(length, 1);
}

int task2HelpCheck(int length, int index)
{
    int remainder = length % 2; // checks if the number is even

    char s = getchar(); // get char

    /* the recuisve call get called only if the index
    doesnt crrose the middle*/
    if (index < ((length / 2) + remainder))
    {
        // if even of the recuisve call equal zero the program will return zero
        if (task2HelpCheck(length, index + 1) == 0)
        {
            return 0;
        }
    }

    // if the number odd
    if (remainder == 1 && index == ((length / 2) + 1))
    {
        return 1;
    }

    char g = getchar();

    return g == s;
}

void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM + 1], int subjectsCount,
                                          char verbs[][LONGEST_TERM + 1], int verbsCount,
                                          char objects[][LONGEST_TERM + 1], int objectsCount)
{
    task3GenerateSentencesHelperSubject(subjects, subjectsCount, 0,
                                        verbs, verbsCount, 0,
                                        objects, objectsCount, 0);
}

// recursive function for subjects acts as the main loop
void task3GenerateSentencesHelperSubject(char subjects[][LONGEST_TERM + 1], int subjectsCount, int subjectIndex,
                                         char verbs[][LONGEST_TERM + 1], int verbsCount, int vebvIndex,
                                         char objects[][LONGEST_TERM + 1], int objectsCount, int objectIndex)
{
    if (subjectIndex >= subjectsCount || vebvIndex >= verbsCount || objectIndex >= objectsCount)
    {
        return;
    }
    int numberOfSentence = 1 + ((subjectIndex) * (verbsCount) * (objectsCount));

    task3GenerateSentencesHelperVerb(subjects, subjectsCount, subjectIndex,
                                     verbs, verbsCount, 0,
                                     objects, objectsCount, 0);
    task3GenerateSentencesHelperSubject(subjects, subjectsCount, subjectIndex + 1,
                                        verbs, verbsCount, 0,
                                        objects, objectsCount, 0);
}

// recursive function for verbs acts as the second loop
void task3GenerateSentencesHelperVerb(char subjects[][LONGEST_TERM + 1], int subjectsCount, int subjectIndex,
                                      char verbs[][LONGEST_TERM + 1], int verbsCount, int vebvIndex,
                                      char objects[][LONGEST_TERM + 1], int objectsCount, int objectIndex)
{
    if (subjectIndex >= subjectsCount || vebvIndex >= verbsCount || objectIndex >= objectsCount)
    {
        return;
    }

    // print the number of the setntence

    int numberOfSentence = ((subjectIndex) * (verbsCount) * (objectsCount)) + vebvIndex * objectsCount + 1;
    printf("%d. %s %s %s \n", numberOfSentence, subjects[subjectIndex], verbs[vebvIndex], objects[objectIndex]);

    task3GenerateSentencesHelperObject(subjects, subjectsCount, subjectIndex,
                                       verbs, verbsCount, vebvIndex,
                                       objects, objectsCount, objectIndex + 1);
    task3GenerateSentencesHelperVerb(subjects, subjectsCount, subjectIndex,
                                     verbs, verbsCount, vebvIndex + 1,
                                     objects, objectsCount, 0);
}

// recursive function for objects acts as the last loop
void task3GenerateSentencesHelperObject(char subjects[][LONGEST_TERM + 1], int subjectsCount, int subjectIndex,
                                        char verbs[][LONGEST_TERM + 1], int verbsCount, int vebvIndex,
                                        char objects[][LONGEST_TERM + 1], int objectsCount, int objectIndex)
{
    if (subjectIndex >= subjectsCount || vebvIndex >= verbsCount || objectIndex >= objectsCount)
    {
        return;
    }

    // print the number of the setntence
    int numberOfSentence = ((subjectIndex) * (verbsCount) * (objectsCount)) + vebvIndex * objectsCount + objectIndex + 1;
    printf("%d. %s %s %s \n", numberOfSentence, subjects[subjectIndex], verbs[vebvIndex], objects[objectIndex]);

    task3GenerateSentencesHelperObject(subjects, subjectsCount, subjectIndex,
                                       verbs, verbsCount, vebvIndex,
                                       objects, objectsCount, objectIndex + 1);
}

int task4SolveZipBoardImplementation(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     int size, int startR, int startC, int highest)
{
    /*in adddtion to the stats i get from the main fuction i send the turn ,
     and the number of the next target 2
    */
    return task4SolveZipBoardHelper(board, solution, size, 1, 2, startR, startC, highest);
}

int task4SolveZipBoardHelper(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                             char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                             int size, int currentTurn, int target, int posR, int posC, int highest)
{
    // check boand
    if (posR >= size || posC >= size || posC < 0 || posR < 0)
    {
        return 0;
    }
    // check if there was check here
    if (solution[posR][posC] != 0)
    {
        return 0;
    }
    int currentSquareValue = board[posR][posC]; // the square we are at for easiser use

    // check if the current square value is higher than the target
    if (currentSquareValue > target)
    {
        return 0;
    }
    // if it is equal increase the target
    if (currentSquareValue == target)
    {
        target++;
    }

    // check if this is the last turn
    if (currentTurn == (size * size))
    {
        // check if we reached the highest value and the target is highest +1
        if (currentSquareValue == highest && (target - 1) == highest)
        {
            return 1; // we found a solution
        }
        return 0; // not a solution
    }

    // keep the og value to backtrack later
    char ogValue = solution[posR][posC];

    // go up
    solution[posR][posC] = 'U';
    int tempValue = task4SolveZipBoardHelper(
        board,
        solution,
        size, currentTurn + 1, target, posR - 1, posC, highest);
    if (tempValue)
    {
        return 1; // we found a solution
    }
    else
    {
        // backtrack
        solution[posR][posC] = ogValue;
    }

    // go down
    solution[posR][posC] = 'D';
    tempValue = task4SolveZipBoardHelper(
        board,
        solution,
        size, currentTurn + 1, target, posR + 1, posC, highest);
    if (tempValue)
    {
        return 1;// we found a solution
    }
    else
    {
        // backtrack
        solution[posR][posC] = ogValue;
    }

    // go left
    solution[posR][posC] = 'L';
    tempValue = task4SolveZipBoardHelper(
        board,
        solution,
        size, currentTurn + 1, target, posR, posC - 1, highest);
    if (tempValue)
    {
        return 1;// we found a solution
    }
    else
    {
        // backtrack
        solution[posR][posC] = ogValue;
    }
    // go right
    solution[posR][posC] = 'R';
    tempValue = task4SolveZipBoardHelper(
        board,
        solution,
        size, currentTurn + 1, target, posR, posC + 1, highest);
    if (tempValue)
    {
        return 1;// we found a solution
    }
    else
    {
        // backtrack
        solution[posR][posC] = ogValue;
    }
    return 0;
}

int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{



    return 0;
}


int task5SolveSudokuHelper(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int posR,int posC)
{



}

int task5CheckIfvalueIsValid(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int posR,int posC,int value){
    //not valid value
    if (value>SUDOKU_MAX_NUMBER){
        return 0;
    }

    //in bounderis
    if (posR>=SUDOKU_GRID_SIZE||posC>=SUDOKU_GRID_SIZE)
    {
        return 0;
    }
    

    //not valid position
    if (board[posR][posC]!=0)
    {
        return 0;
    }

    //check if is the value in row 
    int notInRow=task5IsNumberinRow(board,posR,0,value,SUDOKU_GRID_SIZE);
    int notInColumn = task5IsNumberinColumn(board,0,posC,value);
    int notInSquare= task5isNumberInSqure(board,posR,posC,value);
    
    return notInRow==notInSquare==notInColumn==1;

}


int task5IsNumberinRow(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int posR,int posC,int value,int boarder)
{
    //invaild input can't accpet
    if (posR>=SUDOKU_GRID_SIZE)
    {
        return 0;
    }
    

    //checked all row and the value is'nt in it
    if (posC>=boarder)
    {
        return 1;
    }

    int currentBoardValue=board[posR][posC];

    // value is in the row
    if (currentBoardValue==value)
    {
        return 0;
    }
    
    return task5IsNumberinRow(board,posR,posC+1,value,boarder);
}

int task5IsNumberinColumn(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int posR,int posC,int value)
{
    //invaild input can't accpet
    if (posC>=SUDOKU_GRID_SIZE)
    {
        return 0;
    }
    

    //checked all row and the value is'nt in it
    if (posR>=SUDOKU_GRID_SIZE)
    {
        return 1;
    }

    int currentBoardValue=board[posR][posC];

    // value is in the row
    if (currentBoardValue==value)
    {
        return 0;
    }
    
    return task5IsNumberinColumn(board,posR+1,posC,value);
}

int task5isNumberInSqure(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int posR,int posC,int value)
{
    /*what square are we looking at 9*9 example
     0,0 | 0,1 | 0,2
     1,0 | 1,1 | 1,2
     2,0 | 2,1 | 2,2
    */
    int squareRow= posR%SUDOKU_SUBGRID_SIZE;
    int squareColumn= posC%SUDOKU_SUBGRID_SIZE;

    // boundires 
    int firstColumnTocheck=squareColumn*SUDOKU_SUBGRID_SIZE;
    int columnNotToCross= firstColumnTocheck+SUDOKU_SUBGRID_SIZE;

    int firstRowTocheck=squareRow*SUDOKU_SUBGRID_SIZE;
    int RowNotToCross= firstRowTocheck+SUDOKU_SUBGRID_SIZE;

    return task5isNumberInSquareHelper(board,firstRowTocheck,RowNotToCross,firstColumnTocheck,columnNotToCross,value);

}


int task5isNumberInSquareHelper(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int posR,int RowNotToCross ,int firstColumnTocheck,int columnNotToCross,int value)
{   
    //means the value isnt in squre 
    if (posR==RowNotToCross)
    {
        return 1;
    }
    //if true value is in the squre
    if (task5IsNumberinRow(board,posR,firstColumnTocheck,value,columnNotToCross)==0)
    {
        return 0;
    }
    
    return task5isNumberInSquareHelper(board,posR+1,RowNotToCross,firstColumnTocheck,columnNotToCross,value);


}





/// custom

void clearBuffer()
{
    char s = getchar();
    if (s == '\n')
    {
        return;
    }
    clearBuffer();
}
