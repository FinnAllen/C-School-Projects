#ifndef PA9_H
#define PA9_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

const int ROWS = 1000;
const int COLS = 1000;
const int PIXEL_SIZE = 3;

void readHeader(ifstream&, int&, int&);
void readBody(ifstream&, short[ROWS][COLS][PIXEL_SIZE]);
void openFile(ofstream& outputFile, string nameOfFile);
void openInputFile(ifstream& inputFile, string nameOfFile);
void applyModification(short[ROWS][COLS][PIXEL_SIZE], int, int, string&, ofstream&, ifstream&);


void applyVerticalFlip(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void applyHorizontalFlip(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void JacksonPollock(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void removeRed(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void removeGreen(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void removeBlue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void computeNegativeValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void computeHighContrastValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void computeRandomNoiseValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void computeGrayScaleValue(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);
void horozontalBlur(short imageData[ROWS][COLS][PIXEL_SIZE], int rows, int cols, ofstream& outputFile);

#endif
