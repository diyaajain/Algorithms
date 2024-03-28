#include <iostream>
#include <fstream>
#include <vector>

int main(){
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
