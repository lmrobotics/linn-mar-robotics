#ifndef MESSAGE_LOADER_H
#define MESSAGE_LOADER_H

#include <math.h>
#include <string>

#define MESSAGE_HEADING_LENGTH 6

namespace message{

   using namespace std;

   typedef char int8;
   typedef int int16;
   typedef long int32;
   typedef unsigned char uint8;
   typedef unsigned int uint16;
   typedef unsigned long uint32;

   struct MessageHeader{
     string messageHeading;
     int16 size;
     float* floatData;
     int16 floatSize;
     int32* longData;
     int16 longSize;
     int16* intData;
     int16 intSize;
     int8* shortData;
     int16 shortSize;
   };

   class MessageLoader{
     public:
        MessageLoader();
        ~MessageLoader(void);
        void Run(void);
     private:
        void EncodeMsgHeader(int8* rawData, MessageHeader msgHead, int offset);
        MessageHeader DecodeMsgHeader(int8* rawData, int offset);
        string DecodeString(int8* rawData, int size, int offset);
        void EncodeString(string String, int8* rawData, int offset);
        float DecodeFloat(int8* rawData, int offset);
        void EncodeFloat(float Float, int8* rawData, int offset);
        int32 DecodeInt32(int8* rawData, int offset);
        void EncodeInt32(int32 Int32, int8* rawData, int offset);
        int16 DecodeInt16(int8* rawData, int offset);
        void EncodeInt16(int16 Int16, int8* rawData, int offset);
    };
}
#endif
