#ifndef MESSAGE_QUEUE_CLASS_H
#define MESSAGE_QUEUE_CLASS_H

#include "baseMessageClass.h"
#include <queue>

using namespace Messages;

class messageQueueClass{

public:
	messageQueueClass();
	~messageQueueClass();

	static bool messageAvailable();
	static BaseMessageClass* getMessage();
	static void putMessage(BaseMessageClass *msg);

private:
	static std::queue<BaseMessageClass*> msgQueue;
	static bool available;
	static BaseMessageClass *msg;
};

#endif
