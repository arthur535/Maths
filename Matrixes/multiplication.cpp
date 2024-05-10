vector<vector<double>> mul(vector<vector<double>> first, vector<vector<double>> second) {
    long r1 = first.size();
    long c1 = first[0].size();
    long r2 = second.size();
    long c2 = second[0].size();
    if(c1 != r2){ throw std::invalid_argument("no viable sizes");}
    vector<vector<double>> mulmatrix(r1, vector<double>(c2));
    for(int i = 0; i < r1; ++i) {
        for(int j = 0; j < c2; ++j) {
            mulmatrix[i][j]=0;
        }
    }
    vector<double> row;
    for(int i = 0; i < r1; ++i) {
        row.clear();
        for(int j = 0; j < c2; ++j){
            for(int k = 0; k < c1; ++k) {
                mulmatrix[i][j] += first[i][k] * second[k][j];
            }
        }
    }
    return mulmatrix;
}
