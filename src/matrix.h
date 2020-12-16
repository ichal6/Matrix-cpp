#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix 
{
    private:
        int colsSize;
        int rowsSize;
        vector<vector<double>> matrix;

    public:

        Matrix();

        Matrix(int rowsSize, int colsSize);

        Matrix(int size);

        Matrix(string filename, string path);

        Matrix(const Matrix &matrixToCopy);

        Matrix add(Matrix m2);

        Matrix operator+ (const Matrix & m2);

        Matrix subtract(Matrix m2);

        Matrix operator-(const Matrix & m2);

        Matrix multiply(Matrix m2);

        Matrix operator*(const Matrix & m2);

        void store(string filename, string path);

        static ofstream openFile(string filename, string path);

        void set(int rowsPosition, int colsPosition, double val);

        double get(int rowsPosition, int colsPosition) const;

        int cols();

        int rows();

        void print();

        friend std::ofstream& operator<<(std::ofstream &strm, Matrix matrix);

        friend bool operator==(const Matrix& m1, const Matrix& m2);

        vector<double> &operator[](int rowsPosition);
    private:
        void printToFile(ofstream &outputStream);

        void initMatrix(int rowsSize, int colsSize);

        void readMatrixFromFile(std::ifstream &inputStream);

        void makeCopyMatrix(Matrix const &matrixToCopy);

        bool isTheSameSize(Matrix m2);

        bool isIndexOutOfBounds(int rowsPosition, int colsPosition) const;

        bool isIndexOutOfBounds(int rowsPosition) const;

        void printToFile(std::ofstream &strm, vector<vector<double>> &matrix);
};
