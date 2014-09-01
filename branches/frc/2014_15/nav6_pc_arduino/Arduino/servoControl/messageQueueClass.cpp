#include "messageQueueClass.h"

messageQueueClass::messageQueueClass() :
   available(false)
{
}

messageQueueClass::~messageQueueClass()
{

}

bool messageQueueClass::messageAvailable()
{
	return messageQueueClass::available;
}

BaseMessageClass* messageQueueClass::getMessage()
{
	available = false;
	return msg;
}

void messageQueueClass::putMessage(BaseMessageClass *msg_)
{
	available = true;
	msg = msg_;
}
