#ifndef MESSAGE_QUEUE_CLASS_H
#define MESSAGE_QUEUE_CLASS_H

#include "BaseMessageClass.h"
#include <queue>
#include <semaphore.h>

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
    * \brief Return a message from message queue if available.  Calling thread is
    * blocked if no message is available until one is put in the queue.
    */
    BaseMessageClass* getMessage();

    /** ***************************************************************************
    * \brief Add a message to message queue.
    */
    void putMessage(BaseMessageClass *msg);

private:
    std::queue<BaseMessageClass*> msgQueue;
    sem_t msgSem;
    bool available;
};

#endif
