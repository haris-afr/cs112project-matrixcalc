#include<iostream>
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
                swap(temp.Matrix[i][j], temp.Matrix[pivot][j]);
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

