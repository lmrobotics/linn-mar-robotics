#include "messageWrapper.h"
 
messageWrapper::messageWrapper(unsigned short port) : threadRunning(true){
	server = new udpServerMessageTransport(port);
	serverThread = new pthread_t();
	pthread_create( serverThread, NULL, &messageWrapper::updateMessage, (void*)this);
}

void *messageWrapper::updateMessage(void* umt){
	
	messageWrapper* This = (messageWrapper*)umt;
	while(This->threadRunning){
		while (This->server->messageAvailable())
		{
		BaseMessageClass *tmp = This->server->getMessage();
		MessageTypesClass::messageId msgType = tmp->messageType();
		switch (msgType)
		{
			case Messages::MessageTypesClass::nav6Id:
			{
				Messages::nav6 nav6(tmp->message);
				This->mYaw = nav6.nav6Yaw;
				This->mRoll = nav6.nav6Roll;
				This->mPich = nav6.nav6Pich;
				
				Messages::nav6Resp nav6Response;
				This->server->send((Messages::BaseMessageClass&)nav6Response);
				
			}     
			break;

			default:
			break;
		}
		delete tmp;
		}
	}
	return umt;
}


void messageWrapper::stopServerThread(){
	threadRunning = false;
	pthread_join(*serverThread, NULL);
}

float messageWrapper::getPich(){
	return mPich;
}

float messageWrapper::getRoll(){
	return mRoll;
}

float messageWrapper::getYaw(){
	return mYaw;
}

messageWrapper::~messageWrapper(){
	delete server;
	delete serverThread;
}
