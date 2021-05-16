#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SpriteData.h"

#define GRID_HEIGHT 21
#define GRID_WIDTH 12

sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");

SpriteData playerData;

sf::Texture spritesheet;

sf::IntRect cyanPos(0, 0, 16, 16);
sf::IntRect yellowPos(16, 0, 16, 16);
sf::IntRect purplePos(32, 0, 16, 16);
sf::IntRect greenPos(48, 0, 16, 16);
sf::IntRect bluePos(64, 0, 16, 16);
sf::IntRect redPos(80, 0, 16, 16);
sf::IntRect orangePos(96, 0, 16, 16);
sf::IntRect blackPos(112, 0, 16, 16);
sf::IntRect whitePos(128, 0, 16, 16);

sf::Sprite cyan(spritesheet, cyanPos);
sf::Sprite yellow(spritesheet, yellowPos);
sf::Sprite purple(spritesheet, purplePos);
sf::Sprite green(spritesheet, greenPos);
sf::Sprite blue(spritesheet, bluePos);
sf::Sprite red(spritesheet, redPos);
sf::Sprite orange(spritesheet, orangePos);
sf::Sprite black(spritesheet, blackPos);
sf::Sprite white(spritesheet, whitePos);

sf::SoundBuffer musicBuffer;

sf::Sound sound;

float actualScale = 2.5;
float scale = 16 * actualScale;

bool moveLeft = true;
bool moveRight = true;

int grid[GRID_HEIGHT][GRID_WIDTH];
int moveGrid[GRID_HEIGHT][GRID_WIDTH];

int tetramino[4][7][4][4] = {
    {
        { // 0 = I tetramino
            { 0,0,9,0 },
            { 0,0,9,0 },
            { 0,0,9,0 },
            { 0,0,9,0 },
        },
        { // 1 = J tetramino
            { 0,13,0,0 },
            { 0,13,13,13 },
            { 0,0,0,0 },
            { 0,0,0,0 },
        },
        { // 2 = L tetramino
            { 0,0,0,15 },
            { 0,15,15,15 },
            { 0,0,0,0 },
            { 0,0,0,0 },
        },
        { // 3 = O tetramino
            { 0,0,0,0 },
            { 0,10,10,0 },
            { 0,10,10,0 },
            { 0,0,0,0 },
        },
        { // 4 = S tetramino
            { 0,0,12,12 },
            { 0,12,12,0 },
            { 0,0,0,0 },
            { 0,0,0,0 },
        },
        { // 5 = T tetramino
            { 0,0,11,0 },
            { 0,11,11,11 },
            { 0,0,0,0 },
            { 0,0,0,0 },
        },
        { // 6 = Z tetramino
            { 0,14,14,0 },
            { 0,0,14,14 },
            { 0,0,0,0 },
            { 0,0,0,0 }
        },
    },
    {
        { // 0 = I tetramino
            { 0,0,0,0 },
            { 0,0,0,0 },
            { 9,9,9,9 },
            { 0,0,0,0 },
        },
        { // 1 = J tetramino
            { 0,0,13,13 },
            { 0,0,13,0 },
            { 0,0,13,0 },
            { 0,0,0,0 },
        },
        { // 2 = L tetramino
            { 0,0,15,0 },
            { 0,0,15,0 },
            { 0,0,15,15 },
            { 0,0,0,0 },
        },
        { // 3 = O tetramino
            { 0,0,0,0 },
            { 0,10,10,0 },
            { 0,10,10,0 },
            { 0,0,0,0 },
        },
        { // 4 = S tetramino
            { 0,0,12,0 },
            { 0,0,12,12 },
            { 0,0,0,12 },
            { 0,0,0,0 },
        },
        { // 5 = T tetramino
            { 0,0,11,0 },
            { 0,0,11,11 },
            { 0,0,11,0 },
            { 0,0,0,0 },
        },
        { // 6 = Z tetramino
            { 0,0,0,14 },
            { 0,0,14,14 },
            { 0,0,14,0 },
            { 0,0,0,0 }
        },
    },
    {
        { // 0 = I tetramino
            { 0,0,9,0 },
            { 0,0,9,0 },
            { 0,0,9,0 },
            { 0,0,9,0 },
        },
        { // 1 = J tetramino
            { 0,13,13,13 },
            { 0,0,0,13 },
            { 0,0,0,0 },
            { 0,0,0,0 },
        },
        { // 2 = L tetramino
            { 0,15,15,15 },
            { 0,15,0,0 },
            { 0,0,0,0 },
            { 0,0,0,0 },
        },
        { // 3 = O tetramino
            { 0,0,0,0 },
            { 0,10,10,0 },
            { 0,10,10,0 },
            { 0,0,0,0 },
        },
        { // 4 = S tetramino
            { 0,0,12,12 },
            { 0,12,12,0 },
            { 0,0,0,0 },
            { 0,0,0,0 },
        },
        { // 5 = T tetramino
            { 0,0,0,0 },
            { 0,11,11,11 },
            { 0,0,11,0 },
            { 0,0,0,0 },
        },
        { // 6 = Z tetramino
            { 0,14,14,0 },
            { 0,0,14,14 },
            { 0,0,0,0 },
            { 0,0,0,0 }
        },
    },
    {
        { // 0 = I tetramino
            { 0,0,0,0 },
            { 0,0,0,0 },
            { 9,9,9,9 },
            { 0,0,0,0 },
        },
        { // 1 = J tetramino
            { 0,0,0,13 },
            { 0,0,0,13 },
            { 0,0,13,13 },
            { 0,0,0,0 },
        },
        { // 2 = L tetramino
            { 0,0,15,15 },
            { 0,0,0,15 },
            { 0,0,0,15 },
            { 0,0,0,0 },
        },
        { // 3 = O tetramino
            { 0,0,0,0 },
            { 0,10,10,0 },
            { 0,10,10,0 },
            { 0,0,0,0 },
        },
        { // 4 = S tetramino
            { 0,0,12,0 },
            { 0,0,12,12 },
            { 0,0,0,12 },
            { 0,0,0,0 },
        },
        { // 5 = T tetramino
            { 0,0,11,0 },
            { 0,11,11,0 },
            { 0,0,11,0 },
            { 0,0,0,0 },
        },
        { // 6 = Z tetramino
            { 0,0,0,14 },
            { 0,0,14,14 },
            { 0,0,14,0 },
            { 0,0,0,0 }
        },
    },
};

void updateGame() {

    int leftOffset = 165;
    int topOffset = 0;

    window.clear();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tetramino[playerData.getRotation()][playerData.getRandTet()][i][j] >= 9) {
                grid[i + playerData.y][j + playerData.x] = tetramino[playerData.getRotation()][playerData.getRandTet()][i][j];
            }
        }
    }

    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i + 1][j] < 9 && grid[i + 1][j] > 0 && grid[i][j] >= 9) {
                for (int u = 0; u < GRID_HEIGHT; ++u) {
                    for (int h = 0; h < GRID_WIDTH; ++h) {
                        if (grid[u][h] >= 9) {
                            grid[u][h] -= 8;
                        }
                    }
                }
                playerData.setPosition(3, -1);
                playerData.setRotation(0);
                playerData.randTet();
            }
            if (grid[i][j + 1] < 9 && grid[i][j + 1] > 0 && grid[i][j] >= 9) { // Right collision
                moveRight = false;
            }
            if (grid[i][j - 1] < 9 && grid[i][j - 1] > 0 && grid[i][j] >= 9) { // Left collision
                moveLeft = false;
            }
            if (i == GRID_HEIGHT-1 || j == 0 || j == GRID_WIDTH-1) {
                grid[i][j] = 8;
            }

            if (grid[i][j] == 8) {
                black.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(black);
            }
            if (grid[i][j] == 9 || grid[i][j] == 1) {
                cyan.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(cyan);
            }
            if (grid[i][j] == 10 || grid[i][j] == 2) {
                yellow.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(yellow);
            }
            if (grid[i][j] == 11 || grid[i][j] == 3) {
                purple.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(purple);
            }
            if (grid[i][j] == 12 || grid[i][j] == 4) {
                green.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(green);
            }
            if (grid[i][j] == 13 || grid[i][j] == 5) {
                blue.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(blue);
            }
            if (grid[i][j] == 14 || grid[i][j] == 6) {
                red.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(red);
            }
            if (grid[i][j] == 15 || grid[i][j] == 7) {
                orange.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(orange);
            }
            if (grid[i][j] == 16) {
                white.setPosition((j * scale) + leftOffset, (i * scale) + topOffset);
                window.draw(white);
            }
        }
    }
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] >= 9) {
                grid[i][j] = 0;
            }
        }
    }
    window.display();
}

int main() {

    float tickLength = 1;

    bool gameRunning = true;

    musicBuffer.loadFromFile("theme.wav");
    sound.setBuffer(musicBuffer);
    sound.setLoop(true);
    
    spritesheet.loadFromFile("spritesheet.png");

    cyan.setScale(actualScale, actualScale);
    yellow.setScale(actualScale, actualScale);
    purple.setScale(actualScale, actualScale);
    green.setScale(actualScale, actualScale);
    blue.setScale(actualScale, actualScale);
    red.setScale(actualScale, actualScale);
    orange.setScale(actualScale, actualScale);
    black.setScale(actualScale, actualScale);

    srand(time(NULL));

    sf::Clock gameTick;
    sf::Clock moveTick;

    playerData.setPosition(3, -1);
    playerData.setRotation(0);

    sound.play();

    while (window.isOpen())
    {
        sf::Event e;

        if (gameRunning) {
            for (int i = GRID_HEIGHT - 2; i > 0; --i) { // Checks for row of tetraminos
                int checkRow = 0;
                for (int j = 1; j < GRID_WIDTH - 1; ++j) {
                    if (grid[0][j] != 0) {
                        gameRunning = false;
                    }
                    if (grid[i][j] < 9 && grid[i][j] > 0) {
                        ++checkRow;
                    }
                    if (checkRow == 10) {
                        for (int x = 1; x < GRID_WIDTH - 1; ++x) {
                            grid[i][x] = 0;
                            for (int v = 0; v < i; ++v) {
                                for (int b = 1; b < GRID_WIDTH - 1; ++b) {
                                    moveGrid[v + 1][b] = grid[v][b];
                                }
                            }
                        }
                        for (int v = 1; v <= i; ++v) {
                            for (int b = 1; b < GRID_WIDTH - 1; ++b) {
                                grid[v][b] = moveGrid[v][b];
                            }
                        }
                    }
                }
            }
            if (gameTick.getElapsedTime().asSeconds() > tickLength) {
                playerData.move(0, 1);
                updateGame();
                gameTick.restart();
            }
            if (moveTick.getElapsedTime().asSeconds() > 0.15f) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    moveRight = true;
                    updateGame();
                    if (moveRight) {
                        playerData.move(1, 0);
                        updateGame();
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    moveLeft = true;
                    updateGame();
                    if (moveLeft) {
                        playerData.move(-1, 0);
                        updateGame();
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    playerData.rotate();
                    updateGame();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    tickLength = 0.1;
                }
                else {
                    tickLength = 1;
                }
                moveTick.restart();
            }
        }

        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                window.close();

        }
    }
}