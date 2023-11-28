/*Program to reduce row echelon form  of a matrix
  Author: Saifullah
*/
//header files 
#include <stdio.h>
#include <stdlib.h>
void print_Matrix(double **matrix, int rows, int columns);
void convert_inRef(double **matrix, int rows, int columns);
void convert_into_reduce(double **matrix, int rows, int columns);

int main()
{
    //declairing variable
    int rows,column;

    //taking input
    printf("Enter the number of rows : ");
    scanf("%d", &rows);

    printf("Enter the number of columns : ");
    scanf("%d", &column);

    double **matrix;//creating 2-D array using pointer

    matrix = (double **)malloc(rows * (sizeof(double *)));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(column * sizeof(double));
    }
    
    //taking input elements of array
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("Enter the element of row %d and col %d : ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    }
    //printing matrix
    printf("%s\n", "Matrix you enter:");
    print_Matrix(matrix, rows, column);
    //caling function 
    convert_into_reduce(matrix, rows, column);
    //printing rref
    printf("%s\n", "Matrix reduce row echelon form:");
    print_Matrix(matrix, rows, column);

    //freeing memory
      for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
void print_Matrix(double **matrix, int rows, int columns)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%.1f\t", matrix[i][j]);
        }
        puts("");
    }
}
void convert_inRef(double **matrix, int rows, int columns)
{
    int current_row = 0;//the raw on which operation to be applied

    for (int col = 0; col < columns; col++)
    {
        int pivot_row = current_row; // taking 1st row as pivot
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

        // pivot is not in current row dont have least pivot change it
        if (pivot_row != current_row)
        {
            for (int i = 0; i <= columns; i++)
            {
                double temp = matrix[pivot_row][i];
                matrix[pivot_row][i] = matrix[current_row][i];
                matrix[current_row][i] = temp;
            }
        }

        double pivot_element = matrix[current_row][col];

        // maaking zeros below leading entery of pivot row
        for (int i = current_row + 1; i < rows; i++)
        {
            double factor_element = matrix[i][col];

            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] -= factor_element * matrix[current_row][j] / pivot_element;
            }
        }

        current_row++;
    }
}
void convert_into_reduce(double **matrix, int rows, int columns)
{
    convert_inRef(matrix, rows, columns);                // converting matrix into ref
    for (int current_row = rows - 1; current_row >=0; current_row--) // for traversing through rows in backward
    {
        int pivot_column = -1;
        for (int j = 0; j < columns; j++)
        {
            if (matrix[current_row][j] != 0)
            {
                pivot_column = j;
                break;
            }
        }
        if (pivot_column == -1)//if row dont have pivot i.e zero row goes to above row
        {
            continue;
        }
        else
        {
            double leading_entry = matrix[current_row][pivot_column];
            for (int i = 0; i < columns; i++)//making leading entery 1
            {
                matrix[current_row][i] /= leading_entry;
            }
            if (current_row==0)//if we at the top row break loop because we dont have make any zero
            {
                break;
            }
            

            for (int i = 0; i < current_row; i++)
            {
                double element = matrix[i][pivot_column];//element that we want to convert to 0 
                for (int j = 0; j < columns; j++)
                {
                    matrix[i][j] = matrix[i][j] - (element * matrix[current_row][j]);
                }
            }
        }
    }
  }
