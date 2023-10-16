#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задача 3. Хоккейное соперничество
// Задача с сайта DMOJ (dmoj.ca) под номером cco18p1

/*
Условие
Команда «Гуси» сыграла n игр, каждая из которых имела один из двух исходов: победа (W) 
или проигрыш (L). Ничейных игр не было. Нам известны исходы всех игр «Гусей», 
а также количество голов, которые они забили в каждой игре. Например, мы знаем, 
что их первая игра закончилась победой (W) и что в ней они забили четыре гола 
(следовательно, их противники забили меньше). Команда «Ястребы» также отыграла n игр, 
в которых либо победила, либо проиграла. В этом случае нам тоже известно, как закончилась 
для них каждая игра и сколько голов они забили. Некоторые игры команды провели друг против друга, 
в то время как остальные — против других соперников.
Информации о том, кто и с кем играл, не дано. Например, мы можем знать, что
«Гуси» победили в определенной игре, забив в ней четыре гола, но нам неизвестно,
с кем именно они играли — это могли быть «Ястребы» или любая другая команда.

Принципиальный матч — это игра, в которой «Гуси» играли против «Ястребов».
Наша задача — определить максимальное число голов, которые могли быть забиты 
в принципиальных матчах. 
*/

/*
Входные данные
Входные данные содержат всего один тестовый пример, но информация приводится в пяти строках:
 *  Первая строка содержит n, количество игр, сыгранных каждой командой. 
    Значение n находится между 1 и 1000.
 *  Вторая строка, содержащая n символов W (победа) и L (поражение), сообщает исход каждой 
    сыгранной «Гусями» игры. К примеру, WLL означает, что команда выиграла первую игру, 
    а затем проиграла вторую и третью.
 *  На третьей строке приводится n целых чисел, сообщающих количество забитых «Гусями» голов 
    в каждой игре. К примеру, 4 1 2 означает, что команда забила четыре гола в первой игре, 
    один во второй и два в третьей.
 *  Четвертая строка подобна второй и сообщает исход каждой игры «Ястребов».
 *  Пятая строка аналогична третьей и указывает количество голов, забитых
    «Ястребами» в каждой игре.
*/

/*
Выходные данные
Следует вывести только одно число — максимальное количество голов, забитых
в возможных принципиальных матчах.
Время на решение тестового примера — одна секунда.
*/

// Решение 3. Динамическое программирование с оптимизацией использования памяти

#define SIZE 1000

int max_v(int v1, int v2) {
   if (v1 > v2) {
      return v1;
   }
   else {
      return v2;
   }
}


int solve(char outcome1[], char outcome2[], int goals1[], int goals2[], int n) {
   int i, j, k;
   int first, second, third, fourth;
   static int previous[SIZE +1], current[SIZE + 1];
   for (i = 0; i <= n; i++) {
      previous[i] = 0;
   }
   for (i = 1; i <= n; i++) {
      for (j = 1; j <= n; j++) {
         if ((outcome1[i] == 'W' && outcome2[j] == 'L' && goals1[i] > goals2[j]) || (outcome1[i] == 'L' && outcome2[j] == 'W' && goals1[i] < goals2[j])) {
            first = previous[j-1] + goals1[i] + goals2[j];
         } else {
            first = 0;
         }
         second = previous[j-1];
         third = previous[j];
         fourth = current[j-1];
         current[j] = max_v(first, max_v(second, max_v(third, fourth)));
      }
      for (k = 0; k <= SIZE; k++) {
         previous[k] = current[k];
      }
   }
   return current[n];
}

int main(void) {
   int i, j, n, result;
   char outcome1[SIZE + 1], outcome2[SIZE + 1];
   int goals1[SIZE + 1], goals2[SIZE + 1];
   scanf("%d ", &n);
   for (i = 1; i <= n; i++) {
      scanf("%c", &outcome1[i]);
   }
   for (i = 1; i <= n; i++) {
      scanf("%d ", &goals1[i]);
   }
   for (i = 1; i <= n; i++) {
      scanf("%c", &outcome2[i]);
   }
   for (i = 1; i <= n; i++) {
      scanf("%d ", &goals2[i]);
   }
   result = solve(outcome1, outcome2, goals1, goals2, n);
   printf("%d\n", result);
   return 0;
}