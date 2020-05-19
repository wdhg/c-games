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
      char c = '_';
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
  int x, y;
  do {
    printf("> ");
    scanf("%i %i", &x, &y);
    if (0 <= x && x < BOARD_SIZE && 0 <= y && y < BOARD_SIZE &&
        board[x + y * BOARD_SIZE] == Blank) {
      break;
    }
    puts("INVALID POS");
  } while (1);
  board[x + y * BOARD_SIZE] = player;
}

int player_has_won(enum tile *board) { return 0; }

int main(int argc, char *argv[]) {
  enum tile board[BOARD_SIZE * BOARD_SIZE];
  enum tile player = Naught;
  initialise_board(board);
  puts("--- TIC-TAC-TOE ---");
  while (1) {
    display_board(board);
    player_turn(player, board);
    if (player_has_won(board)) {
      printf("PLAYER %s HAS WON\n", player == Naught ? "O" : "X");
      break;
    }
    player = player == Naught ? Cross : Naught;
  }
  return 0;
}
