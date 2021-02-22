#include <iostream>

using namespace std;

int main() {
    // Not a string
    char dog[9] = {'b', 'e', 'a', 'u', 't', 'i', 'f', 'u', 'l'};
    // Is a string
    char cat[9] = {'f', 'a', 't', '&', 'c', 'u', 't', 'e', '\0'};
    // To large
    char bird[12] = "Mr. Jeefies";
    char fish[] = "Fast and testy";
    char bad = 'S';
    
    // Two level matrix
    // Change The order(two lines)
    cout << "Please enter a integer matrix (5x5) sep with a space:" << endl;
    int matrix_l2[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> matrix_l2[i][j];
        }
    }
    cout << "Please Enter the two lines to swap the order:" << endl;
    int m,n;
    cin >> m >> n;
    m -= 1; n -= 1;
    for (int i = 0; i < 5; i++) {
        int t = matrix_l2[m][i];
        matrix_l2[m][i] = matrix_l2[n][i];
        matrix_l2[n][i] = t;
    }
    // Print the matrix
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrix_l2[i][j] << ' ';
        }
        cout <<  endl;
    }
    cout << "Please Enter the two rows to swap the order:" << endl;
    cin >> m >> n;
    m -= 1; n -=1;
    for (int i = 0; i < 5; i++) {
        int t = matrix_l2[i][m];
        matrix_l2[i][m] = matrix_l2[i][n];
        matrix_l2[i][n] = t;
    }
    // Print the matrix
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << matrix_l2[i][j] << ' ';
        }
        cout <<  endl;
    }
}
