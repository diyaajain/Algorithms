#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *file;
    int k, m, n;
    val sequence;  //have to redefine
    //define matrix

    //open file for reading
    file = fopen("input.txt", "r");
    
    fscanf(file, "%d %d %d", &k, &m, &n);

    //read the sequence
    for (int i = 0; i < k; i++){
        fscanf(file, "%d", sequence[i]);
    }

    //read the matrx
    for (int i = 0;  i < m; i++){
        for (int j = 0; j < n; j++){
            fscanf(file, "%d", matrix[i][j]);
        }
    }
    
    fclose(file);
    return 0;
}
