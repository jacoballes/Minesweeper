#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Cell.hpp"
#include <random>
#include <ctime>

using namespace std;

static int bombsLeft = -1; // this number will change once the game loads, so it doesn't matter what value it's set to initially
static Font font;
static int nonBombCellsLeft = -1;

struct Board {

    const double PERCENT_BOMBS = 20.0; // Roughly 20 percent of the board will be bombs -- Will probably be stuck in a while loop if there are fewer than 9 bombs
    bool firstClick;

    Texture flagTexture;
    Sprite flag;

    Texture bombTexture;
    Sprite bomb;

    Text number;

    Board();

    Cell* board[Coord::HEIGHT][Coord::WIDTH];

    void draw(RenderWindow& window);

    void showBombs();

    void reset();

    void setBoard();

};

Board::Board() {

    srand(time(0));
    rand();

    for(int row = 0; row < Coord::HEIGHT; row++) {
        for(int col = 0; col < Coord::WIDTH; col++) {

            board[row][col] = new Cell(col, row);

        }
    }

    firstClick = true;

    flagTexture.loadFromFile("assets/flag.png");
    flagTexture.setRepeated(true);
    flag.setTexture(flagTexture);
    flag.setScale((Cell::CELL_SIZE * Cell::CELL_SCALE)/flag.getLocalBounds().width, (Cell::CELL_SIZE * Cell::CELL_SCALE)/flag.getLocalBounds().height);

    bombTexture.loadFromFile("assets/bomb.png");
    bombTexture.setRepeated(true);
    bomb.setTexture(bombTexture);
    bomb.setColor(Color(255,255,255));
    bomb.setScale((Cell::CELL_SIZE * Cell::CELL_SCALE)/bomb.getLocalBounds().width, (Cell::CELL_SIZE * Cell::CELL_SCALE)/bomb.getLocalBounds().height);

    font.loadFromFile("assets/luximb.ttf");
    number.setFont(font);
    number.setCharacterSize(Cell::CELL_SIZE * Cell::CELL_SCALE);
    number.setStyle(Text::Bold);
}

void Board::draw(RenderWindow& window) {

    for(int row = 0; row < Coord::HEIGHT; row++) {
        for(int col = 0; col < Coord::WIDTH; col++) {

            Cell* currentCell = board[row][col];
            window.draw(currentCell->cellSquare);
            double drawAtX = currentCell->location->x * Cell::CELL_SIZE + Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/2 + sideBarWidth * Cell::CELL_SIZE;
            double drawAtY = currentCell->location->y * Cell::CELL_SIZE + Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/2 + sideBarWidth * Cell::CELL_SIZE * 2;
            if(currentCell->cellNumber == -1 && currentCell->cellOpened) {
                bomb.setPosition(drawAtX, drawAtY);
                window.draw(bomb);
            } else if(currentCell->cellNumber > 0 && currentCell->cellOpened) {
                number.setString(to_string(currentCell->cellNumber));
                number.setFillColor(currentCell->getNumColor());
                number.setOrigin(Vector2f(number.getLocalBounds().width/2, 0));
                number.setPosition(drawAtX + Cell::CELL_SIZE/2 - Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/0.9, drawAtY - Cell::CELL_SIZE/9.0);
                window.draw(number);
            } else if(currentCell->flagged) {
                flag.setPosition(drawAtX, drawAtY);
                window.draw(flag);
            }
            
            
            if(currentCell->isClicked(window, 1) && !currentCell->flagged && !gameOver) {
                if(firstClick) {
                    currentCell->cellNumber = 0;
                    for(int i = 0; i < currentCell->touching.size(); i++) {
                        board[currentCell->touching.at(i)->y][currentCell->touching.at(i)->x]->cellNumber = 0;
                    }
                    setBoard();
                    firstClick = false;
                }
                currentCell->open(board,nonBombCellsLeft);
            }

            if(currentCell->isClicked(window, 2) && !currentCell->cellOpened && !gameOver && bombsLeft != -1) {
                currentCell->flagged = !currentCell->flagged;
                if(currentCell->flagged) {
                    bombsLeft--;
                } else {
                    bombsLeft++;
                }
            }
        
        }
    }

}

void Board::showBombs() {

    for(int row = 0; row < Coord::HEIGHT; row++) {
        for(int col = 0; col < Coord::WIDTH; col++) {

            if(board[row][col]->cellNumber == -1) {
                board[row][col]->open(board, nonBombCellsLeft);
            }

        }
    }

}

void Board::reset() {
    gameOver = false;
    firstClick = true;
    bombsLeft = -1;
    nonBombCellsLeft = -1;
    for(int row = 0; row < Coord::HEIGHT; row++) {
        for(int col = 0; col < Coord::WIDTH; col++) {

            delete board[row][col];
            board[row][col] = new Cell(col, row);

        }
    }
}

void Board::setBoard() {
    int numBombs = (int) (Coord::WIDTH * Coord::HEIGHT * (PERCENT_BOMBS / 100));
    bombsLeft = numBombs;
    nonBombCellsLeft = Coord::WIDTH * Coord::HEIGHT - numBombs;

    while(numBombs > 0) {

        int randomX = rand() % Coord::WIDTH;
        int randomY = rand() % Coord::HEIGHT;

        if(board[randomY][randomX]->cellNumber == -2) { // If the cell is not already a bomb
            board[randomY][randomX]->cellNumber = -1; // Make it a bomb
            numBombs--;
        }

    }

    for(int row = 0; row < Coord::HEIGHT; row++) {
        for(int col = 0; col < Coord::WIDTH; col++) {

            board[row][col]->setNumber(board);

        }
    }
}

#endif