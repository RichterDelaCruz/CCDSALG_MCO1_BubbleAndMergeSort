#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Generates a random number from the inputted range
	@param (int) min is the lowest possible value that can be generated
	@param (int) max is the highest possible value that can be generated
	@return (int) the randomly generated number
*/
int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/* Given an index, this function returns the suffix from the text string
	@param (int) index is the position of the suffix that we are looking for
	@param (char*) generatedText is the text string from where we obtain the suffixes from
	@param (int) textLength is the textLength of the generatedText string
	@return (char*) the suffix at the given index
*/
char* getRandomString(int index, char* generatedText, int textLength)
{
	//creates a string the size of the suffix we are generating
	char* randomString = malloc(sizeof(char) * (textLength - index + 1));

	//sets the end of the string as the null to prevent garbage values
	randomString[textLength - index] = '\0';

	//assigns the suffix from the text
	for (int i = index; i < textLength; i++)
		randomString[i - index] = generatedText[i];

	return randomString;
}

/* The bubble sort algorithm which repeatedly goes through the array and compares
   adjacent elements, and swaps them if they are not in the correct order.
	@param (char*) generatedText is the text string whose suffixes we are sorting
	@param (int) *TextArray is the integer array we are sorting that contains the indices of the suffixes
	@param (int) textLength is the textLength of the generatedText string
*/
void BubbleSort(char* generatedText, int *TextArray, int textLength)
{
	int i, j, temp;

	//sort
	for(i = 0; i < textLength; i++)
	{
		for(j = i + 1; j < textLength; j++)
		{
			//generates the suffixes at the indices being compared
			char* string1 = getRandomString(TextArray[i], generatedText, textLength);
    		char* string2 = getRandomString(TextArray[j], generatedText, textLength);

			//comparing suffixes using strcmp
			if(strcmp(string1, string2) > 0)
			{
				//swaps the corresponding indices of the suffixarray
				temp = TextArray[i];
                TextArray[i] = TextArray[j];
                TextArray[j] = temp;
	        }
	        //frees the generated suffixes
	        free(string1);
	        free(string2);
	    }
	}
}

/* Prints the elements of the suffix array
	@param (int) *SuffixArray is the integer array we are sorting that contains the indexes of the suffixes
	@param (int) length is the length of the Text string
*/
void printTextArray(char* generatedText, int *TextArray, int textLength)
{
    int i;

    for(i = 0; i < textLength; i++)
        printf("%2d : %s \n", TextArray[i], getRandomString(TextArray[i], generatedText, textLength));
}

int main()
{
	int i, textLength;
	char textCharacter;

    time_t random_seed;
    random_seed = time(NULL);
    srand(random_seed);

	printf("Input the length of the string: ");
	scanf("%d", &textLength);

	//creates a string the size of the text we are generating
	char *generatedText = malloc(sizeof(char) * (textLength + 1));

	//sets the end of the string as the null to prevent garbage values
    generatedText[textLength] = '\0';

	//generates a random string from the alphabet {a,c,g,t}
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



	//creates an integer array to store the indexes of the suffixes of the text string
	int *SuffixArray = malloc(sizeof(int) * (textLength));

	//sets the indices of the unsorted suffix array
	for(i = 0 ; i < textLength; i++)
		SuffixArray[i] = i;

    printf("Unsorted Array: \n");
    printTextArray(generatedText, SuffixArray, textLength);

	//measures the time at the beginning of the algorithm, then runs the algorithm, then measures the time at the end
	clock_t begin = clock();

	BubbleSort(generatedText, SuffixArray, textLength);

	clock_t end = clock();

    printf("Sorted Array: \n");
    printTextArray(generatedText, SuffixArray, textLength);

	//frees the allocated memory for the string array and suffix array
	free(generatedText);
	free(SuffixArray);

	//measures the time spent by subtracting the time at the start from the time at the end
	double runningTime = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("\nTime spent: %f", runningTime);

	return 0;
}
