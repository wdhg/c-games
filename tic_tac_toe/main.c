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

void player_turn(enum tile player, enum tile *board) {
  printf("PLAYER %s's TURN\n", player == Naught ? "O" : "X");
  // get user input
  // validate it
  // update board
}

int player_has_won(enum tile *board) { return 0; }

int main(int argc, char *argv[]) {
  enum tile board[BOARD_SIZE * BOARD_SIZE];
  enum tile player = Naught;
  initialise_board(board);
  printf("--- TIC-TAC-TOE ---\n\n");
  while (1) {
    display_board(board);
    player_turn(player, board);
    if (player_has_won(board)) {
      printf("PLAYER %s HAS WON\n", player == Naught ? "O" : "X");
      break;
    }
  }
  return 0;
}
