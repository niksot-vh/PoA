# Dockerfile для установки и запуска программы
FROM debian:13.2

# Обновляем репозиторий и устанавливаем зависимости
RUN apt-get update && \
    apt-get install -y build-essential && \
    rm -rf /var/lib/apt/lists/*

# Копируем deb-пакет внутрь контейнера
COPY poapr.deb /tmp/poapr.deb

# Устанавливаем deb-пакет
RUN dpkg -i /tmp/poapr.deb || apt-get install -f -y

# Рабочая директория
WORKDIR /usr/local/bin

# Команда по умолчанию — запуск программы
CMD ["poapr"]
