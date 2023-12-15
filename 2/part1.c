#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "part1.h"

int MAX_NO_OF_ROUNDS = 10;

struct Round {
  int green;
  int blue;
  int red;
};

struct Game {
  int ID;
  struct Round* rounds;
};

int main() {
  FILE *fptr;
  if ((fptr = fopen("./input_part1.txt","r")) == NULL){
      printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
      exit(1);
  }

  int sum = 0;

  char line[200];
  while (fgets(line, 200, fptr)) {

    struct Game game = gameFromLine(line);
    
    if (isGameValid(game)) {
      printf("%d\n", sum);
      sum += game.ID;
      printf("Game %d is valid\n", game.ID);
    } else {
      printf("Game %d is NOT valid\n", game.ID);
    }
    free(game.rounds);
  }

  printf("answer is %d\n", sum);
  fclose(fptr);
  return 0;
}

struct Game gameFromLine(char* line) {
  struct Game game;

  // Find iD
  int ID = getIdFromLine(line);
  // Allocates an array of 3 rounds.
  struct Round* rounds = getRoundsFromLine(line);
  game.rounds = rounds;
  game.ID = ID;

  return game;
}

int getIdFromLine(char* line) {
  int posOfColon = getIndexOfColon(line);
  int startOfId = 5;
  int lengthOfID = posOfColon - startOfId;

  int ID = 0;
  for (int i = 0 ; i < lengthOfID ; i++) {
    char currentChar = line[startOfId + i];
    int num = currentChar - '0';
    if (i != lengthOfID) {
      // Not last number
      ID += num * pow(10, lengthOfID - i - 1);
    } else {
      // Last number
      ID += num;
    }
  }
  return ID;
}

struct Round* getRoundsFromLine(char* line) {
  struct Round* rounds = malloc(MAX_NO_OF_ROUNDS * sizeof(struct Round));
  int searchStart = getIndexOfColon(line);

  int currentRound = 0;
  int currentNumber = 0;
  rounds[0].red = 0;
  rounds[0].green = 0;
  rounds[0].blue = 0;
  printf("%s\n", line);
  for (int i = searchStart + 2;i < strlen(line); i++) {
    char currentChar = line[i];
    if (isdigit(currentChar)) {
      int number = currentChar - '0';
      printf("%d\n", number);
      currentNumber = currentNumber * 10 + number;
    } else {
      if (currentChar == 'r' && line[i-1] == ' ') { 
        // Number was for red
        rounds[currentRound].red = currentNumber;
        currentNumber = 0;
      }
      if (currentChar == 'g' && line[i-1] == ' ') { 
        // Number was for green 
        rounds[currentRound].green = currentNumber;
        currentNumber = 0;
      }
      if (currentChar == 'b' && line[i-1] == ' ') { 
        // Number was for blue
        rounds[currentRound].blue = currentNumber;
        currentNumber = 0;
        printf("BLUE %d\n", currentNumber);
      }
      if (currentChar == ';') {
        currentRound += 1;
      }
    }
  }

  return rounds;
}

int getIndexOfColon(char* line) {
  char colon[2] = ":";

  char *searchColon = strstr(line, colon);
  int posOfColon = searchColon - line;
  return posOfColon;
}

int isGameValid(struct Game game) {
  for (int i = 0; i < MAX_NO_OF_ROUNDS ; i++) {
    struct Round* round = &game.rounds[i];
    printf("Round %d of game %d has %d red %d green %d blue\n", i, game.ID, round->red, round->green, round->blue);
    if (round->red > 12) {
      return 0;
    }
    if (round->green > 13) {
      return 0;
    }
    if (round->blue > 14) {
      return 0;
    }
  }
  return 1;
}
