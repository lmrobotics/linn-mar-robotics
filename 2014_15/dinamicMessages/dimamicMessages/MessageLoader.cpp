#include "MessageLoader.h"

using namespace message;

MessageLoader::MessageLoader(){

}

void MessageLoader::Run(void){

}

MessageHeader MessageLoader::DecodeMsgHeader(int8* rawData, int offset){
    int16 size = DecodeInt16(rawData, 0);
    string heading = DecodeString(rawData, size, offset + sizeof(int16));
    MessageHeader msgHead;
    msgHead.messageHeading = heading;
    msgHead.size = size;
    unsigned lessId = 'd';
    unsigned greaterId = 'd';
    char buffer[6];
    for(int i = 0; i < MESSAGE_HEADING_LENGTH; i++){
        lessId = heading.find("<");
        greaterId = heading.find(">");
        heading.copy(buffer, greaterId - 1, lessId + 1);
    }

    return msgHead;
}

void MessageLoader::EncodeMsgHeader(int8* rawData, MessageHeader msgHead, int offset){

}

string MessageLoader::DecodeString(int8* rawData, int size, int offset){
    int8* rawString = new int8[size];
    for(int i = 0; i < size; i++){
        rawString[i] = rawData[offset + i];
    }
    string val(rawString);
    return val;
}

void MessageLoader::EncodeString(string String,int8* rawData, int offset){
    const int8* rawString = String.c_str();
    for(unsigned int i = 0; i < String.size(); i++){
        rawData[offset + i] = rawString[i];
    }
}

float MessageLoader::DecodeFloat(int8* rawData, int offset){
    int16 exp = DecodeInt16(rawData, offset);
    int32 mantissa = DecodeInt32(rawData, offset + 2);
    return ldexp(((float)mantissa)/(float)2147483647.0, exp);
}

void MessageLoader::EncodeFloat(float Float, int8* rawData, int offset){
    int exp;
    float mantissa = frexp(Float, &exp);
    EncodeInt16(exp, rawData, offset);
    EncodeInt32(mantissa*2147483647.0, rawData, offset+2);
}

int32 MessageLoader::DecodeInt32(int8* rawData, int offset){
    int32 i32 = ((int32)rawData[offset + 3]<<24) +
            ((int32)rawData[offset + 2]<<16) +
            ((int32)rawData[offset + 1]<<8) +
             (int32)rawData[offset];

    return i32;
}

void MessageLoader::EncodeInt32(int32 Int32, int8* rawData, int offset){
    rawData[offset] = Int32 & 0xFF;
    rawData[offset + 1] = (Int32>>8) & 0xFF;
    rawData[offset + 2] = (Int32>>16) & 0xFF;
    rawData[offset + 3] = (Int32>>24) & 0xFF;
}

int16 MessageLoader::DecodeInt16(int8* rawData, int offset){
    int16 i16 = (rawData[offset + 1]<<8) + rawData[offset];
    return i16;
}

void MessageLoader::EncodeInt16(int16 Int16, int8* rawData, int offset){
    rawData[offset] = Int16 & 0xFF;
    rawData[offset + 1] = (Int16>>8) & 0xFF;
}

MessageLoader::~MessageLoader(){

}
