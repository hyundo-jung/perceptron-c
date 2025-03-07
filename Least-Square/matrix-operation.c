#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatrix(double* matrix, int row, int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%f ", matrix[i*col + j]);
        }
        printf("\n");
    }
    printf("\n");
}

double* copyMatrix(double* matrix, int row, int col)
{
    double* two_d_array;
    int i, j;
    two_d_array = malloc(sizeof(double) * row * col);

    if (two_d_array == NULL)
    {
        printf("ERROR: malloc failed! \n");
        exit(1);
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            // one of two method to dynamically allocate 2D array
            two_d_array[i*col + j] = matrix[i*col + j];
        }
    }
    return two_d_array;
} 

double* transpose(double* matrix, int rows, int cols)
{
    double* transposeMatrix = malloc(sizeof(double) * cols * rows);
    int i, j, temp;


    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            transposeMatrix[i + rows*j] = matrix[i*cols + j];
        }
    }

    return transposeMatrix;
}

double* multiplication(double *matrix1, int rows1, int cols1, double *matrix2, int rows2, int cols2)
{
    double* resultMatrix;
    int i, j, k, value, idx = 0;
    resultMatrix = malloc(sizeof(double) * rows1 * cols2);

    for (i = 0; i < rows1; i++)
    {
        for (j = 0; j < cols2; j++)
        {
            value = 0;
            for (k = 0; k < rows2; k++)
            {
                value += matrix1[i*cols1 + k] * matrix2[j + k*cols2];
            }
            resultMatrix[i*cols2 + j] = value;
        }
    }

    return resultMatrix;
}

double* addZeroColum(double *matrix, int row, int col, double* endCol)
{
    double* newMatrix;
    int i, j, n = 0;

    newMatrix = malloc(sizeof(double) * row * (col + 1));

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col + 1; j++)
        {
            if (j == col)
            {
                newMatrix[i*(col + 1) + j] = endCol[n];
                n++;
            }
            else
            {
                newMatrix[i*(col + 1) + j] = matrix[i*col + j];
            }
        }
    }

    return newMatrix;
}

// void inverse(int *matrix, int rows, int cols);

void exchange(double *matrix, int row1, int row2, int col)
{
    double arr[col];
    int i, j;

    for (i = 0; i < col; i++)
    {
        arr[i] = matrix[(row1 - 1)*col + i];
        matrix[(row1-1)*col + i] = matrix[(row2 - 1)*col + i];
    }

    for (i = 0; i < col; i++)
    {
        matrix[(row2 - 1)*col + i] = arr[i];
    }

    return;
}

void mult(double *matrix, double d, int row, int col)
{
    int i;

    for (i = 0; i < col; i++)
    {
        matrix[(row-1)*col + i] *= d;
    }

    return;
}

// add row2 to row1 after multiplying with factor of d
void add(double *matrix, double d, int row1, int row2, int col)
{
    int i;

    for (i = 0; i < col; i++)
    {
        matrix[(row1 - 1)*col + i] += d * matrix[(row2 - 1)*col + i];
    }

    return;
}

void max(double* value, int* pivIdx, double *matrix, int row, int col, int a, int b)
{
    int i, j;

    for (i = a; i < row; i++)
    {
        for (j = b; j < col; j++)
        {
            if (fabs(matrix[i*col + j]) > fabs(value[j]))
            {
                value[j] = matrix[i*col + j];
                pivIdx[j] = i;
            }
        }
    }
}

void findSolution(double* matrix, int row, int col, int pivCount);

void rref(double *matrix, int row, int col, int sol)
{
    // 
    double pivValue[col];
    int pivRow[col];

    // indicate which columns have pivot
    int loc;
    int currentCol = 0;
    int currentRow;
    int pivCol;
    double pivot;
    int i, j;
    int pivTrue;

    for (i = 0; i < col; i++)
    {
        pivValue[i] = 0;
        pivRow[i] = -1;
    }

    for (i = 0; i < row - 1; i++)
    {
        if (currentCol == col)
        {
            return;
        }


        pivTrue = 0;
        loc = 0;

        max(pivValue, pivRow, matrix, row, col, i, currentCol);

        pivCol = -1;
        for (j = currentCol; j < col; j++)
        {
            if (pivValue[j] != 0)
            {
                pivCol = j;
                pivTrue = 1;
                break;
            }
        }

        if (pivTrue == 0)
        {
            return;
        }

        if (pivRow[loc] != i)
        {
            exchange(matrix, i + 1, pivRow[pivCol] + 1, col);
        }


        pivot = matrix[i*col + pivCol];

        for (j = i + 1; j < row; j++)
        {
            if (matrix[j*col + pivCol] != 0 && pivot != 0)
            {
                double multiplier = matrix[j*col + pivCol] / pivot;
                add(matrix, -multiplier, j + 1, i + 1, col);
            }
        }

        currentCol++;
    }

    printMatrix(matrix, row, col);


    // ** row reduced form
    int pivCount = 0;

    for (i = 0; i < col; i++)
    {
        // printf("PivRow: %d \n", pivRow[i]);
        if (pivRow[i] != -1)
        {
            pivCount++;
        }
    }

    int pivColumn[pivCount];

    for (i = 0; i < pivCount; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (fabs(matrix[i*col + j]) > 1e-8)
            {
                pivColumn[i] = j;
                break;
            }
        }
    }
    
    for (i = pivCount - 1; i >= 0; i--)
    {
        
        if (fabs(matrix[i*col + pivColumn[i]]) > 1e-8)
        {
            mult(matrix, 1/matrix[i*col + pivColumn[i]], i + 1, col);
        }

        for (j = 0; j < i; j++)
        {
            if(matrix[j*col + pivColumn[i]] > 1e-8)
            {
                add(matrix, -matrix[j*col + pivColumn[i]], j + 1, i + 1, col);
            }
        }
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            if (fabs(matrix[i*col + j]) < 1e-8)
            {
                matrix[i*col + j] = 0;
            }
        }
    }

    printMatrix(matrix, row, col);

    if (sol == 1)
    {
        findSolution(matrix, row, col, pivCount);
    }
}

void findSolution(double* matrix, int row, int col, int pivCount)
{
    int sol[pivCount];
    double arr[col];
    int i, j;

    int pivColumn[col - 1];

    for (i = 0; i < col - 1; i++)
    {
        pivColumn[i] = -1;
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col - 1; j++)
        {
            if (fabs(matrix[i*col + j]) != 0)
            {
                pivColumn[i] = j;
                break;
            }
        }
    }

    // for (i = 0; i < col - 1; i++)
    // {
    //     printf("%d \n", pivColumn[i]);
    // }


    // int nonPivot[col];

    // if (pivCount < col)
    // {
    //     for (i = 0; i < col; i++)
    //     {
    //         if (pivColumn[i] == -1)
    //         {
    //             nonPivot[i] = 1;
    //         }
    //         else
    //         {
    //             nonPivot[i] = 0;
    //         }
    //     }
    // }

    printf("Result: \n");

    for (i = row - 1; i >= 0; i--)
    {
        for (j = 0; j < col; j++)
        {
            if (j < col - 1 && pivColumn[j] == -1)
            {
                arr[j] = 0;
            }
            else
            {
                arr[j] = matrix[i*col + j]; 
            }
        }

        int basicvariable = 0;
        
        for (j = 0; j < col - 1; j++)
        {
            if (arr[j] != 0 && pivColumn[j] != -1)
            {
                basicvariable = 1;
                printf("x%d = %lf ", j + 1, arr[col - 1]);
            }
        }

        for (j = 0; j < col - 1; j++)
        {
            if (pivColumn[j] == -1 && basicvariable == 1)
            {
                printf("+ (%lf) * x%d ", matrix[i*col +j], j + 1);
            }
        }
        printf("\n");
    }
    printf("\n");
}
