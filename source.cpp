#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include "source.h"

using namespace std;

class IncorrectSizeException: public exception 
{
    public:
        virtual const char* what() const throw(){
            return "Incorrect size";
        }
};

class FailureOpenFileException: public exception
{
    public:
        virtual const char* what() const throw(){
            return "Cannot open a file";
        }
};

class Matrix 
{
    private:
        int colsSize;
        int rowsSize;
        vector<vector<double>> matrix;

    public:

        Matrix()
        {
            int const deafaultValue = 2;
            this->colsSize = deafaultValue;
            this->rowsSize = deafaultValue; 
            initMatrix(deafaultValue, deafaultValue);
        }

        Matrix(int rowsSize, int colsSize)
        {
            if(rowsSize <= 0 || colsSize <= 0)
            {
                throw IncorrectSizeException();
            }
            this->colsSize = colsSize;
            this->rowsSize = rowsSize; 
            initMatrix(rowsSize, colsSize);
        }

        Matrix(int size)
        {
            if(size <= 0)
            {
                throw IncorrectSizeException();
            }
            this->colsSize = size;
            this->rowsSize = size; 
            initMatrix(size, size);
        }

        Matrix(string filename, string path){
            ifstream readFile(path + '/' + filename);
            if(!readFile.is_open()){
                throw FailureOpenFileException();
            }

            readFile >> this->colsSize >> this->rowsSize;
            initMatrix(this->rowsSize, this->colsSize);

            readMatrixFromFile(readFile);

            readFile.close();
        }

        Matrix(const Matrix &matrixToCopy)
        {
            this->colsSize = matrixToCopy.colsSize;
            this->rowsSize = matrixToCopy.rowsSize; 
            initMatrix(rowsSize, colsSize);
            makeCopyMatrix(matrixToCopy);
        }

        Matrix add(Matrix m2)
        {
            if(isTheSameSize(m2) == false){
                throw IncorrectSizeException();
            }
            Matrix newMatrix(rowsSize, colsSize);
            for(int indexR = 0; indexR < matrix.size(); indexR++) {
                for(int indexC = 0; indexC < matrix[indexR].size(); indexC++){
                    double value = m2.get(indexR, indexC) + this->get(indexR, indexC);
                    newMatrix.set(indexR, indexC, value);
                }
            }
            return newMatrix;
        }

        Matrix subtract(Matrix m2)
        {
            if(isTheSameSize(m2) == false){
                throw IncorrectSizeException();
            }
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
                throw IncorrectSizeException();
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

        void store(string filename, string path)
        {
            ofstream outputFile(path + '/' + filename);
            if(outputFile.fail()){
                throw FailureOpenFileException();
            }
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
        double get(int rowsPosition, int colsPosition) const 
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

        void makeCopyMatrix(Matrix const &matrixToCopy){
            double singlePosition;
            for (int indexR = 0; indexR < this->rowsSize; indexR++){
                for (int indexC = 0; indexC < this->colsSize; indexC++){
                    double value = matrixToCopy.get(indexR, indexC);
                    this->set(indexR, indexC, value);
                }      
            }
        }

        bool isTheSameSize(Matrix m2){
            if(this->colsSize == m2.colsSize && this->rowsSize == m2.rowsSize){
                return true;
            }
            return false;
        }
};

int main() 
{
    Matrix newMatrix;
    Matrix secondMatrix;
    try
    {
        newMatrix = Matrix(2,2);
        secondMatrix = Matrix(8);
    }
    catch(const IncorrectSizeException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    // newMatrix.multiply(secondMatrix);

    newMatrix.print();
    secondMatrix.print();
   newMatrix.set(0,0,3.5);
   newMatrix.print();
   cout << newMatrix.cols() << endl;

    // Matrix resultMatrix = newMatrix.multiply(secondMatrix);
    newMatrix.store("matrixToFile.txt", "D:\\tempDir");

    try{
        secondMatrix = Matrix("matrixToFile.txt", "D:\\tempDir");
    } catch(const FailureOpenFileException& ex){
        std::cerr << ex.what() << "Exception ocuure" <<"\n";
    }

    Matrix anotherMatrix = Matrix(secondMatrix);

    secondMatrix.set(1,0,4.6);
    anotherMatrix.set(1,0,99.999);

    cout << "Second Matrix" << endl;
    secondMatrix.print();
    cout << "Another Matrix" << endl;
    anotherMatrix.print();
}
