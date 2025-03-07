#include <stdio.h>
#include <stdlib.h>

#include "matrixoperation.c"

int main(void)
{
    int A_rows, A_cols;

    printf("Dimension of Matrix A: ");

    scanf("%d %d", &A_rows, &A_cols);

    printf("Verifying the dimension of Matrix A: %d X %d \n\n", A_rows, A_cols); 

    double* matrixA = malloc(sizeof(double) * A_rows * A_cols);

    int i, j, value;

    for (i = 0; i < A_rows; i++)
    {
        printf("Entry for Row %d: \n", i+1);
        for (j = 0; j < A_cols; j++)
        {
            printf("Element %d: ", i*A_cols + j + 1);
            scanf("%lf", &matrixA[i*A_cols + j]);
        }
        printf("\n");
    }

    printf("Matrix A: \n");
    printMatrix(matrixA, A_rows, A_cols);

    double* matrixA_transpose = copyMatrix(matrixA, A_rows, A_cols);
    int At_rows = A_rows, At_cols = A_cols;

    matrixA_transpose = transpose(matrixA_transpose, At_rows, At_cols);
    At_rows = A_cols, At_cols = A_rows;

    printf("Matrix A transposed: \n");
    printMatrix(matrixA_transpose, At_rows, At_cols);

    double* bCol = malloc(sizeof(double) * A_rows);

    printf("Entry for b column: \n");
    for (i = 0; i < A_rows; i++)
    {
        printf("Element %d: ", i + 1);
        scanf("%lf", &bCol[i]);
    }
    printf("\n");

    double* rhs = multiplication(matrixA_transpose, At_rows, At_cols, bCol, A_rows, 1);
    printf("rhs: \n");
    printMatrix(rhs, At_rows, 1);

    double* lhs = multiplication(matrixA_transpose, At_rows, At_cols, matrixA, A_rows, A_cols);
    printf("lhs: \n");
    printMatrix(lhs, At_rows, A_cols);

    double* augmented_matrix = addZeroColum(lhs, At_rows, A_cols, rhs);

    rref(augmented_matrix, At_rows, A_cols + 1, 1);

    free(matrixA);
    free(bCol);
    free(matrixA_transpose);
    free(rhs);
    free(lhs);
    free(augmented_matrix);
    return 0;
}
