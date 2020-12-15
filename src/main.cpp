#include <iostream>
#include <vector>
#include <fstream>
#include "matrix.cpp"

using namespace std;

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

    Matrix matrixAfterAdd = matrix1 + matrix2;
    cout << "Wynik dodawania do macierzy nr 1 macierzy nr 2" << endl;
    matrixAfterAdd.print();
    cout <<  endl;

    Matrix matrixAfterSubtract = matrix1 - matrix2;
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
