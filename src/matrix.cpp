#include "matrix.h"
#include "exceptions.cpp"

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

Matrix Matrix::operator+(const Matrix & m2){
    return this->add(m2);
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

Matrix Matrix::operator-(const Matrix & m2){
    return this->subtract(m2);
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

Matrix Matrix::operator*(const Matrix & m2){
    return this->multiply(m2);
}

void Matrix::store(string filename, string path)
{
    ofstream outputFile = openFile(filename, path);
    outputFile << this->colsSize << " " << this->rowsSize << endl;
    printToFile(outputFile); 
    outputFile.close();
}

ofstream Matrix::openFile(string filename, string path){
    ofstream outputFile(path + '/' + filename);
    if(outputFile.fail()){
        throw FailureOpenFileException();
    }
    return outputFile;
}

ofstream &operator<<(std::ofstream &strm, Matrix matrix) {
    strm << matrix.colsSize << " " << matrix.rowsSize << endl;
    matrix.printToFile(strm, matrix.matrix); 
    return strm;
}

void Matrix::printToFile(std::ofstream &strm, vector<vector<double>> &matrix) {
    for (int i = 0; i < matrix.size(); i++) { 
        for (int j = 0; j < matrix[i].size(); j++) 
            strm << matrix[i][j] << " "; 
        strm << endl; 
    }
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
