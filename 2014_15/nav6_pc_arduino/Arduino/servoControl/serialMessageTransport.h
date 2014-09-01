#ifndef SERIALMESSAGETRANSPORT_H
#define SERIALMESSAGETRANSPORT_H

#include "messageTransport.h"

class serialMessageTransport : messageTransport
{
public:

    serialMessageTransport(int baudRate);
    ~serialMessageTransport();

    /** ***************************************************************************
    * \brief Send a message.
    */
    void send(BaseMessageClass& message);

    /** ***************************************************************************
    * \brief Provide an indication if whether a message is available or not.
    */
    bool messageAvailable();

    /** ***************************************************************************
    * \brief Return a message from message queue.
    */
    BaseMessageClass *getMessage();

private:

    /** ***************************************************************************
    * \brief Connect serial port
    */

    void connect(int baudRate);
    /** ***************************************************************************
    * \brief Disconnect serial port
    */
    void disconnect();

    /** ***************************************************************************
    * \brief Send array of bytes
    */
    void send(unsigned char byteArray[], int length);

    /** ***************************************************************************
    * \brief Read 1 byte from serial stream.
    */
    int receive(unsigned char* buffer, int length);

    /** ***************************************************************************
    * \brief Read and parse serial stream data.
    */
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
