#include<iostream>
#include<algorithm>
#include<cmath>
#include "interface.hpp"

using namespace std;
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

void SquareMatrix:: Transpose() {
    for (int i = 0; i < rows; i++) {
        for (int j = i; j < columns; j++) {
            int temp = Matrix[i][j];
            Matrix[i][j]= Matrix[j][i];
            Matrix[j][i]= temp;
        }
    }
}
