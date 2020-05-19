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

int check_rows(enum tile *board) {
  for (int y = 0; y < BOARD_SIZE; y++) {
    if (board[y * BOARD_SIZE] == Blank)
      continue;
    int won = 1;
    for (int x = 0; x < BOARD_SIZE; x++) {
      won &= board[x + y * BOARD_SIZE] == board[y * BOARD_SIZE];
    }
    if (won)
      return 1;
  }
  return 0;
}

int check_cols(enum tile *board) {
  for (int x = 0; x < BOARD_SIZE; x++) {
    if (board[x] == Blank)
      continue;
    int won = 1;
    for (int y = 0; y < BOARD_SIZE; y++) {
      won &= board[x + y * BOARD_SIZE] == board[x];
    }
    if (won)
      return 1;
  }
  return 0;
}

int check_diag(enum tile *board) {
  // check main diagonal
  if (board[0] != Blank) {
    int won = 1;
    for (int x = 1; x < BOARD_SIZE; x++) {
      won &= board[x + x * BOARD_SIZE] == board[0];
    }
    if (won)
      return 1;
  }
  // check antidiagonal
  if (board[BOARD_SIZE - 1] != Blank) {
    int won = 1;
    for (int x = 1; x < BOARD_SIZE; x++) {
      won &=
          board[(BOARD_SIZE - 1 - x) + x * BOARD_SIZE] == board[BOARD_SIZE - 1];
    }
    if (won)
      return 1;
  }
  return 0;
}

int player_has_won(enum tile *board) {
  return check_rows(board) || check_cols(board) || check_diag(board);
}

int main(int argc, char *argv[]) {
  enum tile board[BOARD_SIZE * BOARD_SIZE];
  enum tile player = Naught;
  initialise_board(board);
  puts("--- TIC-TAC-TOE ---");
  while (1) {
    display_board(board);
    player_turn(player, board);
    if (player_has_won(board)) {
      display_board(board);
      printf("PLAYER %s HAS WON\n", player == Naught ? "O" : "X");
      break;
    }
    player = player == Naught ? Cross : Naught;
  }
  return 0;
}
