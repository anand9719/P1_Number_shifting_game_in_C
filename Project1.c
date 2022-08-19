#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
// create matrix 4x4
void createMatrix(int arr[][4])
{
    int n = 15;
    int num[n], i, j;
    for (i = 0; i < 15; i++) // 1-15 number will be in matrix
        num[i] = i + 1;
    srand(time(NULL)); // for random number generation
    int lastIndex = n - 1, index;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
        {
            if (lastIndex >= 0)
            {
                index = rand() % (lastIndex + 1); // idea : performing % operation by (lastIndex+1)
                arr[i][j] = num[index];           // will give index , so put that num[index] number in matrix
                num[index] = num[lastIndex--];    // and replace last number with this indexed position number
            }                                     // and finally lastIndex--
        }
    arr[i - 1][j - 1] = 0; // last number is zero
}
// showing matrix
void showMatrix(int arr[][4])
{
    int i, j;
    printf("--------------------\n");
    for (i = 0; i < 4; i++)
    {
        printf("|");
        for (j = 0; j < 4; j++)
        {
            if (arr[i][j] != 0)
                printf("%-2d | ", arr[i][j]);
            else
                printf("   | ");
        }
        printf("\n");
    }
    printf("--------------------\n");
}
// winning check by function
int winner(int arr[][4])
{
    int i, j, k = 1;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++, k++)
            if (arr[i][j] != k && k != 16)
                break;
        if (j < 4)
            break;
    }
    if (j < 4)
        return 0;
    return 1;
}
// swap two numbers
void swap(int *x, int *y)
{
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
    printf("");
}
// Reads the user input character and return ascii value of that
int readEnteredKey()
{
    char c;
    c = _getch();
    if (c == -32)
        c = _getch();
    return c;
}
// shift up function
int shiftUp(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (i == 3) // shifting not possible
        return 0;
    swap(&arr[i][j], &arr[i + 1][j]);
    return 1; // shifting up
}
// shift down function
int shiftDown(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (i == 0) // shifting not possible
        return 0;
    swap(&arr[i][j], &arr[i - 1][j]); // swap numbers
    return 1; // shifting up 
}

int shiftRight(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (j == 0) // shifting not possible
        return 0;
    swap(&arr[i][j], &arr[i][j - 1]);
    return 1; // shift up 
}

int shiftLeft(int arr[][4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            if (arr[i][j] == 0)
                break;
        if (j < 4)
            break;
    }
    if (j == 3) // shifting not possible
        return 0;
    swap(&arr[i][j], &arr[i][j + 1]);
    return 1; // shift up
}
// Game rules
void gameRule(int arr[][4])
{
    system("cls");
    int i, j, k = 1;
    printf("                 RULES OF THIS GAME                 \n");
    printf("\n1.You can move only 1 step at a time by arrow key ");
    printf("\nMove Up   : by Up arrow key ");
    printf("\nMove Down : by Down arrow key");
    printf("\nMove Left : by Left arrow key");
    printf("\nMove Right: by Right arrow key\n");
    printf("\n2.You can move number at empty position only\n");
    printf("\n3.For each valid move : your total number of move will decreased by 1\n\n");
    printf("4.Wining situation : ");
    printf("Number in a 4x4 matrix should be in order from 1 to 15 ");
    printf("\n\n            Winning situation:         \n");
    printf("---------------------\n");
    for (i = 0; i < 4; i++)
    {
        printf("| ");
        for (j = 0; j < 4; j++)
        {
            if (arr[i][j] != 0)
                printf("%-2d | ", 4 * i + j + 1);
            else
                printf("   |");
        }
        printf("\n");
    }
    printf("---------------------\n");
    printf("\n5.You can exit the game at any time by pressing 'E' or 'e' \n");
    printf("\nSo, Try to win in minimum number of moves \n");
    printf("\n         Happy Gaming, Good Luck !\n");
    printf("\nPress any key to start..... ");
    int x = readEnteredKey();
}
// main function
int main()
{
    int arr[4][4];    // matrix
    int maxTry = 100; // maximum move
    char name[25];
    system("cls"); // to clear screen
    printf("Welcome To The Game !\n\n");
    printf("Enter Your Name: ");
    scanf("%s", name);
    while (1)
    {
        createMatrix(arr); // calling function to create matrix
        gameRule(arr);     // game rule function calling
        while (!winner(arr)) // checking winning situation
        {
            system("cls");
            if (!maxTry) // for remaining zero move
                break;
            printf("\n\nWelcome %s!,  Moves remaining : %d\n\n", name, maxTry);
            showMatrix(arr); // show matrix
            int key = readEnteredKey(); // return ascii code of user entered key
            switch (key) 
            {
            case 69: // ascii of E
            case 101: // ascii of e
                printf("\a\a\a\a\a\a\n     Thanks for Playing ! \n\a");
                printf("\n      Hit 'Enter' to exit the game... \n");
                key = readEnteredKey();
                exit(0);
            case 72: // arrow up
                if (shiftUp(arr))
                    maxTry--;
                break;
            case 80: // arrow down
                if (shiftDown(arr))
                    maxTry--;
                break;
            case 77: // arrow  right
                if (shiftRight(arr))
                    maxTry--;
                break;
            case 75: // arrow left
                if (shiftLeft(arr))
                    maxTry--;
                break;
            default:
                printf("\n\n      \a\a Not Allowed \a");
                //  delay(200);
            }
        }
        if (!maxTry)
            printf("\n\a              YOU LOSE !          \a\a\n");
        else
        {
            printf("\a                YOU WON !     \a\a\a ");
            printf("\n\a!!!!!!!!!!!!! Congratulations !!!!!!!!!!!!!\n\a");
        }
        char check;
        printf("\nWant to play again ? \n");
        printf("Press 'y' to play again or 'any key' to exit the game: ");
        fflush(stdin);
        scanf("%c", &check);
        if (check != 'y' && check != 'Y'){
            printf("Thanks for Playing !");
            break;}
        maxTry = 100;
    }
    return 0;
}