#ifndef MESSAGE_TRANSPORT_H
#define MESSAGE_TRANSPORT_H
#include "baseMessageClass.h"

using namespace Messages;

class messageTransport {

public:

    messageTransport();
	~messageTransport();
	static void send(unsigned char* message, int length);
	static bool messageAvailable();
	static BaseMessageClass *getMessage();
	static bool getMessage(BaseMessageClass *msg);

private:
    enum serialReadStateE { searching_aa, searching_55, searching_c3, searching_3c, readingId, readingData };
    static serialReadStateE serialState;
    static unsigned char currentByte;
    static void readSerial();
    static unsigned char currentMsgId;
    static int msgByteCount;
    static unsigned char currentMsg[256];
    static unsigned char preamble[4];

};

#endif
