# Установка Crow для Debian/Ubuntu (если нужен API сервер)

Crow не требуется для серверной версии (main_server.cpp), но если вы хотите использовать API сервер, нужно установить Crow вручную.

## Способ 1: Установка из исходников

```bash
# Установка зависимостей для компиляции Crow
apt-get install -y git build-essential

# Клонируем Crow репозиторий
cd /tmp
git clone https://github.com/CrowCpp/Crow.git
cd Crow

# Копируем заголовочные файлы в системную директорию
mkdir -p /usr/local/include/crow
cp include/crow.h /usr/local/include/
cp include/crow/*.h /usr/local/include/crow/

# Очистка
cd ..
rm -rf Crow

# Теперь можно собирать проект
```

## Способ 2: Использование переменной окружения

```bash
# Скачиваем Crow
cd /tmp
git clone https://github.com/CrowCpp/Crow.git
cd Crow

# Экспортируем переменную окружения
export CROW_ROOT=/tmp/Crow

# Теперь можно собирать проект
cd ~/projects/Blockchain/build
cmake -DCROW_ROOT=/tmp/Crow ..
make
```

## Способ 3: Установка в домашнюю директорию

```bash
# Устанавливаем в ~/local
cd /tmp
git clone https://github.com/CrowCpp/Crow.git
mkdir -p ~/local/include
cp -r Crow/include/crow* ~/local/include/

# Используем при сборке
export CROW_ROOT=~/local
cd ~/projects/Blockchain/build
cmake ..
make
```

## Проверка установки

После установки Crow, проверьте что файл найден:
```bash
find /usr -name "crow.h" 2>/dev/null
# или
ls -la /usr/local/include/crow.h
```
