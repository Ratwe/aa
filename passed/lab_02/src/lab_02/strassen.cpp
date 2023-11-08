#define strassen strassenen_algo
#define m_sub matrix_sub
#define m_add matrix_add

vector<vector<double>> MatrixSolver::strassen(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();

    if (n == 1) {
        vector<vector<double>> C(1, vector<double>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int half_n = n / 2;
    vector<vector<double>> A11(half_n, vector<double>(half_n));
    vector<vector<double>> A12(half_n, vector<double>(half_n));
    vector<vector<double>> A21(half_n, vector<double>(half_n));
    vector<vector<double>> A22(half_n, vector<double>(half_n));
    vector<vector<double>> B11(half_n, vector<double>(half_n));
    vector<vector<double>> B12(half_n, vector<double>(half_n));
    vector<vector<double>> B21(half_n, vector<double>(half_n));
    vector<vector<double>> B22(half_n, vector<double>(half_n));

    for (int i = 0; i < half_n; i++) {
        for (int j = 0; j < half_n; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half_n];
            A21[i][j] = A[i + half_n][j];
            A22[i][j] = A[i + half_n][j + half_n];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half_n];
            B21[i][j] = B[i + half_n][j];
            B22[i][j] = B[i + half_n][j + half_n];
        }
    }