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
	@param (char*) TextArray is the text string from where we obtain the suffixes from
	@param (int) textLength is the textLength of the TextArray string
	@return (char*) the suffix at the given index
*/
char* getRandomString(int index, char* TextArray, int textLength)
{
	int i;
	
	//creates a string the size of the text we are generating
	char* text = malloc(sizeof(char) * (textLength - index + 1));
	
	//sets the end of the string as the null to prevent garbage values
	text[textLength - index] = '\0';
	
	//assigns the text from the text
	for (i = index; i < textLength; i++)
        text[i - index] = TextArray[i];
	
	return text;
}

/* Merges the two halves created by the mergeSort() function
	@param (char*) generatedText is the text string whose suffixes we are sorting
	@param (int) *TextArray is the integer array we are sorting that contains the indices of the suffixes
	@param (int) low is the lowest index of the input array
	@param (int) mid is the middle index of the input array
	@param (int) high is the highest index of the input array
	@param (int) textLength is the textLength of the generatedText string
*/
void merge(char* generatedText, int* TextArray, int low, int mid, int high, int textLength)
{
	int left = mid - low + 1;
    int right = high - mid;
    
	//temporary Arrays
    int *leftArray = malloc(sizeof(int) * (left));
    int *rightArray = malloc(sizeof(int) * (right));
    
    int i, j, k;
    
	//copies the indices from the unsorted suffix array to the temporary int arrays
    for(i = 0; i < left; i++)
    	leftArray[i] = TextArray[low + i];
    	
    for(j = 0; j < right; j++)
    	rightArray[j] = TextArray[mid + 1 + j];
    
    i = 0;
    j = 0;
	k = low;
	
	//sort
    while(i < left && j < right)
    {
    	//generates the suffixes at the indices being compared
    	char* string1 = getRandomString(leftArray[i], generatedText, textLength);
    	char* string2 = getRandomString(rightArray[j], generatedText, textLength);
    	
    	//comparing suffixes using strcmp
        if(strcmp(string1, string2) < 0)
        {
        	//assigns the current element of the left array to the suffix array
        	TextArray[k] = leftArray[i];
			i++;
		}
        else
        {
        	//assigns the current element of the right array to the suffix array
        	TextArray[k] = rightArray[j];
			j++;
		}
		k++;
		//frees the generated suffixes
		free(string1);
		free(string2);
    }
    
    //assigns the remaining elements of the left array
    while(i < left)
	{
        TextArray[k] = leftArray[i];
    	k++;
    	i++;
	}
	
	//assigns the remaining elements of the right array
    while(j < right)
	{
        TextArray[k] = rightArray[j];
		k++;
    	j++;
	}
	
	//frees the temporary arrays
	free(leftArray);
	free(rightArray);
}

/* The merge sort algorithm which repeatedly divides the input array into two halves,
	calls itself for the two halves, and then merges the two sorted halves.
	@param (char*) generatedText is the text string whose suffixes we are sorting
	@param (int) *TextArray is the integer array we are sorting that contains the indices of the suffixes
	@param (int) low is the lowest index of the input array
	@param (int) high is the highest index of the input array
	@param (int) textLength is the textLength of the generatedText string
*/
void mergeSort(char *generatedText, int *TextArray, int low, int high, int textLength)
{
	if(low < high)
	{
		int mid = low + (high - low) / 2;
		
		//sort the two halves
        mergeSort(generatedText, TextArray, low, mid, textLength);
        mergeSort(generatedText, TextArray, mid + 1, high, textLength);

        merge(generatedText, TextArray, low, mid, high, textLength);
	}
}

/* Prints the elements of the suffix array
	@param (int) *randomTextArray is the integer array we are sorting that contains the indexes of the suffixes
	@param (int) textLength is the textLength of the generatedText string
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
	char *generatedText= malloc(sizeof(char) * (textLength + 1));

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
	int *TextArray = malloc(sizeof(int) * (textLength));
	
	//sets the indices of the unsorted suffix array
	for(i = 0 ; i < textLength; i++)
        TextArray[i] = i;

    printf("Sorted Array: \n");
    printTextArray(generatedText, TextArray, textLength);

	//measures the time at the beginning of the algorithm, then runs the algorithm, then measures the time at the end
	clock_t begin = clock();

    mergeSort(generatedText, TextArray, 0, textLength - 1, textLength);
	
	clock_t end = clock();

    printf("Unsorted Array: \n");
    printTextArray(generatedText, TextArray, textLength);
	
	//frees the allocated memory for the string array and suffix array
	free(generatedText);
	free(TextArray);
	
	//measures the time spent by subtracting the time at the start from the time at the end
	double runningTime = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("\n\nTime spent: %f", runningTime);
	
	return 0;
}
