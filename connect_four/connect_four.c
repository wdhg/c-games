#include <stdio.h>

#define WIDTH 7
#define HEIGHT 6
#define LINE_LENGTH 4

enum disc {
  Empty,
  Black,
  White,
};

void initialise_grid(enum disc *grid) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      grid[x + y * WIDTH] = Empty;
    }
  }
}

void display_grid(enum disc *grid) {
  for (int x = 1; x <= WIDTH; x++) {
    printf(" %i", x);
  }
  printf("\n");
  for (int y = HEIGHT - 1; 0 <= y; y--) {
    printf("|");
    for (int x = 0; x < WIDTH; x++) {
      int c = ' ';
      if (grid[x + y * WIDTH] == Black) {
        c = '@';
      } else if (grid[x + y * WIDTH] == White) {
        c = 'O';
      }
      printf("%c|", c);
    }
    printf("\n");
  }
}

int valid_column(int column, enum disc *grid) {
  if (column < 0 || WIDTH <= column)
    return 0;
  return grid[WIDTH * (HEIGHT - 1) + column] == Empty;
}

void insert_to_column(enum disc player, int column, enum disc *grid) {
  for (int y = 0; y < HEIGHT; y++) {
    if (grid[column + y * WIDTH] == Empty) {
      grid[column + y * WIDTH] = player;
      return;
    }
  }
}

void player_turn(enum disc player, enum disc *grid) {
  printf("\n%s'S TURN\n", player == Black ? "BLACK" : "WHITE");
  int column;
  do {
    printf("> ");
    scanf("%i", &column);
    column--; // because we index columns from 1 for better usability
    if (valid_column(column, grid))
      break;
    puts("INVALID COLUMN");
  } while (1);
  insert_to_column(player, column, grid);
}

int main(int arc, char *argv[]) {
  enum disc grid[WIDTH * HEIGHT]; // (0, 0) is the bottom left
  enum disc player = White;
  initialise_grid(grid);
  while (1) {
    display_grid(grid);
    player_turn(player, grid);
    player = player == White ? Black : White;
  }
  return 0;
}
