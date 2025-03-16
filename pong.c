#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3

// Очистка экрана через ANSI-коды (Unix)
void clearScreen() { printf("\033[2J\033[H"); }

// Отрисовка поля, ракеток, мяча и счета
void draw(int ball_x, int ball_y, int paddle1_y, int paddle2_y, int score1,
          int score2) {
  clearScreen();
  printf("Player 1: %d | Player 2: %d\n", score1, score2);

  // Верхняя граница
  for (int i = 0; i < WIDTH + 2; i++)
    printf("#");
  printf("\n");

  // Тело поля
  for (int y = 0; y < HEIGHT; y++) {
    printf("#"); // Левая граница
    for (int x = 0; x < WIDTH; x++) {
      if (x == ball_x && y == ball_y)
        printf("O"); // Мяч
      else if ((x == 0 && y >= paddle1_y &&
                y < paddle1_y + PADDLE_SIZE) || // Левая ракетка
               (x == WIDTH - 1 && y >= paddle2_y &&
                y < paddle2_y + PADDLE_SIZE) // Правая ракетка
      )
        printf("|");
      else
        printf(" ");
    }
    printf("#\n"); // Правая граница
  }

  // Нижняя граница
  for (int i = 0; i < WIDTH + 2; i++)
    printf("#");
  printf("\n");
}

int main() {
  int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
  int ball_dx = 1, ball_dy = 1;
  int paddle1_y = HEIGHT / 2 - PADDLE_SIZE / 2;
  int paddle2_y = HEIGHT / 2 - PADDLE_SIZE / 2;
  int score1 = 0, score2 = 0;
  char input;

  while (1) {
    draw(ball_x, ball_y, paddle1_y, paddle2_y, score1, score2);

    // Проверка победы
    if (score1 >= 21 || score2 >= 21) {
      printf("Player %d wins!\n", (score1 >= 21) ? 1 : 2);
      break;
    }

    // Ввод команды
    printf("Input (a/z/k/m/space): ");
    scanf("%c", &input);

    // Управление ракетками
    if (input == 'a' && paddle1_y > 0)
      paddle1_y--;
    if (input == 'z' && paddle1_y < HEIGHT - PADDLE_SIZE)
      paddle1_y++;
    if (input == 'k' && paddle2_y > 0)
      paddle2_y--;
    if (input == 'm' && paddle2_y < HEIGHT - PADDLE_SIZE)
      paddle2_y++;

    // Пошаговое движение мяча
    if (input == 32) {
      ball_x += ball_dx;
      ball_y += ball_dy;

      // Отскок от стен
      if (ball_y <= 0 || ball_y >= HEIGHT - 1)
        ball_dy *= -1;

      // Отскок от ракеток
      if ((ball_x == 1 && ball_y >= paddle1_y &&
           ball_y < paddle1_y + PADDLE_SIZE) ||
          (ball_x == WIDTH - 2 && ball_y >= paddle2_y &&
           ball_y < paddle2_y + PADDLE_SIZE)) {
        ball_dx *= -1;
      }

      // Гол
      if (ball_x < 0) {
        score2++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
      } else if (ball_x >= WIDTH) {
        score1++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
      }
    }
  }

  return 0;
}
