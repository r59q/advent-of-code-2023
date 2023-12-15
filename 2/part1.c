#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

int isGameValid(struct Game game);

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

    struct Game game = gameFromLine(line, MAX_NO_OF_ROUNDS);
    
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
