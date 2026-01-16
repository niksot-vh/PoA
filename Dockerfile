FROM debian:13.2

RUN apt-get update && \
    apt-get install -y build-essential && \
    rm -rf /var/lib/apt/lists/*

COPY poapr.deb /tmp/poapr.deb

RUN dpkg -i /tmp/poapr.deb || apt-get install -f -y

WORKDIR /usr/local/bin

CMD ["poapr"]
