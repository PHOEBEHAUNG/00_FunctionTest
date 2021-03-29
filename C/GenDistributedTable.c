#include <math.h> 
#include <stdlib.h> 
#include <stdarg.h> 
#include <stdio.h> 
#include <string.h> 
#include <ctype.h> 
#include <time.h> 

char *matrix;
#define TEMP_CTRL_MAX_CNT     (250)

void GenMatrix()
{
  matrix = calloc(MAX_CNT, sizeof(char));
}

void FreeMatrix()
{
  free(matrix);
}

int cnt_1 = 0;
int GenTable(char *matrix, int targetN, int target_cnt, int block_cnt, int total_cnt, int start_idx)
{
  int res = 0;
  int blockCnt = block_cnt;
  int num_high_cnt_in_block = 0;
  int num_element_in_block = 0;

  if(target_cnt <= block_cnt)
  {
    if(target_cnt >= total_cnt)
    {
      blockCnt = total_cnt;
      num_high_cnt_in_block = 1;
      num_element_in_block = 1;
    }
    else
    {
      blockCnt = target_cnt;
      num_high_cnt_in_block = 1;
      num_element_in_block = (int)(total_cnt / blockCnt);
    }
    
    //printf("element in block1: %d, %d, %d\r\n", total_cnt, target_cnt, num_element_in_block);
    for(int i = 0; i < blockCnt; i++)
    {
      matrix[start_idx + num_element_in_block * i] = targetN;
      //printf("element in block: %d\r\n", start_idx + num_element_in_block * i);
    }
  }
  else
  {
    num_high_cnt_in_block = (int) (target_cnt / blockCnt);
    num_element_in_block = (int)(total_cnt / blockCnt);
    int high_cnt_ex  = (int) (target_cnt / blockCnt);
    int reminder_high_cnt = target_cnt - (high_cnt_ex * (blockCnt - 1));
    //printf("element in block: %d, %d, %d, %d, %d\r\n", target_cnt, blockCnt, high_cnt_ex, reminder_high_cnt, num_element_in_block);
    int block_cnt_ex = high_cnt_ex; 
    int total_cnt_ex = (int) (total_cnt / blockCnt);
    int reminder_totsl_cnt = total_cnt - (total_cnt_ex * blockCnt);
    int start_idx_ex = 0;

    for(int i = 0; i < blockCnt; i++)
    {
      if(i == (blockCnt - 1))
      {
        total_cnt_ex = total_cnt_ex + reminder_totsl_cnt;
        high_cnt_ex = reminder_high_cnt;
      }

      if(reminder_high_cnt > high_cnt_ex)
      {
        reminder_high_cnt --;
        start_idx_ex = start_idx + i * num_element_in_block;
        GenTable(matrix, targetN, high_cnt_ex + 1, block_cnt_ex, total_cnt_ex, start_idx_ex);
      }
      else
      {
        start_idx_ex = start_idx + i * num_element_in_block;
        GenTable(matrix, targetN, high_cnt_ex, block_cnt_ex, total_cnt_ex, start_idx_ex);
      }
    }

  }
  return res;
}

void GemTempTable(int duty)
{
  int num_high_cnt = 0;
  int num_block_cnt = 25;

  num_high_cnt = (int)(duty / (100.0f) * TEMP_CTRL_MAX_CNT);
  //printf("Check the duty , num_high_cnt : %d , %d\r\n", duty, num_high_cnt);

  if(duty == 0)
  {
    memset(matrix, 0, TEMP_CTRL_MAX_CNT);
  }
  else if(duty == 100)
  {
    memset(matrix, 1, TEMP_CTRL_MAX_CNT);
  }
  else if(duty > 50)
  {
    memset(matrix, 1, TEMP_CTRL_MAX_CNT);
    num_high_cnt = TEMP_CTRL_MAX_CNT - num_high_cnt;
    GenTable(matrix, 0, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
  else
  {
    GenTable(matrix, 1, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
}

int main(int argc, char* argv[])
{
  int duty = 0;
  sscanf(argv[1],"%d",&duty);
 
  GenMatrix();
  GemTempTable(duty);
  cnt_1 = 0;
  for(int i = 0; i < 10; i++)
  {
    printf("[");
    for(int j = 0; j < 25; j ++)
    {
      printf("%d, ", matrix[i * 25 + j]);
      if(matrix[i * 25 + j] == 1)
      {
        cnt_1 ++;
      }
    }
    printf("]\r\n");
  }
  printf("Check cnt_1 : %d\r\n", cnt_1);

  FreeMatrix();
  return 0;
}
