vector<vector<double>> P1 = strassen(A11, m_sub(B12, B22));
vector<vector<double>> P2 = strassen(m_add(A11, A12), B22);
vector<vector<double>> P3 = strassen(m_add(A21, A22), B11);
vector<vector<double>> P4 = strassen(A22, m_sub(B21, B11));
vector<vector<double>> P5 = strassen(m_add(A11, A22), m_add(B11, B22));
vector<vector<double>> P6 = strassen(m_sub(A12, A22), m_add(B21, B22));
vector<vector<double>> P7 = strassen(m_sub(A11, A21), m_add(B11, B12));

vector<vector<double>> C11 = matrix_add(matrix_sub(matrix_add(P5, P4), P2), P6);
vector<vector<double>> C12 = matrix_add(P1, P2);
vector<vector<double>> C21 = matrix_add(P3, P4);
vector<vector<double>> C22 = matrix_sub(matrix_sub(matrix_add(P5, P1), P3), P7);

vector<vector<double>> C(n, vector<double>(n, 0));
for (int i = 0; i < half_n; i++) {
    for (int j = 0; j < half_n; j++) {
        C[i][j] = C11[i][j];
        C[i][j + half_n] = C12[i][j];
        C[i + half_n][j] = C21[i][j];
        C[i + half_n][j + half_n] = C22[i][j];
    }
}

mC = C;
return C;
}