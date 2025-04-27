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

