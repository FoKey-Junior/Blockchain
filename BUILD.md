# Команды для сборки проекта

## macOS

### 1. Установка зависимостей
```bash
# Установка через Homebrew
brew install libsodium sqlite3 qt@6 cmake

# Или если Qt установлен вручную, убедитесь что он доступен
# Установите переменную окружения QT_DIR если нужно:
# export QT_DIR=/path/to/Qt
```

### 2. Сборка проекта
```bash
# Создаем директорию для сборки
mkdir -p build
cd build

# Генерируем файлы сборки
cmake ..

# Собираем проект
make

# Или если доступен ninja (быстрее)
cmake -GNinja ..
ninja
```

### 3. Запуск
```bash
./Blockchain
```

## Debian/Ubuntu

### 1. Установка зависимостей
```bash
# Обновляем список пакетов
sudo apt-get update

# Устанавливаем необходимые пакеты
sudo apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libsodium-dev \
    libsqlite3-dev \
    libasio-dev \
    libcrow-dev
```

**Примечание:** Если `libasio-dev` или `libcrow-dev` недоступны в репозиториях, их можно установить вручную:
- ASIO - header-only библиотека, можно скачать и установить в `/usr/local/include`
- Crow - header-only библиотека, можно скачать с GitHub и установить в `/usr/local/include`

### 2. Сборка проекта
```bash
# Создаем директорию для сборки
mkdir -p build
cd build

# Генерируем файлы сборки
cmake ..

# Собираем проект
make

# Или используя больше потоков для ускорения
make -j$(nproc)

# Или если доступен ninja (быстрее)
cmake -GNinja ..
ninja
```

### 3. Запуск сервера
```bash
./server
```

## Проверка сборки

### macOS
```bash
# Проверяем что собран правильный файл
ls -lh build/Blockchain
file build/Blockchain
```

### Debian
```bash
# Проверяем что собран правильный файл (server, а не Blockchain)
ls -lh build/server
file build/server

# Убеждаемся что используется main_server.cpp
strings build/server | grep -i "server node started"
```

## Переменные окружения (опционально)

### macOS
```bash
# Если Qt установлен нестандартным образом
export QT_DIR=/path/to/Qt

# Если ASIO установлен вручную
export ASIO_ROOT=/path/to/asio

# Если Crow установлен вручную
export CROW_ROOT=/path/to/crow
```

### Debian
```bash
# Если ASIO установлен вручную
export ASIO_ROOT=/path/to/asio

# Если Crow установлен вручную
export CROW_ROOT=/path/to/crow
```

## Очистка

```bash
# Удалить директорию сборки
rm -rf build

# Или только пересобрать
cd build
make clean
```

## Отладка

Если сборка не удается, проверьте:
1. Все зависимости установлены
2. CMake находит все библиотеки (проверьте вывод `cmake ..`)
3. Компилятор поддерживает C++23
4. Правильные права доступа
