#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "source.h"

using namespace std;

class Matrix 
{
    private:
        int colsSize;
        int rowsSize;
        vector<vector<double>> matrix;

    public:
        // Should check correct size
        Matrix(int rowsSize, int colsSize) 
        {
            this->colsSize = colsSize;
            this->rowsSize = rowsSize; 
            initMatrix(rowsSize, colsSize);
        }

        // Should check correct size
        Matrix(int size) 
        {
            this->colsSize = size;
            this->rowsSize = size; 
            initMatrix(size, size);
        }

        // Add exception handling
        Matrix(string filename, string path){
            ifstream readFile(path + '/' + filename);

            readFile >> this->colsSize >> this->rowsSize;
            initMatrix(this->rowsSize, this->colsSize);

            readMatrixFromFile(readFile);

            readFile.close();
        }

        // Should check correct size
        Matrix add(Matrix m2)
        {
            Matrix newMatrix(rowsSize, colsSize);
            for(int indexR = 0; indexR < matrix.size(); indexR++) {
                for(int indexC = 0; indexC < matrix[indexR].size(); indexC++){
                    double value = m2.get(indexR, indexC) + this->get(indexR, indexC);
                    newMatrix.set(indexR, indexC, value);
                }
            }
            return newMatrix;
        }

        // Should check correct size
        Matrix subtract(Matrix m2)
        {
            Matrix newMatrix(rowsSize, colsSize);
            for(int indexR = 0; indexR < matrix.size(); indexR++) {
                for(int indexC = 0; indexC < matrix[indexR].size(); indexC++){
                    double value = this->get(indexR, indexC) - m2.get(indexR, indexC);
                    newMatrix.set(indexR, indexC, value);
                }
            }
            return newMatrix;
        }

        Matrix multiply(Matrix m2)
        {
            if(colsSize != m2.rowsSize){
                // throw an exception
                return 1;
            }

            Matrix newMatrix(rowsSize, m2.colsSize);

            for (int indexR = 0; indexR < matrix.size(); indexR++)
            { 
                for (int indexC = 0; indexC < matrix[indexR].size(); indexC++)
                {
                    for (int k = 0; k < colsSize; k++)
                    {
                        double value = 
                            (matrix[indexR][k] * m2.get(k, indexC)) + newMatrix.get(indexR, indexC);
                        newMatrix.set(indexR, indexC, value);
                    }
                }
            }
            return newMatrix;
        }

        // Add exception handling
        void store(string filename, string path)
        {
            ofstream outputFile(path + '/' + filename);
            outputFile<< this->colsSize << " " << this->rowsSize << endl;
            printToFile(outputFile);
            outputFile.close();
        }

        // Should write protect by index out of bounds
        void set(int rowsPosition, int colsPosition, double val) 
        {
            matrix[rowsPosition][colsPosition] = val;
        }

        // Should write protect by index out of bounds
        double get(int rowsPosition, int colsPosition) 
        {
            return matrix[rowsPosition][colsPosition];
        }

        int cols()
        {
            return this->colsSize;
        }

        int rows()
        {
            return this->rowsSize;
        }

        void print()
        {
           for (int i = 0; i < matrix.size(); i++) { 
                for (int j = 0; j < matrix[i].size(); j++) 
                    cout << setprecision(2) << fixed << matrix[i][j] << " "; 
                cout << endl; 
            }  
        }
    private:
        void printToFile(ofstream &outputStream)
        {
            for (int i = 0; i < matrix.size(); i++) { 
                for (int j = 0; j < matrix[i].size(); j++) 
                    outputStream << matrix[i][j] << " "; 
                outputStream << endl; 
            }  
        }

        void initMatrix(int rowsSize, int colsSize)
        {
            double initValue = 0.0;
            for(int indexR = 0; indexR < rowsSize;indexR++) {
                vector<double> singleRow;
                for(int indexC = 0; indexC < colsSize ;indexC++) {
                    singleRow.push_back(initValue); // change to 0.0 for prod version
                }
                matrix.push_back(singleRow);
            }
        }

        // Add exception handling
        void readMatrixFromFile(std::ifstream &inputStream){
            double singlePosition;
            for (int indexR = 0; indexR < this->rowsSize; indexR++){
                for (int indexC = 0; indexC < this->colsSize; indexC++){
                    inputStream >> singlePosition;
                    this->set(indexR, indexC, singlePosition);
                }      
            }
        }
};

int main() 
{
    Matrix newMatrix = Matrix(2,2);
    Matrix secondMatrix = Matrix(2,2);
    // newMatrix.print();
    // secondMatrix.print();
   newMatrix.set(0,0,3.5);
//    newMatrix.print();
//    cout << newMatrix.cols() << endl;

    Matrix resultMatrix = newMatrix.multiply(secondMatrix);
    newMatrix.store("matrixToFile.txt", "P:\\PK\\JiPP\\ex1\\Windows");
    secondMatrix = Matrix("matrixToFile.txt", "P:\\PK\\JiPP\\ex1\\Windows");
    secondMatrix.print();
}