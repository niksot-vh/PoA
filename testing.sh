#!/bin/bash
set -eux

BINARY="usr/local/bin/poapr"

if [ ! -f "$BINARY" ]; then
  echo "Ошибка: бинарник не найден по пути $BINARY"
  exit 1
fi

# Пример теста: массив из 10 элементов
# Минимум = 1, Максимум = 10
INPUT="10
1 2 4 6 5 7 8 9 3 10
"

# Ожидаемый результат (зависит от разбиения на три части)
# Часть 1: элементы до минимума (нет, так как минимум в начале)
# Часть 2: между min и max
# Часть 3: после max (нет)
EXPECTED="Part 1: no even numbers
Part 2: average of even values = 5.00
Part 3: no even numbers"

# Запуск программы с "вводом" через here-document
RESULT=$(echo "$INPUT" | "$BINARY" | sed '/Enter/d' | sed '/integers/d' | sed '/must/d' | sed '/Expected/d' | sed '/Failed/d' | sed '/Invalid/d' )

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

