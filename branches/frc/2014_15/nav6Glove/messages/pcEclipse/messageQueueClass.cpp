#include "messageQueueClass.h"
#include <iostream>

/** ***************************************************************************
* \brief Constructor
*/
messageQueueClass::messageQueueClass() :
    msgQueue(),
    available(false)
{
   sem_init(&msgSem, 1, 0);
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
   bool emptyFlag = true;
   {
      emptyFlag = !msgQueue.empty();
   }
   return emptyFlag;
}

/** ***************************************************************************
* \brief Return a message from message queue.

*/
BaseMessageClass* messageQueueClass::getMessage()
{
	sem_wait(&msgSem);
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
	sem_post(&msgSem);
}
