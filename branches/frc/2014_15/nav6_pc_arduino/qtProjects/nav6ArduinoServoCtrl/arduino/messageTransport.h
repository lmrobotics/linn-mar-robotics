#ifndef MESSAGE_TRANSPORT_H
#define MESSAGE_TRANSPORT_H
#include "baseMessageClass.h"
#include "messageQueueClass.h"
using namespace Messages;

class messageTransport {

public:

    messageTransport();
	~messageTransport();
    void send(BaseMessageClass& message);
    bool messageAvailable();
    BaseMessageClass *getMessage();

protected:

    messageQueueClass msgQueue;

};

#endif
