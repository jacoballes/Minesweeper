#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

#include <vector>
using namespace std;

#include "Coord.hpp"

static bool mouseLocked = false;
static bool gameOver = false;
static int sideBarWidth = 1; // width in cells, so 1 = CELL_SIZE

struct Cell {

    static const int CELL_SIZE = 32;
    static const int GRAY_BRIGHTNESS = 190; // Out of 255
    static const int OPENED_GRAY_BRIGHTNESS = GRAY_BRIGHTNESS - 30;
    static constexpr double CELL_SCALE = 0.9;
    

    Coord* location;
    vector<Coord*> touching;

    int cellNumber; // -1 is bomb, other numbers represent the number of bombs surrounding it
    bool cellOpened;
    bool flagged;
    bool isClicked(RenderWindow& window, const int BUTTON) const;
    Color cellColor = Color(GRAY_BRIGHTNESS, GRAY_BRIGHTNESS, GRAY_BRIGHTNESS);
    
    RectangleShape cellSquare;

    Cell();
    ~Cell();
    Cell(const int X, const int Y);

    void open(Cell* board[Coord::HEIGHT][Coord::WIDTH], int& numLeft);
    void setNumber(Cell* board[Coord::HEIGHT][Coord::WIDTH]);

    Color getNumColor() const;
    
};



// Definitions

Cell::Cell() {

}

Cell::~Cell() {
    
    delete location;
    touching.clear();

}

Cell::Cell(const int X, const int Y) {

    location = new Coord(X, Y);
    touching = location->getSurroundingCoords();
    cellNumber = -2;
    cellOpened = false;
    flagged = false;

    cellColor = Color(GRAY_BRIGHTNESS, GRAY_BRIGHTNESS, GRAY_BRIGHTNESS);
    cellSquare.setFillColor(cellColor);
    cellSquare.setPosition(Vector2f(CELL_SIZE * location->x + CELL_SIZE * (1 - CELL_SCALE)/2 + sideBarWidth * CELL_SIZE, CELL_SIZE * location->y + CELL_SIZE * (1 - CELL_SCALE)/2 + sideBarWidth * CELL_SIZE * 2));
    cellSquare.setSize(Vector2f(CELL_SIZE * CELL_SCALE, CELL_SIZE * CELL_SCALE));

}

void Cell::open(Cell* board[Coord::HEIGHT][Coord::WIDTH], int& numLeft) {

    if(!cellOpened) {
        flagged = false;
        cellOpened = true;
        numLeft--;
        cellSquare.setFillColor(Color(OPENED_GRAY_BRIGHTNESS, OPENED_GRAY_BRIGHTNESS, OPENED_GRAY_BRIGHTNESS));
        if(cellNumber == -1) {
            cellSquare.setFillColor(Color::Red);
            gameOver = true;
        } else if(cellNumber == 0) {
            for(int i = 0; i < touching.size(); i++) {
                board[touching.at(i)->y][touching.at(i)->x]->open(board, numLeft);
            }
        }
    }

}

void Cell::setNumber(Cell* board[Coord::HEIGHT][Coord::WIDTH]) {

    if(cellNumber != -1) {
        int counter = 0;
        for(int currentCoord = 0; currentCoord < touching.size(); currentCoord++) {
            if(board[touching.at(currentCoord)->y][touching.at(currentCoord)->x]->cellNumber == -1) {
                counter++;
            }
        }
        cellNumber = counter;
    }

}

Color Cell::getNumColor() const {

    Color color = Color::Blue;
    if(cellNumber == 2) color = Color(0, 153, 0); // Green
    else if(cellNumber == 3) color = Color::Red;
    else if(cellNumber == 4) color = Color(160, 32, 240); // Purple
    else if(cellNumber == 5) color = Color(255, 153, 51); // Orange
    else if(cellNumber == 6) color = Color(64, 224, 208); // Turquoise
    else if(cellNumber == 7) color = Color::Black;
    else if(cellNumber == 8) color = Color(100, 100, 100); // Gray

    return color;

}

bool Cell::isClicked(RenderWindow& window, const int BUTTON) const {

    Vector2i position = Mouse::getPosition(window);

    bool xCorrect = position.x/Cell::CELL_SIZE == location->x + sideBarWidth;
    bool yCorrect = position.y/Cell::CELL_SIZE == location->y + sideBarWidth * 2;

    if(BUTTON == 1 && xCorrect && yCorrect && Mouse::isButtonPressed(Mouse::Left) && !mouseLocked) {
        mouseLocked = true;
        return true;
    } else if(BUTTON == 2 && xCorrect && yCorrect && Mouse::isButtonPressed(Mouse::Right) && !mouseLocked) {
        mouseLocked = true;
        return true;
    }

}

#endif