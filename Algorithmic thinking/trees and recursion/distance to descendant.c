#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Условие
Дано генеалогическое древо и некоторое расстояние d. 
Количество потомков, которые находятся на расстоянии d от узла, определяют его рейтинг 
(количество баллов). Требуется вывести узлы с наиболее высоким рейтингом. 
Чтобы понять условие, взгляните на генеалогическое древо.
*/
/*
Входные данные
Первая строка входных данных представляет число тестовых примеров. 
Каждый пример состоит из следующих строк:
  * строки, содержащей два целых числа, n и d. Число n сообщает, сколько еще 
    строк в этом тестовом примере, а d указывает интересующее нас расстояние 
    до потомков;
  * n строк, используемых для построения дерева. Каждая состоит из имени 
    узла, целого числа m и m имен узлов потомков. Длина имени — не более 
    10 символов. Эти строки могут идти в любом порядке, то есть родители не 
    обязательно будут идти перед потомками.

В каждом тестовом примере может быть не более 1000 узлов.
Ниже представлен пример входных данных, которые сгенерируют дерево.
В примере нужно вывести узлы с наибольшим числом потомков на расстоянии два:

1
7 2
Lucas 1 Enzo
Zara 1 Amber
Sana 2 Gabriel Lucas
Enzo 2 Min Becky
Kevin 2 Jad Cassie
Amber 4 Vlad Sana Ashley Kevin
Vlad 1 Omar
*/
/*
Выходные данные
Вывод для каждого тестового примера содержит две части.
Сначала идет следующая строка:
Tree i:
Здесь i — номер примера.
Затем выводятся имена с максимальным рейтингом (где число баллов узла равно 
количеству потомков, находящихся от него на расстоянии d), упорядоченные по 
убыванию. Имена с одинаковым рейтингом выводятся в алфавитном порядке.
Для определения количества выводимых имен следует руководствоваться двумя правилами:
  * Если имен с потомками на расстоянии d не более трех, то следует выводить их все.
  * Если имен с потомками на расстоянии d более трех, то следует начать с вывода трех, 
    имеющих наиболее высокий рейтинг. Назовем эти имена условно n1, n2 и n3; 
    они сортируются от большего к меньшему. Кроме них следует выводить все имена, 
    чей рейтинг равен рейтингу n3. Например, если у нас есть имена с 
    восемью, восемью, пятью, пятью, пятью и двумя потомками на расстоянии d, 
    мы выведем информацию для пяти имен: с восемью, восемью, пятью, пятью и пятью потомками.

Для каждого подлежащего выводу имени выводится строка, которая содержит само имя, 
затем пробел и затем количество потомков на расстоянии d.
Вывод для каждого тестового примера отделяется от следующего пустой строкой.
Вот как это должно выглядеть для приведенного выше образца входных данных:
Tree 1:
Amber 5
Zara 4
Lucas 2
Время на вычисление всех тестовых примеров составляет одну секунду.
*/

typedef struct node {
  char *name;
  int num_children;
  struct node **children;
  int score;
} node;

// Поиск узла
node *find_node(node *nodes[], int num_nodes, char *name) {
  int i;
  for (i = 0; i < num_nodes; i++) {
    if (strcmp(nodes[i]->name, name) == 0) { // если строки равны функция strcmp вернёт 0
      return nodes[i];
    }  
  }
  return NULL;
}

// Функция malloc с проверкой ошибок
void *malloc_safe(int size) {
  char *mem = malloc(size);
  if (mem == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  return mem;
}

// Создание нового узла
node *new_node(char *name) {
  node *n = malloc_safe(sizeof(node));
  n->name = name;
  n->num_children = 0;
  return n;
}

// Преобразование строк в дерево
#define MAX_NAME 10

int read_tree(node *nodes[], int num_lines) {
  node *parent_node, *child_node;
  char *parent_name, *child_name;
  int i, j, num_children;
  int num_nodes = 0;
  // каждая строка содержит имя родителя и одно или более имён детей. первым обрабатывается родитель.
  for (i = 0; i < num_lines; i++) { // перебор каждой входной строки из num_lines
    parent_name = malloc_safe(MAX_NAME + 1);
    scanf("%s", parent_name);
    scanf("%d", &num_children);
    parent_node = find_node(nodes, num_nodes, parent_name); // определяем встречался ли родитель ранее
    if (parent_node == NULL) {
      parent_node = new_node(parent_name);
      nodes[num_nodes] = parent_node;
      num_nodes++;
    }
    else {
      free(parent_name); // если родитель уже есть в массиве то созданная выше память освобождается
    }
    parent_node->children = malloc_safe(sizeof(node) * num_children); // выделяем память для детей родителя
    parent_node->num_children = num_children; // сохраняем количество связей детей с родителем
    for (j = 0; j < num_children; j++) { // каждый дочерний узел обрабатываем аналогично родительскому
      child_name = malloc_safe(MAX_NAME + 1);
      scanf("%s", child_name);
      child_node = find_node(nodes, num_nodes, child_name);
      if (child_node == NULL) {
        child_node = new_node(child_name);
        nodes[num_nodes] = child_node;
        num_nodes++;
      } else {
        free(child_name);
      }
      parent_node->children[j] = child_node; // указатель на потомка сохраняется в массиве children родителя
    }
  }
  return num_nodes;
}

// Количество потомков одного узла
int score_one(node *n, int d) {
  int total, i;
  if (d == 1)
    return n->num_children;
  total = 0;
  for (i = 0; i < n->num_children; i++)
    total = total + score_one(n->children[i], d - 1);
  return total;
}

// Количество потомков всех узлов
void score_all(node **nodes, int num_nodes, int d) {
  int i;
  for (i = 0; i < num_nodes; i++) {
    nodes[i]->score = score_one(nodes[i], d);
  }
}

// Функция сравнения для упорядочивания
int compare(const void *v1, const void *v2) {
  const node *n1 = *(const node **)v1;
  const node *n2 = *(const node **)v2;
  if (n1->score > n2->score)
    return -1;
  if (n1->score < n2->score)
    return 1;
  // Функция strcmp возвращает отрицательное число, ноль или положительное число, 
  // если первая строка по алфавитному порядку меньше, равна или больше второй строки соответственно.
  return strcmp(n1->name, n2->name);
}

// Вывод узлов 
void output_info(node *nodes[], int num_nodes, int case_num) {
  int i = 0;
  printf("Tree %d:\n", case_num);
  while (i < 3 && i < num_nodes && nodes[i]->score > 0) {
    printf("%s %d\n", nodes[i]->name, nodes[i]->score);
    i++;
    while (i < num_nodes && nodes[i]->score == nodes[i-1]->score) {
      printf("%s %d\n", nodes[i]->name, nodes[i]->score);
      i++;
    }
  }
}

#define MAX_NODES 1000

int main(void) {
  int num_cases, case_num;
  int n, d, num_nodes;
  node **nodes = malloc_safe(sizeof(node) * MAX_NODES); // память для указателей максимального количества узлов
  // Далее идет считывание количества тестовых примеров и однократный перебор каждого
  scanf("%d", &num_cases);
  for (case_num = 1; case_num <= num_cases; case_num++) {
    scanf("%d %d", &n, &d);
    num_nodes = read_tree(nodes, n);
    score_all(nodes, num_nodes, d);
    qsort(nodes, num_nodes, sizeof(node*), compare);
    output_info(nodes, num_nodes, case_num);
    if (case_num < num_cases) // находимся ли мы в последнем тестовом примере
      printf("\n"); // вывод пустой строки между тестами
  }
  return 0;
}

