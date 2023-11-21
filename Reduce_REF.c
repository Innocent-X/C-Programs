#include <stdio.h>
#include <stdlib.h>

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
double **convert_into_ref(double **matrix, int rows, int columns)
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
                matrix[i][j] -= factor_element * matrix[row][j] / pivot_element;
            }
        }

        row++;
    }
    return matrix;
}
double **convert_into_reduce(double **matrix, int rows, int columns)
{
    matrix = convert_into_ref(matrix, rows, columns);                // converting matrix into ref
    for (int current_row = rows - 1; current_row > 0; current_row--) // for traversing through rows in backward
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
        if (pivot_column == -1)//if row dont have pivot i.e zero row
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

            for (int i = 0; i < current_row; i++)
            {
                double element = matrix[i][pivot_column];
                for (int j = 0; j < columns; j++)
                {
                    matrix[i][j] = matrix[i][j] - (element * matrix[current_row][j]);
                }
            }
        }
    }
    for (int i = 0; i < columns; i++)//making leading entry of first row 1 
    {
        double leading_entry = matrix[0][i];
        if (leading_entry != 0)
        {
            for (int j = 0; j < columns; j++)
            {
                matrix[0][j] /= leading_entry;
            }
            break;
        }
    }

    return matrix;
}

int main()
{

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
    printf("%s\n", "Matrix you enter:");
    print_Matrix(matrix, rows, col);
    matrix = convert_into_reduce(matrix, rows, col);
    printf("%s\n", "Matrix reduce row echelon form:");
    print_Matrix(matrix, rows, col);

    return 0;
}