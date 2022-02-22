CC = gcc
TH = -lpthread

all : server

server : server.c
	$(CC) -o main server.c logsystem.c  logedClients.c $(TH)

clean:
	rm main 
