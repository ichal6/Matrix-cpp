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

class IndexOutOfBoundsException: public exception
{
    public:
        virtual const char* what() const throw(){
            return "Index is not contain to matrix";
        }    
};

class FailureStreamException: public exception
{
    public:
        virtual const char* what() const throw(){
            return "Stream is  damaged";
        }    
};


Matrix::Matrix()
{
    int const deafaultValue = 2;
    this->colsSize = deafaultValue;
    this->rowsSize = deafaultValue; 
    initMatrix(deafaultValue, deafaultValue);
}

Matrix::Matrix(int rowsSize, int colsSize)
{
    if(rowsSize <= 0 || colsSize <= 0)
    {
        throw IncorrectSizeException();
    }
    this->colsSize = colsSize;
    this->rowsSize = rowsSize; 
    initMatrix(rowsSize, colsSize);
}

Matrix::Matrix(int size)
{
    if(size <= 0)
    {
        throw IncorrectSizeException();
    }
    this->colsSize = size;
    this->rowsSize = size; 
    initMatrix(size, size);
}

Matrix::Matrix(string filename, string path){
    ifstream readFile(path + '/' + filename);
    if(!readFile.is_open()){
        throw FailureOpenFileException();
    }

    readFile >> this->colsSize >> this->rowsSize;
    initMatrix(this->rowsSize, this->colsSize);

    readMatrixFromFile(readFile);
    readFile.close();
}

Matrix::Matrix(const Matrix &matrixToCopy)
{
    this->colsSize = matrixToCopy.colsSize;
    this->rowsSize = matrixToCopy.rowsSize; 
    initMatrix(rowsSize, colsSize);
    makeCopyMatrix(matrixToCopy);
}

Matrix Matrix::add(Matrix m2)
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

Matrix Matrix::subtract(Matrix m2)
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

Matrix Matrix::multiply(Matrix m2)
{
    if(colsSize != m2.rowsSize){
        throw IncorrectSizeException();
    }

    Matrix newMatrix(this->rowsSize, m2.colsSize);

    for (int indexR = 0; indexR < this->rowsSize; indexR++)
    { 
        for (int indexC = 0; indexC < m2.colsSize; indexC++)
        {
            for (int k = 0; k < this->colsSize; k++)
            {
                double value = 
                    (matrix[indexR][k] * m2.get(k, indexC)) + newMatrix.get(indexR, indexC);
                newMatrix.set(indexR, indexC, value);
            }
        }
    }
    return newMatrix;
}

void Matrix::store(string filename, string path)
{
    ofstream outputFile(path + '/' + filename);
    if(outputFile.fail()){
        throw FailureOpenFileException();
    }
    outputFile<< this->colsSize << " " << this->rowsSize << endl;
    printToFile(outputFile);
    outputFile.close();
}

void Matrix::set(int rowsPosition, int colsPosition, double val) 
{
    if(isIndexOutOfBounds(rowsPosition, colsPosition)){
            throw IndexOutOfBoundsException();
        }
    
    matrix[rowsPosition][colsPosition] = val;
}

double Matrix::get(int rowsPosition, int colsPosition) const 
{
    if(isIndexOutOfBounds(rowsPosition, colsPosition)){
            throw IndexOutOfBoundsException();
        }

    return matrix[rowsPosition][colsPosition];
}

int Matrix::cols()
{
    return this->colsSize;
}

int Matrix::rows()
{
    return this->rowsSize;
}

void Matrix::print()
{
    for (int i = 0; i < matrix.size(); i++) { 
        for (int j = 0; j < matrix[i].size(); j++) 
            cout << setprecision(2) << fixed << matrix[i][j] << " "; 
        cout << endl; 
    }  
}

void Matrix::printToFile(ofstream &outputStream)
{
    for (int i = 0; i < matrix.size(); i++) { 
        for (int j = 0; j < matrix[i].size(); j++) 
            outputStream << matrix[i][j] << " "; 
        outputStream << endl; 
    }  
}

void Matrix::initMatrix(int rowsSize, int colsSize)
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

void Matrix::readMatrixFromFile(std::ifstream &inputStream){
    if(!inputStream.is_open()){
        throw FailureStreamException();
    }
    double singlePosition;
    for (int indexR = 0; indexR < this->rowsSize; indexR++){
        for (int indexC = 0; indexC < this->colsSize; indexC++){
            inputStream >> singlePosition;
            this->set(indexR, indexC, singlePosition);
        }      
    }
}

void Matrix::makeCopyMatrix(Matrix const &matrixToCopy){
    double singlePosition;
    for (int indexR = 0; indexR < this->rowsSize; indexR++){
        for (int indexC = 0; indexC < this->colsSize; indexC++){
            double value = matrixToCopy.get(indexR, indexC);
            this->set(indexR, indexC, value);
        }      
    }
}

bool Matrix::isTheSameSize(Matrix m2){
    if(this->colsSize == m2.colsSize && this->rowsSize == m2.rowsSize){
        return true;
    }
    return false;
}

bool Matrix::isIndexOutOfBounds(int rowsPosition, int colsPosition) const{
        if(rowsPosition < 0 || rowsPosition >= this->rowsSize ||
            colsPosition < 0 || colsPosition >= this->colsSize){
            return true;
        }
        return false;
}


int main() 
{
    // fill matrixs
    int sizeR = 5;
    int sizeC = 5;
    Matrix matrix1(sizeR, sizeC);
    Matrix matrix2(sizeR);
    double value = 0.5;
    for(int indexR = 0; indexR < sizeR; indexR++){
        for(int indexC = 0; indexC < sizeC; indexC++){
            matrix1.set(indexR, indexC, value);
            matrix2.set(indexR, indexC, ++value);
        }
    }

    cout << "Drukowanie pierwszej macierzy:" << endl;
    matrix1.print();
    cout << endl << "Drukowanie drugiej macierzy: " << endl;
    matrix2.print();
    cout << endl;

    cout << "Liczba wierszy macierzy 1: " << matrix1.rows() << endl;
    cout << "Liczba kolumn macierzy 1: " << matrix1.cols() << endl;

    Matrix matrixAfterAdd = matrix1.add(matrix2);
    cout << "Wynik dodawania do macierzy nr 1 macierzy nr 2" << endl;
    matrixAfterAdd.print();
    cout <<  endl;

    Matrix matrixAfterSubtract = matrix1.subtract(matrix2);
    cout << "Wynik odejmowania od macierzy nr 1 macierzy nr 2" << endl;
    matrixAfterSubtract.print();
    cout << endl;
    
    Matrix matrixAfterMultiply = matrix1.multiply(matrix2);
    cout << "Wynik mnozenia macierzy nr 1 przez macierz nr 2" << endl;
    matrixAfterMultiply.print();
    cout << endl;

    try{
        matrixAfterMultiply.store("matrix", "/tmp");
        Matrix matrixFromFile("matrix", "/tmp");
        cout << "Zapisano i odczytano wynik mnozenia macierzy z pliku:" << endl;
        matrixFromFile.print();
        cout << endl;
    } catch(FailureOpenFileException ex){
        cerr << "Błąd otwarcia pliku" << endl;
        cerr << "Czy program zostal uruchomiono pod linuxem?" << endl;
        return 1;
    }

}
