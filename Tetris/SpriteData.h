#pragma once

class SpriteData {
public:
    int x;
    int y;
    int rotation;
    int randTetramino;
    void setRotation(int rot);
    void rotate();
    int getRotation();
    void move(float xOffset, float yOffset);
    void setPosition(float xPosition, float yPosition);
    void randTet();
    int getRandTet();
};
