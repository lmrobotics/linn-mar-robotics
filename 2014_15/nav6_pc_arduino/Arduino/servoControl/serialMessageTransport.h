#ifndef SERIALMESSAGETRANSPORT_H
#define SERIALMESSAGETRANSPORT_H

#include "messageTransport.h"

class serialMessageTransport : messageTransport
{
public:

    serialMessageTransport(int baudRate);
    ~serialMessageTransport();
    void send(BaseMessageClass& message);
    bool messageAvailable();
    BaseMessageClass *getMessage();

private:
    void connect(int baudRate);
    void disconnect();
    void send(unsigned char byteArray[], int length);
    int receive(unsigned char* buffer, int length);
    void readSerial();

    enum serialReadStateE { searching_aa, searching_55, searching_c3, searching_3c, readingId, readingData };
    serialReadStateE serialState;
    unsigned char currentByte;
    unsigned char currentMsgId;
    int msgByteCount;
    unsigned char currentMsg[256];
    static unsigned char preamble[4];
};

#endif // SERIALMESSAGETRANSPORT_H
