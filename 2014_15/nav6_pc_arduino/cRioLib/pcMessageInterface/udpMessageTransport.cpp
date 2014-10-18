#include "udpMessageTransport.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "sockLib.h" 

udpMessageTransport::udpMessageTransport(char* ipAddress, unsigned short port)
{
   //create an internet, datagram, socket using UDP
   sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if (-1 == sock) /* if socket failed to initialize, exit */
   {
      //printf("Error Creating Socket");
      exit(EXIT_FAILURE);
   }

   //Zero out socket address
   memset(&sa, 0, sizeof sa);

   //The address is ipv4
   sa.sin_family = AF_INET;

   //ip_v4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value
   sa.sin_addr.s_addr = inet_addr(ipAddress);

   //sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654
   sa.sin_port = htons(port);
}

udpMessageTransport::~udpMessageTransport()
{
   close(sock);
}

void udpMessageTransport::send(BaseMessageClass &message)
{
   //sendto(int socket, char data, int dataLength, flags, destinationAddress, int destinationStructureLength)
   int bytes_sent = sendto(sock, (char*)message.message, message.messageSize(), 0,(struct sockaddr*)&sa, sizeof sa);
   if (bytes_sent < 0)
   {
      exit(EXIT_FAILURE);
   }
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
   struct sockaddr tempAddr;
   int len = sizeof tempAddr;
   memset(&tempAddr, 0, sizeof tempAddr);
   int size = recvfrom(sock, (char*)buffer, length, MSG_DONTWAIT, &tempAddr,  &len);
   if (size>0)
   {
      return size;
   }
   return 0;
}

