#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
void print_Matrix(double **matrix, int rows, int columns)
{

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%.3f\t", matrix[i][j]);
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
            determinant *= -1; // as we swapp we change sign of determinant
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
    if (fullRank == false) // if matrix is not full rank determianant is 0
    {
        return 0;
    }

    return determinant;
}
double **transpose(double **matrix, int rows, int columns)
{
    double **output;
    output = (double **)malloc(rows * (sizeof(double *)));
    for (int i = 0; i < rows; i++)
    {
        output[i] = (double *)malloc(columns * sizeof(double));
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            output[j][i] = matrix[i][j];
        }
    }
    return output;
}
double **inverse(double **matrix, int rows, int columns,double*det)
{
    double **minor;  // minor matrix
    double **output; // matrix for output
    output = (double **)malloc(rows * (sizeof(double *)));
    for (int i = 0; i < rows; i++)
    {
        output[i] = (double *)malloc(columns * sizeof(double));
    }

    minor = (double **)malloc((rows - 1) * (sizeof(double *)));
    for (int i = 0; i < rows; i++)
    {
        minor[i] = (double *)malloc((columns - 1) * sizeof(double));
    }
    int minor_row = 0, minor_colum = 0;
    // getting adjoint
    for (int current_row = 0; current_row < rows; current_row++)
    {

        for (int current_colum = 0; current_colum < columns; current_colum++)
        {
            if (matrix[current_row][current_colum] == 0)
            {
                continue;
            }

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    if (i != current_row && j != current_colum)
                    {
                        minor[minor_row][minor_colum] = matrix[i][j];

                        if ((minor_colum + 1) < (columns - 1))
                        {
                            minor_colum++;
                        }
                        else
                        {
                            minor_row++;
                            minor_colum = 0;
                        }
                    }
                }
            }
            output[current_row][current_colum] = pow(-1, current_row + current_colum) * determinant(minor, rows - 1, columns - 1);
            minor_row = 0;
        }
    }
    output = transpose(output, rows, columns);
    // dividing by determinant
    double determint = determinant(matrix, rows, columns);
    if (determint==0)
    {
        *det=0;
    }
    

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            output[i][j] /= determint;
        }
    }
    return output;
}

int main()
{

    int rows = 0;
    int col = 0;
    printf("Enter the number of rows : ");
    scanf("%d", &rows);

    printf("Enter the number of columns : ");
    scanf("%d", &col);
    if (rows != col)
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
    printf("%s\n", "Matrix you enter:");
    print_Matrix(matrix, rows, col);
    double det;
    
    matrix=inverse(matrix,rows,col,&det);
   
   if (det==0)
    {
        printf("%s","Determinant is Zero Inverse cannot be calculated.");
    }
    else{
        puts("The inverse of matrix is");
        print_Matrix(matrix,rows,col);
    }
    

    



    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
