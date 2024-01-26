CC = g++

Minesweeper: main.cpp
	$(CC) main.cpp -o Minesweeper -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network