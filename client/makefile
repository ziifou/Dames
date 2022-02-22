CC = gcc
SDLI =   `sdl-config --libs` -lSDL_image
TH = -lpthread

all : client

client : client.c 
	$(CC) -o main client.c network.c ./jeu/lunch.c ./jeu/interfacejeu.c ./jeu/jeu.c $(TH)  $(SDLI)

clean:
	rm main
