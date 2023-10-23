#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задача 2. Лазание по канату
// Рассмотрим задачу с DMOJ(dmoj.ca) под номером wc18c1s3

/*
Условие
На уроке физкультуры одному из учеников, Бобу, нужно взобраться вверх по канату. 
Канат этот бесконечно длинный, но Боба просят забраться только на высоту не менее h метров.
Боб начинает с нулевой высоты. При движении вверх он обучен только одному 
действию — прыжку ровно на j метров. То есть если j равно 5, то он не сможет 
подпрыгнуть на четыре, шесть или любое другое число метров, только на 5. Кроме того, 
Боб умеет спускаться вниз на любое целое число метров: один, два, три и т.д.
Каждое подпрыгивание или спуск считается одним движением. К примеру, если Боб 
подпрыгивает на пять метров, затем спускается на два, потом снова подпрыгивает на 
пять и следом спускается на восемь, то считается, что он совершил четыре действия.
А теперь самая забавная часть условия: Алиса нанесла на некоторые участки каната 
чесоточный порошок. Если такой участок простирается от высоты a до высоты b, 
то весь он, включая конечные точки a и b, считается покрытым порошком. Оказавшись 
на участке с чесоточным порошком, Боб не может ни подпрыгнуть вверх, ни спуститься вниз.
Цель — определить минимальное количество действий, необходимое Бобу для достижения высоты h 
или более.
*/

/*
Входные данные
Входные данные содержат один тестовый пример, состоящий из следующих строк:
  * Строка с целыми числами h, j и n, где h — минимальная высота, которую должен достичь Боб; 
    j — высота его прыжка; n — количество участков, на которые Алиса нанесла чесоточный порошок. 
    Каждое из этих чисел не более 1 000 000, а j меньше или равно h.
  * n строк, каждая из которых содержит два целых числа. 
    Первое число задает высоту начала участка каната, покрытого порошком, 
    а второе — высоту конца этого участка. 
    Каждое из этих чисел не может быть больше h – 1.
*/

/*
Выходные данные
Требуется вывести минимальное количество действий, необходимых Бобу, 
чтобы достичь высоты h или выше. Если такого способа нет, следует вывести –1.
Время на решение тестового примера — четыре секунды.
*/

// #define SIZE 1000000

// typedef int board[SIZE * 2];
// typedef int positions[SIZE * 2];

// void add_position(int from_height, int to_height, int max_height,
//                   positions new_positions, int *num_new_positions,
//                   int itching[], board min_moves) {
//   if (to_height <= max_height && itching[to_height] == 0 &&
//       min_moves[to_height] == -1) {
//     min_moves[to_height] = 1 + min_moves[from_height];
//     new_positions[*num_new_positions] = to_height;
//     (*num_new_positions)++;
//   }
// }

// void find_distances(int target_height, int jump_distance,
//                     int itching[], board min_moves) {
//   static positions cur_positions, new_positions;
//   int num_cur_positions, num_new_positions;
//   int i, j, from_height;
//   for (i = 0; i < target_height * 2; i++)
//     min_moves[i] = -1;
//   min_moves[0] = 0;
//   cur_positions[0] = 0;
//   num_cur_positions = 1;

//   while (num_cur_positions > 0) {
//     num_new_positions = 0;
//     for (i = 0; i < num_cur_positions; i++) {
//       from_height = cur_positions[i];

//       add_position(from_height, from_height + jump_distance,
//                    target_height * 2 - 1,
//                    new_positions, &num_new_positions,
//                    itching, min_moves);
//       for (j = 0; j < from_height; j++)
//         add_position(from_height, j,
//                      target_height * 2 - 1,
//                      new_positions, &num_new_positions,
//                      itching, min_moves);
//     }

//     num_cur_positions = num_new_positions;
//     for (i = 0; i < num_cur_positions; i++)
//       cur_positions[i] = new_positions[i];
//   }
// }

// void solve(int target_height, board min_moves) {
//   int best = -1;
//   int i;
//   for (i = target_height; i < target_height * 2; i++)
//     if (min_moves[i] != -1 && (best == -1 || min_moves[i] < best))
//       best = min_moves[i];
//   printf("%d\n", best);
// }

// int main(void) {
//   int target_height, jump_distance, num_itching_sections;
//   static int itching[SIZE * 2] = {0};
//   static board min_moves;
//   int i, j, itch_start, itch_end;
//   scanf("%d%d%d", &target_height, &jump_distance, &num_itching_sections);
//   for (i = 0; i < num_itching_sections; i++) {
//     scanf("%d%d", &itch_start, &itch_end);
//     for (j = itch_start; j <= itch_end; j++)
//       itching[j] = 1;
//   }
//   find_distances(target_height, jump_distance, itching, min_moves);
//   solve(target_height, min_moves);
//   return 0;
// }

// Решение 2. Модификация
#define SIZE 1000000

typedef struct position {
  int height, state;
} position;

typedef int board[SIZE * 2][2];
typedef position positions[SIZE * 4];

void add_position_up(int from_height, int to_height, int max_height,
                     positions pos, int *num_pos,
                     int itching[], board min_moves) {
  int distance = 1 + min_moves[from_height][0];
  if (to_height <= max_height && itching[to_height] == 0 &&
      (min_moves[to_height][0] == -1 ||
       min_moves[to_height][0] > distance)) {
    min_moves[to_height][0] = distance;
    pos[*num_pos] = (position){to_height, 0};
    (*num_pos)++;
  }
}

void add_position_down(int from_height, int to_height,
                       positions pos, int *num_pos,
                       board min_moves) {
  int distance = min_moves[from_height][1];
  if (to_height >= 0 &&
      (min_moves[to_height][1] == -1 ||
       min_moves[to_height][1] > distance)) {
    min_moves[to_height][1] = distance;
    pos[*num_pos] = (position){to_height, 1};
    (*num_pos)++;
  }
}

void add_position_01(int from_height,
                     positions pos, int *num_pos,
                     board min_moves) {
  int distance = 1 + min_moves[from_height][0];
  if (min_moves[from_height][1] == -1 ||
      min_moves[from_height][1] > distance) {
    min_moves[from_height][1] = distance;
    pos[*num_pos] = (position){from_height, 1};
    (*num_pos)++;
  }
}

void add_position_10(int from_height,
                     positions pos, int *num_pos,
                     int itching[], board min_moves) {
  int distance = min_moves[from_height][1];
  if (itching[from_height] == 0 &&
      (min_moves[from_height][0] == -1 ||
       min_moves[from_height][0] > distance)) {
    min_moves[from_height][0] = distance;
    pos[*num_pos] = (position){from_height, 0};
    (*num_pos)++;
  }
}

void find_distances(int target_height, int jump_distance,
                    int itching[], board min_moves) {
  static positions cur_positions, new_positions;
  int num_cur_positions, num_new_positions;
  int i, j, from_height, from_state;
  for (i = 0; i < target_height * 2; i++)
    for (j = 0; j < 2; j++)
      min_moves[i][j] = -1;
  min_moves[0][0] = 0;
  cur_positions[0] = (position){0, 0};
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;
    for (i = 0; i < num_cur_positions; i++) {
      from_height = cur_positions[i].height;
      from_state = cur_positions[i].state;

      if (from_state == 0) {
        add_position_up(from_height, from_height + jump_distance,
                        target_height * 2 - 1,
                        new_positions, &num_new_positions,
                        itching, min_moves);
        add_position_01(from_height, new_positions, &num_new_positions,
                        min_moves);
      } else {
        add_position_down(from_height, from_height - 1,
                          cur_positions, &num_cur_positions, min_moves);
        add_position_10(from_height,
                        cur_positions, &num_cur_positions,
                        itching, min_moves);
      }
    }

    num_cur_positions = num_new_positions;
    for (i = 0; i < num_cur_positions; i++)
      cur_positions[i] = new_positions[i];
  }
}

void solve(int target_height, board min_moves) {
  int best = -1;
  int i;
  for (i = target_height; i < target_height * 2; i++)
    if (min_moves[i][0] != -1 && (best == -1 || min_moves[i][0] < best))
      best = min_moves[i][0];
  printf("%d\n", best);
}

int main(void) {
  int target_height, jump_distance, num_itching_sections;
  static int itching[SIZE * 2] = {0};
  static board min_moves;
  int i, j, itch_start, itch_end;
  scanf("%d%d%d", &target_height, &jump_distance, &num_itching_sections);
  for (i = 0; i < num_itching_sections; i++) {
    scanf("%d%d", &itch_start, &itch_end);
    for (j = itch_start; j <= itch_end; j++)
      itching[j] = 1;
  }
  find_distances(target_height, jump_distance, itching, min_moves);
  solve(target_height, min_moves);
  return 0;
}
