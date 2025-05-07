#ifndef INTERFACE_HPP
#define INTERFACE_HPP
class BaseMatrix{
    protected: 
    double** Matrix;
    int rows, columns;
    public:
    BaseMatrix();
    BaseMatrix(int x, int y);
    BaseMatrix(const BaseMatrix& other);//copy constructor.
    ~BaseMatrix();
    BaseMatrix& operator=(const BaseMatrix& rhs);
    BaseMatrix operator+(const BaseMatrix& rhs);
    BaseMatrix operator-(const BaseMatrix& rhs);
    BaseMatrix operator*(const BaseMatrix& rhs);
    BaseMatrix operator/(double scalar);
    bool operator==(const BaseMatrix& rhs);
    //virtual void Transpose(); // make the thing equal to matrix in the function itself.
    BaseMatrix RowEchelon(bool normalize);
    BaseMatrix ReducedRowEchelon();
    int Rank();
    void Display();
    virtual void ChangeMatrix();
    
    void setRow(int rowNo, double* newRow, BaseMatrix& givenMatrix);
    void getRow(int rowNo, double*, BaseMatrix& givenMatrix);
    void swapRows(int row1, int row2, BaseMatrix& givenMatrix);
    void multiplyRow(int row, double coefficient, BaseMatrix& givenMatrix);
    void rowPlusRow(int row1, int row2, BaseMatrix& givenMatrix, double multiplier);
};

class SquareMatrix: public BaseMatrix{
    protected: 
    int size; //will be equal to either rows or columns
    public:
    SquareMatrix();
    SquareMatrix(int a);
    SquareMatrix(const SquareMatrix& other); //copy construcot
    SquareMatrix& operator=(const SquareMatrix& other);
    SquareMatrix Inverse(); // make the thing equal to matrix in function itself.
    double Determinant();
    SquareMatrix Transpose();
    void ChangeMatrix() override;
};

#endif
