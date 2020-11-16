#include <iostream>
#include <fstream>

using namespace std;

void printToFile(std::ofstream outputStream);

void initMatrix(int rowsSize, int colsSize);

void set(int rowsPosition, int colsPosition, double val);

double get(int rowsPosition, int colsPosition);

int cols();

int rows();

void print();
