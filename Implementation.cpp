#include<iostream>
#include "interface.hpp"

using namespace std;
BaseMatrix::BaseMatrix(int rows, int column){
    double** Matrix = new double*[rows];
    for(int i =0; i<column; i++){
        Matrix[i]= new double[column];
    }
    for(int i = 0; i<rows; i++){
        for(int j=0; j<column; j++){
            double temp;
            cout<<"Please enter "<<i<<"'"<<j<<"th element: ";
            cin>>temp;
            Matrix[i][j]= temp;
            
        }
    }
};
