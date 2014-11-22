#include "udpMessageTransport.h"

static byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xDE };

udpMessageTransport::udpMessageTransport(IPAddress ipAddress, unsigned int port) 
   : Udp()
{
   Ethernet.begin(mac,ipAddress);
   Udp.begin(port);
}

udpMessageTransport::~udpMessageTransport()
{
   Udp.stop();
}

void udpMessageTransport::send(BaseMessageClass &message)
{
   Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
   Udp.write(message.message, message.messageSize());
   Udp.endPacket();
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
   int packetSize = Udp.parsePacket();
   if (packetSize > 0) 
   {
      Udp.read(buffer, length);
      return packetSize;
   }
   else
   {
      return 0;
   }
}

