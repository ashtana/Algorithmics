/*
Задача 2. Прыжки вдоль реки
А теперь рассмотрим задачу, в которой для определения допустимости решений  потребуется жадный алгоритм.
Это задача с платформы POJ под номером 3258.
*/

/*
Условие
Дана река длиной L, вдоль которой лежат камни. Один камень лежит в точке 0 (начало реки), другой в точке L (конец реки), 
а между ними находится еще n камней.
Например, вдоль реки длиной 12 камни могут располагаться в следующих местах: 0, 5, 8 и 12.
Корова начинает с первого камня (локация 0), перепрыгивает оттуда на второй камень, 
потом со второго на третий и так далее, пока не достигает последнего камня в точке L. 
Минимальная длина прыжка равна минимальному расстоянию между любыми двумя соседними камнями. 
В примере выше минимальное расстояние будет 3 (между точками 5 и 8).
Фермеру Джону наскучили короткие прыжки коровы, и он хочет максимально
увеличить их длину. Камни в точках 0 или L он убрать не может, но может удалить m других камней.
Предположим, что в приведенном выше примере Джон может убрать один камень.
В этом случае перед ним стоит выбор — убрать камень из точки 5 или 6. 
Если он уберет его из точки 5, то минимальное расстояние прыжка станет 4 (из 8 в 12). 
Однако если он уберет камень из точки 8, то получит минимальный прыжок большей длины (из 0 в 5).
Задача — максимизация минимальной длины прыжка, которой может добиться фермер, убрав m камней.
*/

/*
Входные данные
Входные данные состоят из одного тестового примера, содержащего следующие строки:
Три целых числа: L — протяженность реки; n — количество камней, не включая начальный и конечный камни; 
m — количество камней, которые Джон может убрать. 
Значение L может находиться в диапазоне от 1 до 1 000 000 000, n — от 0 до 50 000, а m — между 0 и n.
n строк, каждая из которых указывает координату камня. При этом два камня в одном месте оказаться не могут.
*/

/*
Выходные данные
Требуется вывести максимально достижимое минимальное расстояние прыжка.
Для примера выше выводом будет 5.
Время на решение тестового примера — две секунды.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROCKS 50000

int can_make_min_distance(int distance, int rocks[], int num_rocks,
                          int num_remove, int length) {
  int i;
  int removed = 0, prev_rock_location = 0, cur_rock_location;
  if (length < distance)
    return 0;
  for (i = 0; i < num_rocks; i++) {
    cur_rock_location = rocks[i];
    if (cur_rock_location - prev_rock_location < distance)
      removed++;
    else
      prev_rock_location = cur_rock_location;
  }
  if (length - prev_rock_location < distance)
    removed++;
  return removed <= num_remove;
}

void solve(int rocks[], int num_rocks,
           int num_remove, int length) {
  int low, high, mid;
  low = 0;
  high = length + 1;
  while (high - low > 1) {
    mid = (low + high) / 2;
    if (can_make_min_distance(mid, rocks, num_rocks, num_remove, length))
      low = mid;
    else
      high = mid;
  }
  printf("%d\n", low);
}

int compare(const void *v1, const void *v2) {
  int num1 = *(const int *)v1;
  int num2 = *(const int *)v2;
  return num1 - num2;
}

int main(void) {
  static int rocks[MAX_ROCKS];
  int length, num_rocks, num_remove, i;
  scanf("%d%d%d", &length, &num_rocks, &num_remove);
  for (i = 0; i < num_rocks; i++)
    scanf("%d", &rocks[i]);
  qsort(rocks, num_rocks, sizeof(int), compare);
  solve(rocks, num_rocks, num_remove, length);
  return 0;
}
