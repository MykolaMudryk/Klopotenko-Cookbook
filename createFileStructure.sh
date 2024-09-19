#!/bin/bash

touch main.cpp

# Створюємо папки для клієнтської частини
mkdir -p client/src
mkdir -p client/include

# Створюємо файли для клієнтської частини
touch client/src/client.cpp
touch client/src/network_client.cpp
touch client/src/qml_handler.cpp
touch client/src/json_parser.cpp
touch client/include/client.h
touch client/include/network_client.h
touch client/include/qml_handler.h
touch client/include/json_parser.h

# Створюємо папки для серверної частини
mkdir -p server/src
mkdir -p server/include

# Створюємо файли для серверної частини
touch server/src/server.cpp
touch server/src/request_handler.cpp
touch server/src/database_handler.cpp
touch server/include/server.h
touch server/include/request_handler.h
touch server/include/database_handler.h

echo "Структура каталогів і файлів успішно створена!"
