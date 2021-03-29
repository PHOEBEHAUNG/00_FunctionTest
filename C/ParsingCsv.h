#define PARSE_TYPE_GLUCOSE                         (1)

typedef struct CsvDataSt
{
  JINT iTotalDataCnt;
  JINT iValidCnt;
  JINT  *pGlucoseDatas;
  JFLOAT *pISIGDatas;
  JINT *pTime;

}CsvDataType;

class ParsingCsv
{
  JWORD parsingType;

  CString updateProgress;
  JINT iUpdateProgress;
  CString sUpdateMsg;

  JINT iTotalFileSize;
  JINT iUpdateFileSize;

  BOOL sendFileEnd;
  BOOL selectFile;
  JBYTE filePath[256];

  /// data buffer point
  CsvDataType csvData;

public:
  ParsingCsv(void);
  ~ParsingCsv(void);

  void FileInitGlucose(FILE *pFile);
  BOOL FileParseExeGlucose(FILE *pFile);
  JINT* GetGlucoseData();
  JFLOAT* GetISIGData();
  JINT* GetTimeData();

  BOOL FileInit(JWORD parseType, char* parFilePath);
  void FileUnInit();
  BOOL FileParseExecute();

  JINT GetValidCnt();

  BOOL CsvDataInit(int iTotalDataCnt);
  void CsvDataUnInit();

protected:

private:


};