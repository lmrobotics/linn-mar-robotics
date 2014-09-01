#ifndef MESSAGE_TRANSPORT_H
#define MESSAGE_TRANSPORT_H
#include "baseMessageClass.h"
#include "messageQueueClass.h"
using namespace Messages;

class messageTransport {

public:

    messageTransport();
	~messageTransport();

    /** ***************************************************************************
    * \brief Send a message.
    */
    virtual void send(BaseMessageClass& message) = 0;

    /** ***************************************************************************
    * \brief Provide an indication if whether a message is available or not.
    */
    virtual bool messageAvailable() = 0;

    /** ***************************************************************************
    * \brief Return a message from message queue.
    */
    virtual BaseMessageClass *getMessage() = 0;

protected:

    messageQueueClass msgQueue;

};

#endif
