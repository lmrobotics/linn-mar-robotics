#ifndef UDPSERVERMESSAGETRANSPORT_H
#define UDPSERVERMESSAGETRANSPORT_H

#include "BaseMessageClass.h"
#include "messageTransport.h"
#include <arpa/inet.h>
#include <pthread.h>

class udpServerMessageTransport : public messageTransport
{
public:

	udpServerMessageTransport(unsigned short port);
    ~udpServerMessageTransport();

    /** ***************************************************************************
    * \brief Send a message to last IP/Port received from
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
    static void *rxThread(void* umt);

    enum ethSize {UDP_TX_PACKET_MAX_SIZE = 1500};

    int sock;
    struct sockaddr_in sa;
    struct sockaddr rxConnection;
    bool rxConnectionValid;

    pthread_t rxT;

};

#endif // UDPSERVERMESSAGETRANSPORT_H
