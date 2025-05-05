#ifndef INTERFACE_HPP
#define INTERFACE_HPP
class BaseMatrix{
    protected: 
    double** Matrix;
    int rows, columns;
    public:
    BaseMatrix();
    BaseMatrix(int x, int y);
    //~BaseMatrix(); temporarily comment this out cause it creates problems until it is fully implemented
    BaseMatrix& operator=(const BaseMatrix& rhs);
    BaseMatrix operator+(const BaseMatrix& rhs);
    BaseMatrix operator-(const BaseMatrix& rhs);
    BaseMatrix& operator*(const BaseMatrix& rhs);
    BaseMatrix& operator/(double scalar);
    //virtual void Transpose(); // make the thing equal to matrix in the function itself.
    void RowEchelon(bool normalize);
    void ReducedRowEchelon();
    int Rank();
    void Display();
    int ChangeMatrix();
    
    void displayRow(int rowNo);
    void displayCol(int colNo);
    void setRow(int rowNo, double* newRow);
    void setCol(int colNo, double* newCol);
    void getRow(int rowNo, double*);
    void getCol(int colNo, double*);
    void swapRows(int row1, int row2);
    void multiplyRow(int row, double coefficient);
    void rowPlusRow(int row1, int row2, double multiplier);
};

class SquareMatrix: public BaseMatrix{
    protected: 
    int size; //will be equal to either rows or columns
    public:
    SquareMatrix();
    SquareMatrix(int a, int b);
    SquareMatrix Inverse(); // make the thing equal to matrix in function itself.
    double Determinant();
    SquareMatrix Transpose();
};
class IdentityMatrix: public SquareMatrix{

};

#endif
