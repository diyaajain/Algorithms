#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>

using std::vector;
using std::min;

int minDifference(vector <int>& sequence, vector<vector<int>>& matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    int k = sequence.size();

    //dp table to store the minimum absolute differnce for each (r, c, k)
    vector<vector<vector<int>>> dp((m, vector<vector<int>>(n, vector<int>(k, INT_MAX))));

    //absolute difference at the start
    for (int r = 0; r < m; r++){
        for (int c = 0; c < n; c++){
            dp[r][c][0] = std::abs(sequence[0] - matrix[r][c]); 
        }
    }

    //for each element, pick one from 4 directions
    for (int i = 1; i < k; i++){
        for (int r = 0; r < m; r++){
            for (int c = 0; c < n; c++){
                if (r > 0)
                    dp[r][c][i] = min(dp[r][c][i], dp[r-1][c][i-1] + std::abs(sequence[i] - matrix[r][c]));
                if (r < m-1)
                    dp[r][c][i] = min(dp[r][c][i], dp[r+1][c][i-1] + std::abs(sequence[i] - matrix[r][c]));
                if (c > 0)
                    dp[r][c][i] = min(dp[r][c][i], dp[r][c-1][i-1] + std::abs(sequence[i] - matrix[r][c]));
                if (c < n-1)
                    dp[r][c][i] = min(dp[r][c][i], dp[r][c+1][i-1] + std::abs(sequence[i] - matrix[r][c]));
            }
        }
    }
    
    int cur = INT_MAX;
    for (int r = 0; r < m; r++){
        for (int c = 0; c < n; c++){
            cur = min(cur, dp[r][c][k-1]);
        }
    }
}


int main(){
    //read input
    std::ifstream file("input.txt");
    if (!file){
        return 1;
    }
    int k, m, n;
    file >> k >> m >> n;

    std::vector<int> sequence(k);
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));

    //read the sequence
    for (int i = 0; i < k; i++){
        file >> sequence[i];
    }

    //read the matrix
    for (int i = 0;  i < m; i++){
        for (int j = 0; j < n; j++){
            file >> matrix[i][j];
        }
    }
    
    file.close();
    return 0;
}
