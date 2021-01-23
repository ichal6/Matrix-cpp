#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

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

        Matrix add(const Matrix & m2);

        Matrix operator+ (const Matrix & m2);

        Matrix subtract(const Matrix &m2);

        Matrix operator-(const Matrix & m2);

        Matrix multiply(const Matrix & m2);

        Matrix operator*(const Matrix & m2);

        void store(string filename, string path);

        static ofstream openFile(string filename, string path);

        void set(int rowsPosition, int colsPosition, double val);

        double get(int rowsPosition, int colsPosition) const;

        int cols() const;

        int rows() const;

        void print();

        friend std::ostream& operator<<(std::ostream &strm, Matrix matrix);

        friend bool operator==(const Matrix& m1, const Matrix& m2);

        vector<double> &operator[](int rowsPosition);
    private:
        void printToFile(ofstream &outputStream);

        void initMatrix(int rowsSize, int colsSize);

        void readMatrixFromFile(std::ifstream &inputStream);

        void makeCopyMatrix(Matrix const &matrixToCopy);

        bool isTheSameSize(Matrix m2) const;

        bool isIndexOutOfBounds(int rowsPosition, int colsPosition) const;

        bool isIndexOutOfBounds(int rowsPosition) const;

        void printToFile(std::ostream &strm, vector<vector<double>> &matrix);
};
