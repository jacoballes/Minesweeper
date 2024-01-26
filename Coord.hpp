#ifndef COORD_HPP
#define COORD_HPP

#include <vector>
using namespace std;

struct Coord {

    const static unsigned int WIDTH = 24;
    const static unsigned int HEIGHT = 18;

    Coord(const int X, const int Y);

    vector<Coord*> getSurroundingCoords();

    bool equals(const Coord& OTHER) const;
    bool isValid() const;

    int x;
    int y;

};

Coord::Coord(const int X, const int Y) {

    x = X;
    y = Y;

}

vector<Coord*> Coord::getSurroundingCoords() {

    vector<Coord*> coords;

    Coord* coord1 = new Coord(x - 1, y); // Left
    Coord* coord2 = new Coord(x + 1, y); // Right
    Coord* coord3 = new Coord(x, y - 1); // Up
    Coord* coord4 = new Coord(x, y + 1); // Down
    
    Coord* coord5 = new Coord(x - 1, y - 1); // Upper-left
    Coord* coord6 = new Coord(x + 1, y - 1); // Upper-right
    Coord* coord7 = new Coord(x - 1, y + 1); // Lower-left
    Coord* coord8 = new Coord(x + 1, y + 1); // Lower-right

    if(coord1->isValid()) {
        coords.push_back(coord1);
    } else {
        delete coord1;
    }
    if(coord2->isValid()) {
        coords.push_back(coord2);
    } else {
        delete coord2;
    }
    if(coord3->isValid()) {
        coords.push_back(coord3);
    } else {
        delete coord3;
    }
    if(coord4->isValid()) {
        coords.push_back(coord4);
    } else {
        delete coord4;
    }
    if(coord5->isValid()) {
        coords.push_back(coord5);
    } else {
        delete coord5;
    }
    if(coord6->isValid()) {
        coords.push_back(coord6);
    } else {
        delete coord6;
    }
    if(coord7->isValid()) {
        coords.push_back(coord7);
    } else {
        delete coord7;
    }
    if(coord8->isValid()) {
        coords.push_back(coord8);
    } else {
        delete coord8;
    }

    return coords;

}

bool Coord::equals(const Coord& OTHER) const {

    return x == OTHER.x && y == OTHER.y;

}

bool Coord::isValid() const {

    return x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT;

}

#endif