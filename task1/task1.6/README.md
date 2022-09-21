## Инструкция к запуску

Запуск каждой команды производится из этой директории

### Сборка

```
mkdir build
cd build
cmake ..
make
```

### Запуск тестов

```
cd bin
./tests
```

### Запуск кода

```
cd bin
./market <strategy> <input_file> <output_file>
```

`<strategy>` либо `sell_first`, либо `sell_last`