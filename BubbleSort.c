/*******************************************************************************
BubbleSort.c
Last updated: October 27, 2022
Authors:    DELA CRUZ, ANGELO RICHTER L.
            EUSEBIO, JOSEPH BRYAN Z.
            OSTIA, LUIS P.

MRS. MA. CHRISTINE A. GENDRANO
CCDSALG S15 A.Y. 2021-2022

PROGRAM DESCRIPTION: This program generates a random string from the alphabet
 {a, c, g, t} in a given length. The length of the string is also the number
 of strings to be generated. The purpose of this program is to sort all the
 generated String using Bubble Sort.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*******************************************************************************
    Purpose: This function generates a random number from 1 to 4.
    Returns: The generated random number.
    Pre-condition: The parameters should contain numbers.

    @param : min is the minimum number you want to generate.
    @param : max is the maximum number you want to generate.

*******************************************************************************/
int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/*******************************************************************************
    Purpose: This function gets the string from the generated random
    text.
    Returns: The string value of an index.
    Pre-condition: The parameters should contain numbers.

    @param : index is the assigned number of the another set of string.
    @param : *generatedText the address of  array.
    @param : textLength is the length of the generated string.

*******************************************************************************/
char* getString(int index, char* generatedText, int textLength)
{
    char* randomString = malloc(sizeof(char) * (textLength - index + 1));
    randomString[textLength - index] = '\0';
    for (int i = index; i < textLength; i++)
        randomString[i - index] = generatedText[i];
    return randomString;
}

/*******************************************************************************
    Purpose: Bubble sorts the TextArray.

    @param : *generatedText the address of the generated array.
    @param : *textArray is the indexes of the generated text.
    @param : textLength is the length of the generated string.

*******************************************************************************/
void BubbleSort(char* generatedText, int *textArray, int textLength)
{
    int i, j, temp;
    for(i = 0; i < textLength; i++)
    {
        //Last i elements are already in place
        for(j = i + 1; j < textLength; j++)
        {
            char* string1 = getString(textArray[i], generatedText, textLength);
            char* string2 = getString(textArray[j], generatedText, textLength);

            //Swaps the given values.
            if(strcmp(string1, string2) > 0)
            {
                temp = textArray[i];
                textArray[i] = textArray[j];
                textArray[j] = temp;
            }

            //Frees the memory in your program which will be available for later use.
            free(string1);
            free(string2);
        }
    }
}

/*******************************************************************************
    Purpose: Prints the original index and their string value.

*******************************************************************************/
void printTextArray(char* generatedText, int *TextArray, int textLength)
{
    int i;

    for(i = 0; i < textLength; i++)
        printf("%2d : %s \n", TextArray[i], getString(TextArray[i], generatedText, textLength));
}

int main()
{
    int i, textLength;
    char textCharacter;

    //For the randomNumber().
    time_t random_seed;
    random_seed = time(NULL);
    srand(random_seed);

    //Prompts the user for the string length.
    printf("Input the length of the string: ");
    scanf("%d", &textLength);

    //Allocates a string of characters according to the text length.
    char *generatedText = malloc(sizeof(char) * (textLength + 1));

    //Converts the end of the string to a null value to prevent garbage values.
    generatedText[textLength] = '\0';

    //Generates a random number to create a text.
    for (i = 0; i < textLength; i++)
    {
        switch(getRandomNumber(1, 4))
        {
            case 1:
                textCharacter = 'a'; break;
            case 2:
                textCharacter = 'c'; break;
            case 3:
                textCharacter = 'g'; break;
            case 4:
                textCharacter = 't'; break;
        }
        generatedText[i] = textCharacter;
    }

    printf("Generated string: %s \n", generatedText);

    //Allocates an array of integer according to the length of the text.
    int *textArray = malloc(sizeof(int) * (textLength));

    //Inputs a value to the textArray[] according to the length of the text.
    for(i = 0 ; i < textLength; i++)
        textArray[i] = i;

    //Prints the unsorted array.
    printf("Unsorted Array: \n");
    printTextArray(generatedText, textArray, textLength);

    clock_t begin = clock();

    BubbleSort(generatedText, textArray, textLength);

    clock_t end = clock();

    //Prints the sorted array.
    printf("Sorted Array: \n");
    printTextArray(generatedText, textArray, textLength);

    //frees the memory in your program which will be available for later use.
    free(generatedText);
    free(textArray);

    //prints the running time of the program.
    double runningTime = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nTime spent: %f", runningTime);

    return 0;
}
