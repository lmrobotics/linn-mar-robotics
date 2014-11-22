#ifndef MESSAGE_WRAPPER_H
#define MESSAGE_WRAPPER_H

#include <vector>
#include <pthread.h>
#include "BaseMessageClass.h"
#include "MessageTypesClass.h"
#include "udpServerMessageTransport.h"
#include "nav6.h"
#include "nav6Resp.h"

class messageWrapper
{
public:
	messageWrapper(unsigned short port);
	~messageWrapper(void);
	float getYaw(void);
	float getPich(void);
	float getRoll(void);
	void stopServerThread(void);
private:
	bool threadRunning;
	pthread_t* serverThread;
	static void* updateMessage(void* umt);
	udpServerMessageTransport* server;
	float mRoll;
	float mYaw;
	float mPich;
};

#endif
