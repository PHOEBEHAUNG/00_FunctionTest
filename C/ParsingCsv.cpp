#include "stdafx.h"
#include "Global.h"

const char * strpWeekDays[] =
{ "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", "Invalid" };
const char * strpMonthNames[] =
{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "Invalid" };

struct tm * timeinfo; 
time_t rawtime;
JINT ParsingBlucoseDate(char *date)
{
  JINT timeDate = 0;
  JINT year = 0;
  JINT month = 0;
  JINT day = 0;
  JINT hour = 0;
  JINT min = 0;
  JINT sec = 0;

  char *pStr;
  JINT monCnt = 0;

  while (monCnt < 12)
  {
    pStr = strstr(date, strpMonthNames[monCnt]);
    monCnt++;
    if (pStr != NULL)
    {
      break;
    }
  }

  if (pStr == NULL)
  {
    return timeDate;
  }

  month = monCnt;
  pStr = pStr + 4;
  sscanf(pStr, "%d %d:%d:%d UTC %d", &day, &hour, &min, &sec, &year);

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  timeinfo->tm_year = year - 1900;
  timeinfo->tm_mon = month - 1;
  timeinfo->tm_mday = day;
  timeinfo->tm_hour = hour;
  timeinfo->tm_min = min;
  timeinfo->tm_sec = sec;
  timeDate = mktime(timeinfo);

  return timeDate;
}

BOOL ParsingCsv::CsvDataInit(int iTotalDataCnt)
{
  this->csvData.iValidCnt = 0;
  this->csvData.iTotalDataCnt = iTotalDataCnt;
  if (iTotalDataCnt == 0)
  {
    this->csvData.pGlucoseDatas = NULL;
    this->csvData.pISIGDatas = NULL;
    this->csvData.pTime = NULL;
    return FALSE;
  }

  if (this->csvData.pGlucoseDatas != NULL)
  {
    free(this->csvData.pGlucoseDatas);
    this->csvData.pGlucoseDatas = NULL;
  }

  if (this->csvData.pISIGDatas != NULL)
  {
    free(this->csvData.pISIGDatas);
    this->csvData.pISIGDatas = NULL;
  }

  if (this->csvData.pTime != NULL)
  {
    free(this->csvData.pTime);
    this->csvData.pTime = NULL;
  }
  this->csvData.pGlucoseDatas = (JINT*)calloc(iTotalDataCnt, sizeof(JINT));
  this->csvData.pISIGDatas = (JFLOAT*)calloc(iTotalDataCnt, sizeof(JFLOAT));
  this->csvData.pTime = (JINT*)calloc(iTotalDataCnt, sizeof(JINT));

  return TRUE;
}

void ParsingCsv::CsvDataUnInit()
{
  if (this->csvData.pGlucoseDatas != NULL)
  {
    free(this->csvData.pGlucoseDatas);
    this->csvData.pGlucoseDatas = NULL;
  }

  if (this->csvData.pISIGDatas != NULL)
  {
    free(this->csvData.pISIGDatas);
    this->csvData.pISIGDatas = NULL;
  }

  if (this->csvData.pTime != NULL)
  {
    free(this->csvData.pTime);
    this->csvData.pTime = NULL;
  }
}

/// PARSE_TYPE_GLUCOSE init 
void ParsingCsv::FileInitGlucose(FILE *pFile)
{
  char line[512];
  char *pStr = NULL;
  int i = 0;

  i = 0;
  while (1)
  {
    fgets(line, sizeof(line), pFile);
    if (line != NULL)
    {
      if (strstr(line, "Number of Records") != NULL)
      {
        pStr = strstr(line, ",");
        pStr++;
        sscanf(pStr, "%d", &this->csvData.iTotalDataCnt);
        break;
      }
    }

    i++;
    /// if no Number of Records row
    if (i > 25)
    {
      break;
    }
  }

  if (i > 25)
  {
    this->csvData.iTotalDataCnt = 2000;
  }

}

/// PARSE_TYPE_GLUCOSE init 
BOOL ParsingCsv::FileParseExeGlucose(FILE *pFile)
{
  BOOL res = 0;
  char line[512];
  char *pStr = NULL;
  char *pStr2 = NULL;
  BOOL bDataSection = FALSE;
  JINT iValidCnt = 0;
  int i = 0;

  char strDate[64];
  JINT iTime = 0;
  JFLOAT fISIG = 0.0f;
  JINT iGlucose = 0;
  while (1)
  {
    if (fgets(line, sizeof(line), pFile) == NULL)
    {
      break;
    }

    i++; /// line cnt

    if (bDataSection == FALSE)
    {
      if (strstr(line, "Index") != NULL)
      {
        bDataSection = TRUE;
      }
    }
    else
    {
      pStr = NULL;
      pStr = line;
      if (pStr == NULL)
      {
        break;
      }
      iGlucose = -1;
      fISIG = -1.0f;

      while (1)
      {
        if (strstr(pStr, "DATE") != NULL)
        {
          memset(strDate, 0, sizeof(strDate));
          pStr = strstr(line, "DATE");
          pStr = strstr(pStr, "=");
          pStr = pStr + 1;

          pStr2 = strstr(line, ";");
          memcpy(strDate, pStr, strlen(pStr) - strlen(pStr2));

          iTime = ParsingBlucoseDate(strDate);
          continue;
        }

        if (strstr(pStr, "AMOUNT") != NULL)
        {
          pStr = strstr(line, "AMOUNT");
          pStr = strstr(pStr, "=");
          pStr = pStr + 1;
          sscanf(pStr, "%d;", &iGlucose);
          continue;
        }

        if (strstr(pStr, "CALIB_ISIG") != NULL)
        {
          pStr = strstr(line, "CALIB_ISIG");
          pStr = strstr(pStr, "=");
          pStr = pStr + 1;
          sscanf(pStr, "%f;", &fISIG);
          continue;
        }

        if (strstr(pStr, "\n") != NULL)
        {
          break;
        }
      }

      if (iGlucose != -1)
      {
        this->csvData.pTime[iValidCnt] = iTime;
        this->csvData.pGlucoseDatas[iValidCnt] = iGlucose;
        this->csvData.pISIGDatas[iValidCnt] = fISIG;
        iValidCnt++;
      }
    }
  }

  /// not find any data
  if ((bDataSection == FALSE) || (iValidCnt <= 0))
  {
    res = -1;
  }
  else
  {
    printf("Get data cnt : %d \r\n", iValidCnt);
    this->csvData.iValidCnt = iValidCnt;
  }

  return res;
}

/// PARSE_TYPE_GLUCOSE Get 
JINT* ParsingCsv::GetGlucoseData()
{
  return this->csvData.pGlucoseDatas;
}

JFLOAT* ParsingCsv::GetISIGData()
{
  return this->csvData.pISIGDatas;
}

JINT* ParsingCsv::GetTimeData()
{
  return this->csvData.pTime;
}
/// PARSE_TYPE_GLUCOSE Get End

BOOL ParsingCsv::FileInit(JWORD parseType, char* parFilePath)
{
  BOOL res = 0;
  //JINT iSeekPos = 0;
  char line[512];
  char *pStr = NULL;
  FILE *pFile;

  int i = 0;
  memset(this->filePath, 0, sizeof(this->filePath));
  
  this->iUpdateProgress = 0;
  this->iTotalFileSize = 0;
  this->iUpdateFileSize = 0;
  this->csvData.iTotalDataCnt = 0;

  this->sendFileEnd = FALSE;
  this->selectFile = TRUE;

  this->parsingType = parseType;
  strcpy((char*)this->filePath, parFilePath);

  pFile = fopen((char*)this->filePath, "r");
  if (pFile == NULL)
  {
    res = -1;
    return res;
  }

  /// [PH] get data size to create array ; 20191113 
  if (this->parsingType == PARSE_TYPE_GLUCOSE)
  {
    this->FileInitGlucose(pFile);
  }
  /// init buffer
  this->CsvDataInit(this->csvData.iTotalDataCnt);

  /// [PH] get file size ; 20191113
  fseek(pFile, 0L, SEEK_END);
  this->iTotalFileSize = ftell(pFile);

  /// [PH] get data size to create array ; 20191113 
  /*
  iSeekPos = -2;
  fseek(pFile, iSeekPos, SEEK_END);
  char c = fgetc(pFile);

  while (c != '\n')
  {
    iSeekPos -= 1;
    fseek(pFile, iSeekPos, SEEK_END);
    c = fgetc(pFile);
  }

  iSeekPos += 1;
  fseek(pFile, iSeekPos, SEEK_END);
  fgets(line, sizeof(line), pFile);

  sscanf(line, "%d", &this->iTotalDataCnt);
  */

  fclose(pFile);
  
  return res;
}

void ParsingCsv::FileUnInit()
{
  memset(this->filePath, 0, sizeof(this->filePath));
  this->iUpdateProgress = 0;
  this->iTotalFileSize = 0;
  this->iUpdateFileSize = 0;
  this->csvData.iTotalDataCnt = 0;

  this->sendFileEnd = FALSE;
  this->selectFile = TRUE;

  this->CsvDataUnInit();
}

BOOL ParsingCsv::FileParseExecute()
{
  BOOL res = 0;
  FILE *pFile;

  pFile = fopen((char*)this->filePath, "r");

  if (pFile == NULL)
  {
    res = -1;
    return res;
  }

  if (this->csvData.iTotalDataCnt <= 0)
  {
    res = -1;
  }

  /// parsing file
  if (res != -1)
  {
    if (this->parsingType == PARSE_TYPE_GLUCOSE)
    {
      this->FileParseExeGlucose(pFile);
    }
  }

  fclose(pFile);
  return res;
}

JINT ParsingCsv::GetValidCnt()
{
  return this->csvData.iValidCnt;
}

ParsingCsv::ParsingCsv()
{
  /// cnt = 0
  this->CsvDataInit(0);
}

ParsingCsv::~ParsingCsv()
{
  this->CsvDataUnInit();
}

