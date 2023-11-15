#include <iostream>
using namespace std; // видимость имён из std без std:: (§2.4.2 Глава 14)
#include <complex>
#include <vector>

using namespace std; // видимость имён из std без std::

// Пример функции
double square(double x) { // возвести в квадрат число типа double
    return x*x;
}

void print_square(double x) {
    cout << "the square of " << x << " is " << square(x) << "\n";
}

// Главная функция откуда начинает работу программа
int main() {  // (§15.4)
    print_square(1.234); // печать: квадрат 1.234 есть 1.52276

    // Написать здесь любой код который идёт ниже, чтобы увидеть как он отработает
}

// §2.2.2. Типы, переменные и арифметические операции
// int inch; декларирует что inch имеет тип int, т.е. inch - это целая переменная
// Объявление - это оператор, который вводит имя в программу. 
// Он специфицирует тип для именованной сущности:
// Тип определяет набор допустимых значений и операций над объектом
// Объект есть блок памяти, содержащий значение для некоторого типа
// Значение - это набор битов информации, интерпретируемый согласно типу
// Переменная - это именованнывй объект

// bool - логический тип, возможные значения true или false
// char - символьный тип, например 'a', 'г', '9'
// int - целое число, например 1, 11, 456 и т.п.
// double - число с плавающей точкой двойной точности, например 3.14 и 299793.0
// sizeof(<подставить название типа>) возвращает размер типа в байтах
// Арифметические операции
// x+y
// +x унарный плюс
// x-y
// -x унарный минус
// x*y умножить
// x/y поделить
// x%y остаток(модуль) для целых чисел

// Операции сравнения
// x==y  // равно
// x!=y  // не равно
// x<y
// x>y
// x<=y
// x>=y

// В языке C++ для присваиваний и арифметических операций выполняются все имеющие смысл 
// преобразования (§10.5.3) между базовыми типами, так что их можно свобоно смешивать:
void some_function() { // у функции нет возврата
    double d = 2.2; // инициализация double
    int i = 7; // инициализация int
    d = d+i; // присвоить d значение суммы
    i = d*i; // присвоть i значение d*i с усечением до целого
}

// два способа инициализации
double d1 = 2.3; // через знак =
double d2 {2.3}; // списковая форма

complex<double> z = 1; // комплексное число со скалярами двойной точности
complex<double> z2 {d1, d2};
complex<double> z3 = {1,2}; // необязательно с {...}
vector<int> v {1,2,3,4,5,6}; // вектор целых чисел

// Применение знака = традиционно восходит к языку C, но в сомнительных ситуациях использовать
// лучше общую форму {}-списковую форму (§6.3.5.2)
// Списковая форма предохранит от преобразований, теряющих информацию(сужающих преобразований)
// (§10.5)
int i1 = 7.2;
int i2 {7.2};  // ошибка: конверсия в целое из числа с плавающей точкой
int i3 = {7.2};  // тоже самое ошибка и знак = - избыточен

// Пользовательские типы (такие как string, vector, Matrix, Motor_controller или Orc_warrior)
// можно определить так, что станет возможной неявная инициализация (§3.2.1.1)

// При определении переменной нет необходимости явно специфицировать тип, если его можно вывести из
// инициализирующего значения:
auto b = true; // bool
auto z = sqrt(i1); // z имеет тип возврата sqrt(i1)

// Применяем auto, используем синтаксис со знаком =, 
// поскольку при этом отсутствует преобразование типов, которое может породить проблемы

// Специфические операции для изменения значения переменной
// x+=y -> x = x+y
// ++x -> инкремент x = x + 1
// x-=y -> x = x-y
// -x -> декремент x = x-1
// x*=y -> масштабирование x = x*y
// x/=y -> масштабирование x = x/y
// x%=y -> x = x%y

// §2.2.3. Константы
// const примерно означает "обещаю не изменять эту величину".
// Применяется приемущественно на уровне интерфейсов, так что можно передавать в функции данные, 
// не опасаясь того, что там они будут модифицированы. Компилятор проверяет обещание не изменять 
// данные в переменной которая была обозначена как const
// constexpr примерно означает "подлежит вычислению во время компиляции".
// Применяется преимущественно для констант, позволяет размещать данные в памяти, где маловероятна
// их порча, а также ради производительности.
// Например:
const int dmv = 17; // dmv это именованная константа
int var = 17; // var не константа
constexpr double max1 = 1.4*square(dmv); // Будет ОК если square(17) это константа
constexpr double max2 = 1.4*square(var); // Ошибка var не константа
const double max3 = 1.4*square(var); // ОК, вычисляется при выполнении
double sum(const vector<double>&); // sum не изменяет аргумент (§2.2.5)
vector<double> v {1.2, 3.4, 4.5}; // v не константа
const double s1 = sum(v); // вычисляется при выполнении если существует преобразование
constexpr double s2 = sum(v); // ошибка: sum(v) не констант. выраж-е

// Чтобы функцию можно было использовать в константном выражении, то есть в выражении, 
// вычисляемом компилятором, её нужно определить с модификатором constexpr
constexpr double square(double x) {return x*x;}

/* В этом случае функция должна быть достаточно простой: всего лишь оператор return, 
вычисляющий и возвращающий значение. Такую функцию можно использовать с неконстантными 
аргументами, но тогда результат не является константным выражением. Это разрешается делать 
в случаях, не требующих константных выражений, так что не нужно определять практически 
идентичную функцию дважды: Один раз для константных выражений и второй раз для переменных.

В небольшом количестве случаев константные выражения требуются в соответствии с правилами языка
(границы массивов (§2.2.5, §7.3), case-метки (§2.2.4, §9.4.2), ряд аргументов шаблонов (§25.2) и
константы, объявленные с constexpr). В остальных случаях вычисления во время компиляции актуальны
для производительности. Кроме того, в независимости от вопросов эффективности концепция 
неизменяемости (для объекта с неизменным состоянием) является важной концепцией проектирования
(§10.4).
*/

// §2.2.4 Операторы выбора и циклы
