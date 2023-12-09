#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

struct StringSearchResult {
  int firstIndex;
  int lastIndex;
  int firstTerm;   
  int secondTerm;
};

struct NumSearchResult {
  int firstIndex;
  int lastIndex;
  int firstNum;
  int secondNum;
};

int * getPair(struct NumSearchResult numResult, struct StringSearchResult stringResult);
struct NumSearchResult indexOfNum(char *line);
struct StringSearchResult indexOfStringNum(char *line);
void reverseString(char *input); 
char searchTerms[9][6] = {
  "one",
  "two",
  "three",
  "four",
  "five",
  "six", 
  "seven",
  "eight",
  "nine"
};

int main() {
  FILE *fptr;
  if ((fptr = fopen("./input_part2.txt","r")) == NULL){
      printf("Error! opening file");
       // Program exits if the file pointer returns NULL.
      exit(1);
  }
  
  int resultSum = 0;

  char line[200];
  while (fscanf(fptr, "%s", &line) == 1) {
    printf("\n%s\n", line);
    struct NumSearchResult numResult = indexOfNum(line);
    struct StringSearchResult stringResult = indexOfStringNum(line);
    printf("First alpha index = %d (%d)\n", stringResult.firstIndex, stringResult.firstTerm);
    printf("Last alpha index = %d (%d)\n", stringResult.lastIndex, stringResult.secondTerm);
    
    printf("First numeric index = %d (%d)\n", numResult.firstIndex, numResult.firstNum);
    printf("Last numeric index = %d (%d)\n", numResult.lastIndex, numResult.secondNum);

    int* pair = getPair(numResult, stringResult);

    int combine = pair[0] * 10 + pair[1];
    resultSum = resultSum + combine;
    printf("result : %d:%d (%d)\n", pair[0], pair[1], combine);
  }
  fclose(fptr);
  printf("Total combined(answer) = %d\n", resultSum);
  return 0;
}

struct StringSearchResult indexOfStringNum(char *line) {
  int indexOfFirst = 999;
  int indexOfLast = 999;
  int firstTerm = -1;
  int secondTerm = -1;

  // Find the first index
  for (int i = 0 ; i < 9 ; i++) {
    char *searchTerm = searchTerms[i];
    char *search = strstr(line, searchTerm);
    int pos = search - line;
    if (search != NULL) {
      // Element was found
      if (pos < indexOfFirst || indexOfFirst == -1) {
        indexOfFirst = pos;
        firstTerm = i;
      }
    }
  }
  // Find the last index by reversing
  char lineReverse[strlen(line)];
  strcpy(lineReverse, line);
  reverseString(lineReverse);
  for (int i = 0 ; i < 9 ; i++) {
    char *searchTerm = searchTerms[i];
    char searchTermReverse[strlen(searchTerm)];
    strcpy(searchTermReverse, searchTerm);
    reverseString(searchTermReverse);
    char *search = strstr(lineReverse, searchTermReverse);
    int pos = search - lineReverse;
    if (search != NULL) {
      // Element was found
      if (pos < indexOfLast || indexOfLast == -1) {
        indexOfLast= pos;
        secondTerm = i;
      }
    }
  }
  if (indexOfLast != 999) {
    indexOfLast = strlen(line) - indexOfLast;
  }
  if (indexOfLast == 999) {
    indexOfLast = -1;
  } else {
    secondTerm++;
    indexOfLast--;
  }
  if (indexOfFirst == 999) {
    indexOfFirst = -1;
  } else {
    firstTerm++;
  }

  struct StringSearchResult result = {indexOfFirst, indexOfLast, firstTerm, secondTerm};
  return result;
}

struct NumSearchResult indexOfNum(char *line) {
  int indexOfFirst = 999;
  int indexOfLast = -1;
  int firstNum = -1;
  int secondNum = -1;


  // Find the first index
  for (int i = 0 ; i < strlen(line) ; i++) {
    char currentChar = line[i];
    if (isdigit(currentChar)) {
        indexOfFirst = i;
        firstNum = currentChar - '0';
        break;
    }
  }
  // find second index
  for (int i = strlen(line)-1 ; i >= 0 ; i--) {
    char currentChar = line[i];
    if (isdigit(currentChar)) {
      indexOfLast = i;
      secondNum = currentChar - '0';
      break;
    }
  }

  if (indexOfFirst == 999) {
    indexOfFirst = -1;
  }

  struct NumSearchResult result = {indexOfFirst, indexOfLast, firstNum, secondNum};
  return result;
}

int * getPair(struct NumSearchResult numResult, struct StringSearchResult stringResult) {
  static int result[2] = {0, 0};

  if (numResult.firstIndex == -1){
    result[0] = stringResult.firstTerm;
  } else if (stringResult.firstIndex == -1) {
    result[0] = numResult.firstNum;
  } else {
    if (numResult.firstIndex < stringResult.firstIndex) {
       result[0] = numResult.firstNum;
    } else {
      result[0] = stringResult.firstTerm;
    }
  }
  if (numResult.lastIndex == -1) {
    result[1] = stringResult.secondTerm;
  } else if (stringResult.lastIndex == -1 ) {
    result[1] = numResult.secondNum;
  } else {
    if (numResult.lastIndex > stringResult.lastIndex) {
      result[1] = numResult.secondNum;
    } else {
     result[1] = stringResult.secondTerm; 
    }
  }
  return result;
}

void reverseString(char *input) {
  int length = strlen(input);
  if (length == 0) {
    return;
  }
  int ptr1 = 0;
  int ptr2 = length-1;
  while(ptr1 < ptr2) {
    char a = input[ptr1];
    char b = input[ptr2];
    input[ptr1] = b;
    input[ptr2] = a;
    ptr1++;
    ptr2--;
  }
}
