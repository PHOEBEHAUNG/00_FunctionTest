#include <math.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <time.h> 

int *matrix;

void GenMatrix(int rowN, int colN, int rootX, int rootY)
{
  int i = 0;
  int j = 0;
  int a = 0;
  matrix = calloc(rowN * colN, sizeof(int));

  srand(time(NULL));
  matrix[rootX * colN + rootY] = 1;
  
  for(i = 0; i < rowN; i++)
  {
    printf("[");
    for(j = 0; j < colN; j++)
    {
      //a = (rand() % 100) + 1;
      //a = a % 2;
      //matrix[i * colN + j] = a;
      printf("%d ", matrix[i * colN + j]);
    }
    printf("]\r\n");
  }

  printf("\r\n");
}

void FreeMatrix()
{
  free(matrix);
}

int calExcuteTimes(int rowN, int colN)
{
  int res = 0;
  int end = 0;
  int center = 0;
  int *subMatrix;

  int i = 0;
  int j = 0;

  subMatrix = calloc(rowN * colN, sizeof(int));

  while(end == 0)
  {
    for(i = 0; i < rowN; i++)
    {
      for(j = 0; j < colN; j++)
      {
        center = matrix[i * colN + j];

        if(center == 1)
        {
          subMatrix[i * colN + j] = center;
          continue;
        }

        /// top left
        if(i == 0 && j == 0)
        {
          /// below || right
          if((matrix[i * colN + j + rowN] == 1) || (matrix[i * colN + j + 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
        }
        /// top right
        else if(i == 0 && j == (colN - 1))
        {
          /// below || left
          if((matrix[i * colN + j + rowN] == 1) || (matrix[i * colN + j - 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
        }
        /// bottom left
        else if(i == (rowN - 1) && j == 0)
        {
          /// top || right
          if((matrix[i * colN + j - rowN] == 1) || (matrix[i * colN + j + 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
          
        }
        /// bottom right 
        else if(i == (rowN - 1) && j == (colN - 1))
        {
          /// top || left
          if((matrix[i * colN + j - rowN] == 1) || (matrix[i * colN + j - 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
          
        }
        /// top 
        else if(i == 0)
        {
          /// below || left || right
          if((matrix[i * colN + j + rowN] == 1) || (matrix[i * colN + j - 1] == 1) || (matrix[i * colN + j + 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
          
        }
        /// bottom 
        else if(i == (rowN - 1))
        {
          /// top || left || right
          if((matrix[i * colN + j - rowN] == 1) || (matrix[i * colN + j - 1] == 1) || (matrix[i * colN + j + 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
        }
        /// left 
        else if(j == 0)
        {
          /// top || below || right
          if((matrix[i * colN + j - rowN] == 1) || (matrix[i * colN + j + rowN] == 1) || (matrix[i * colN + j + 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
        }
        /// right 
        else if(j == (colN - 1))
        {
          /// top || below || left
          if((matrix[i * colN + j - rowN] == 1) || (matrix[i * colN + j + rowN] == 1) || (matrix[i * colN + j - 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
        }
        /// center
        else
        {
          /// top || below || left || right
          if((matrix[i * colN + j - rowN] == 1) || (matrix[i * colN + j + rowN] == 1) || (matrix[i * colN + j - 1] == 1) || (matrix[i * colN + j + 1] == 1))
          {
            subMatrix[i * colN + j] = 1;
          }
        }
      }
    }

    end = 1;
    
    memcpy(matrix, subMatrix, sizeof(subMatrix));
    /// debug print
    /*
    for(i = 0; i < rowN; i++)
    {
      printf("[");
      for(j = 0; j < colN; j++)
      {
        //matrix[i * colN + j] = subMatrix[i * colN + j];
        printf("%d ", matrix[i * colN + j]);
        if(matrix[i * colN + j] == 0)
        {
          end = 0;
        }
      }
      printf("]\r\n");
    }
    printf("\r\n");
    */
    res ++;
  }
  free(subMatrix);
  return res;
}

int main(int argc, char* argv[])
{
  int row;
  int column;
  int rootX;
  int rootY;
  int res = 0;

  sscanf(argv[1],"%d",&row);
  sscanf(argv[2],"%d",&column);
  sscanf(argv[3],"%d",&rootX);
  sscanf(argv[4],"%d",&rootY);

  printf("Check the result : %d \r\n", res);

  GenMatrix(row, column, rootX, rootY);

  res = calExcuteTimes(row, column);
  printf("Check the result : %d \r\n", res);
  FreeMatrix();
  return 0;
}
