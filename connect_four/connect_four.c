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

int player_turn(enum disc player, enum disc *grid) {
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

int check_rows(enum disc player, enum disc *grid) {
  for (int y = 0; y < HEIGHT; y++) {
    int count = 0;
    for (int x = 0; x < WIDTH; x++) {
      if (grid[x + y * WIDTH] == player) {
        count++;
      } else {
        count = 0;
      }
      if (count == LINE_LENGTH) {
        return 1;
      }
    }
  }
  return 0;
}

int check_cols(enum disc player, enum disc *grid) {
  for (int x = 0; x < WIDTH; x++) {
    int count = 0;
    for (int y = 0; y < HEIGHT; y++) {
      if (grid[x + y * WIDTH] == player) {
        count++;
      } else {
        count = 0;
      }
      if (count == LINE_LENGTH) {
        return 1;
      }
    }
  }
  return 0;
}

int in_bounds(int x, int y) {
  return 0 <= x && 0 <= y && x < WIDTH && y < HEIGHT;
}

int check_diag(enum disc player, enum disc *grid) {
  // forward diagonals
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT - LINE_LENGTH; y++) {
      int forward_count = 0;
      int backwards_count = 0;
      int i = 0;
      while (1) {
        if (in_bounds(x + i, y + i) &&
            grid[(x + i) + (y + i) * WIDTH] == player) {
          forward_count++;
        } else {
          forward_count = 0;
        }
        if (in_bounds(x - i, y + i) &&
            grid[(x - i) + (y + i) * WIDTH] == player) {
          backwards_count++;
        } else {
          backwards_count = 0;
        }
        if (forward_count == LINE_LENGTH || backwards_count == LINE_LENGTH) {
          return 1;
        }
        i++;
        if (!in_bounds(x + i, y + i) && !in_bounds(x - i, y + i))
          break;
      }
    }
  }
  return 0;
}

int has_won(enum disc player, enum disc *grid) {
  return check_rows(player, grid) || check_cols(player, grid) ||
         check_diag(player, grid);
}

int is_draw(enum disc *grid) {
  for (int x = 0; x < WIDTH; x++) {
    if (valid_column(x, grid))
      return 0;
  }
  return 1;
}

int main(int arc, char *argv[]) {
  enum disc grid[WIDTH * HEIGHT]; // (0, 0) is the bottom left
  enum disc player = White;
  initialise_grid(grid);
  while (1) {
    display_grid(grid);
    player_turn(player, grid);
    if (has_won(player, grid)) {
      display_grid(grid);
      printf("\nPLAYER %s HAS WON\n", player == White ? "WHITE" : "BLACK");
      break;
    }
    if (is_draw(grid)) {
      display_grid(grid);
      printf("\nDRAW\n");
      break;
    }
    player = player == White ? Black : White;
  }
  return 0;
}
