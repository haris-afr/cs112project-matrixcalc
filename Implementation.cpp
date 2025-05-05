#include<iostream>
#include<algorithm>
#include<cmath>
#include "interface.hpp"

using namespace std;
BaseMatrix::BaseMatrix(const BaseMatrix& other) : rows(other.rows), columns(other.columns) { // copy constructor.
    Matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        Matrix[i] = new double[columns];
        for (int j = 0; j < columns; j++) {
            Matrix[i][j] = other.Matrix[i][j];
        }
    }
}
BaseMatrix:: BaseMatrix():rows(3), columns(3){// makes a default 3x3 with 1s. can later use assignment operator to change it.
    Matrix = new double*[3];
    for(int i =0; i<3; i++){
        Matrix[i]= new double[3];
    }
    for(int i = 0; i<3; i++){
        for(int j=0; j<3; j++){
            Matrix[i][j]=1;
        }
    }
}
SquareMatrix:: SquareMatrix():BaseMatrix(), size(3){}// makes a default 3x3 with 1s

BaseMatrix::BaseMatrix(int x, int y): rows(x), columns(y) {
    Matrix = new double*[x];
    for(int i=0; i<x; i++){
        Matrix[i]= new double[y];
    }
    for(int i = 0; i<x; i++){
        for(int j=0; j<y; j++){
            double temp;
            cout<<"Please enter "<<i<<"'"<<j<<"th element: ";
            cin>>temp;
            Matrix[i][j]= temp;
        }
    }
};

void BaseMatrix::Display(){
    for(int i= 0; i<rows;i++){
        for(int j=0; j<columns; j++){
            cout<<Matrix[i][j]<<" ";
        }
        cout<<endl;
    }
};
SquareMatrix:: SquareMatrix(int a, int b):BaseMatrix(a,b), size(a){};//constructor for squarematrix.

double SquareMatrix:: Determinant(){
    double det = 1.0;
    SquareMatrix temp(*this);
    //need to find the pivot which will be the largest value in the column.
    for(int i=0; i<size; i++){
        int pivot =i;
        for(int j=i+1; j<size; j++){
            if(abs(temp.Matrix[j][i])>abs(temp.Matrix[pivot][i])){
                pivot= j;
            }
        }
        if(pivot !=i){ //swap temp[pivot][i] with temp[i][j]
            for(int j=0; j<size; j++){
                std::swap(temp.Matrix[i][j], temp.Matrix[pivot][j]);
            }
            det *=-1;
        }
        if(temp.Matrix[i][i]==0.0){return 0;}// if top row is 0 then it is singular.

        for(int j=i+1; j<size; j++){ //gaussian elimination.
            double factor= temp.Matrix[j][i]/temp.Matrix[i][i];
            for(int k=i; k<size; k++){
                temp.Matrix[j][k]-= factor*temp.Matrix[i][k];
            }
        }
        det *= temp.Matrix[i][i];

    }
    return det;

}

void BaseMatrix::displayRow(int rowNo){
	for (int i = 0; i < columns; i++){
		cout << Matrix[rowNo][i] << " ";
	}
	cout << endl;
}
void BaseMatrix::displayCol(int colNo){
	for (int i = 0; i < rows; i++){
		cout << Matrix[i][colNo] << endl;
	}
	cout << endl;
}

void BaseMatrix::setRow(int rowNo, double* newRow){
	for (int i = 0; i < columns; i++){
		Matrix[rowNo][i] = newRow[i];
	}
}
void BaseMatrix::setCol(int colNo, double* newCol){
	for (int i = 0; i < rows; i++){
		Matrix[i][colNo] = newCol[i];
	}
}
void BaseMatrix::getRow(int rowNo, double* rowArray){
	for (int i = 0; i < columns; i++){
		rowArray[i] = Matrix[rowNo][i];
	}
}
void BaseMatrix::getCol(int colNo, double* ColArray){
	for (int i = 0; i < rows; i++){
		ColArray[i] = Matrix[i][colNo];
	}
}

void BaseMatrix::swapRows(int row1, int row2){
		double *tempRow = new double [columns];
		getRow(row1, tempRow);
		setRow(row1, Matrix[row2]);
		setRow(row2, tempRow);
		delete tempRow;
}

void BaseMatrix::multiplyRow(int row, double coefficient){
	for (int i = 0; i < columns; i++){
		Matrix[row][i] *= coefficient;
	}
}

void BaseMatrix::rowPlusRow(int row1, int row2, double multiplier = 1){
	for (int i = 0; i < columns;i++){
		Matrix[row1][i] += Matrix[row2][i] * multiplier;
	}
}

void BaseMatrix::RowEchelon(bool normalize = 0) {
    int pivotCol = 0;
    for (int pivotRow = 0; pivotRow < rows && pivotCol < columns; pivotRow++) {
        // Find the first row with a non-zero entry in pivotCol
        int i = pivotRow;
        while (i < rows && Matrix[i][pivotCol] == 0) {
            i++;
        }
        if (i == rows) { //if i is equal to rows, i.e. we've gone beyond the scope of the matrix...
            pivotCol++;  // no pivot in this column, go to the next column
            pivotRow--;  // to off-set pivotRow++ we do pivotRow-- since we want to do the same row again
            continue;
        }
        if (i != pivotRow) {	
            swapRows(pivotRow, i); 
        }
        // If the user asks to normalize, make the pivot = 1
        if (normalize){
        multiplyRow(pivotRow, 1.0 / Matrix[pivotRow][pivotCol]);
    	}
		// make the below elements = 0
        for (int row = pivotRow + 1; row < rows; row++) {
        	if (normalize){
            rowPlusRow(row, pivotRow, -Matrix[row][pivotCol]);
            }
            else{
            rowPlusRow(row, pivotRow, -Matrix[row][pivotCol]/Matrix[pivotRow][pivotCol]);
			}
        }
        pivotCol++;
    }
}

void BaseMatrix::ReducedRowEchelon(){
	RowEchelon(1);
	for (int pivotRow=rows-1;pivotRow >= 0;pivotRow--){
		int column, pivotCol = -1;
		column = 0;
		while (true){
			if (Matrix[pivotRow][column] != 0){
				pivotCol = column;
				break;
			}
			else{
				column++;
			}
			if (column >= columns){
				break;
			}
		}
		if (pivotCol == -1){
			continue;
		}
		for (int row = pivotRow-1; row>= 0; row--){
			rowPlusRow(row, pivotRow, -Matrix[row][pivotCol]);
		}
	}
}

int BaseMatrix::Rank(){
	RowEchelon(0);
	int zeroRows = rows;
	int rank = 0;
	for (int row = 0; row < rows; row++){
		bool zeroRow = 1;
		for (int column = 0; column < columns; column++){
			if (Matrix[row][column] != 0){
				zeroRow = 0;
				break;
			}
		}
		if (zeroRow == 0){
			zeroRows--;
			continue;
		}
	}
	rank = rows - zeroRows;
	return rank;
}

BaseMatrix& BaseMatrix:: operator=(const BaseMatrix& rhs){
    for(int i =0; i<rows; i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;

    rows = rhs.rows;
    columns = rhs.columns;
    Matrix = new double*[rows];
    for(int i =0; i<rows; i++){
        Matrix[i]= new double[columns];
    }
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            Matrix[i][j] = rhs.Matrix[i][j];
        }
    }
    
    return *this;
}

SquareMatrix SquareMatrix:: Transpose() {
    SquareMatrix result;
    result = *this;

    for (int i = 0; i < rows; i++) {
        for (int j = i; j < columns; j++) {
            int temp = result.Matrix[i][j];
            result.Matrix[i][j]= result.Matrix[j][i];
            result.Matrix[j][i]= temp;
        }
    }
    return result;
}



BaseMatrix& BaseMatrix::operator*(const BaseMatrix& rhs) {
    if (columns != rhs.rows) {
        throw std::invalid_argument("Matrix dimensions not compatible for multiplication.");
    }
    BaseMatrix result(rows, rhs.columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rhs.columns; ++j) {
            result.Matrix[i][j] = 0;
            for (int k = 0; k < columns; ++k) {
                result.Matrix[i][j] += Matrix[i][k] * rhs.Matrix[k][j];
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        delete[] Matrix[i];
    }
    delete[] Matrix;

    rows = result.rows;
    columns = result.columns;
    Matrix = new double* [rows];
    for (int i = 0; i < rows; i++) {
        Matrix[i] = new double[columns];
        for (int j = 0; j < columns; j++) {
            Matrix[i][j] = result.Matrix[i][j];
        }
    }

    return *this;
}





BaseMatrix& BaseMatrix::operator/(double scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero.");
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            Matrix[i][j] /= scalar;
        }
    }

    return *this;
}
BaseMatrix BaseMatrix::operator+(const BaseMatrix& rhs) const {
    if (rows != rhs.rows || columns != rhs.columns) {
        throw std::invalid_argument("Matrix dimensions must match for addition.");
    }

    BaseMatrix result(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.Matrix[i][j] = Matrix[i][j] + rhs.Matrix[i][j];
        }
    }
    return result;
}

BaseMatrix BaseMatrix::operator-(const BaseMatrix& rhs) const {
    if (rows != rhs.rows || columns != rhs.columns) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction.");
    }

    BaseMatrix result(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result.Matrix[i][j] = Matrix[i][j] - rhs.Matrix[i][j];
        }
    }
    return result;
}

bool BaseMatrix::operator==(const BaseMatrix& rhs) const {
    if (rows != rhs.rows || columns != rhs.columns) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (Matrix[i][j] != rhs.Matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

SquareMatrix SquareMatrix::Inverse() {
    const double EPSILON = 1e-10; // using this for floating point precision.
    
    // Create augmented matrix [Matrix|I]
    double** augmented = new double*[size];
    for (int i = 0; i < size; i++) {
        augmented[i] = new double[2 * size];
        for (int j = 0; j < size; j++) {
            augmented[i][j] = Matrix[i][j];
        }
        for (int j = size; j < 2 * size; j++) {
            augmented[i][j] = (i == (j - size)) ? 1.0 : 0.0;
        }
    }

    // Performing Gauss Jordan elimination
    for (int col = 0; col < size; col++) {
        // Partial pivoting
        int pivot = col;
        for (int row = col + 1; row < size; row++) {
            if (fabs(augmented[row][col]) > fabs(augmented[pivot][col])) {
                pivot = row;
            }
        }
        
        if (pivot != col) {
            for (int k = 0; k < 2 * size; k++) {
                swap(augmented[col][k], augmented[pivot][k]);
            }
        }

        // Checking for singularity
        if (fabs(augmented[col][col]) < EPSILON) {
            for (int i = 0; i < size; i++) delete[] augmented[i];
            delete[] augmented;
            throw runtime_error("Matrix is singular");
        }

        // Normalize pivot row
        double pivot_val = augmented[col][col];
        for (int k = col; k < 2 * size; k++) {
            augmented[col][k] /= pivot_val;
        }

        // Eliminate other rows
        for (int row = 0; row < size; row++) {
            if (row != col && fabs(augmented[row][col]) > EPSILON) {
                double factor = augmented[row][col];
                for (int k = col; k < 2 * size; k++) {
                    augmented[row][k] -= factor * augmented[col][k];
                }
            }
        }
    }
    SquareMatrix result;
    result = *this;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.Matrix[i][j] = augmented[i][j + size];
        }
    }
    for (int i = 0; i < size; i++) delete[] augmented[i];
    delete[] augmented;
    return result;
}
