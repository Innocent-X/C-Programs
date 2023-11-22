#include <stdio.h>
#include <stdlib.h>


void print_Matrix(double **matrix, int rows, int columns) {

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            printf("%.1f\t", matrix[i][j]);
        }
        printf("\n");
    }
}
void **convert_into_ref(double **matrix, int rows, int columns)
{
    int row = 0;

    for (int col = 0; col < columns; col++)
    {
        int pivot_row = row; // taking 1st row as pivot
        // finding row which have least pivot
        while (pivot_row < rows && matrix[pivot_row][col] == 0)
        {
            pivot_row++;
        }
        // if first column dont have any pivot continue loop for next column
        if (pivot_row == rows)
        {
            continue;
        }

        // pivot is not in first row dont have least pivot change it
        if (pivot_row != row)
        {
            for (int i = 0; i <= columns; i++)
            {
                double temp = matrix[pivot_row][i];
                matrix[pivot_row][i] = matrix[row][i];
                matrix[row][i] = temp;
            }
        }
        
        double pivot_element = matrix[row][col];
       
       // maaking zeros below leading entery of pivot row
        for (int i = row + 1; i < rows; i++)
        {
            double factor_element = matrix[i][col];

            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] -= factor_element * matrix[row][j]/pivot_element;
            }
        }

        row++;
    }
}
int main() {
  
    int rows = 0;
    int col = 0;
    printf("Enter the number of rows : ");
    scanf("%d", &rows);

    printf("Enter the number of columns : ");
    scanf("%d", &col);

    double **matrix; 

    matrix = (double **)malloc(rows * (sizeof(double *)));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(col * sizeof(double));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("Enter the element of row %d and col %d : ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    }
    printf("%s\n","Matrix you enter:");
    print_Matrix(matrix,rows,col);
    convert_into_ref(matrix,rows,col);
    printf("%s\n","Matrix row echelon form:");
    print_Matrix(matrix,rows,col);

  for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
