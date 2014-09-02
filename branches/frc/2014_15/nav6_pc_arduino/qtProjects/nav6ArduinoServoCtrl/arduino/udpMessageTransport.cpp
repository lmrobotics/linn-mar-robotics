#include "udpMessageTransport.h"

udpMessageTransport::udpMessageTransport(QString ipAddress, unsigned int port) :
    localPort(port),
    hostAddr(ipAddress),
    socket()
{
    socket.bind(hostAddr, port);
    socket.connectToHost(hostAddr, port);
}

udpMessageTransport::~udpMessageTransport()
{
    socket.close();
}

void udpMessageTransport::send(BaseMessageClass &message)
{
    if(socket.state() == QAbstractSocket::UnconnectedState)
    {
       socket.bind(hostAddr, localPort);
    }
    socket.writeDatagram((const char *)message.message,
                         message.messageSize(), hostAddr, localPort);
}

/** ***************************************************************************
* \brief Provide an indication if whether a message is available or not.
*/
bool udpMessageTransport::messageAvailable()
{
    unsigned char currentMsg[UDP_TX_PACKET_MAX_SIZE];
    int size = receive(currentMsg, UDP_TX_PACKET_MAX_SIZE);
    if (size > 0)
    {
       BaseMessageClass *tmp = new BaseMessageClass(currentMsg);
       msgQueue.putMessage(tmp);
    }
    return msgQueue.messageAvailable();
}

/** ***************************************************************************
* \brief Return a message from message queue.
*/
BaseMessageClass* udpMessageTransport::getMessage()
{
    return msgQueue.getMessage();
}

/** ***************************************************************************
* \brief Check UDP port for data grams
*/
int udpMessageTransport::receive(unsigned char* buffer, int length)
{
   if(socket.state() == QAbstractSocket::UnconnectedState)
   {
      socket.bind(hostAddr, localPort);
   }
   quint16* port = new quint16();
   *port = localPort;
   int size = socket.readDatagram((char*)buffer, length, &hostAddr, port);
   if (size>0)
   {
      return size;
   }
   return 0;

}

