# Словарь и машина Тьюринга

C++17, CMake 3.24+, doctest. Для документации — Doxygen в PATH.
Команды выполняются из корня репозитория. При первой настройке скачивается doctest.

## Сборка

```sh
cmake -S lab1 -B build-lab1
cmake --build build-lab1 --config Release
```

## Тесты

```sh
ctest --test-dir build-lab1 -C Release --output-on-failure
```

## Словарь

```sh
./build-lab1/Release/dictionary.exe
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
save build-lab1/dictionary.txt
exit
```

В файле словаря сначала указано число записей, затем пары слов. Кавычки позволяют использовать пробелы.
Повторное добавление обновляет перевод. Поиск неизвестного слова сообщает об ошибке.

## Машина Тьюринга

```sh
./build-lab1/Release/turing.exe lab1/examples/unary_increment.txt -log
```

Пример дописывает единицу к `111`. Итог — `1111`, состояние `halt`, головка в позиции 3.

```sh
./build-lab1/Release/turing.exe
```

```text
load lab1/examples/unary_increment.txt
rules
show
step
log
exit
```

Команды `write POSITION SYMBOL`, `add STATE READ NEXT WRITE L/R/S` и `remove STATE READ` изменяют ленту и правила.
В файле машины записаны состояние и позиция головки, затем лента и таблица правил.
`_` — пустая клетка. `L`, `R`, `S` — влево, вправо, на месте.
Выполнение заканчивается, когда подходящего правила нет.

## Документация

```sh
cmake --build build-lab1 --target docs
explorer.exe build-lab1/html/index.html
```

## Покрытие (Linux)

GCC и gcovr.

```sh
cmake -S lab1 -B build-lab1-coverage -DENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-lab1-coverage
ctest --test-dir build-lab1-coverage --output-on-failure
gcovr --root . --filter 'lab1/(dictionary|turing|cli)/' --txt --fail-under-line 90.01 build-lab1-coverage
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
cmake --install build-lab1 --config Release --prefix build-lab1/package
```

В архивах Releases программы запускаются из папки распаковки.
Для Ninja и Linux каталог `Release` в пути запуска отсутствует. На Linux расширение `.exe` отсутствует.

[Releases](https://github.com/sonorinne/PPOIS-labs/releases) · [Actions](https://github.com/sonorinne/PPOIS-labs/actions)

Выпуск версий — по тегам `lab1-v*`.