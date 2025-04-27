#ifndef INTERFACE_HPP
#define INTEFACE_HPP
class BaseMatrix{
    private: 
    double** Matrix;
    const int rows, columns;
    public:
    BaseMatrix(int x, int y);
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
    public:
    void Inverse(); // make the thing equal to matrix in function itself.
    bool Issingular();
    int Determinant();
};
class IdentityMatrix: public SquareMatrix{

};

#endif
