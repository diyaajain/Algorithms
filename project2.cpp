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
            //std::cout << dp[r][c][0] << std::endl;
        }
    }

    // Iterate over each element in the sequence
    for (int i = 1; i < k; i++) {
        // For each position in the matrix, update the DP state by considering absolute difference scores from all possible previous positions
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (r > 0)
                    dp[r][c][i] = min(dp[r][c][i], dp[r - 1][c][i - 1] + std::abs(sequence[i] - matrix[r][c]));
                    //dp[r][c][i] = dp[r - 1][c][i - 1] + std::abs(sequence[i] - matrix[r][c]);
                if (r < m - 1)
                    dp[r][c][i] = min(dp[r][c][i], dp[r + 1][c][i - 1] + std::abs(sequence[i] - matrix[r][c]));
                    //dp[r][c][i] = dp[r + 1][c][i - 1] + std::abs(sequence[i] - matrix[r][c]);
                if (c > 0)
                    dp[r][c][i] = min(dp[r][c][i], dp[r][c - 1][i - 1] + std::abs(sequence[i] - matrix[r][c]));
                    //dp[r][c][i] = dp[r][c - 1][i - 1] + std::abs(sequence[i] - matrix[r][c]);
                if (c < n - 1)
                    dp[r][c][i] = min(dp[r][c][i], dp[r][c + 1][i - 1] + std::abs(sequence[i] - matrix[r][c]));
                    //dp[r][c][i] = dp[r][c + 1][i - 1] + std::abs(sequence[i] - matrix[r][c]);
                std::cout << dp[r][c][i] << std::endl;
            }
            std::cout << " " << std::endl;
        }
        std::cout << " **" << std::endl;
    }
    std::cout << " " << std::endl;

    int minDifference = INT_MAX;
    //int startRow = -1, startCol = -1;
    int startRow, startCol;

    // Find the minimum score and the starting position
    for (int i = 0; i < k; i++){
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (dp[r][c][i] < minDifference) {
                    minDifference = dp[r][c][i];
                    startRow = r;
                    startCol = c;
                    std::cout << "Minimum difference found at row: " << startRow << ", column: " << startCol << std::endl;
                }
            }
        }
    }
    
    // Output the directions
    vector<char> directions;
    int currRow = startRow, currCol = startCol;
    std::cout << startRow << std::endl;
    std::cout << startCol << std::endl;

    for (int i = 0; i < k - 1; i++) {
        int prevDiff = std::abs(sequence[i] - matrix[currRow][currCol]);
        std::cout << "f" << currRow << std::endl;
        std::cout << "f" << currCol << std::endl;
        std::cout << prevDiff << std::endl;
        if (currRow > 0 && (dp[currRow - 1][currCol][i + 1] == prevDiff + dp[currRow][currCol][i])) {
            directions.push_back('U'); // Move up
            currRow--;
        } else if (currRow < m - 1 && (dp[currRow + 1][currCol][i + 1] == prevDiff + dp[currRow][currCol][i])) {
            directions.push_back('D'); // Move down
            currRow++;
        } else if (currCol > 0 && (dp[currRow][currCol - 1][i + 1] == prevDiff + dp[currRow][currCol][i])) {
            directions.push_back('L'); // Move left
            currCol--;
        } else if (currCol < n - 1 && (dp[currRow][currCol + 1][i + 1] == prevDiff + dp[currRow][currCol][i])) {
            directions.push_back('R'); // Move right
            currCol++;
        }
    }

    // Reverse the directions since we started from the end
    //std::reverse(directions.begin(), directions.end());

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
    std::ifstream file("input2.txt");
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
