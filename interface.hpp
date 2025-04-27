#ifndef INTERFACE_HPP
#define INTEFACE_HPP
class BaseMatrix{
    protected: 
    double** Matrix;
    const int rows, columns;
    public:
    BaseMatrix(int x, int y);
    ~BaseMatrix();
    BaseMatrix operator+(const BaseMatrix& rhs);
    BaseMatrix operator-(const BaseMatrix& rhs);
    BaseMatrix operator*(const BaseMatrix& rhs);
    void Transpose(); // make the thing equal to matrix in the function itself.
    int RowEchelon();
    int Rank();
    int Display();
    int ChangeMatrix();
};
class SquareMatrix: public BaseMatrix{
    protected: 
    int size; //will be equal to either rows or columns
    public:
    SquareMatrix(int a, int b);
    void Inverse(); // make the thing equal to matrix in function itself.
    double Determinant();
};
class IdentityMatrix: public SquareMatrix{

};

#endif
