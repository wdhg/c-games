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

int main(int arc, char *argv[]) {
  enum disc grid[WIDTH * HEIGHT]; // (0, 0) is the bottom left
  initialise_grid(grid);
  return 0;
}
