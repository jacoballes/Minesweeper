#include <SFML/Graphics.hpp>
using namespace sf;

using namespace std;

#include "Board.hpp"

int main() {
    double r, g, b;
    bool rUp, gUp, bUp;
    r = 10;
    g = 70;
    b = 130;
    rUp = true;
    gUp = true;
    bUp = true;

    Board board = Board();

    int boardWidth = Coord::WIDTH * Cell::CELL_SIZE + sideBarWidth * 2 * Cell::CELL_SIZE;
    int boardHeight = Coord::HEIGHT * Cell::CELL_SIZE + sideBarWidth * 4 * Cell::CELL_SIZE;

    RenderWindow window(VideoMode(boardWidth, boardHeight), "Minesweeper");


    const double bombBarTileWidth = 9.0;
    double bombBarPixelWidth = Cell::CELL_SIZE * bombBarTileWidth - Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/2 * 2;
    //double bombBarPositionX = sideBarWidth * Cell::CELL_SIZE + Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/2;
    double bombBarPositionX = boardWidth/2 - bombBarPixelWidth/2;
    double bombBarPositionY = sideBarWidth * Cell::CELL_SIZE - Cell::CELL_SIZE/2;

    RectangleShape bombsLeftBar;
    bombsLeftBar.setFillColor(Color(Cell::GRAY_BRIGHTNESS, Cell::GRAY_BRIGHTNESS, Cell::GRAY_BRIGHTNESS));
    bombsLeftBar.setSize(Vector2f(bombBarPixelWidth, Cell::CELL_SIZE));
    bombsLeftBar.setPosition(bombBarPositionX, bombBarPositionY);

    Text bombNum;
    bombNum.setFont(font);
    bombNum.setFillColor(Color::Black);
    bombNum.setCharacterSize(Cell::CELL_SIZE * Cell::CELL_SCALE);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setFillColor(Color::Black);
    gameOverText.setCharacterSize(Cell::CELL_SIZE * Cell::CELL_SCALE);

    while(window.isOpen()) {
        // if(r >= 170) rUp = false;
        // else if(r <= 50) rUp = true;
        // if(g >= 170) gUp = false;
        // else if(g <= 50) gUp = true;
        // if(b >= 170) bUp = false;
        // else if(b <= 50) bUp = true;

        // if(rUp) r += 0.1;
        // else r -= 0.1;
        // if(gUp) g += 0.2;
        // else g -= 0.2;
        // if(bUp) b += 0.3;
        // else b -= 0.3;

        window.clear(Color(Cell::GRAY_BRIGHTNESS+30, Cell::GRAY_BRIGHTNESS+30, Cell::GRAY_BRIGHTNESS+30));

        if(gameOver) {
            gameOverText.setString("R to reset");
            gameOverText.setOrigin(Vector2f(gameOverText.getLocalBounds().width/2, Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/2));
            gameOverText.setPosition(boardWidth/2, boardHeight - sideBarWidth * 1.5 * Cell::CELL_SIZE);
            window.draw(gameOverText);
            board.showBombs();
        } else if(nonBombCellsLeft == 0) {
            gameOverText.setString("You win!");
            gameOverText.setOrigin(Vector2f(gameOverText.getLocalBounds().width/2, Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/2));
            gameOverText.setPosition(boardWidth/2, boardHeight - sideBarWidth * 1.5 * Cell::CELL_SIZE);
            window.draw(gameOverText);
        }

        board.draw(window);

        string bombText;
        if(bombsLeft == -1) {
            bombText = "Bombs left: ??";
        } else {
            bombText = "Bombs left: " + to_string(bombsLeft);
        }

        int numCharacters = bombText.length();
        bombNum.setOrigin(Vector2f(bombNum.getLocalBounds().width/2, Cell::CELL_SIZE * (1 - Cell::CELL_SCALE)/2));
        bombNum.setPosition(bombBarPositionX + bombBarPixelWidth/2, bombBarPositionY);
        window.draw(bombsLeftBar);
        bombNum.setString(bombText);
        window.draw(bombNum);

        window.display();

        Event event;
        while(window.pollEvent(event)) {
            // if event type corresponds to pressing window X
            if(event.type == Event::Closed) {
                // tell the window to close
                window.close();
            }
            // check addition event types to handle additional events

            if (event.type == Event::EventType::KeyPressed){
                if(event.key.code == Keyboard::R) {
                    board.reset();
                }
                if(event.key.code == Keyboard::S) {
                    board.showBombs();
                }
            }

            if(event.type == Event::MouseButtonReleased) {
                mouseLocked = false;
            }
        }
    }

    return 0;

}