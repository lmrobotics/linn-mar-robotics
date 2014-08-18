#include "messageQueueClass.h"
#include <iostream>

std::queue< BaseMessageClass*> messageQueueClass::msgQueue;

bool messageQueueClass::available = false;
BaseMessageClass *messageQueueClass::msg;

messageQueueClass::messageQueueClass()
{
}

messageQueueClass::~messageQueueClass()
{

}

bool messageQueueClass::messageAvailable()
{
	return !msgQueue.empty();
}

BaseMessageClass* messageQueueClass::getMessage()
{
	BaseMessageClass* temp = msgQueue.front();
	msgQueue.pop();
	return temp;
}

void messageQueueClass::putMessage(BaseMessageClass *msg_)
{
	msgQueue.push(msg_);
}
