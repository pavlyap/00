#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define RAKETKA_SIZE 3
#define MAX_SCORE 21

void pole(int ball_x, int ball_y, int raketka1_y, int raketka2_y, int score1,
          int score2);  // Объявление функций
int stena_boom(int ball_y, int ball_dy);
int raketka_boom(int ball_x, int ball_y, int raketka1_y, int raketka2_y, int ball_dx);

int main() {
    int ball_x = WIDTH / 2,
        ball_y = HEIGHT / 2;       // Установка начального положения мяча
    int ball_dx = 1, ball_dy = 1;  // Скорость мяча
    int raketka1_y = HEIGHT / 2 - RAKETKA_SIZE / 2;  // Положение ракетки 1
    int raketka2_y = HEIGHT / 2 - RAKETKA_SIZE / 2;  // Положение ракетки 2
    int score1 = 0, score2 = 0;                      // Начальные значения счета

    while (score1 < MAX_SCORE && score2 < MAX_SCORE) {
        pole(ball_x, ball_y, raketka1_y, raketka2_y, score1,
             score2);  // Функция отрисовки поля
        printf("Player 1 (a/z), Player 2 (k/m), then press space: ");  // Вывод текста

        char input1 = '\0', input2 = '\0',
             space = '\0';  // Инициализация переменных для ввода

        while (1) {  // Считываем ввод до тех пор, пока не найдем пробел
            char c = getchar();  // Считывает введеный символ
            if (c == ' ') {  // Если введен пробел, завершаем ввод и цикл завершается
                space = c;
                break;
            }
            if (input1 == '\0' &&
                (c == 'a' || c == 'z')) {  // Если input1 еще не заполнен, ищем символ от игрока 1
                input1 = c;
            } else if (input2 == '\0' && (c == 'k' || c == 'm')) {  // Если input2 еще не заполнен, ищем
                                                                    // символ от игрока 2
                input2 = c;
            }
        }
        while (getchar() != '\n');  // Очистка оставшегося мусора

        raketka1_y -= (input1 == 'a' && raketka1_y > 0) ? 1 : 0;  // Смена положения ракеток
        raketka1_y += (input1 == 'z' && raketka1_y < HEIGHT - RAKETKA_SIZE) ? 1 : 0;
        raketka2_y -= (input2 == 'k' && raketka2_y > 0) ? 1 : 0;
        raketka2_y += (input2 == 'm' && raketka2_y < HEIGHT - RAKETKA_SIZE) ? 1 : 0;

        if (space == ' ') {  // Движение мяча (если введен пробел)
            ball_x += ball_dx;
            ball_y += ball_dy;

            ball_dy = stena_boom(ball_y, ball_dy);  // Проверка столкновений
            ball_dx = raketka_boom(ball_x, ball_y, raketka1_y, raketka2_y, ball_dx);

            if (ball_x < 0 || ball_x >= WIDTH) {   // Гол
                ball_x < 0 ? score2++ : score1++;  // Начисление очков
                ball_x = WIDTH / 2;
                ball_y = HEIGHT / 2;
            }
        }
    }
    printf("Player %d wins!\n", (score1 >= 2) ? 1 : 2);  // Вывод счета

    return 0;
}

void pole(int ball_x, int ball_y, int raketka1_y, int raketka2_y, int score1, int score2) {
    printf("\033[2J\033[H");                                  // Очистка экрана
    printf("Player 1: %d | Player 2: %d\n", score1, score2);  // Выводит счет

    for (int i = 0; i < WIDTH + 2; i++) printf("#");  // Верхняя граница
    printf("\n");                                     // Перевод на новую строку

    // Отрисовка поля
    for (int y = 0; y < HEIGHT; y++) {
        printf(".");  // Первый символ слева
        for (int x = 0; x < WIDTH; x++) {
            if (x == ball_x && y == ball_y)
                printf("O");  // Мяч
            else if ((x == 2 && y >= raketka1_y && y < raketka1_y + RAKETKA_SIZE) ||
                     (x == WIDTH - 3 && y >= raketka2_y && y < raketka2_y + RAKETKA_SIZE))
                printf("|");  // Отрисовка ракеток
            else
                printf(" ");  // Последний символ справа
        }
        printf(".\n");  // Перевод на новую строку
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");  // Нижняя граница
    printf("\n");                                     // Перевод на новую строку
}

// Проверка отскока от стен
int stena_boom(int ball_y, int ball_dy) { return (ball_y <= 0 || ball_y >= HEIGHT - 1) ? -ball_dy : ball_dy; }

// Проверка отскока от ракеток
int raketka_boom(int ball_x, int ball_y, int raketka1_y, int raketka2_y, int ball_dx) {
    if ((ball_x == 1 && ball_y >= raketka1_y && ball_y < raketka1_y + RAKETKA_SIZE) ||
        (ball_x == WIDTH - 2 && ball_y >= raketka2_y && ball_y < raketka2_y + RAKETKA_SIZE)) {
        return -ball_dx;
    }
    return ball_dx;
}
