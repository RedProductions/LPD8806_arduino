#include "LPD8806.h"


int width = 16;
int height = 10;

int fillColorR = 0;
int fillColorG = 0;
int fillColorB = 0;

int strokeColorR = 0;
int strokeColorG = 0;
int strokeColorB = 0;

boolean showStroke = true;

int dataPin = 13;
int clockPin = 12;


//LPD8806 strip = LPD8806(gridSize, dataPin, clockPin);

LPD8806 strip = NULL;

void setup() {

  createGrid(width, height, dataPin, clockPin);

  strip.begin();

  strip.show();
  
}

void loop() {

  background(255, 255, 255);

  fill(255, 0, 0);
  stroke(0, 255, 0);
  
  makeRect(3, 3, 6, 5);
  
  strip.show();
  
}


void createGrid(int nwidth, int nheight, int ndataPin, int nclockPin){

  uint8_t gridSize = nwidth * nheight;
  
  strip = LPD8806(gridSize, ndataPin, nclockPin);
  
}

void setSinglePixel(int posX, int posY){
  
  setPixelfromIndex(calcFinalPos(posX, posY), fillColorR, fillColorG, fillColorB);
  
}
void setSinglePixel(int posX, int posY, int r, int g, int b){
  
  setPixelfromIndex(calcFinalPos(posX, posY), r, g, b);
  
}

void setPixelfromIndex(int index, int r, int g, int b){

  strip.setPixelColor(index, strip.Color(r, g, b));

}

void background(int r, int g, int b){
  
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      setSinglePixel(i, j, r, g, b);
    }
  }
  
}

void fill(int r, int g, int b){
  fillColorR = r;
  fillColorG = g;
  fillColorB = b;
}

void fill(int color){
  fillColorR = color;
  fillColorG = color;
  fillColorB = color;
}

void stroke(int r, int g, int b){
  strokeColorR = r;
  strokeColorG = g;
  strokeColorB = b;
}

void stroke(int color){
  strokeColorR = color;
  strokeColorG = color;
  strokeColorB = color;
}

void makeRect(int posX, int posY, int squareWidth, int squareHeight){

  for(int i = posX; i < posX + squareWidth; i++){
    for(int j = posY; j < posY + squareHeight; j++){
      if((i == posX || i == posX + squareWidth - 1 || j == posY || j == posY + squareHeight - 1) && showStroke){
        setSinglePixel(i, j, strokeColorR, strokeColorG, strokeColorB);
      }else {
        setSinglePixel(i, j);
      }
    }
  }
  
}

void makeCircle(int posX, int posY, int radius){

  for(int i = posX - radius; i <= posX + radius; i++){
    for(int j = posY - radius; j <= posY + radius; j++){
      
      if((i - posX) * (i - posX) + (j - posY) * (j - posY) <= radius * radius){
        
        setSinglePixel(i, j);
        
      }
      
    }
  }
  
}


int calcFinalPos(int i, int j){
  
  int finalPos = 0;

  
  int finalX = i;
  int finalY = j;

  if(j%2 == 1){
    
    finalX = width - (i + 1);
    
  }
  

  finalPos = finalY*width + finalX;
  
  return finalPos;
  
}

