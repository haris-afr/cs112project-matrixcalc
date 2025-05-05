#include <iostream>
#include "interface.hpp"
using namespace std;


int main(){
	BaseMatrix test(3, 3);
	test.Display();
	test.ReducedRowEchelon();
	cout << test.Rank() << endl;
	test.Display();
}
