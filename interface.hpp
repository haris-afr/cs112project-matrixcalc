#ifndef INTERFACE_HPP
#define INTEFACE_HPP
class BaseMatrix{
    BaseMatrix(double x, double y);
    int operator+(const BaseMatrix& rhs);
    int operator-(const BaseMatrix& rhs);
    int operator*(const BaseMatrix& rhs);
    int Transpose();
    bool Issingular();
    int Determinant();
    int RowEchelon();
    int Rank();
    int Display();
    int ChangeMatrix();
};
class SquareMatrix: public BaseMatrix{
    int Inverse();
};
class IdentityMatrix: public SquareMatrix{

};

#endif
