#include "gui.h"

#ifdef SNAKE
using namespace s21;
#endif

void CLASS print_pause() {
  mvprintw(MAP_ROWS / 2, (MAP_COLS + PADDING * 4) / 2 - 4, "PAUSE");
}

void CLASS print_game_over() {
  mvprintw(MAP_ROWS / 2 - 3, (MAP_COLS + PADDING * 4) / 2 - 3, "GAME");
  mvprintw(MAP_ROWS / 2 - 2, (MAP_COLS + PADDING * 4) / 2 - 3, "OVER.");
  mvprintw(MAP_ROWS / 2 - 1, (MAP_COLS + PADDING * 4) / 2 - 3, "PRESS");
  mvprintw(MAP_ROWS / 2, (MAP_COLS + PADDING * 4) / 2 - 4, "\"ENTER\"");
  mvprintw(MAP_ROWS / 2 + 1, (MAP_COLS + PADDING * 4) / 2 - 4, " TO ");
  mvprintw(MAP_ROWS / 2 + 2, (MAP_COLS + PADDING * 4) / 2 - 3, "TRY");
  mvprintw(MAP_ROWS / 2 + 3, (MAP_COLS + PADDING * 4) / 2 - 3, "AGAIN");
}

void CLASS print_field(GameInfo_t* frame) {
  for (int row = 0; row < MAP_ROWS; row++) {
    for (int col = 0; col < MAP_COLS; col++) {
      if (frame->field[row][col])
        mvaddch(row + PADDING, col + PADDING, '0');
      else
        mvaddch(row + PADDING, col + PADDING, ' ');
    }
  }
}

void CLASS print_stats(GameInfo_t* stats, void* fig) {
  (void)fig;
  mvprintw(3, (MAP_COLS + PADDING * 4) / 2 + MAP_COLS, "%d", stats->high_score);
  mvprintw(6, (MAP_COLS + PADDING * 4) / 2 + MAP_COLS,
           "    ");  // To prevent printing of extra zeros
  mvprintw(6, (MAP_COLS + PADDING * 4) / 2 + MAP_COLS, "%d", stats->score);
  mvprintw(9, (MAP_COLS + PADDING * 4) / 2 + MAP_COLS, "%d", stats->level);
#ifndef SNAKE
  figure* tetr = (figure*)fig;
  if (tetr->y < 0 || tetr->type == END) {
    for (int row = 0; row < FIGURE_ROWS - 1;
         row++) {  // -1 to keep frame (has no effect on operation)
      for (int col = 0; col < FIGURE_COLS; ++col) {
        if (stats->next[row][col])
          mvaddch(14 + row, col + (MAP_COLS + PADDING * 4) / 2 + MAP_COLS, '0');
        else
          mvaddch(14 + row, col + (MAP_COLS + PADDING * 4) / 2 + MAP_COLS, ' ');
      }
    }
  }
#endif  // SNAKE
}

void CLASS print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  right_x += PADDING;
  bottom_y += PADDING;
  for (int i = left_x; i < right_x; i++) {
    mvaddch(top_y, i, ACS_HLINE);
    mvaddch(bottom_y, i, ACS_HLINE);
  }
  for (int i = top_y; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }
  mvaddch(top_y, left_x, ACS_ULCORNER);
  mvaddch(top_y, right_x, ACS_URCORNER);
  mvaddch(bottom_y, right_x, ACS_LRCORNER);
  mvaddch(bottom_y, left_x, ACS_LLCORNER);
}

void CLASS menu() {
  mvprintw(1, MAP_COLS + 6 * PADDING, "HIGH");
  mvprintw(2, MAP_COLS + 6 * PADDING, "SCORE");
  mvprintw(5, MAP_COLS + 6 * PADDING, "SCORE");
  mvprintw(8, MAP_COLS + 6 * PADDING, "LEVEL");
  mvprintw(11, MAP_COLS + 6 * PADDING, "NEXT");
  mvprintw(19, MAP_COLS + 4 * PADDING, "EXIT:\"ESC\"");
  mvprintw(20, MAP_COLS + 4 * PADDING, "PAUSE:\"P\"");
  print_rectangle(0, MAP_ROWS, MAP_COLS + PADDING * 2,
                  MAP_COLS + BOARD_COLS + PADDING);
  print_rectangle(12, MAP_ROWS - 4 * PADDING, MAP_COLS + PADDING * 4,
                  MAP_COLS + BOARD_COLS - PADDING);
}

void CLASS print_start() {
  mvprintw(MAP_ROWS / 2 - 2, (MAP_COLS + PADDING * 4) / 2 - 3, "PRESS");
  mvprintw(MAP_ROWS / 2 - 1, (MAP_COLS + PADDING * 4) / 2 - 4, "\"ENTER\"");
  mvprintw(MAP_ROWS / 2, (MAP_COLS + PADDING * 4) / 2 - 3, " TO ");
  mvprintw(MAP_ROWS / 2 + 1, (MAP_COLS + PADDING * 4) / 2 - 3, "START");
}

void CLASS init_front(GameInfo_t* frame) {
  initscr();
  curs_set(0);
  menu();
  print_rectangle(0, MAP_ROWS, 0, MAP_COLS);
  print_field(frame);
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  cbreak();
  noecho();
}

void CLASS refresh_scr(GameInfo_t* frame, void* tetr) {
  print_field(frame);
  print_stats(frame, tetr);
  refresh();
}

#ifdef SNAKE
void s21::Front::print_win() {
  mvprintw(MAP_ROWS / 2 - 3, (MAP_COLS + PADDING * 4) / 2 - 4, "YOU");
  mvprintw(MAP_ROWS / 2 - 2, (MAP_COLS + PADDING * 4) / 2 - 4, "WIN!");
  mvprintw(MAP_ROWS / 2 - 1, (MAP_COLS + PADDING * 4) / 2 - 4, "PRESS");
  mvprintw(MAP_ROWS / 2, (MAP_COLS + PADDING * 4) / 2 - 4, "\"ESC\"");
  mvprintw(MAP_ROWS / 2 + 1, (MAP_COLS + PADDING * 4) / 2 - 4, "TO EXIT");
}

#endif  // SNAKE
