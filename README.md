# DIST_lab4 - Лабораторная работа 4: Шифрование/дешифрование файлов

**DIST_lab4** — консольное приложение для рекурсивного шифрования и дешифрования всех файлов в указанной директории и её подпапках с использованием алгоритма AES-256.

## Постановка задачи

Реализовать программу шифрования и дешифрования файлов.  
Использовать паттерн Singleton для управления процессом.

## Возможности

- Рекурсивное шифрование (`encrypt`) и дешифрование (`decrypt`) всех файлов внутри указанной папки.
- Обход директорий реализован с помощью `dirent.h`.
- Алгоритм AES-256 CBC реализован через OpenSSL.
- Использован паттерн проектирования **Singleton** для централизованного управления процессом шифрования и дешифрования.
- Отдельный модуль `DirSearch` для рекурсивного сбора файлов по пути.
- Простая консольная команда с тремя аргументами: режим, путь, пароль.

## Требования

- ОС Linux
- CMake версии 3.10 и выше  
- Компилятор с поддержкой C++17 (g++ 7+)  
- Библиотека OpenSSL с заголовочными файлами (dev-пакет)

## Установка зависимостей

```bash
sudo apt update
sudo apt install -y build-essential cmake libssl-dev
```

## Сборка проекта

```bash
git clone <адрес_репозитория>
cd DIST_lab4
mkdir build && cd build
cmake ..
make
```

## Запуск и использование

```bash
./main encrypt <путь_к_папке_или_файлу> <пароль>
./main decrypt <путь_к_папке_или_файлу> <пароль>
```

- `<путь_к_папке_или_файлу>` — абсолютный или относительный путь к директории или отдельному файлу.
- `<пароль>` — ключ для AES-256 (максимум 32 байта).

## Структура проекта

```bash
DIST_lab4/
├── CMakeLists.txt
├── includes/               # Заголовочные файлы
│   ├── aes_encrypt.h
│   ├── dirsearch.h
│   └── singleton.h
├── src/
│   ├── aes_encrypt.cpp     # Реализация AES-256 шифрования через OpenSSL
│   ├── dirsearch.cpp       # Реализация рекурсивного обхода папок через dirent.h
│   ├── singleton.cpp       # Singleton класс, управляющий шифрованием/дешифрованием
│   └── main.cpp            # Основной файл с разбором аргументов и вызовом Singleton
└── README.md
```
