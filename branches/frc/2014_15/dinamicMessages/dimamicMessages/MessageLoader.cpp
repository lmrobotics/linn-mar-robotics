#include "MessageLoader.h"

using namespace Message;

MessageLoader::MessageLoader(){

}

void MessageLoader::Run(void){

}

void* MessageLoader::DecodeFloat(int8* rawData){
    return 0;
}

int8* MessageLoader::EncodeFloat(void* Float){
    return 0;
}

void* MessageLoader::DecodeInt32(int8* rawData){
    int32 i32 = ((int32)message[3]<<24) +
            ((int32)message[2]<<16) +
            ((int32)message[1]<<8) +
             (int32)message[0];

    return (void*)&i32;
}

int8* MessageLoader::EncodeInt32(void* Int32){
    return 0;
}

void* MessageLoader::DecodeInt16(int8* rawData){
    int16 i16 = (rawData[1]<<8) + rawData[0];
    return (void*)&i16;
}

int8* MessageLoader::EncodeInt16(void* Int16){
    return 0;
}

MessageLoader::~MessageLoader(){

}
