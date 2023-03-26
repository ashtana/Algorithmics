#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Условие
Итак, наступил Хэллоуин, праздник, который начинается с веселых нарядов, сбора 
конфет по соседям, а заканчивается обычно болью в животе из-за переедания сладостей. 
По условиям задачи нужно максимально эффективно собрать все конфеты в домах одного квартала. 
Расположение домов задано, причем выглядит оно весьма необычно:
             O
            / \
           O   O
          /|   |\ 
         O O   7 41
        /| |\
      72 3 6 O
            / \
           O   2
          / \
         O   15
        / \
       4   9

Числами — это дома. Каждое число обозначает количество конфет, которое нас ждет в этом доме. 
Оно может быть одно- или двухзначным. Самый верхний круг является стартовой локацией. 
Круги без чисел представляют перекрестки, где нужно выбирать, в каком направлении продолжать движение. 
Линии, соединяющие круги, — это улицы. Перемещение от круга к кругу соответствует прогулке по одной из улиц. 

Начнем с планирования перемещения по кварталу. Если от верхнего круга двигаться по правой улице, 
то вы попадете на перекресток. Если далее снова выбрать правую улицу, то в итоге вы окажетесь в доме, 
где получите 41 конфету. Затем можно вернуться назад к началу пути. 
Таким образом, в общей сложности будут пройдены 4 улицы и получена 41 конфета.
Однако целью является собрать все конфеты, пройдя при этом минимальное количество улиц. 
Закончить прогулку можно сразу же по окончании сбора всех трофеев, 
то есть возвращаться к стартовой локации не нужно.
*/

/*
Входные данные
Входные данные представлены пятью строками, каждая из которых может содержать не более 255 символов, 
описывающих квартал.
*/

/* 
Выходные данные
Программа должна выводить пять текстовых строк, соответствующих входным.
Каждая строка должна содержать два целых числа, разделенных пробелом: 
количество улиц, пройденных для получения всех конфет, и общее количество собранных конфет.

На расчет всех тестовых примеров дается две секунды.
*/

typedef struct node {
  int candy;
  struct node *left, *right;
} node;

// Вспомогательные функции для создания узлов
node *new_house(int candy) {
  node *house = malloc(sizeof(node));
  if (house == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  house->candy = candy;
  house->left = NULL;
  house->right = NULL;
  return house;
}

node *new_nonhouse(node *left, node *right) {
  node *nonhouse = malloc(sizeof(node));
  if (nonhouse == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  nonhouse->left = left;
  nonhouse->right = right;
  return nonhouse;
}

#define SIZE 255

typedef struct stack
{
  node * values[SIZE];
  int highest_used;
} stack;

// Создание стека
stack *new_stack(void) {
  stack *s = malloc(sizeof(stack)); // выделяем под стек память
  if (s == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  s->highest_used = -1; // -1 это когда вначале пустой стек
  return s;
}

// Добавление элементов в стек
void push_stack(stack *s, node *value) {
  s->highest_used++; // выделяем индекс под новый элемент
  s->values[s->highest_used] = value; // записываем элемент в стек
}

// Удаление элементов из стека
node * pop_stack(stack *s) {
  node * ret = s->values[s->highest_used]; // достаём элемент по последнему индексу
  s->highest_used--; // уменьшаем индекс
  return ret; // возврат элемента
}

// Проверка наличия элементов в стеке
int is_empty_stack(stack *s) { 
  return s->highest_used == -1;
}

// Вычисление общего количества конфет при помощи стека
// int tree_candy(node *tree) {
//   int total = 0;
//   stack *s = new_stack();
//   while (tree != NULL) {
//     if (tree->left && tree->right) {
//       push_stack(s, tree->left);
//       tree = tree->right;
//     } else {
//       total = total + tree->candy;
//       if (is_empty_stack(s))
//         tree = NULL;
//       else
//         tree = pop_stack(s);
//     }
//   }
//   return total;
// }

// Вычисление общего числаи конфет с помощью рекурсии
int tree_candy(node *tree) {
  if (!tree->left && !tree->right) {
    return tree->candy;
  }
  return tree_candy(tree->left) + tree_candy(tree->right);
}

// Вычисление количества узлов
int tree_nodes(node *tree) {
  if (!tree->left && !tree->right)
    return 1;
  return 1 + tree_nodes(tree->left) + tree_nodes(tree->right);
}

// Вычисление количества концевых узлов
int tree_leaves(node *tree) {
  if (!tree->left && !tree->right)
    return 1;
  return tree_leaves(tree->left) + tree_leaves(tree->right);
}

// Вычисление количества улиц при возвращении обратно к корню
int tree_streets(node *tree) {
  if (!tree->left && !tree->right)
    return 0;
  return tree_streets(tree->left) + tree_streets(tree->right) + 4;
}

// Вычисление высоты дерева
int max_value(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

int tree_height(node *tree) {
  if (!tree->left && !tree->right)
    return 0;
  return 1 + max_value(tree_height(tree->left), tree_height(tree->right));
}

// Решение задачи по условию для заданного дерева
void tree_solve(node *tree) {
  int candy = tree_candy(tree);
  int height = tree_height(tree);
  int num_streets = tree_streets(tree) - height;
  printf("%d %d\n", num_streets, candy);
}

// Преобразование строки в дерево
node *read_tree_helper(char *line, int *pos) {
  node *tree;
  tree = malloc(sizeof(node));
  if (tree == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  if (line[*pos] == '(') {
    (*pos)++;
    tree->left = read_tree_helper(line, pos);
    (*pos)++;
    tree->right = read_tree_helper(line, pos);
    (*pos)++;
    return tree;
  } else {
    tree->left = NULL;
    tree->right = NULL;
    tree->candy = line[*pos] - '0';
    (*pos)++;
    if (line[*pos] != ')' && line[*pos] != ' ' && line[*pos] != '\0') {
      tree->candy = tree->candy * 10 + line[*pos] - '0';
      (*pos)++;
    }
    return tree;
  }
}

// Вызов вспомогательной функции с указателем на int
node *read_tree(char *line) {
  int pos = 0;
  return read_tree_helper(line, &pos);
}

#define SIZE 255
#define TEST_CASES 5

int main(void) {
  int i;
  char line[SIZE + 1];
  node *tree;
  for (i = 0; i < TEST_CASES; i++) {
    gets(line);
    tree = read_tree(line);
    tree_solve(tree);
  }
  return 0;
}
