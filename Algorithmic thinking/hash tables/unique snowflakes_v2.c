#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Задача 1. Уникальные снежинки
Рассмотрим задачу под номером cco07p2 с сайта DMOJ. */

/* Условие
Дана коллекция снежинок, нужно определить, содержит ли она идентичные снежинки.
Каждая снежинка описывается шестью целыми числами, 
каждое из которых характеризует длину одного ее луча. Вот пример:
3, 9, 15, 2, 1, 10
При этом значения длин лучей могут повторяться, скажем, вот так:
8, 4, 8, 9, 2, 8
Две снежинки идентичны, если они описываются одинаковыми последовательностями чисел 
либо если сходство обнаруживается при перемещении по этим последовательностям влево или вправо.
*/

/* 
Входные данные
Первая строка входных данных является целым числом n, 
описывающим количество сравниваемых снежинок. 
Значение n будет находиться в диапазоне от 1 до 100 000. 
Каждая из следующих n строк характеризует одну снежинку: содержит шесть целых чисел, 
каждое из которых может иметь значение в диапазоне от 0 до 10 000 000.
*/

/*
Выходные данные
На выходе должна быть получена одна текстовая строка:
Если идентичных снежинок не обнаружено, следует вывести:
Нет одинаковых снежинок.
Если есть хотя бы две идентичные снежинки, следует вывести:
Найдены одинаковые снежинки.
Время выполнения вычислений ограничено двумя секундами.
*/

#define SIZE 100000

// Вычисление кода снежинок
int code(int snowflake[]) {
    return (snowflake[0] + snowflake[1] + snowflake[2] + snowflake[3] + snowflake[4] + snowflake[5]) % SIZE;
}

// Реализация связанного списка
typedef struct snowflake_node {
    int snowflake[6];
    struct snowflake_node *next; 
} snowflake_node;

// Определение идентичности снежинок перемещением вправо с вычислением остатка
int identical_right(int snow1[], int snow2[], int start) {
    int offset, snow2_index;
    for(offset = 0; offset < 6; offset++) {
        snow2_index = start + offset;
        // if (snow2_index >= 6) snow2_index = snow2_index - 6;
        if (snow1[offset] != snow2[snow2_index % 6]) return 0;
    }
    return 1;
}

//  Определение идентичности снежинок перемещением влево
int identical_left(int snow1[], int snow2[], int start) {
    int offset, snow2_index;
    for(offset = 0; offset < 6; offset++) {
        snow2_index = start - offset;
        if (snow2_index < 0) snow2_index = snow2_index + 6;
        if (snow1[offset] != snow2[snow2_index]) return 0;
    }
    return 1;
}

// Определение идентичности снежинок
int are_identical(int snow1[], int snow2[]) {
    int start;
    for (start = 0; start < 6; start++) {
        if (identical_right(snow1, snow2, start)) return 1;
        if (identical_left(snow1, snow2, start)) return 1;
    }
    return 0;
}

// Определение идентичных снежинок в связном списке
void identify_identical(snowflake_node *snowflakes[]) {
    snowflake_node *node1, *node2;
    int i;
    for (i = 0; i < SIZE; i++) {
        node1 = snowflakes[i];
        while (node1 != NULL)
        {
            node2 = node1->next;
            while (node2 != NULL)
            {
                if (are_identical(node1->snowflake, node2->snowflake)) {
                    printf("Twin snowflakes found.\n");
                    return;
                }
                node2 = node2->next;
            }
            node1 = node1->next;            
        }        
    }
    printf("No two snowflakes are alike.\n");
}


int main(void) {
    static snowflake_node *snowflakes[SIZE] = {NULL};
    snowflake_node *snow;
    int n, i, j, snowflake_code;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        snow = malloc(sizeof(snowflake_node));
        if (snow == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        for (j = 0; j < 6; j++)
            scanf("%d", &snow->snowflake[j]);
        snowflake_code = code(snow->snowflake);
        snow->next = snowflakes[snowflake_code];
        snowflakes[snowflake_code] = snow;
    }
    identify_identical(snowflakes);
    free(snow);
    system("pause");
    return 0;
}
