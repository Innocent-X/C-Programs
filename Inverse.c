/*Program to find inverse  of a matrix
  Author: Saifullah
*/

// header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
// function prototype

void print_Matrix(double **matrix, int rows, int columns);             // function for printing matrix
double determinant(double **matrix, int rows, int columns);            // function to find determinant
double **transpose(double **matrix, int rows, int columns);            // function to find transpose
double **inverse(double **matrix, int rows, int columns, double *det); // function to find inverse

int main(void)
{
    // declairing variable
    int order;
    // taking input
    printf("Enter the order of square matrix which inverse to be found: ");
    scanf("%d", &order);

    double **matrix; // creating 2 D array

    matrix = (double **)malloc(order * (sizeof(double *))); // allocating memory for rows using dynamic memory allocation
    for (int i = 0; i < order; i++)
    {
        matrix[i] = (double *)malloc(order * sizeof(double)); // allocating memory for col using dynamic memory allocation
    }

    // taking input of matrix
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            printf("Enter the element of row %d and col %d : ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    }

    // printing matrix which user enter
    printf("%s\n", "Matrix you enter:");
    print_Matrix(matrix, order, order);

    if (order == 1) // if order of matrix is 1
    {
        if (matrix[0][0] == 0)
        {
            printf("%s", "Determinant is Zero Inverse cannot be calculated.");
        }
        else
        {
            printf("Inverse of matrix is %.2lf", 1 / matrix[0][0]);
        }
        return 0;
    }
    double det = 1;
    matrix = inverse(matrix, order, order, &det);

    if (det == 0)
    {
        printf("%s", "Determinant is Zero Inverse cannot be calculated.");
    }
    else
    {
        puts("The inverse of matrix is");
        print_Matrix(matrix,order,order);
    }

    // freeing memory which we allocated
    for (int i = 0; i < order; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;

} // end main
// function defination
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
double determinant(double **matrix, int rows, int columns)
{
    double determinant = 1;
    int current_row = 0;

    for (int col = 0; col < columns; col++)
    {
        int pivot_row =current_row; // taking 1st row as pivot
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

        // pivot is not in current row  change it
        if (pivot_row != current_row)
        {
            determinant *= -1; // as we swap we change sign of determinant
            for (int i = 0; i <= columns; i++)
            {
                double temp = matrix[pivot_row][i];
                matrix[pivot_row][i] = matrix[current_row][i];
                matrix[current_row][i] = temp;
            }
        }

        // mutilpying determiant with leading entery
        double pivot_element = matrix[current_row][col];
        determinant *= pivot_element;

        // making zeros below leading entery of pivot row
        for (int i = current_row + 1; i < rows; i++)
        {
            double factor_element = matrix[i][col] / pivot_element;

            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] -= factor_element * matrix[current_row][j];
            }
        }

        current_row++;
    }
    bool fullRank = false; // checking if ref is full rank
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
double **inverse(double **matrix, int rows, int columns, double *det)
{
    double **minor;  // minor matrix
    double **output; // matrix for output
    //allocating memory for minor and output matrix inverse
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


    int minor_row = 0, minor_colum = 0;//initializing row and col 0 for minor
    // getting adjoint
    for (int current_row = 0; current_row < rows; current_row++)
    {

        for (int current_colum = 0; current_colum < columns; current_colum++)
        {

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
    // finding determinant
    double determint = determinant(matrix, rows, columns);
    if (determint == 0)//if determiant is zero
    {
        *det = 0;
        return output;
    }
    //if not divide adjoint by determinant
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            output[i][j] /= determint;
        }
    }
    return output;
}
