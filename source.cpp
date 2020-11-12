#include <iostream>
#include <vector>
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

        // Should write protect by index out of bounds
        void set(int rowsPosition, int colsPosition, double val) 
        {
            matrix[rowsPosition][colsPosition] = val;
        }

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
                    cout << matrix[i][j] << " "; 
                cout << endl; 
            }  
        }
        

    private:
        void initMatrix(int rowsSize, int colsSize)
        {
            for(int indexR = 0; indexR < rowsSize;indexR++) {
                vector<double> singleRow;
                for(int indexC = 0; indexC < colsSize ;indexC++) {
                    singleRow.push_back(1.0); // change to 0.0 for prod version
                }
                matrix.push_back(singleRow);
            }
        }
};

int main() 
{
    Matrix newMatrix = Matrix(4,8);
    Matrix secondMatrix = Matrix(4,8);
    newMatrix.set(2,7,3);
//    newMatrix.print();
//    cout << newMatrix.cols() << endl;

    Matrix resultMatrix = newMatrix.add(secondMatrix);

    resultMatrix.print();
}