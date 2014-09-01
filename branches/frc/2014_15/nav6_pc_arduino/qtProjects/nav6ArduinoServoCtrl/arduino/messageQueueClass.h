#ifndef MESSAGE_QUEUE_CLASS_H
#define MESSAGE_QUEUE_CLASS_H

#include "baseMessageClass.h"
#include <queue>

using namespace Messages;

class messageQueueClass{

public:
    messageQueueClass();
    ~messageQueueClass();

    bool messageAvailable();
    BaseMessageClass* getMessage();
    void putMessage(BaseMessageClass *msg);

private:
    std::queue<BaseMessageClass*> msgQueue;
    bool available;
};

#endif
