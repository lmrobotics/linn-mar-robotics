#ifndef MESSAGE_QUEUE_CLASS_H
#define MESSAGE_QUEUE_CLASS_H

#include "baseMessageClass.h"

using namespace Messages;

class messageQueueClass{

public:
    messageQueueClass();
    ~messageQueueClass();

   bool messageAvailable();
	BaseMessageClass* getMessage();
	void putMessage(BaseMessageClass *msg);

private:
   bool available;
   BaseMessageClass *msg;
};

#endif
