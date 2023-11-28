/*Program to find determinant  of am matrix 
  Author: Saifullah
*/

//header files 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//function prototype
void print_Matrix(double **matrix, int rows, int columns);//function for printing matrix
double determinant(double **matrix, int rows, int columns);//function to fond determinant


int main(void){
    //declairing variable
    int order;
    //taking input
    printf("Enter the order of square matrix which determinant to be found: ");
    scanf("%d", &order);

    
    

    double **matrix;//creating 2 D array 

    matrix = (double **)malloc(order * (sizeof(double *)));//allocating memory for rows using dynamic memory allocation
    for (int i = 0; i < order; i++)
    {
        matrix[i] = (double *)malloc(order * sizeof(double));//allocating memory for col using dynamic memory allocation
    }

    //taking input of matrix
    for (int i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            printf("Enter the element of row %d and col %d : ", i, j);
            scanf("%lf", &matrix[i][j]);
        }
    }
   
    //printing matrix which user enter
    printf("%s\n","Matrix you enter:");
    print_Matrix(matrix,order,order);

    if (order==1)//if order of matrix is 1 
    {
        printf("Determinant of matrix is %.2lf",matrix[0][0]);
        return 0;
    }
    
    printf("Determinant of matrix is  %.2lf\n",determinant(matrix, order, order));//printing determiant of matrix
    

    //freeing memory which we allocated 
    for (int i = 0; i < order; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;

    
}//end main
//function defination
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
