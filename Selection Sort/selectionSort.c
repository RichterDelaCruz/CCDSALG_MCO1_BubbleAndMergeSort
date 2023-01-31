#include <stdio.h>
#include <string.h>
#define STRING 65536

//method1
int main() {
    char input[1024];
    printf("Input string: ");
    scanf("%s", input);
    int inputLength = strlen(input);

    char S[1024][1024];
    int i;
    char subStr[1024];
    for (i = 0; i < inputLength; i++) {
        memcpy(subStr,&input[i],inputLength-i);
        subStr[inputLength-i] = '\0';
        strcpy(S[i],subStr);
        printf("%s\n", S[i]);
    }
    int startingPos[1024];
    char temp[1024];

    //selection sort
    for (int i = 0; i < inputLength; i++) {
        for (int j = i + 1; j < inputLength; j++) {
            if (strcmp(S[i], S[j]) > 0) {
                strcpy(temp, S[i]);
                strcpy(S[i], S[j]);
                strcpy(S[j], temp);
                startingPos[i] = j;
            }

        }
    }

    for (int i = 0; i < inputLength; i++) {
        printf("%d %s\n", startingPos[i], S[i]);
    }
}