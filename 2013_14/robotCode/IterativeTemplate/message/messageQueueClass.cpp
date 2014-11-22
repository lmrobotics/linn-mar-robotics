#include "messageQueueClass.h"

/** ***************************************************************************
* \brief Constructor
*/
messageQueueClass::messageQueueClass() :
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
	return messageQueueClass::available;
}

/** ***************************************************************************
* \brief Return a message from message queue.

*/
BaseMessageClass* messageQueueClass::getMessage()
{
	available = false;
	return msg;
}

/** ***************************************************************************
* \brief Add a message to message queue.
*/
void messageQueueClass::putMessage(BaseMessageClass *msg_)
{
	available = true;
	msg = msg_;
}
