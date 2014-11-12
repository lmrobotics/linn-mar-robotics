#ifndef UDPMESSAGETRANSPORT_H
#define UDPMESSAGETRANSPORT_H

#include "BaseMessageClass.h"
#include "messageTransport.h"
#include <arpa/inet.h>

class udpMessageTransport : public messageTransport
{
public:

    udpMessageTransport(const char* ipAddress, unsigned short port);
    ~udpMessageTransport();

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
    BaseMessageClass* getMessage();

private:

    /** ***************************************************************************
    * \brief Check UDP port for data grams
    */
    int receive(unsigned char* buffer, int length);

    enum ethSize {UDP_TX_PACKET_MAX_SIZE = 1500};

    int sock;
    struct sockaddr_in sa;
};

#endif // UDPMESSAGETRANSPORT_H
