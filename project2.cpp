//run g++ -std=c++17 project2.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>

using std::vector;
using std::min;

// Function to calculate the minimum absolute difference between a sequence and a matrix
int minDifference(vector<int>& sequence, vector<vector<int> >& matrix) {
    int m = matrix.size(); // Number of rows in the matrix
    int n = matrix[0].size(); // Number of columns in the matrix
    int k = sequence.size(); // Size of the sequence

    // Dynamic programming table to store the minimum absolute difference for each (row, column, sequence index) combination
    vector<vector<vector<int> > > dp(m, vector<vector<int> >(n, vector<int>(k, INT_MAX)));

    // Initialize the DP table for the first sequence element
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            dp[r][c][0] = std::abs(sequence[0] - matrix[r][c]);
        }
    }

    // Iterate over each element in the sequence
    for (int i = 1; i < k; i++) {
        // For each position in the matrix, update the DP state by considering absolute difference scores from all possible previous positions
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (r > 0)
                    dp[r][c][i] = min(dp[r][c][i], dp[r - 1][c][i - 1] + std::abs(sequence[i] - matrix[r][c]));
                if (r < m - 1)
                    dp[r][c][i] = min(dp[r][c][i], dp[r + 1][c][i - 1] + std::abs(sequence[i] - matrix[r][c]));
                if (c > 0)
                    dp[r][c][i] = min(dp[r][c][i], dp[r][c - 1][i - 1] + std::abs(sequence[i] - matrix[r][c]));
                if (c < n - 1)
                    dp[r][c][i] = min(dp[r][c][i], dp[r][c + 1][i - 1] + std::abs(sequence[i] - matrix[r][c]));
            }
        }
    }

    int minDifference = INT_MAX;
    int startRow, startCol;

    // Find the minimum score and the starting position
    for (int r = 0; r < m; r++){
        for (int c = 0; c < n; c++){
            if(minDifference > dp[r][c][k-1]){
                minDifference = dp[r][c][k-1];
                startRow = r;
                startCol = c;
                continue;
            }
        }
    }

    // Output the directions
    vector<int> minStore(4, INT_MAX);
    vector<char> directions(k-1);
    int currRow = startRow, currCol = startCol;

    //finding which direction to move
    for (int dir = k - 2; dir >= 0; dir--){
        if (currRow > 0)
            minStore[0] = dp[currRow-1][currCol][dir];
        if (currRow < m - 1)
            minStore[1] = dp[currRow+1][currCol][dir];
        if (currCol > 0)
            minStore[2] = dp[currRow][currCol-1][dir];
        if (currCol < n - 1)
            minStore[3] = dp[currRow][currCol+1][dir];
        int minDirection = *std::min_element(directions.begin(), directions.end());

        /*Here, the directions are printed out differently (opposite direction) than the actual direction
        because we are going back from bottom to the top*/
        if (minStore[0] == minDirection) {
            directions[dir] = 'D'; // Move up
            currRow--;
        } else if (minStore[1] == minDirection) {
            directions[dir] = 'U'; // Move down
            currRow++;
        } else if (minStore[2] == minDirection) {
            directions[dir] = 'R'; //Move left
            currCol--;
        } else if (minStore[3] == minDirection) {
            directions[dir] = 'L'; // Move right
            currCol++;
        }
        for (int i = 0; i < 4; i++){
            minStore[i] = INT_MAX;
        }
    }

    startRow = currRow;
    startCol = currCol;

    // Write output to file
    std::ofstream output("output.txt");
    if (!output) {
        std::cerr << "Error opening output file.\n";
        return 1;
    }
    
    output << minDifference << std::endl;
    output << startRow + 1 << " " << startCol + 1 << std::endl;
    for (char dir : directions) {
        output << dir << " ";
    }
    output << std::endl;

    output.close();
    return 0;
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    int k, m, n;
    file >> k >> m >> n;

    vector<int> sequence(k);
    vector<vector<int> > matrix(m, vector<int>(n));

    for (int i = 0; i < k; i++) {
        file >> sequence[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            file >> matrix[i][j];
        }
    }
    
    return minDifference(sequence, matrix);
    file.close();
}
