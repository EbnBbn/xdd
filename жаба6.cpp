// жаба6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

int* fnullcol(int** matrix, int rows, int cols, int& nullct) {
    int* nulls = (int*)calloc(cols, sizeof(int));

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                nulls[j] = 1;
                break;
            }
        }
    }

    nullct = 0;
    for (int j = 0; j < cols; j++) {
        if (nulls[j] == 1) {
            nullct++;
        }
    }

    int* nullcol = (int*)malloc(nullct * sizeof(int));
    int k = 0;
    for (int j = 0; j < cols; j++) {
        if (nulls[j] == 1) {
            nullcol[k] = j;
            k++;
        }
    }
    free(nulls);
    return nullcol;
}

void removeCols(int** matrix, int rows, int& cols, int* nullcol, int nullct) {
    if (nullct == 0) return;

    for (int i = 0; i < rows; i++) {
        int nj = 0;
        for (int j = 0; j < cols; j++) {
            int skip = 0;
            for (int k = 0; k < nullct; k++) {
                if (nullcol[k] == j) {
                    skip = 1;
                    break;
                }
            }
            if (skip == 0) {
                matrix[i][nj] = matrix[i][j];
                nj++;
            }
        }
        for (int j = nj; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }

    int ncols = cols - nullct;
    for (int i = 0; i < rows; i++) {
        int* nrow = (int*)realloc(matrix[i], ncols * sizeof(int));
        if (nrow) {
            matrix[i] = nrow;
        }
    }

    cols = ncols;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    //пункт 1
    int rows = 2, cols = 2;
    int A, B, C, D;

    do {
        cout << "Введите A(A >= 0): ";
        cin >> A;
    } while (A < 0);
    do {
        cout << "Введите B(B >= 0): ";
        cin >> B;
    } while (B < 0);

    cout << "Введите C и D: " << endl;
    cin >>  C >> D;
    cout << endl;

    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    matrix[0][0] = A;
    matrix[0][1] = B;
    matrix[1][0] = C;
    matrix[1][1] = D;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    rows += A;
    cols += B;

    matrix = (int**)realloc(matrix, rows * sizeof(int*));
    for (int i = 2; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)realloc(matrix[i], cols * sizeof(int));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i < 2 && j < 2) {
                matrix[i][j] = matrix[i][j];
            }
            else {
                matrix[i][j] = (i - 1) * C + (j - 1) * D;
            }
        }
    }

    int nullct;
    int* nullcol = fnullcol(matrix, rows, cols, nullct);

    if (nullct != 0) {
        cout << "Столбцы с нулями: ";
        for (int i = 0; i < nullct; i++) {
            cout << nullcol[i] << " ";
        }
    }
    cout << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    removeCols(matrix, rows, cols, nullcol, nullct);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(nullcol);

    


    //пункт 2
    double a, b;
    cout << "введите числа a и b: "<< endl;
    cin >> a >> b;

    double* p_a = &a;
    double* p_b = &b;

    *p_a *= 3;

    double t = *p_a;
    *p_a = *p_b;
    *p_b = t;

    cout << "После преобразования: a = " << a << ", b = " << b << endl;
    
    return 0;
}