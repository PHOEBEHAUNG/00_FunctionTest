#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define TEMP_CTRL_MAX_CNT               (500)

char state[TEMP_CTRL_MAX_CNT];

int cnt_1 = 0;
int GenTable(char *matrix, int targetN, int target_cnt, int block_cnt, int total_cnt, int start_idx)
{
  int res = 0;
  int blockCnt = block_cnt;
  int num_element_in_block = 0;
  int i = 0;

  /// recurceive
  int high_cnt_ex  = 0;
  int reminder_high_cnt = 0;
  int block_cnt_ex = 0; 
  int total_cnt_ex = 0;
  int reminder_totsl_cnt = 0;
  int start_idx_ex = 0;

  if(target_cnt <= block_cnt)
  {
    if(target_cnt >= total_cnt)
    {
      blockCnt = total_cnt;
      num_element_in_block = 1;
    }
    else
    {
      blockCnt = target_cnt;
      num_element_in_block = (int)(total_cnt / blockCnt);
    }
    
    //printf("element in block1: %d, %d, %d\r\n", total_cnt, target_cnt, num_element_in_block);
    for(i = 0; i < blockCnt; i++)
    {
      matrix[start_idx + num_element_in_block * i] = targetN;
      //printf("element in block: %d\r\n", start_idx + num_element_in_block * i);
    }
  }
  else
  {
    num_element_in_block = (int)(total_cnt / blockCnt);

    high_cnt_ex  = (int) (target_cnt / blockCnt);
    reminder_high_cnt = target_cnt - (high_cnt_ex * (blockCnt - 1));
    //printf("element in block: %d, %d, %d, %d, %d\r\n", target_cnt, blockCnt, high_cnt_ex, reminder_high_cnt, num_element_in_block);
    

    if(high_cnt_ex > 3 && (total_cnt % target_cnt) != 0)
    {
      block_cnt_ex = high_cnt_ex / 2; 
      //printf("b %d, %d\r\n", block_cnt_ex, high_cnt_ex);
    }
    else
    {
      block_cnt_ex = high_cnt_ex; 
    }

    total_cnt_ex = (int) (total_cnt / blockCnt);

    reminder_totsl_cnt = total_cnt - (total_cnt_ex * blockCnt);
    start_idx_ex = 0;
    int iAddRemain = 0;
    for(i = 0; i < blockCnt; i++)
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
        if(iAddRemain == 1)
        {
          start_idx_ex = start_idx_ex + 1;
          iAddRemain = 0;
        }
        
        if(reminder_totsl_cnt > 0)
        {
          //printf("%d, %d, %d, %d, %d\r\n", high_cnt_ex + 1, block_cnt_ex + 1, total_cnt_ex, start_idx_ex+1, reminder_totsl_cnt);
          reminder_totsl_cnt = reminder_totsl_cnt - 1;
          iAddRemain = 1;
          GenTable(matrix, targetN, high_cnt_ex + 1, block_cnt_ex+1, total_cnt_ex + 1, start_idx_ex);
        }
        else
        {
          //printf("%d, %d, %d, %d, %d\r\n", high_cnt_ex + 1, block_cnt_ex + 1, total_cnt_ex, start_idx_ex, reminder_totsl_cnt);

          GenTable(matrix, targetN, high_cnt_ex + 1, block_cnt_ex+1, total_cnt_ex, start_idx_ex);
        }
      }
      else
      {
        start_idx_ex = start_idx + i * num_element_in_block;
        if(iAddRemain == 1)
        {
          start_idx_ex = start_idx_ex + 1;
          iAddRemain = 0;
        }

        if(reminder_totsl_cnt > 0)
        {
          reminder_totsl_cnt = reminder_totsl_cnt - 1;
          iAddRemain = 1;
          //printf("%d, %d, %d, %d, %d\r\n", high_cnt_ex, block_cnt_ex, total_cnt_ex, start_idx_ex+1, reminder_totsl_cnt);
          GenTable(matrix, targetN, high_cnt_ex, block_cnt_ex, total_cnt_ex + 1, start_idx_ex);
        }
        else
        {
           //printf("%d, %d, %d, %d, %d\r\n", high_cnt_ex, block_cnt_ex, total_cnt_ex, start_idx_ex, reminder_totsl_cnt);
           GenTable(matrix, targetN, high_cnt_ex, block_cnt_ex, total_cnt_ex, start_idx_ex);
        }
      }
    }

  }
  return res;
}

void GemTempTable(char *matrix, int duty)
{
  int num_high_cnt = 0;
  int num_block_cnt = 25;

  num_high_cnt = (int)(duty / (100.0f) * TEMP_CTRL_MAX_CNT);
  //printf("Check the duty , num_high_cnt : %d , %d\r\n", duty, num_high_cnt);
  num_high_cnt = duty;
  if(duty == 0)
  {
    memset(matrix, 0, TEMP_CTRL_MAX_CNT);
  }
  else if(duty == TEMP_CTRL_MAX_CNT)
  {
    memset(matrix, 1, TEMP_CTRL_MAX_CNT);
  }
  else if(duty > (TEMP_CTRL_MAX_CNT / 2))
  {
    memset(matrix, 1, TEMP_CTRL_MAX_CNT);
    num_high_cnt = TEMP_CTRL_MAX_CNT - num_high_cnt;
    GenTable(matrix, 0, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
  else
  {
    memset(matrix, 0, TEMP_CTRL_MAX_CNT);
    GenTable(matrix, 1, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
}

int main(int argc, char* argv[])
{
  int duty = 0;
  int max_cnt = TEMP_CTRL_MAX_CNT;
  int max_time = TEMP_CTRL_MAX_CNT;

  int denominator = 0;
  int numerator = 0;

  int num_total_high = 0;
  int num_total_low = 0;
  int num_block = 25;
  int num_element_in_block = 0;

  int num_block_high   = 0;
  int num_remider_high = 0;

  int i = 0;
  int j = 0;

  if(argc <= 1)
  {
    return 0;
  }
  sscanf(argv[1], "%d", &duty);

  num_element_in_block = max_time / num_block;
  //num_total_high = (int)((duty / (100.0f)) * max_time);
  num_total_high = duty;
  num_total_low = max_time - num_total_high;
  //printf("check high, low num : %d, %d\r\n", num_total_high, num_total_low); 

  num_block_high = (int)(num_total_high / (float)num_block); /// force fill the point
  num_remider_high = num_total_high - (num_block_high * num_block);
  //printf("check num_block_high : %d, num_total_high : %d, num_block : %d, num_remider_high : %d, num_element_in_block : %d\r\n", num_block_high, num_total_high, num_block, num_remider_high, num_element_in_block); 

  /// ditruibute
  memset(state, 0, sizeof(char) * TEMP_CTRL_MAX_CNT);
  GemTempTable(state, duty);

  /// print   
  cnt_1 = 0;
  for(i = 0; i < 10; i ++)
  {
    //printf("[");
    for(j = 0; j < TEMP_CTRL_MAX_CNT / 10; j++)
    {
      //printf("%d, ", state[i * (TEMP_CTRL_MAX_CNT / 10) + j]);
      if(state[i * (TEMP_CTRL_MAX_CNT / 10) + j] == 1)
      {
        cnt_1 ++;
      }
    }
    //printf("]\r\n");
  }
  //printf("\r\n");
  printf("cnt : %d \r\n", duty);

  return 0;
}
