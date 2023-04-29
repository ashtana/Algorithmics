#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Условие
Вы хотите купить яблоки в магазине. На яблоки установлена фиксированная цена, 
к примеру $1.75 за штуку. Помимо этого, у магазина есть m ценовых схем, в каждой 
из которых установлена стоимость p за n яблок. Например, в одной схеме три яблока 
стоят $4.00, в другой схеме два яблока стоят $2.50. Вам нужно купить не менее k 
яблок по наименьшей цене.
*/

/*
Входные данные
Каждый тестовый пример состоит из следующих строк:
    1) Цена за одно яблоко и число ценовых схем m для данного примера. 
    Максимальное значение m равно 20.
    2) m строк, в каждой из которых указано число яблок n и их общая стоимость p. 
    Значение n находится в диапазоне между 1 и 100.
    3) Строки с числами k, указывающими количество яблок, которое нужно купить. 
    Их значения находятся между 0 и 100.

Каждая цена во входных данных представлена числом с плавающей точкой 
и имеет два десятичных знака.
В описании задачи я привел в качестве примера цены за яблоко $1.75. Помимо этого, 
приведены две ценовые схемы: три яблока за $4.00 и два яблока за $2.50. Предположим, 
что нужно определить минимальные стоимости при покупке не менее одного 
и при покупке не менее четырех яблок. Вот входные данные для этого примера:
1.75 2
3 4.00
2 2.50
1 4
*/

/*
Выходные данные
Для каждого тестового примера требуется вывести следующее:
    1) Номер примера Case c:, где с является номером тестового примера, отсчет 
    номеров начинается с 1.
    2) Для каждого числа k — фразу Buy k for $d (купить k за $d), 
    где d будет самым дешевым вариантом покупки не менее k яблок.

Вот каким будет вывод для приведенных выше входных данных:
Case 1:
Buy 1 for $1.75
Buy 4 for $5.00

Время на решение всех тестовых примеров — три секунды.
*/

// Решение 1 через рекурсию

#define SIZE 200
#define MAX_SCHEMES 20

double min_v(double v1, double v2) {
  if (v1 < v2)
    return v1;
  else
    return v2;
}

double solve_k(int num[], double price[], int num_schemes,
               double unit_price, int num_items) {
  double best, result;
  int i;
  if (num_items == 0)
    return 0;
  else {
    result = solve_k(num, price, num_schemes, unit_price,
                         num_items - 1);
    best = result + unit_price;
    for (i = 0; i < num_schemes; i++)
      if (num_items - num[i] >= 0) {
        result = solve_k(num, price, num_schemes, unit_price,
                             num_items - num[i]);
        best = min_v(best, result + price[i]);
      }
        return best;
  }
}

double solve(int num[], double price[], int num_schemes,
             double unit_price, int num_items) {
  double best;
  int i;
  best = solve_k(num, price, num_schemes, unit_price, num_items);
  for (i = num_items + 1; i < SIZE; i++)
    best = min_v(best, solve_k(num, price, num_schemes,
                             unit_price, i));
  return best;
}

int get_number(int *num) {
  int ch;
  int ret = 0;
  ch = getchar();
  while (ch != ' ' && ch != '\n') {
    ret = ret * 10 + ch - '0';
    ch = getchar();
  }
  *num = ret;
  return ch == ' ';
}

int main(void) {
  int test_case, num_schemes, num_items, more, i;
  double unit_price, result;
  int num[MAX_SCHEMES];
  double price[MAX_SCHEMES];
  test_case = 0;
  while (scanf("%lf%d", &unit_price, &num_schemes) != -1) {
    test_case++;
    for (i = 0; i < num_schemes; i++)
      scanf("%d%lf", &num[i], &price[i]);
    scanf(" ");
    printf("Case %d:\n", test_case);
    more = get_number(&num_items);
    while (more) {
      result = solve(num, price, num_schemes, unit_price,
                     num_items);
      printf("Buy %d for $%.2f\n", num_items, result);
      more = get_number(&num_items);
    }
    result = solve(num, price, num_schemes, unit_price,
                   num_items);
    printf("Buy %d for $%.2f\n", num_items, result);
  }
  return 0;
}
