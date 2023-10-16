#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задача 1. Страсть к бургерам
// Рассмотрим задачу с платформы UV (uva.onlinejudge.org) под номером 10465

/*
Условие
Гомер Симпсон любит поесть и выпить. Ему дано t минут, чтобы съесть несколько 
бургеров и выпить пива. При этом есть два вида бургеров, первый из них можно 
съесть за m минут, а второй за n минут. Гомер больше любит бургеры, чем пиво, 
поэтому он бы предпочел все t минут потратить на еду. Однако это не всегда возможно. 
К примеру, если m = 4, n = 9, а t = 15, то никакая комбинация 4-минутных и 9-минутных 
бургеров не составит в точности 15 минут. В таком случае Гомер затратит максимально 
возможное время на уничтожение бургеров, а в оставшиеся минуты будет пить пиво. 
Задача — определить количество бургеров, которое он в итоге сможет съесть.
*/

/*
Входные данные
Каждый тестовый пример представлен строкой из трех целых чисел: m — количества 
минут на поедание бургера первого вида; n — количества минут на поедание бургера 
второго вида; и t — количества минут, отведенных на бургеры и пиво. Каждое из 
значений m, n и t меньше 10 000.
*/

/*
Выходные данные
Для каждого тестового примера необходимо вывести следующие данные:
    Если Гомер сможет затратить ровно t минут на поедание бургеров, то следует 
    вывести максимальное число съеденных бургеров.
    В противном случае следует вывести максимальное число съеденных бургеров за максимальное время 
    и число оставшихся минут, в течение которых Гомер будет пить пиво.

Время на решение всех тестовых примеров t — три секунды.
*/

int max_v(int v1, int v2) {
    if (v1 > v2)
        return v1;
    else
        return v2;
}

// Решение с помощью рекурсии

// unsigned long long total_calls;

// int solve_t(int m, int n, int t) {
//     total_calls++;
//     if (t == 0) {
//         return 0;
//     }
//     int first, second;
    
//     if (t >= m)
//         first = solve_t(m, n, t - m);
//     else
//         first = -1;
//     if (t >= n)
//         second = solve_t(m, n, t - n);
//     else
//         second = -1;
//     if (first == -1 && second == -1)
//         return -1;
//     return max_v(first, second) + 1;
// }

// функция под чистую рекурсию
// void solve(int m, int n, int t) {
//     int result, i;
//     total_calls = 0;
//     result = solve_t(m, n, t);
//     if (result >= 0)
//         printf("%d\n", result);
//     else {
//         i = t - 1;
//         result = solve_t(m, n, i);
//         while (result == -1) {
//             i--;
//             result = solve_t(m, n, i);
//         }
//         printf("%d %d\n", result, t - i);
//     }
//     printf("Total calls to solve_t: %llu\n", total_calls);
// }

// Решение с мемоизацией

// unsigned long long total_calls;

// int solve_t(int m, int n, int t, int memo[]) {
//     int first, second;
//     total_calls++;

//     if (memo[t] != -2)
//         return memo[t];

//     if (t == 0) {
//         memo[t] = 0;
//         return memo[t];
//     }
    
//     if (t >= m)
//         first = solve_t(m, n, t - m, memo);
//     else
//         first = -1;
//     if (t >= n)
//         second = solve_t(m, n, t - n, memo);
//     else
//         second = -1;
//     if (first == -1 && second == -1) {
//         memo[t] = -1;
//         return memo[t];
//     }
//     else {
//         memo[t] = max_v(first, second) + 1;
//         return memo[t];
//     }
// }

// #define SIZE 10000

// void solve(int m, int n, int t) {
//     int result, i;
//     total_calls = 0;
//     int memo[SIZE];
//     for (i = 0; i <= t; i++)
//         memo[i] = -2;
//     result = solve_t(m, n, t, memo);
//     if (result >= 0)
//         printf("%d\n", result);
//     else {
//         i = t - 1;
//         result = solve_t(m, n, i, memo);
//         while (result == -1) {
//             i--;
//             result = solve_t(m, n, i, memo);
//         }
//         printf("%d %d\n", result, t - i);
//     }
//     printf("Total calls to solve_t: %llu\n", total_calls);
// }

// Решение с добавлением динамического программирования

#define SIZE 10000

void solve(int m, int n, int t) {
    int result, i, first, second;
    int dp[SIZE];
    dp[0] = 0;
    for (i = 1; i <= t; i++) {
        if (i >= m)
            first = dp[i - m];
        else
            first = -1;
        if (i >= n)
            second = dp[i - n];
        else
            second = -1;
        if (first == -1 && second == -1)
            dp[i] = -1;
        else
            dp[i] = max_v(first, second) + 1;
    }
    result = dp[t];
    if (result >= 0)
        printf("%d\n", result);
    else {
        i = t - 1;
        result = dp[i];
        while (result == -1) {
            i--;
            result = dp[i];
        }
        printf("%d %d\n", result, t - i);
    }
}

int main(void) {
    int m, n, t;
    while (scanf("%d%d%d", &m, &n, &t) != -1)
        solve(m, n, t);
    return 0;
}
