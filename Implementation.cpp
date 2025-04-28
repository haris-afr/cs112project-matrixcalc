#include<iostream>
#include<algorithm>
#include<cmath>
#include "interface.hpp"

using namespace std;
BaseMatrix::BaseMatrix(int x, int y): rows(x), columns(y) {
    Matrix = new double*[x];
    for(int i =0; i<y; i++){
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

void BaseMatrix::RowEchelon(){
	int pivotRow;
	for (int i = 0; i < rows; i++){
		if(Matrix[i][0] != 0){
			pivotRow = i;
			break;
		}
	}
	if (pivotRow != 0){
		swapRows(0, pivotRow);
	}
}
void BaseMatrix::ReducedRowEchelon(){
	cout << "hi";
}

int BaseMatrix::Rank(){
	cout << "hi";	
	return 0;
}

BaseMatrix& BaseMatrix:: operator=(const BaseMatrix& rhs){
    for(int i =0; i<rows; i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;

    rows= rhs.rows;
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
