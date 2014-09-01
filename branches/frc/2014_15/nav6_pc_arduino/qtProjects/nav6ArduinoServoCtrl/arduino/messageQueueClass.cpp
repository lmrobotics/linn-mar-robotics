#include "messageQueueClass.h"
#include <iostream>

/** ***************************************************************************
* \brief Constructor
*/
messageQueueClass::messageQueueClass() :
    msgQueue(),
    available(false)
{
}

/** ***************************************************************************
* \brief Destructor
*/
messageQueueClass::~messageQueueClass()
{

}

/** ***************************************************************************
* \brief Provide an indication if whether a message is available in the queue
* or not.
*/
bool messageQueueClass::messageAvailable()
{
	return !msgQueue.empty();
}

/** ***************************************************************************
* \brief Return a message from message queue.

*/
BaseMessageClass* messageQueueClass::getMessage()
{
	BaseMessageClass* temp = msgQueue.front();
	msgQueue.pop();
	return temp;
}

/** ***************************************************************************
* \brief Add a message to message queue.
*/
void messageQueueClass::putMessage(BaseMessageClass *msg_)
{
	msgQueue.push(msg_);
}
