#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Заданный массив целых чисел А делится на три части двумя элементами: 
максимальным и минимальным. Взаимное расположение максимума и минимума
может быть любым. Определить среднее арифметическое четных значений 
в каждой части массива. Использовать функции для нахождения положения 
минимального и максимального элементов и подсчёта среднего в одной 
части массива. Массивы, состоящие из одинаковых элементов, а также массивы,
в которых более одного элемента имеют максимальное или минимальное значение,
признаются некорректными
*/

// Считывает ровно n целых чисел в массив a.
bool read_array(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1) return false;
    }
    return true;
}

/* Находит уникальные позиции минимального и максимального элементов.
При успехе записывает индексы в *pos_min и *pos_max */
bool find_unique_min_max(const int *a, int n, int *pos_min, int *pos_max) {
    int min_val = a[0], max_val = a[0];
    *pos_min = 0; *pos_max = 0;

    for (int i = 1; i < n; ++i) {
        if (a[i] < min_val) { min_val = a[i]; *pos_min = i; }
        if (a[i] > max_val) { max_val = a[i]; *pos_max = i; }
    }

    int cnt_min = 0, cnt_max = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == min_val) ++cnt_min;
        if (a[i] == max_val) ++cnt_max;
    }

    if (min_val == max_val || cnt_min > 1 || cnt_max > 1) return false;
    return true;
}

/* Вычисляет среднее арифметическое чётных значений в диапазоне a[l..r] */
double avg_even_in_range(const int *a, int n, int l, int r, int *out_count) {
    if (l < 0) l = 0;
    if (r >= n) r = n - 1;
    if (l > r) { *out_count = 0; return 0.0; }

    long long sum = 0;
    int cnt = 0;
    for (int i = l; i <= r; ++i) {
        if ((a[i] % 2) == 0) { sum += a[i]; ++cnt; }
    }
    *out_count = cnt;
    return cnt ? (double)sum / cnt : 0.0;
}

// Печать результата для части
void print_part(int idx, double avg, int count) {
    if (count > 0)
        printf("Часть %d: среднее арифметическое чётных чисел = %.2f\n", idx, avg);
    else
        printf("Часть %d: чётных чисел нет\n", idx);
}

int main() {
    int n;
    printf("Введите размер массива N: "); fflush(stdout);
    if (scanf("%d", &n) != 1) {
        printf("Ошибка: ожидается целое число N\n");
        return 0;
    }
    if (n <= 0) {
        printf("Ошибка: N должно быть положительным\n");
        return 0;
    }

    int *a = malloc(sizeof(int) * n);
    if (!a) { perror("malloc"); return 1; }

    printf("Введите %d целых чисел массива (через пробел или перенос строки):\n", n);
    fflush(stdout);
    if (!read_array(a, n)) {
        printf("Ошибка ввода элементов массива\n");
        free(a); return 1;
    }

    int pos_min, pos_max;
    if (!find_unique_min_max(a, n, &pos_min, &pos_max)) {
        printf("Некорректный ввод: все элементы одинаковы или min/max не уникальны\n");
        free(a);
        return 0;
    }

    int p = pos_min < pos_max ? pos_min : pos_max;
    int q = pos_min < pos_max ? pos_max : pos_min;

    int c1, c2, c3;
    double avg1 = avg_even_in_range(a, n, 0, p - 1, &c1);
    double avg2 = avg_even_in_range(a, n, p + 1, q - 1, &c2);
    double avg3 = avg_even_in_range(a, n, q + 1, n - 1, &c3);

    print_part(1, avg1, c1);
    print_part(2, avg2, c2);
    print_part(3, avg3, c3);

    free(a);
    return 0;
}
