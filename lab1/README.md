# Словарь и машина Тьюринга

C++17, CMake 3.24+, Ninja, doctest. Для документации — Doxygen в PATH.
Команды выполняются из корня репозитория. При первой настройке скачивается doctest.

## Сборка

```sh
cmake -S lab1 -B lab1/build -G Ninja
cmake --build lab1/build
```

## Тесты

```sh
ctest --test-dir lab1/build --output-on-failure
```

## Словарь

```sh
./lab1/build/dictionary.exe
```

```text
load lab1/examples/dictionary.txt
find apple
add sky небо
replace sky "голубое небо"
find sky
size
list
remove sky
save lab1/build/dictionary.txt
exit
```

В файле словаря сначала указано число записей, затем пары слов. Кавычки позволяют использовать пробелы.
Повторное добавление обновляет перевод. Поиск неизвестного слова сообщает об ошибке.

## Машина Тьюринга

Запуск меню из корня репозитория:

```sh
./lab1/build/turing.exe
```

После появления > команды вводятся по одной строке:

```text
load lab1/examples/unary_increment.txt
rules
show
step
log
exit
```

load загружает пример, rules показывает правила, show — текущее состояние, step выполняет один переход, log выполняет остальные переходы с выводом. Итог примера — 1111, состояние halt, головка в позиции 3. Успешная загрузка возвращает приглашение >.

Для повторного запуска примера снова выполняется load.

Запуск файла без меню:

```sh
./lab1/build/turing.exe lab1/examples/unary_increment.txt -log
```

Этот режим выполняет программу и завершается.

Команды `write POSITION SYMBOL`, `add STATE READ NEXT WRITE L/R/S` и `remove STATE READ` изменяют ленту и правила.
В файле машины записаны состояние и позиция головки, затем лента и таблица правил.
`_` — пустая клетка. `L`, `R`, `S` — влево, вправо, на месте.
Выполнение заканчивается, когда подходящего правила нет.

## Документация

```sh
cmake --build lab1/build --target docs
powershell.exe -NoProfile -Command "Invoke-Item './lab1/build/html/index.html'"
```

## Покрытие (Linux)

GCC и gcovr.

```sh
cmake -S lab1 -B lab1/build -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build lab1/build
ctest --test-dir lab1/build --output-on-failure
gcovr --root . --filter 'lab1/(dictionary|turing|cli)/' --txt --fail-under-line 90.01 lab1/build
```

## Файлы

| Каталог | Содержимое |
| --- | --- |
| dictionary | Dictionary — двоичное дерево слов и переводов |
| turing | Tape, Program, Rule, TuringMachine |
| cli | Меню и точки входа |
| tests | Юнит-тесты, сценарии запуска и настройки тестов |
| examples | Словарь и программа машины |
| CMakeLists.txt | Сборка, тестирование и установка |
| Doxyfile.in | Настройки документации |

## Готовые программы

```sh
cmake --install lab1/build --prefix lab1/build/package
```

В архивах Releases программы запускаются из папки распаковки.
На Linux расширение .exe отсутствует.

[Releases](https://github.com/sonorinne/PPOIS-labs/releases) · [Actions](https://github.com/sonorinne/PPOIS-labs/actions)

Выпуск версий — по тегам `lab1-v*`.
