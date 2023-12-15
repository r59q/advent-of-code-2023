#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

struct Round {
  int green;
  int blue;
  int red;
};

struct Game {
  int ID;
  struct Round* rounds;
};

struct Game gameFromLine(char* line, int maxNoOfRounds) {
  struct Game game;

  // Find iD
  int ID = getIdFromLine(line);
  // Allocates an array of 3 rounds.
  struct Round* rounds = getRoundsFromLine(line, maxNoOfRounds);
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

struct Round* getRoundsFromLine(char* line, int maxNoOfRounds) {
  struct Round* rounds = malloc(maxNoOfRounds * sizeof(struct Round));
  int searchStart = getIndexOfColon(line);

  int currentRound = 0;
  int currentNumber = 0;
  for (int i = 0;i < maxNoOfRounds;i++) {
    rounds[i].red = 0;
    rounds[i].blue = 0;
    rounds[i].green = 0;
  }
  printf("%s\n", line);
  for (int i = searchStart + 2;i < strlen(line); i++) {
    char currentChar = line[i];
    if (isdigit(currentChar)) {
      int number = currentChar - '0';
      currentNumber = currentNumber * 10 + number;
    } else {
      if (currentChar == 'r' && line[i-1] == ' ') { 
        // Number was for red
        rounds[currentRound].red = currentNumber;
        printf("RED: %d\n", currentNumber);
        currentNumber = 0;
      }
      if (currentChar == 'g' && line[i-1] == ' ') { 
        // Number was for green 
        rounds[currentRound].green = currentNumber;
        printf("GREEN: %d\n", currentNumber);
        currentNumber = 0;
      }
      if (currentChar == 'b' && line[i-1] == ' ') { 
        // Number was for blue
        rounds[currentRound].blue = currentNumber;
        printf("BLUE: %d\n", currentNumber);
        currentNumber = 0;
      }
      if (currentChar == ';') {


        currentRound += 1;
        printf("ROUND: %d\n", currentRound);
        currentNumber = 0;
        rounds[currentRound].red = 0;
        rounds[currentRound].green = 0;
        rounds[currentRound].blue = 0;
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
