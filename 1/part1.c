#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {

  FILE *fptr;
  if ((fptr = fopen("./input_part1.txt","r")) == NULL){
      printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
      exit(1);
   }

  char str[200];
  int sum = 0; // The result output 
  while (fscanf(fptr, "%s", &str) == 1) {
    int first = -1;
    int second = -1;

    for (int i = 0;i < 200; i++) {
      char ch = str[i];
      if (ch == '\0'){
        break;
      }
      if (isdigit(ch)) {
        int val = ch - '0';
        printf("%d\n", val);
        if (first == -1) {
          first = val;
        } else {
          second = val;
        }
      }
    }
    printf("%d%d\n", first, second);
    if (second != -1) {
      sum = sum + first * 10 + second;
    } else {
      sum = sum + first * 10 + first;
    }
  }
  printf("answer is %d\n", sum);
  fclose(fptr);

  return 0;
}
