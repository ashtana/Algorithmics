#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Задача 2. Сложносоставные слова
// Рассмотрим задачу под номером 10391 с платформы UV (uva.onlinejudge.org)

/*
Условие
Дан список слов, в котором каждое слово представлено в виде строки в нижнем регистре. 
Например, список, содержащий строки crea, create, open и te. 
Поставлена задача определить, какие из них являются сложносоставными словами, 
то есть представляют конкатенацию двух других строк из списка. 
В приведенном примере данному условию удовлетворит только строка create, потому что состоит из crea и te.
*/

/*
Входные данные
Входные данные содержат одно слово на строку в алфавитном порядке. 
Максимальное число строк — 120 000.
*/

/*
Выходные данные
От нас требуется вывести каждое сложносоставное слово на отдельной строке в алфавитном порядке.
Время решения должно укладываться в три секунды.
*/

// Функция считывая строки
/*на основе https://stackoverflow.com/questions/16870485 */
char *read_line(int size) {
    char *str;
    int ch;
    int len = 0;
    str = malloc(size);
    if (str == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    while ((ch = getchar()) != EOF && (ch != '\n')) // считывания символов
    {
        str[len++] = ch;
        if (len == size) {
            size = size * 2;
            str = realloc(str, size); // удвоит размер массива
            if (str == NULL) {
                fprintf(stderr, "readlloc error\n");
                exit(1);
            }
        }
    }
    str[len] = '\0'; // завершить str нулевым знаком, иначе она окажется недопустимой строкой.
    return str;
}

// Функция которая возвращает хэш для слова
#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

unsigned long oaat(char *key, unsigned long len, unsigned long bits) {
    unsigned long hash, i;
    for (hash = 0, i = 0; i < len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash & hashmask(bits);
}


// Функция для поиска слова
#define NUM_BITS 17

typedef struct word_node
{
    char **word;
    struct word_node *next; 
} word_node;

int in_hash_table(word_node *hash_table[], char *find, unsigned find_len) {
    unsigned word_code;
    word_node *wordptr;
    word_code = oaat(find, find_len, NUM_BITS); // Функция вычисляет хеш-код слова
    wordptr = hash_table[word_code]; // и использует его для нахождения соответствующего связного списка
    while (wordptr)
    {
        if ((strlen(*(wordptr->word)) == find_len) && (strncmp(*(wordptr->word), find, find_len) == 0))
            return 1;
        wordptr = wordptr->next;
    }
    return 0;
}

// Функция для определения сложносоставных слов
void identity_compound_words(char *words[], word_node *hash_table[], int total_words) {
    int i, j;
    unsigned len;
    for (i = 0; i < total_words; i++) { // для каждого слова генерирует все возможные разделения
        len = strlen(words[i]);
        for (j = 1; j < len; j++) { // затем просматривает хеш-таблицу в поиске префикса
            if (in_hash_table(hash_table, words[i], j) && in_hash_table(hash_table, &words[i][j], len - j)) {
                printf("%s\n", words[i]);
                break;
            }
        }
    }
}

#define WORD_LENGTH 16

int main(void) {
    // 1 << NUM_BITS является сокращением для вычисления 2**17, что дает 131 072. 
    // Это наименьшая степень 2, обеспечивающая превышение 120 000 (максимального числа слов для считывания)
    static char *words[1 << NUM_BITS] = {NULL}; // определение размера массива слов
    static word_node *hash_table[1 << NUM_BITS] = {NULL}; // определение размера хэш-таблицы
    int total = 0;
    char *word;
    word_node *wordptr;
    unsigned length, word_code;
    word = read_line(WORD_LENGTH);
    while (*word) {
        words[total] = word; // сохраняем каждое слово в массиве words
        wordptr = malloc(sizeof(word_node));
        if (wordptr == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        length = strlen(word);
        // Хеш-функция oaat требует, чтобы хеш-таблица содержала количество элементов определяемое степенью 2
        word_code = oaat(word, length, NUM_BITS);
        wordptr->word = &words[total];
        wordptr->next = hash_table[word_code]; // в хеш-таблице сохраняем 
        hash_table[word_code] = wordptr; // указатели на слова
        word = read_line(WORD_LENGTH);
        total++;
    }
    // По завершении считывания всех слов происходит вызов функции identify_compound_words, 
    // которая находит и выводит сложносоставные слова.
    identity_compound_words(words, hash_table, total);
    return 0;
}
