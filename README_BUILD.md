# Инструкции по сборке

## Требования

### Для macOS:
- Qt 6 (или Qt 5) - установлен через Homebrew или с официального сайта
- libsodium: `brew install libsodium`
- sqlite3: `brew install sqlite3`
- CMake 3.25 или выше

### Для Debian/Ubuntu:
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libsodium-dev \
    libsqlite3-dev \
    pkg-config
```

## Сборка

### macOS:
```bash
mkdir build
cd build
cmake ..
make
```

Если Qt не найден автоматически, укажите путь:
```bash
cmake -DCMAKE_PREFIX_PATH=/path/to/Qt/lib/cmake ..
```

Или установите Qt через Homebrew:
```bash
brew install qt@6
```

### Debian/Ubuntu:
```bash
mkdir build
cd build
cmake ..
make
```

## Переменные окружения

- `QT_DIR` - путь к директории Qt (для macOS)
- `ASIO_ROOT` - путь к ASIO (опционально)
- `CROW_ROOT` - путь к Crow (опционально)

## Примечания

- ASIO - header-only библиотека, обычно находится автоматически
- Crow - header-only библиотека, должна быть установлена в стандартных местах или через пакетный менеджер
