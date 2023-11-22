#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void print_Matrix(double **matrix, int rows, int columns)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%.1f\t", matrix[i][j]);
        }
        printf("\n");
    }
}
double determinant(double **matrix, int rows, int columns)
{
    double determinant = 1;
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
            determinant *= -1;//as we swapp we change sign of determinant
            for (int i = 0; i <= columns; i++)
            {
                double temp = matrix[pivot_row][i];
                matrix[pivot_row][i] = matrix[row][i];
                matrix[row][i] = temp;
            }
        }

        // divding pivot row with leading entery
        double pivot_element = matrix[row][col];
        determinant *= pivot_element;
        for (int i = 0; i < columns; i++)
        {
            matrix[row][i] /= pivot_element;
        }

        // maaking zeros below leading entery of pivot row
        for (int i = row + 1; i < rows; i++)
        {
            double factor_element = matrix[i][col];

            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] -= factor_element * matrix[row][j];
            }
        }

        row++;
    }
    bool fullRank = false;
    for (int i = 0; i < columns; i++)
    {
        double leading_entry = matrix[columns - 1][i];
        if (leading_entry != 0)
        {
            fullRank = true;

            break;
        }
    }
    if (fullRank == false)//if matrix is not full rank determianant is 0
    {
        return 0;
    }

    return determinant;
}
int main() {
  
    int rows = 0;
    int col = 0;
    printf("Enter the number of rows : ");
    scanf("%d", &rows);

    printf("Enter the number of columns : ");
    scanf("%d", &col);
     if (rows!=col)
    {
        puts("Inverse can not be calculated.Matrix should be square.");
        return 0;
    }

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
    printf("Determinant of matrix is  %.2lf\n",determinant(matrix, rows, col));

    
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;

    
}
