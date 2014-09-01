#ifndef MESSAGE_QUEUE_CLASS_H
#define MESSAGE_QUEUE_CLASS_H

#include "baseMessageClass.h"
#include <queue>

using namespace Messages;

class messageQueueClass{

public:
    messageQueueClass();
    ~messageQueueClass();

    /** ***************************************************************************
    * \brief Provide an indication if whether a message is available or not.
    */
    bool messageAvailable();

    /** ***************************************************************************
    * \brief Return a message from message queue.
    */
    BaseMessageClass* getMessage();

    /** ***************************************************************************
    * \brief Add a message to message queue.
    */
    void putMessage(BaseMessageClass *msg);

private:
    std::queue<BaseMessageClass*> msgQueue;
    bool available;
};

#endif
