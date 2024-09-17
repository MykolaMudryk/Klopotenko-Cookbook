#!/bin/bash

touch main.cpp

# Створюємо папки для клієнтської частини
mkdir -p client/src
mkdir -p client/include

# Створюємо файли для клієнтської частини
touch client/src/client.cpp
touch client/src/network_client.cpp
touch client/src/qml_handler.cpp
touch client/include/client.h
touch client/include/network_client.h
touch client/include/qml_handler.h

# Створюємо папки для серверної частини
mkdir -p server/src
mkdir -p server/include

# Створюємо файли для серверної частини
touch server/src/server.cpp
touch server/src/request_handler.cpp
touch server/src/database_handler.cpp
touch server/src/qml_service.cpp
touch server/include/server.h
touch server/include/request_handler.h
touch server/include/database_handler.h
touch server/include/qml_service.h

# Створюємо папки для бази даних
mkdir -p database/src
mkdir -p database/include

# Створюємо файли для роботи з базою даних
touch database/src/database.cpp
touch database/src/query_builder.cpp
touch database/src/connection.cpp
touch database/include/database.h
touch database/include/query_builder.h
touch database/include/connection.h

# Створюємо папки для спільних утиліт
mkdir -p common/src
mkdir -p common/include

# Створюємо файли для спільних утиліт
touch common/src/json_parser.cpp
touch common/src/utility.cpp
touch common/include/common.h
touch common/include/json_parser.h
touch common/include/utility.h

echo "Структура каталогів і файлів успішно створена!"
