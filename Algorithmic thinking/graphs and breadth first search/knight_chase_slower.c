#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задача 1. Погоня за пешкой
// Рассмотрим задачу с платформы DMOJ (dmoj.ca) под номером ccc99s4

/*
Условие
Два человека играют в настольную игру, у одного игрока есть пешка, а у второго конь 
(не беспокойтесь, знание шахматной теории вам не потребуется).
Игровая доска разделена на r рядов. Первый ряд находится вверху, а ряд r внизу. 
Доска также разделена на с столбцов, первый столбец расположен слева, а столбец c справа.
Первой ходит пешка, затем конь, затем снова пешка, затем конь и так далее, пока игра не завершится.
За каждый ход фигура обязана переместиться, оставаться на месте запрещается.
Пешка не выбирает, как именно переместиться, и каждый ход продвигается на одну клетку вверх. 
Конь же каждый ход имеет до восьми вариантов перемещения по клеткам:
 * вверх на 1, вправо на 2;
 * вверх на 1, влево на 2;
 * вниз на 1, вправо на 2;
 * вниз на 1, влево на 2;
 * вверх на 2, вправо на 1;
 * вверх на 2, влево на 1;
 * вниз на 2, вправо на 1;
 * вниз на 2, влево на 1.
Ходы, ведущие  фигуру за границы доски, не допускаются.
Игра завершается при выполнении одного из трех условий: конь съедает пешку; 
возникает ничья (пат); конь проигрывает, поскольку пешка достигает верхнего 
ряда:
 * Конь побеждает, если совершает ход и занимает клетку, в которой стоит пешка, 
до того как пешка достигнет верхнего ряда. Для победы завершающий ход 
должен принадлежать именно коню. Если же последний ход сделает пешка, 
то выигрыш коня не засчитывается.
 * Пат возникает, когда конь совершает ход и занимает клетку над пешкой до того, 
как пешка достигает верхнего ряда. Опять же, последний ход должен быть именно за конем. 
Единственное исключение — ситуация, когда игра начинается с пата, 
то есть стартовая позиция коня окажется в клетке над пешкой.
 * Конь проигрывает, если пешка достигает верхнего ряда до того, как он победит или возникнет пат.
То есть если пешка добирается до верхнего ряда прежде, чем конь ее съест или займет клетку над ней,
то конь проигрывает. Как только пешка достигает верхнего ряда, игра останавливается.

Целью решения является определить результат лучшего варианта для коня и
количество его ходов, необходимых для получения этого результата.
*/

/*
Входные данные
Первая строка входных данных содержит число тестовых примеров, каждый из 
которых состоит из шести строк:
 * количества горизонталей на доске — от 3 до 99;
 * количества вертикалей на доске — от 2 до 99;
 * номера стартовой горизонтали пешки;
 * номера стартовой вертикали пешки;
 * номера стартовой горизонтали коня;
 * номера стартовой вертикали коня.
Гарантируется, что пешка и конь в начале игры стоят на разных клетках доски и что 
конь начинает игру из позиции, откуда ему будет доступно не менее одного хода.
*/

/*
Выходные данные
Для каждого тестового примера требуется вывести строку с одним из трех сообщений:
Если конь может победить: Win in m knight move(s).
Если конь победить не может, но может добиться пата: Stalemate in m knight move(s).
Если конь не может победить или добиться пата: Loss in m knight move(s).
Здесь m — минимальное число ходов, совершенных конем.
Время на решение тестовых примеров — две секунды.
*/

#define MAX_ROWS 99
#define MAX_COLS 99

typedef struct position { 
  int row, col;
} position;


typedef int board[MAX_ROWS + 1][MAX_COLS + 1];
typedef position positions[MAX_ROWS * MAX_COLS];

void add_position(int from_row, int from_col, int to_row, int to_col, int num_rows, int num_cols, positions new_positions, int *num_new_positions, board min_moves) {
    struct position new_position;
    if (to_row >= 1 && to_col >= 1 && to_row <= num_rows && to_col <= num_cols && min_moves[to_row][to_col] == -1) {
        min_moves[to_row][to_col] = 1 + min_moves[from_row][from_col];
        new_position = (position){to_row, to_col};
        new_positions[*num_new_positions] = new_position;
        (*num_new_positions)++;
    }
}

int find_distance(int knight_row, int knight_col, int dest_row, int dest_col, int num_rows, int num_cols) {
    positions cur_positions, new_positions;
    int num_cur_positions, num_new_positions;
    int i, j, from_row, from_col;
    board min_moves;
    for (i = 1; i <= num_rows; i++) {
        for (j = 1; j <= num_cols; j++) {
            min_moves[i][j] = -1;
        }
    }
    min_moves[knight_row][knight_col] = 0;
    cur_positions[0] = (position){knight_row, knight_col};
    num_cur_positions = 1;

    while (num_cur_positions > 0) { 
        num_new_positions = 0;
        for (i = 0; i < num_cur_positions; i++) { 
            from_row = cur_positions[i].row;
            from_col = cur_positions[i].col;
            if (from_row == dest_row && from_col == dest_col) {
                return min_moves[dest_row][dest_col];
            }
            add_position(from_row, from_col, from_row + 1, from_col + 2, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
            add_position(from_row, from_col, from_row + 1, from_col - 2, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
            add_position(from_row, from_col, from_row - 1, from_col + 2, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
            add_position(from_row, from_col, from_row - 1, from_col - 2, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
            add_position(from_row, from_col, from_row + 2, from_col + 1, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
            add_position(from_row, from_col, from_row + 2, from_col - 1, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
            add_position(from_row, from_col, from_row - 2, from_col + 1, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
            add_position(from_row, from_col, from_row - 2, from_col - 1, num_rows, num_cols, new_positions, &num_new_positions, min_moves);
        }
        num_cur_positions = num_new_positions;
        for (i = 0; i < num_cur_positions; i++) {
            cur_positions[i] = new_positions[i];
        }
    }
    return -1;
}

void solve(int pawn_row, int pawn_col, int knight_row, int knight_col, int num_rows, int num_cols) {
    int cur_pawn_row, num_moves, knight_takes;
    cur_pawn_row = pawn_row;
    num_moves = 0;
    while (cur_pawn_row < num_rows) {
        knight_takes = find_distance(knight_row, knight_col, cur_pawn_row, pawn_col, num_rows, num_cols);
    if (knight_takes == num_moves) {
      printf("Win in %d knight move(s).\n", num_moves);
      return;
    }
        cur_pawn_row++;
        num_moves++;
    }
    cur_pawn_row = pawn_row;
    num_moves = 0;
    while (cur_pawn_row < num_rows) {
        knight_takes = find_distance(knight_row, knight_col, cur_pawn_row + 1, pawn_col, num_rows, num_cols);
        if (knight_takes == num_moves) {
            printf("Stalemate in %d knight move(s).\n", num_moves);
            return;
        }
        cur_pawn_row++;
        num_moves++;
    }
    printf("Loss in %d knight move(s).\n", num_rows - pawn_row - 1);
}

int main(void) {
    int num_cases, i;
    int num_rows, num_cols, pawn_row, pawn_col, knight_row, knight_col;
    scanf("%d", &num_cases);
    for (i = 0; i < num_cases; i++) {
        scanf("%d%d", &num_rows, &num_cols);
        scanf("%d%d", &pawn_row, &pawn_col);
        scanf("%d%d", &knight_row, &knight_col);
        solve(pawn_row, pawn_col, knight_row, knight_col, num_rows, num_cols);
    }
    return 0;
}
