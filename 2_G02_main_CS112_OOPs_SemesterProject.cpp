#include <iostream>
#include "2_G02_Implementation_CS112_OOPs_SemesterProject.cpp"
using namespace std;

void showMainMenu() {
    cout << "\n==== MATRIX CALCULATOR MENU ====\n";
    cout << "1. Enter Matrix A\n";
    cout << "2. Enter Matrix B\n";
    cout << "3. Display Matrices\n";
    cout << "4. Add A + B\n";
    cout << "5. Subtract A - B\n";
    cout << "6. Multiply A * B\n";
    cout << "7. Divide A by scalar\n";
    cout << "8. Check if A == B\n";
    cout << "9. Row Echelon Form of A\n";
    cout << "10. Reduced Row Echelon Form of A\n";
    cout << "11. Rank of A\n";
    cout << "12. Transpose of Square Matrix\n";
    cout << "13. Determinant of Square Matrix\n";
    cout << "14. Inverse of Square Matrix\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main(){
	BaseMatrix A, B;
    SquareMatrix S;
    BaseMatrix result;
    int choice;
    bool running = true;

    while (running) {
        showMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                A.ChangeMatrix();
                break;
            case 2:
                B.ChangeMatrix();
                break;
            case 3:
                cout << "\nMatrix A:\n";
                A.Display();
                cout << "\nMatrix B:\n";
                B.Display();
                break;
            case 4: {
                try {
                    BaseMatrix C = A + B;
                    cout << "\nA + B = \n";
                    C.Display();
                } catch (...) {
                    cout << "Error: Matrices must have the same dimensions.\n";
                }
                break;
            }
            case 5: {
                try {
                    BaseMatrix C = A - B;
                    cout << "\nA - B = \n";
                    C.Display();
                } catch (...) {
                    cout << "Error: Matrices must have the same dimensions.\n";
                }
                break;
            }
            case 6: {
                try {
                    BaseMatrix C = A * B;
                    cout << "\nA * B = \n";
                    C.Display();
                } catch (...) {
                    cout << "Error: Incompatible matrix sizes for multiplication.\n";
                }
                break;
            }
            case 7: {
                double scalar;
                cout << "Enter scalar to divide A by: ";
                cin >> scalar;
                try {
                    BaseMatrix C = A / scalar;
                    cout << "\nA / " << scalar << " = \n";
                    C.Display();
                } catch (...) {
                    cout << "Error: Division failed.\n";
                }
                break;
            }
            case 8:
                cout << (A == B ? "\nA and B are equal.\n" : "\nA and B are NOT equal.\n");
                break;
            case 9:
            	
                cout << "\nRow Echelon Form of A:\n";
                result = A.RowEchelon(false);
                result.Display();
                break;
            case 10:
                cout << "\nReduced Row Echelon Form of A:\n";
                result = A.ReducedRowEchelon();
                result.Display();
                break;
            case 11:
                cout << "\nRank of A: " << A.Rank() << endl;
                break;
            case 12:
                S.ChangeMatrix(); // Prompt user for square matrix
                cout << "\nTranspose:\n";
                S.Transpose().Display();
                break;
            case 13:
                S.ChangeMatrix();
                cout << "\nDeterminant: " << S.Determinant() << endl;
                break;
            case 14:
                S.ChangeMatrix();
                try {
                    cout << "\nInverse:\n";
                    S.Inverse().Display();
                } catch (...) {
                    cout << "Error: Matrix is not invertible.\n";
                }
                break;
            case 0:
                running = false;
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }
}// HSSSSSSSSSSSS