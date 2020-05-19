#include <stdio.h>

#define BOARD_SIZE 3

enum tile {
  Blank,
  Naught,
  Cross,
};

void display_board(enum tile *board) {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      char c = ' ';
      if (board[x + y * BOARD_SIZE] == Naught) {
        c = 'O';
      } else if (board[x + y * BOARD_SIZE] == Cross) {
        c = 'X';
      }
      printf(" %c", c);
    }
    printf("\n");
  }
}

void initialise_board(enum tile *board) {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for (int x = 0; x < BOARD_SIZE; x++) {
      board[x + y * BOARD_SIZE] = Blank;
    }
  }
}

int main(int argc, char *argv[]) {
  enum tile board[BOARD_SIZE * BOARD_SIZE];
  initialise_board(board);
  printf("--- TIC-TAC-TOE ---\n\n");
  display_board(board);
  return 0;
}
