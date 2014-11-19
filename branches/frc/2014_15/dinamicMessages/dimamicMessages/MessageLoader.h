#ifndef MESSAGE_LOADER_H
#define MESSAGE_LOADER_H

#define CALL_DECODE_FUNCTION(messageLoader, function) ((messageLoader)->*(function))
#define CALL_ENCODE_FUNCTION(messageLoader, function) ((messageLoader)->*(function))

namespace Message{

   typedef char int8;
   typedef int int16;
   typedef long int32;
   typedef unsigned char uint8;
   typedef unsigned int uint16;
   typedef unsigned long uint32;

    class MessageLoader{
     public:
        typedef void& (MessageLoader::*DecodeFunction)(int8* rawData);
        typedef int8* (MessageLoader::*EncodeFunction)(void* inData);
        MessageLoader();
        ~MessageLoader(void);
        void Run(void);
     private:
        void& DecodeFloat(int8* rawData);
        int8* EncodeFloat(void* Float);
        void& DecodeInt32(int8* rawData);
        int8* EncodeInt32(void* Int32);
        void& DecodeInt16(int8* rawData);
        int8* EncodeInt16(void* Int16);
    };
}
#endif
