// Задача 2. Дорога к бабушке
// Рассмотрим задачу с платформы DMOJ(dmoj.ca) под номером saco08p3

/*
Условие
Брюс планирует путешествие до дома своей бабушки. Есть n городов, пронумерованных от 1 до n. 
Брюс начинает путь в городе 1, а бабушка живет в городе n. Между каждой парой городов есть дорога 
определенной длины. По пути к бабушке Брюсу надо купить коробку печенья. 
В некоторых городах есть кондитерские, и Брюсу необходимо заехать хотя бы в один такой город.
Во-первых, требуется определить минимальное расстояние, которое Брюсу нужно преодолеть, 
чтобы попасть от стартовой точки в дом бабушки, купив по пути печенье. 
Этот параметр не сообщает нам, сколько у Брюса есть вариантов попасть к старушке. 
Возможно, есть всего один способ, а все остальные маршруты требуют преодоления большего расстояния. 
Также возможно, что есть несколько одинаково коротких путей. 
Во-вторых, задача требует определить количество маршрутов минимальной длины.
*/

/*
Входные данные
Входные данные содержат один тестовый пример, состоящий из следующих строк:
 - Целого числа n, указывающего количество городов. Города пронумерованы от 1 до n. 
Всего может быть от 2 до 700 городов.
 - n строк, каждая из которых содержит n чисел. Первая из этих строк сообщает протяженность дорог 
от города 1 до каждого города (города 1, города 2 и т. д.). Вторая строка указывает протяженность дорог 
от города 2 до каждого города, и т. д. Расстояния от городов до них самих равны нулю. 
Любое другое расстояние не меньше 1. Расстояние от города a до города b равно расстоянию от города b до города a.
 - Целого числа m, отражающего количество городов с кондитерскими. Значение m не меньше единицы.
 - Строки, содержащей m целых чисел — номеров городов с кондитерскими.
*/

/*
Выходные данные
Нам необходимо вывести на одной строке минимальное расстояние от города 1 до города n 
(при условии попутной покупки печенья) и отделенное пробелом количество маршрутов с минимальной дистанцией 
по модулю 1 000 000.

Время на решение тестового примера — одна секунда.
*/

// Решение с вычислением количества кратчайших путей

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOWNS 700

typedef struct edge {
  int to_town, length;
  struct edge *next;
} edge;

void solve(edge *adj_list[], int num_towns, int store[]) {
  static int done[MAX_TOWNS + 1][2];
  static int min_distances[MAX_TOWNS + 1][2];
  static int num_paths[MAX_TOWNS + 1][2];  // массив для записи количества кратчайших путей
  int i, j, state, found;
  int min_distance, min_town_index, min_state_index, old_distance;
  edge *e;

  for (state = 0; state <= 1; state++)
    for (i = 1; i <= num_towns; i++) {
      done[i][state] = 0;
      min_distances[i][state] = -1;
      num_paths[i][state] = 0; // установка начальных значений в 0
  }
  min_distances[1][0] = 0;
  num_paths[1][0] = 1;  // счёт с 1 количества путей со стартовой вершины до самой себя

  for (i = 0; i < num_towns * 2; i++) {
    min_distance = -1;
    found = 0;
    for (state = 0; state <= 1; state++)
      for (j = 1; j <= num_towns; j++) {
        if (!done[j][state] && min_distances[j][state] >= 0) {
          if (min_distance == -1 || min_distances[j][state] < min_distance) {
            min_distance = min_distances[j][state];
            min_town_index = j;
            min_state_index = state;
            found = 1;
          }
        }
      }
    if (!found)
      break;
    done[min_town_index][min_state_index] = 1;

    if (min_state_index == 0 && store[min_town_index]) {
      old_distance = min_distances[min_town_index][1];
      if (old_distance == -1 || old_distance >= min_distance) { // >= иначе не будет возможности накапливать кратчайшие пути
        min_distances[min_town_index][1] = min_distance;
        if (old_distance == min_distance) // Если кратчайший путь остается прежним
          num_paths[min_town_index][1] += num_paths[min_town_index][0]; // прибавить путь
        else
          num_paths[min_town_index][1] = num_paths[min_town_index][0];
        num_paths[min_town_index][1] %= 1000000; // чтобы количество кратчайших путей не превысило 1000000
      }
    } else {
      e = adj_list[min_town_index];
      while (e) {
        old_distance = min_distances[e->to_town][min_state_index];
        if (old_distance == -1 ||
            old_distance >= min_distance + e->length) {
          min_distances[e->to_town][min_state_index] = min_distance +
                                                       e->length;
          if (old_distance == min_distance + e->length) // Ребра, которые исходят из текущей вершины
            num_paths[e->to_town][min_state_index] +=
                num_paths[min_town_index][min_state_index];
          else
            num_paths[e->to_town][min_state_index] =
                num_paths[min_town_index][min_state_index];
          num_paths[e->to_town][min_state_index] %= 1000000; // кол-во кратчайших путей не превысило 1000000
        }
        e = e->next;
      }
    }
  }
  printf("%d %d\n", min_distances[num_towns][1], num_paths[num_towns][1]); // Выводим также кол-во кратч.путей
}

int main(void) {
  static edge *adj_list[MAX_TOWNS + 1] = {NULL};
  int i, num_towns, from_town, to_town, length;
  int num_stores, store_num;
  static int store[MAX_TOWNS + 1] = {0};
  edge *e;

  scanf("%d", &num_towns);
  for (from_town = 1; from_town <= num_towns; from_town++)
    for (to_town = 1; to_town <= num_towns; to_town++) {
      scanf("%d", &length);
      if (from_town != to_town) {
        e = malloc(sizeof(edge));
        if (e == NULL) {
          fprintf(stderr, "malloc error\n");
          exit(1);
        }
        e->to_town = to_town;
        e->length = length;
        e->next = adj_list[from_town];
        adj_list[from_town] = e;
      }
    }

  scanf("%d", &num_stores);
  for (i = 1; i <= num_stores; i++) {
    scanf("%d", &store_num);
    store[store_num] = 1;
  }
  solve(adj_list, num_towns, store);
  return 0;
}
