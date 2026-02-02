<div align="center">

<img src="https://github.com/FoKey-Junior/Blockchain/blob/main/assets/background.jpg?raw=true" alt="Blockchain Guardian" width="450" style="border-radius: 30px; box-shadow: 0 25px 50px rgba(138, 43, 226, 0.6); margin-bottom: 35px; border: 5px solid rgba(138, 43, 226, 0.4); display: block; margin-left: auto; margin-right: auto;"/>

# 🔗 Blockchain File Transfer System

**Безопасная децентрализованная система передачи файлов через блокчейн**

[![C++](https://img.shields.io/badge/C++-23-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.25+-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![libsodium](https://img.shields.io/badge/libsodium-✓-success.svg)](https://libsodium.org/)

*Профессиональная реализация блокчейна с честной FIFO очередью транзакций*

<div style="margin-top: 20px; font-style: italic; color: #8a2be2; font-size: 0.95em;">
✨ Защищая ваши данные с элегантностью и надежностью ✨
</div>

</div>

---

## 📋 Содержание

- [О проекте](#-о-проекте)
- [Ключевые особенности](#-ключевые-особенности)
- [Архитектура](#-архитектура)
- [Технологии](#-технологии)
- [Установка](#-установка)
- [Использование](#-использование)
- [Тестирование](#-тестирование)
- [Структура проекта](#-структура-проекта)
- [Безопасность](#-безопасность)
- [Вклад в проект](#-вклад-в-проект)

---

## 🎯 О проекте

**Blockchain File Transfer System** — это высокопроизводительная блокчейн-система для безопасной передачи и проверки файлов в децентрализованной сети. Проект реализован с использованием современных стандартов C++23 и следует принципам production-ready разработки.

### Основные принципы

- ✅ **Честность** — FIFO очередь транзакций без скрытых приоритетов
- ✅ **Безопасность** — полная защита памяти (RAII), криптографическая валидация
- ✅ **Надежность** — потокобезопасность, отсутствие гонок данных и утечек памяти
- ✅ **Производительность** — оптимизированная архитектура для высоких нагрузок
- ✅ **Прозрачность** — детерминированный порядок обработки транзакций

---

## ✨ Ключевые особенности

### 🔐 Криптография
- **Ed25519** подписи для транзакций
- **SHA-256** хеширование файлов
- **BLAKE2b** для адресов и блоков
- Полная проверка целостности данных

### 📦 Mempool
- **Честная FIFO очередь** — первый пришел, первый обработан
- **Потокобезопасность** — корректная работа в многопоточной среде
- **Детерминированный порядок** — предсказуемая обработка транзакций
- **Защита от дубликатов** — автоматическая проверка уникальности

### ⛏️ Майнинг/Валидация
- **Без комиссий** — транзакции обрабатываются бесплатно
- **Протокольное вознаграждение** — майнеры получают награду через механизм протокола
- **Быстрое подтверждение** — эффективная обработка транзакций

### 🌐 Сеть
- **P2P архитектура** — децентрализованная сеть узлов
- **Асинхронная обработка** — ASIO для высокопроизводительного I/O
- **Автоматическое обнаружение** — динамическое подключение к сети

### 📁 Передача файлов
- **Проверка целостности** — автоматическая валидация хешей
- **Метаданные** — полная информация о передаваемых файлах
- **Безопасная передача** — криптографическая защита данных

---

## 🏗️ Архитектура

```
┌────────────────────────────────────────────────────────────────────┐
│                         Blockchain Network                         │
├────────────────────────────────────────────────────────────────────┤
│                                                                    │
│         ┌──────────┐      ┌──────────┐      ┌──────────┐           │
│         │   Node   │◄────►│   Node   │◄────►│   Node   │           │
│         └────┬─────┘      └────┬─────┘      └────┬─────┘           │
│              │                 │                 │                 │
│         ┌────▼─────────────────▼─────────────────▼─────┐           │
│         │              Mempool (FIFO Queue)            │           │
│         └──────────────────────┬───────────────────────┘           │
│                                │                                   │
│         ┌──────────────────────▼───────────────────────┐           │
│         │               Miner/Validator                │           │
│         └──────────────────────┬───────────────────────┘           │
│                                │                                   │
│         ┌──────────────────────▼───────────────────────┐           │
│         │                  Blockchain                  │           │
│         │    ┌──────┐  ┌──────┐  ┌──────┐  ┌──────┐    │           │
│         │    │Block │─►│Block │─►│Block │─►│Block │    │           │
│         │    └──────┘  └──────┘  └──────┘  └──────┘    │           │
│         └──────────────────────────────────────────────┘           │
│                                                                    │
└────────────────────────────────────────────────────────────────────┘
```

### Компоненты системы

- **`user`** — управление ключами и адресами
- **`transaction`** — создание и валидация транзакций
- **`mempool`** — честная FIFO очередь транзакций
- **`miner`** — майнинг и валидация блоков
- **`block`** — структура блока с файлами
- **`blockchain`** — цепочка блоков с валидацией
- **`node`** — P2P узел сети
- **`file_sender`** — отправка файлов через блокчейн

---

## 🛠️ Технологии

### Языки и стандарты
- **C++23** — современный стандарт C++
- **CMake 3.25+** — система сборки

### Библиотеки
- **libsodium** — криптографические операции
- **ASIO** — асинхронный сетевой I/O
- **Catch2** — фреймворк для unit-тестов

### Принципы разработки
- **RAII** — управление ресурсами
- **constexpr** — вычисления на этапе компиляции
- **noexcept** — гарантии исключений
- **std::optional** — безопасная обработка опциональных значений
- **enum class** — типобезопасные перечисления

---

## 📦 Установка

### Требования

- **Компилятор** с поддержкой C++23 (GCC 13+, Clang 16+)
- **CMake** 3.25 или выше
- **libsodium** — криптографическая библиотека
- **pkg-config** — для поиска зависимостей

### Linux (Debian/Ubuntu)

```bash
# Установка зависимостей
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libsodium-dev \
    pkg-config \
    libasio-dev

# Клонирование репозитория
git clone https://github.com/yourusername/blockchain-project.git
cd blockchain-project

# Сборка
mkdir build && cd build
cmake ..
make -j$(nproc)

# Запуск сервера
./server
```

### macOS

```bash
# Установка зависимостей через Homebrew
brew install cmake libsodium pkg-config

# Сборка
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)

# Запуск
./server
```

### Сборка с тестами

```bash
cmake -DBUILD_TESTS=ON ..
make -j$(nproc)

# Запуск тестов
ctest --output-on-failure
# или
./Blockchain_tests
```

---

## 🚀 Использование

### Запуск серверного узла

```bash
./server
```

Сервер автоматически:
- Создает genesis блок
- Инициализирует майнера
- Запускает P2P сеть на свободном порту (39150-39199)
- Начинает обработку транзакций

### Создание транзакции

```cpp
#include "user.h"
#include "file_sender.h"
#include "node.h"

// Создание пользователя
user sender;
user receiver;

// Подготовка файлов
std::vector<std::string> file_names = {"document.pdf"};
std::vector<std::string> file_paths = {"/path/to/document.pdf"};

// Отправка
file_sender sender_instance(
    sender.get_address_bytes(),
    receiver.get_address_bytes(),
    std::move(file_names),
    std::move(file_paths),
    sender,
    node_instance
);

sender_instance.prepare_and_send();
```

### Проверка блокчейна

```cpp
#include "blockchain.h"

blockchain chain(miner_address);

// Добавление блока
chain.add_block(transactions);

// Валидация цепочки
if (chain.validate_chain()) {
    // Цепочка валидна
}

// Получение последнего блока
const block& last = chain.get_last_block();
```

---

## 🧪 Тестирование

Проект включает comprehensive unit-тесты для всех ключевых компонентов:

```bash
# Запуск всех тестов
./Blockchain_tests

# Запуск конкретного теста
./Blockchain_tests "[mempool]"

# Запуск с подробным выводом
./Blockchain_tests --success
```

### Покрытие тестами

- ✅ **mempool** — FIFO очередь, потокобезопасность, дубликаты
- ✅ **blockchain** — валидация, добавление блоков, genesis
- ✅ **transaction** — создание, подпись, верификация, сериализация
- ✅ **block** — создание, сериализация, десериализация
- ✅ **crypto_utils** — подписи, верификация, хеширование

---

## 📂 Структура проекта

```
Blockchain/
├── include/                 # Заголовочные файлы
│   ├── types.h             # Базовые типы (address_bytes, hash_bytes)
│   ├── crypto_utils.h      # Криптографические утилиты
│   ├── user.h              # Пользователь/кошелек
│   ├── transaction.h       # Транзакции
│   ├── block.h             # Блоки
│   ├── blockchain.h        # Блокчейн
│   ├── mempool.h           # Mempool (FIFO очередь)
│   ├── miner.h             # Майнер/валидатор
│   ├── file_sender.h       # Отправка файлов
│   ├── node.h              # P2P узел
│   ├── peer.h              # Пиры
│   ├── message.h            # Сообщения сети
│   └── port_utils.h        # Утилиты портов
│
├── src/                     # Исходный код
│   ├── crypto_utils.cpp
│   ├── user.cpp
│   ├── transaction.cpp
│   ├── block.cpp
│   ├── blockchain.cpp
│   ├── mempool.cpp
│   ├── miner.cpp
│   ├── file_sender.cpp
│   ├── node.cpp
│   ├── peer.cpp
│   ├── port_utils.cpp
│   └── main_server.cpp     # Точка входа сервера
│
├── tests/                   # Unit-тесты
│   ├── test_mempool.cpp
│   ├── test_blockchain.cpp
│   ├── test_transaction.cpp
│   ├── test_block.cpp
│   ├── test_crypto_utils.cpp
│   └── main.cpp
│
├── CMakeLists.txt           # Конфигурация сборки
└── README.md               # Документация
```

---

## 🔒 Безопасность

### Реализованные меры

- ✅ **Memory Safety** — RAII, отсутствие new/delete
- ✅ **Thread Safety** — мьютексы, condition variables
- ✅ **Cryptographic Security** — libsodium для всех криптоопераций
- ✅ **Input Validation** — проверка всех входных данных
- ✅ **No UB** — отсутствие неопределенного поведения
- ✅ **Exception Safety** — корректная обработка исключений

### Рекомендации

- Храните приватные ключи в безопасном месте
- Используйте HTTPS для передачи данных между узлами
- Регулярно обновляйте зависимости
- Проверяйте целостность файлов перед обработкой

---

## 🤝 Вклад в проект

Мы приветствуем вклад в развитие проекта! Пожалуйста:

1. Форкните репозиторий
2. Создайте ветку для новой функции (`git checkout -b feature/amazing-feature`)
3. Закоммитьте изменения (`git commit -m 'Add amazing feature'`)
4. Запушьте в ветку (`git push origin feature/amazing-feature`)
5. Откройте Pull Request

### Стандарты кода

- **snake_case** для всех имен
- **C++23** стандарт
- **noexcept** где возможно
- **constexpr** для вычислений на этапе компиляции
- **RAII** для управления ресурсами
- **Unit-тесты** для новой функциональности

---

## 📄 Лицензия

Этот проект распространяется под лицензией MIT. См. файл `LICENSE` для подробностей.

---

## 👥 Авторы

- **Команда разработки** — первоначальная разработка и поддержка

---

## 🙏 Благодарности

- **libsodium** — за отличную криптографическую библиотеку
- **ASIO** — за высокопроизводительный асинхронный I/O
- **Catch2** — за удобный фреймворк тестирования

---

---

<div align="center">

<table>
<tr>
<td align="center" width="50%">
<img src="https://i.pinimg.com/originals/8a/3f/8b/8a3f8b5c5e5e5e5e5e5e5e5e5e5e5e5.jpg" alt="Guardian" width="200" style="border-radius: 20px; box-shadow: 0 10px 25px rgba(138, 43, 226, 0.4); border: 2px solid rgba(138, 43, 226, 0.2);"/>
</td>
<td align="center" width="50%">

**Сделано с ❤️ для децентрализованного будущего**

[⭐ Поставить звезду](https://github.com/yourusername/blockchain-project)  
[🐛 Сообщить об ошибке](https://github.com/yourusername/blockchain-project/issues)  
[💡 Предложить функцию](https://github.com/yourusername/blockchain-project/issues)

*Наш цифровой хранитель всегда на страже ваших данных* 🛡️

</td>
</tr>
</table>

</div>
