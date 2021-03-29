#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define TEMP_CTRL_MAX_CNT               (500)
typedef unsigned char        JBYTE;

JBYTE state[TEMP_CTRL_MAX_CNT];
int cnt_1 = 0;

int GenTable(JBYTE *matrix, int targetN, int target_cnt, int block_cnt, int total_cnt, int start_idx)
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
    
    //printf("element in block1: total_cnt = %d, target_cnt = %d, num_element_in_block = %d\r\n", total_cnt, target_cnt, num_element_in_block);
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
    //printf("element in block: totalhigh/total = %d / %d, blockCnt = %d, high/elemantCnt(block) = %d / %d, remained cnt = %d\r\n", target_cnt, total_cnt, blockCnt, high_cnt_ex, num_element_in_block, reminder_high_cnt);
    block_cnt_ex = high_cnt_ex; 
    total_cnt_ex = (int) (total_cnt / blockCnt);
    reminder_totsl_cnt = total_cnt - (total_cnt_ex * blockCnt);
    start_idx_ex = 0;

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
        GenTable(matrix, targetN, high_cnt_ex + 1, block_cnt_ex + 1, total_cnt_ex, start_idx_ex);
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

int GenTableEx(JBYTE *matrix, int targetN, int target_cnt, int block_cnt, int total_cnt, int start_idx)
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
    
    //printf("element in block1: total_cnt = %d, target_cnt = %d, num_element_in_block = %d\r\n", total_cnt, target_cnt, num_element_in_block);
    for(i = 0; i < blockCnt; i++)
    {
      matrix[start_idx + num_element_in_block * i] = targetN;
      matrix[start_idx + num_element_in_block * i + 1] = targetN;
      //printf("element in block end : %d, %d\r\n", start_idx + num_element_in_block * i, start_idx + num_element_in_block * i + 1);
    }
  }
  else
  {
    num_element_in_block = (int)(total_cnt / blockCnt);

    high_cnt_ex  = (int) (target_cnt / blockCnt);
    reminder_high_cnt = target_cnt - (high_cnt_ex * (blockCnt - 1));
    //printf("element in block: totalhigh/total = %d / %d, blockCnt = %d, high/elemantCnt(block) = %d / %d, remained cnt = %d\r\n", target_cnt, total_cnt, blockCnt, high_cnt_ex, num_element_in_block, reminder_high_cnt);
    block_cnt_ex = high_cnt_ex; 
    total_cnt_ex = (int) (total_cnt / blockCnt);
    reminder_totsl_cnt = total_cnt - (total_cnt_ex * blockCnt);
    start_idx_ex = 0;

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
        GenTableEx(matrix, targetN, high_cnt_ex + 1, block_cnt_ex + 1, total_cnt_ex, start_idx_ex);
      }
      else
      {
        start_idx_ex = start_idx + i * num_element_in_block;
        GenTableEx(matrix, targetN, high_cnt_ex, block_cnt_ex, total_cnt_ex, start_idx_ex);
      }
    }

  }
  return res;
}

int GenTableEx2(JBYTE *matrix, int targetN, int target_cnt, int block_cnt, int total_cnt, int start_idx)
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
    //printf("element in block1: total_cnt = %d, target_cnt = %d, num_element_in_block = %d\r\n", total_cnt, target_cnt, num_element_in_block);

    for(i = 0; i < blockCnt; i++)
    {
      matrix[start_idx + num_element_in_block * i] = targetN;
      //printf("element in block end : index %d\r\n", start_idx + num_element_in_block * i);
    }
  }
  else
  {
    num_element_in_block = (int)(total_cnt / blockCnt);

    high_cnt_ex  = (int) (target_cnt / blockCnt);
    reminder_high_cnt = target_cnt - (high_cnt_ex * (blockCnt - 1));
    //printf("element in block: totalhigh/total = %d / %d, blockCnt = %d, high/elemantCnt(block) = %d / %d, remained cnt = %d\r\n", target_cnt, total_cnt, blockCnt, high_cnt_ex, num_element_in_block, reminder_high_cnt);
/*
    if(high_cnt_ex > (num_element_in_block / high_cnt_ex))
    {
      printf("%d, %d, %d\r\n", num_element_in_block, high_cnt_ex, (num_element_in_block / high_cnt_ex));
      if((num_element_in_block / high_cnt_ex) == 0)
      {
        block_cnt_ex = high_cnt_ex;
      }
      else
      {
        block_cnt_ex = high_cnt_ex / (int)(num_element_in_block / high_cnt_ex);
      } 
    }
    else
    {
      block_cnt_ex = high_cnt_ex;
    }
*/
    if(high_cnt_ex > 3 && (total_cnt % target_cnt) != 0)
    {
      block_cnt_ex = high_cnt_ex / 2; 
      //printf("b %d, %d\r\n", block_cnt_ex, high_cnt_ex);
    }
    else
    {
      block_cnt_ex = high_cnt_ex; 
    }

    //block_cnt_ex = num_element_in_block / high_cnt_ex;
    
    total_cnt_ex = (int) (total_cnt / blockCnt);
    reminder_totsl_cnt = total_cnt - (total_cnt_ex * blockCnt);
    start_idx_ex = 0;

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
        GenTableEx2(matrix, targetN, high_cnt_ex + 1, block_cnt_ex + 1, total_cnt_ex, start_idx_ex);
      }
      else
      {
        start_idx_ex = start_idx + i * num_element_in_block;
        GenTableEx2(matrix, targetN, high_cnt_ex, block_cnt_ex, total_cnt_ex, start_idx_ex);
      }
    }
  }
  return res;
}

int GenTableEx3(JBYTE *matrix, int targetN, int target_cnt, int block_cnt, int total_cnt, int start_idx)
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
    //printf("element in block1: total_cnt = %d, target_cnt = %d, num_element_in_block = %d\r\n", total_cnt, target_cnt, num_element_in_block);

    for(i = 0; i < blockCnt; i++)
    {
      matrix[start_idx + num_element_in_block * i] = targetN;
      //printf("element in block end : index %d\r\n", start_idx + num_element_in_block * i);
    }
  }
  else
  {
    num_element_in_block = (int)(total_cnt / blockCnt);

    high_cnt_ex  = (int) (target_cnt / blockCnt);
    reminder_high_cnt = target_cnt - (high_cnt_ex * (blockCnt - 1));
    //printf("element in block: totalhigh/total = %d / %d, blockCnt = %d, high/elemantCnt(block) = %d / %d, remained cnt = %d\r\n", target_cnt, total_cnt, blockCnt, high_cnt_ex, num_element_in_block, reminder_high_cnt);

    total_cnt_ex = (int) (total_cnt / blockCnt);
    reminder_totsl_cnt = total_cnt - (total_cnt_ex * blockCnt);
    start_idx_ex = 0;

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
        GenTableEx3(matrix, targetN, high_cnt_ex + 1, block_cnt_ex + 1, total_cnt_ex, start_idx_ex);
      }
      else
      {
        start_idx_ex = start_idx + i * num_element_in_block;
        GenTableEx3(matrix, targetN, high_cnt_ex, block_cnt_ex, total_cnt_ex, start_idx_ex);
      }
    }
  }
  return res;
}

/// combine by 101010101
void GemTempTable(JBYTE *matrix, int duty)
{
  int num_high_cnt = 0;
  int num_block_cnt = 25;
  //num_high_cnt = (int)(duty / (100.0f) * TEMP_CTRL_MAX_CNT);
  num_high_cnt = duty;
  //printf("Check the duty , num_high_cnt : %d , %d\r\n", duty, num_high_cnt);

  if(num_high_cnt < 0)
  {
    num_high_cnt = 0; 
  }
  else if(num_high_cnt > TEMP_CTRL_MAX_CNT)
  {
    num_high_cnt = TEMP_CTRL_MAX_CNT;
  }

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

/// combine by 110, 1100, 11000, 1100000
void GemTempTableEx(JBYTE *matrix, int duty)
{
  int num_high_cnt = 0;
  int num_block_cnt = 25;

  num_high_cnt = duty;
  //num_high_cnt = (int)(duty / (100.0f) * TEMP_CTRL_MAX_CNT);
  //printf("Check the duty , num_high_cnt : %d , %d\r\n", duty, num_high_cnt);

  if(num_high_cnt < 0)
  {
    num_high_cnt = 0; 
  }
  else if(num_high_cnt > TEMP_CTRL_MAX_CNT)
  {
    num_high_cnt = TEMP_CTRL_MAX_CNT;
  }

  if(duty == 0)
  {
    memset(matrix, 0, TEMP_CTRL_MAX_CNT);
  }
  else if(duty == TEMP_CTRL_MAX_CNT)
  {
    memset(matrix, 1, TEMP_CTRL_MAX_CNT);
  }
  else if(duty > TEMP_CTRL_MAX_CNT / 2)
  {  
    memset(matrix, 1, TEMP_CTRL_MAX_CNT);
    num_high_cnt = (TEMP_CTRL_MAX_CNT - num_high_cnt) / 2;
    GenTableEx(matrix, 0, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
  else
  {
    num_high_cnt = num_high_cnt / 2;
    memset(matrix, 0, TEMP_CTRL_MAX_CNT);
    GenTableEx(matrix, 1, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
}

/// combine by 10, 100, 10000, 100000 
void GemTempTableEx2(JBYTE *matrix, int duty)
{
  int num_high_cnt = 0;
  int num_block_cnt = 25;

  //num_high_cnt = (int)(duty / (100.0f) * TEMP_CTRL_MAX_CNT);
  num_high_cnt = duty;
  printf("Check the duty , num_high_cnt : %d , %d\r\n", duty, num_high_cnt);

  if(num_high_cnt < 0)
  {
    num_high_cnt = 0; 
  }
  else if(num_high_cnt > TEMP_CTRL_MAX_CNT)
  {
    num_high_cnt = TEMP_CTRL_MAX_CNT;
  }

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
    GenTableEx2(matrix, 0, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
  else
  {
    memset(matrix, 0, TEMP_CTRL_MAX_CNT);
    GenTableEx2(matrix, 1, num_high_cnt, num_block_cnt, TEMP_CTRL_MAX_CNT, 0);
  }
}

/// 111000
void GemTempTableEx3(JBYTE *matrix, int actCnt)
{
  int maxCnt = TEMP_CTRL_MAX_CNT;
 // int actCnt = //(int)(duty / (100.0f) * TEMP_CTRL_MAX_CNT);
  int locatCnt;
  int locatArr[4];
  int idx = 0;
  int i;
  int max;
  int tmp;

  memset((JBYTE*)&locatArr[0], 0, sizeof(locatArr));
  
  /// the period 1,2,4
  if(((float)actCnt / 4) >= 2)
  {
    /// the preiod only 4
    locatCnt = actCnt;
    idx = 0;
    max = 4;
    while(1)
    {
      if(locatCnt == 0)
      {
        break;
      }
      if(idx == max)
      {
        idx = 0;
      }
      locatArr[idx]++;
      idx++;
      locatCnt--;
    }
    /// move the  location
    tmp = locatArr[2];
    locatArr[2] = locatArr[1];
    locatArr[1] = tmp;
  }
  else if(((float)actCnt/2) >= 2)
  {
    /// the preiod 2
    locatCnt = actCnt;
    idx = 0;
    max = 2;
    while(1)
    {
      if(locatCnt == 0)
      {
        break;
      }
      if(idx == max)
      {
        idx = 0;
      }
      locatArr[idx]++;
      idx++;
      locatCnt--;
    }
    /// move the  location
    tmp = locatArr[2];
    locatArr[2] = locatArr[1];
    locatArr[1] = tmp;

  }
  else
  {
    /// the preiod 1
    locatArr[0] = actCnt;
  }
  
  /// initial the control table
  memset((JBYTE *)state, 0, TEMP_CTRL_MAX_CNT);
  idx = 0;
  i = 0;
  locatCnt =(int) (((float)locatArr[idx]/3) * 7) - (maxCnt / 4);
  printf("locatCnt = %d\r\n", locatCnt);
  while (1)
  {
    /// check the last item
    if ((i+4) >= TEMP_CTRL_MAX_CNT)
    {
      break;
    }

    if (locatArr[idx] > 2)
    {
      state[i]     = 1;
      state[i + 1] = 1;
      state[i + 2] = 1;
      i += 3;
      /// setting the low
      if (locatCnt > 0)
      {
        i += 3;
        locatCnt--;
      }
      else
      {
        i += 4;
      }
      locatArr[idx] -= 3;
    }
    else if (locatArr[idx] > 1)
    {
      state[i]     = 1;
      state[i + 1] = 1;
      i += 2;
      /// setting the low
      i += 4;
      locatArr[idx] -= 2;
    }
    else if (locatArr[idx] == 1)
    {
      state[i]     = 1;
      state[i + 1] = 1;
      i += 2;
      /// setting the low
      i += 4;
      locatArr[idx]--;
      if (idx < 3)
      {
        locatArr[idx + 1]--;
      }
    }
    else
    {
      i++;
    }
    
    /// one preiod
    if (i < (maxCnt/4))
    {
      idx = 0;
    }
    else if(i < (maxCnt/2))
    {
      idx = 1;
      /// check need change to 3 item count
      if ((locatCnt == 0) && (i< (maxCnt / 4)+7))
      {
        locatCnt =(int) (((float)locatArr[idx]/3) * 7) - (maxCnt / 4);
      }
    }
    else if(i < (maxCnt*3/4))
    {
      idx = 2;
      /// check need change to 3 item count
      if ((locatCnt == 0) && (i< (maxCnt / 2) + 7))
      {
        locatCnt = (int)(((float)locatArr[idx] / 3) * 7) - (maxCnt / 4);
      }
    }
    else
    {
      idx = 3;
      /// check need change to 3 item count
      if ((locatCnt == 0) && (i<  (maxCnt * 3 / 4) + 7))
      {
        locatCnt = (int)(((float)locatArr[idx] / 3) * 7) - (maxCnt / 4);
      }
    }
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

  FILE *pFile = NULL;
  char fileName[32];
  if(argc <= 1)
  {
    return 0;
  }
  sscanf(argv[1], "%d", &duty);

  num_element_in_block = max_time / num_block;
  //num_total_high = (int)((duty / (100.0f)) * max_time);
  num_total_high = duty;
  num_total_low = max_time - num_total_high;
  printf("check high, low num : %d, %d\r\n", num_total_high, num_total_low); 

  num_block_high = (int)(num_total_high / (float)num_block); /// force fill the point
  num_remider_high = num_total_high - (num_block_high * num_block);
  printf("check num_block_high : %d, num_total_high : %d, num_block : %d, num_remider_high : %d, num_element_in_block : %d\r\n", num_block_high, num_total_high, num_block, num_remider_high, num_element_in_block); 

  /// ditruibute
  memset(state, 0, sizeof(JBYTE) * TEMP_CTRL_MAX_CNT);
  GemTempTableEx3(state, duty);

  /// print debug
  cnt_1 = 0;
#if 0
  sprintf(fileName, "./Distribution_%d.csv", num_total_high);
  pFile = fopen(fileName, "w");
#endif
int zeroCnt = 0;
int zeroSectionCnt = 0;
int zero[500];
int sum = 0;
float avg = 0;

float vaDiffSum = 0.0f;
float vaDiff = 0.0f;
memset(zero, 0, sizeof(int) * 500);
  for(i = 0; i < 10; i++)
  {
    printf("[");
    for(j = 0; j < TEMP_CTRL_MAX_CNT / 10; j++)
    {
      printf("%d,", state[i * (TEMP_CTRL_MAX_CNT / 10) + j]);
      if(state[i * (TEMP_CTRL_MAX_CNT / 10) + j] == 1)
      {
        cnt_1 ++;
      }
      if(pFile != NULL)
      {
        fprintf(pFile, "%d,\n", state[i * (TEMP_CTRL_MAX_CNT / 10) + j]);
      }


      if(state[i * (TEMP_CTRL_MAX_CNT / 10) + j] == 0)
      {
        zeroCnt++;
      }

      if(state[i * (TEMP_CTRL_MAX_CNT / 10) + j] == 1 && zeroCnt != 0)
      {                   

        zero[zeroSectionCnt] = zeroCnt;
        zeroSectionCnt++; 
        zeroCnt = 0;
      }
    }
    printf("]\r\n");
  }

  if(state[TEMP_CTRL_MAX_CNT - 1] == 0)
  {
    zero[zeroSectionCnt] = zeroCnt;
    zeroSectionCnt++; 
    zeroCnt = 0;
  }

  for(i = 0; i < zeroSectionCnt; i++)
  {
    sum += zero[i];
  }
  avg = sum / (float)zeroSectionCnt;

  for(i = 0; i < zeroSectionCnt; i++)
  {
    vaDiffSum += (float)pow((zero[i] - avg), 2);
  }

  vaDiff = vaDiffSum / (float)zeroSectionCnt;

  if(pFile != NULL)
  {
    fclose(pFile);
  }
  printf("\r\n");
  printf("cnt : %d \r\n", cnt_1);
  printf("duty vaDiff : %d, %.3f, %.3f \r\n", duty, avg, (float)pow(vaDiff, 0.5));

  return 0;
}