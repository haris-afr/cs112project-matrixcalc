#include <iostream>
#include "Implementation.cpp"
using namespace std;


int main(){
	BaseMatrix test(3, 3);
	test.Display();
	test.RowEchelon();
	test.Display();
}
