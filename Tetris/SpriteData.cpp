#include "SpriteData.h"

void SpriteData::setRotation(int rot) {
    rotation = rot;
}
void SpriteData::rotate() {
    rotation += 1;
    if (rotation == 4) {
        rotation = 0;
    }
}
int SpriteData::getRotation() {
    return rotation;
}
void SpriteData::move(float xOffset, float yOffset) {
    x += xOffset;
    y += yOffset;
}
void SpriteData::setPosition(float xPosition, float yPosition) {
    x = xPosition;
    y = yPosition;
}
void SpriteData::randTet() {
    randTetramino = rand() % 7;
}
int SpriteData::getRandTet() {
    return randTetramino;
}