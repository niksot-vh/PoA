#!/bin/bash
set -eux

BINARY="usr/local/bin/poapr"

if [ ! -f "$BINARY" ]; then
  echo "Ошибка: бинарник не найден по пути $BINARY"
  exit 1
fi

# Ввод для теста
INPUT="10
1 2 4 6 5 7 8 9 3 10
"

# Ожидаемый вывод на русском
EXPECTED="Часть 1: чётных чисел нет
Часть 2: среднее арифметическое чётных чисел = 5.00
Часть 3: чётных чисел нет"

# Запуск программы с вводом через here-document
RESULT=$(echo "$INPUT" | "$BINARY" | sed '/Введите/d' | sed '/целых чисел массива/d')

if [ "$RESULT" == "$EXPECTED" ]; then
  echo "Тест пройден"
else
  echo "Тест не пройден"
  echo "Ожидалось:"
  echo "$EXPECTED"
  echo "Получено:"
  echo "$RESULT"
  exit 1
fi

