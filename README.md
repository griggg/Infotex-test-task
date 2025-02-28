<h1>Инфотекс тестовое задание</h1>

<h2>Структура проекта</h2>

```
/log_library 
    /log_library/liblog.so
    /log_library/log.cpp
    /log_library/log.h
/test_app
    /test_app/main.cpp
    /test_app/test_app
/tests
    /tests/test_logger.cpp
Makefile
README.md
test
```

liblog.so - динамическая библиотека логгера, генерируется make

log.cpp - код логгера

log.h - заголовочные файлы логгера

main.cpp - консольные интерфейс для работы с логгером

test_app - скомпилированный файл main.cpp, генерируется make

test_logger.cpp - тесты логгера

test - скомпилированный test_logger.cpp, генерируется make
    
    
    
<h2>Запуск</h2> 
Находясь в одной директории с Makefile, нужно ввести в консоль:

```
make
LD_LIBRARY_PATH=log_library ./test_app/test_app <log_file> <log_level>
```

Если не сработало, то нужно ввести 

```
./test_app/test_app <log_file> <log_level>
```

log_level = INFO | WARNING | ERROR 

При сборке автоматически запускаются тесты

#   I n f o t e x - t e s t - t a s k 
 
 
