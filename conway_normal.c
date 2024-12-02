#include <stdio.h>
#include <stdlib.h>

// Variáveis globais para o número de linhas e colunas da matriz
int row, col;

// Função que conta o número de células vizinhas vivas
int count_live_neighbour_cell(int a[row][col], int r, int c){
    int i, j, count = 0;
    for(i = r - 1; i <= r + 1; i++){
        for(j = c - 1; j <= c + 1; j++){
            if((i == r && j == c) || (i < 0 || j < 0) || (i >= row || j >= col)){
                continue;
            }
            if(a[i][j] == 1){
                count++;
            }
        }
    }
    return count;
}

int main(){
    // Abre o arquivo para leitura
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê o número de linhas e colunas da matriz do arquivo
    fscanf(file, "%d %d", &row, &col);

    int a[row][col], b[row][col];
    int i, j;
    int neighbour_live_cell;

    // Lê a matriz inicial do arquivo
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            fscanf(file, "%d", &a[i][j]);
        }
    }

    // Fecha o arquivo após a leitura
    fclose(file);

    // Imprime a matriz inicial
    printf("Estado Inicial:\n");
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    // Calcula a próxima geração com base nos vizinhos vivos
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            neighbour_live_cell = count_live_neighbour_cell(a, i, j);
            if(a[i][j] == 1 && (neighbour_live_cell == 2 || neighbour_live_cell == 3)){
                b[i][j] = 1;
            }
            else if(a[i][j] == 0 && neighbour_live_cell == 3){
                b[i][j] = 1;
            }
            else{
                b[i][j] = 0;
            }
        }
    }

    // Salva a próxima geração em um arquivo
    FILE *output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }

    // Escreve o tamanho da matriz na primeira linha
    fprintf(output, "%d %d\n", row, col);
    // fprintf(output, "%d %d\n", row+2, col+2);

    // Imprime a próxima geração na tela
    printf("\nPróxima Geração:\n");
    // for (j = 0; j < col+1; j++) {
    //     printf("0 ");
    //     fprintf(output, "0 ");
    // }
    // printf("0\n");
    // fprintf(output, "0\n");
    for(i = 0; i < row; i++){
        // printf("0 ");
        // fprintf(output, "0 ");
        for(j = 0; j < col; j++){
            fprintf(output, "%d ", b[i][j]);
            printf("%d ", b[i][j]);
        }
        fprintf(output, "\n");
        printf("\n");
        // printf("0\n");
        // fprintf(output, "0\n");
    }
    // for (j = 0; j < col+1; j++) {
    //     printf("0 ");
    //     fprintf(output, "0 ");
    // }
    // printf("0\n");
    // fprintf(output, "0\n");

    // Fecha o arquivo de saída
    fclose(output);

    return 0;
}
