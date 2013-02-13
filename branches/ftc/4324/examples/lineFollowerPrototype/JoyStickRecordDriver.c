#ifndef joy_stick_record_driver_c
#define joy_stick_record_driver_c

typedef struct
{
	unsigned int time;
  TJoystick joystickCopy;
} TjoystickEventData;

static TjoystickEventData eventData[500];
static int events = 0;
static int lastEvent = 0;
static bool recording = false;
static int joystickPlaybackIndex = 0;
static unsigned int previousTime;
static unsigned int timeLastEventProcessed;
static string EventDataFileName;
// ------------------------------------------------------------------- //
// function: writeData

void writeData(TFileHandle file, int size, byte *data)
{
  TFileIOResult nIOResult;

  for (int i = 0; i<size; i++)
  {
    WriteByte(file, nIOResult, data[i]);
  }

} // writeData
// ------------------------------------------------------------------- //
// function: readData

void readData(TFileHandle file, int size, byte *data)
{
  TFileIOResult nIOResult;

  for (int i = 0; i<size; i++)
  {
  	byte tempByte;
    ReadByte(file, nIOResult, tempByte);
    data[i] = tempByte;
  }

} // readData

// ------------------------------------------------------------------- //
// function: writeEvents
void writeEvents()
{
  if (recording && (events > 0))
  {
    TFileHandle   fileHandle;
    int           nFileSize = sizeof(TjoystickEventData)*events;
    TFileIOResult nIOResult;
    Delete(EventDataFileName, nIOResult);
    OpenWrite(fileHandle, nIOResult, EventDataFileName, nFileSize);
    writeData(fileHandle, sizeof(TjoystickEventData)*events, (byte*)&eventData);
    Close(fileHandle, nIOResult);
  }
} // writeEvents

// ------------------------------------------------------------------- //
// function: recordEvent
void recordEvent(TJoystick currentJoystick)
{
  if (events < 500)
  {
  	if (memcmp(eventData[lastEvent].joystickCopy, currentJoystick, sizeof(TJoystick)) != 0)
  	{
      eventData[events].time = nSysTime;
      memcpy(&eventData[events].joystickCopy, &currentJoystick, sizeof(TJoystick));
      lastEvent = events;
      events++;
    }
  }

} // recordEvent

// ------------------------------------------------------------------- //
// function: readJoystickEventData
void readJoystickEventData(string fileName)
{

  // read joystick events
  TFileHandle   fileHandle;
  int           eventDataSize;
  TFileIOResult nIOResult;
  OpenRead(fileHandle, nIOResult, fileName, eventDataSize);
  readData(fileHandle, eventDataSize, (byte*)&eventData);
  Close(fileHandle, nIOResult);

  events = eventDataSize/sizeof(TjoystickEventData);
  joystickPlaybackIndex = 0;
  previousTime = eventData[0].time;

} // readJoystickEventData

// \endcond - Doxigen starts processing comments from here on.

//! Enum type definition used to set the record/playback mode of the driver
typedef enum 
{
  /// Sets the driver to record mode
  record, 
  /// sets the driver to playback mode
  playBack} 
recordOrPlayBackModeType;

/** ***************************************************************************
 * \brief Returns joystick value in both record and playback modes
 *
 * If the driver is in record mode, the joystick values are read from
 * the joystick driver.  If the driver is in playback mode, the joystick values
 * are read from a previously recoreded file.
 *
 * \param currentJoystick - current joystick event data.
 */
void getJoystickValues(TJoystick currentJoystick)
{
  if (recording)
  {
    getJoystickSettings(joystick);
    memcpy(&currentJoystick, &joystick, sizeof(TJoystick));
    recordEvent(joystick);
  }
  else // playback
  {
    memcpy(&currentJoystick, &eventData[joystickPlaybackIndex].joystickCopy, sizeof(TJoystick));
    if (joystickPlaybackIndex != 0)
    {
      unsigned int deltaTime = eventData[joystickPlaybackIndex].time - previousTime;
      unsigned int timeSinceLastEvent = nSysTime - timeLastEventProcessed;
      deltaTime = deltaTime - timeSinceLastEvent;
 	    wait1Msec(deltaTime);
 	  }
    previousTime = eventData[joystickPlaybackIndex].time;
    joystickPlaybackIndex++;
    timeLastEventProcessed = nSysTime;
  }
} // getJoystickValues

/** ***************************************************************************
 * \brief Initializes the joystick Recording Driver.
 *
 * \param fileName - If record mode, the file name to write the joystick events to. If play
 * back mode, the file name to read the joystick events from.
 *
 * \param record - Enumeration used to control what mode the driver operates in.  If set to record, the
 * driver reads the values from the joystick and returns them to the user and saves them to a file to be played
 * back later.  If set to playBack, the driver will read joystick values from a previously saved to a file
 * and return them to the user.
 */
void initalizeJoystickRecording(string fileName, recordOrPlayBackModeType recordMode)
{
	EventDataFileName = fileName;
  recording = recordMode == record;
  if(!recording)
  {
    readJoystickEventData(fileName);
  }
} // initalizeJoystickRecording

#endif
