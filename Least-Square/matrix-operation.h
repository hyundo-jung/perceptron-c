void printMatrix(int* matrix, int row, int col);

int* copyMatrix(int *matrix, int row, int col);

int* transpose(int *matrix, int row, int col);

int* multiplication(int *matrix1, int rows1, int cols1, int *matrix2, int rows2, int cols2);

int* addZeroColum(int *matrix, int row, int col);

void inverse(int **matrix, int rows, int cols);

void exchange(int *matrix, int row1, int row2, int col);

void mult(int *matrix, double d, int row, int col);

void add(int *matrix, double d, int row1, int row2, int col);

int* rref(int *matrix, int row, int col);
