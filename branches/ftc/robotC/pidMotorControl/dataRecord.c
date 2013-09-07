#ifndef data_record_c
#define data_record_c

const int   maxDataLog = 1024*8;
static byte tempData[maxDataLog];
int         logSize = 0;

/** ***************************************************************************
 * \brief
 */
void saveLog(string sFileName)
{
  TFileHandle   fileHandle;
  TFileIOResult ioResult;
  int temp = logSize;
  //string sFileName = "dataRecord.dat";
  Delete(sFileName, ioResult);
  OpenWrite(fileHandle, ioResult, sFileName, temp);
  for(int i=0; i<=temp; i++)
  {
    WriteByte(fileHandle, ioResult, tempData[i]);
  }

  Close(fileHandle, ioResult);

} // saveLog

/** ***************************************************************************
 * \brief
 */
void logByte(byte logDat)
{
  if(logSize < maxDataLog)
  {
    tempData[logSize++] = logDat;
  }
} // logByte

/** ***************************************************************************
 * \brief
 */
void logInt(int logDat)
{
  if(logSize+1 < maxDataLog)
  {
    tempData[logSize++] = logDat>>8;
    tempData[logSize++] = logDat;
  }
} // logByte

#endif
