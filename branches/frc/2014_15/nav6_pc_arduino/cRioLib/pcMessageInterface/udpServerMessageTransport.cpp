#include "udpServerMessageTransport.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "sockLib.h" 

using namespace std;

struct HexCharStruct
{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
  return HexCharStruct(_c);
}

udpServerMessageTransport::udpServerMessageTransport(unsigned short port) : rxConnectionValid(false)
{
   //create an internet, datagram, socket using UDP
   sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if (-1 == sock) /* if socket failed to initialize, exit */
   {
      cout << "Error Creating Socket" << endl;
      exit(EXIT_FAILURE);
   }

   //Zero out socket address
   memset(&sa, 0, sizeof sa);

   //The address is ipv4
   sa.sin_family = AF_INET;

   // Use any host IP
   sa.sin_addr.s_addr = INADDR_ANY;

   //sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654
   sa.sin_port = htons(port);

   if (-1 == bind(sock,(struct sockaddr *)&sa, sizeof(sa)))
     {
	   cout << "Bind Failed" << endl;
       close(sock);
       exit(EXIT_FAILURE);
     }

   memset(&rxConnection, 0, sizeof rxConnection);
   pthread_create(&rxT, NULL, &udpServerMessageTransport::rxThread, (void*)this);
}

udpServerMessageTransport::~udpServerMessageTransport()
{
   pthread_join(rxT, NULL);
   close(sock);
}

/** ***************************************************************************
* \brief Send back to the last connection received from, if it's valid.
*/
void udpServerMessageTransport::send(BaseMessageClass &message)
{
   int bytes_sent = 0;
   if (rxConnectionValid)
   {
      try
      {
         bytes_sent = sendto(sock, (char*)message.message, message.messageSize(), 0, &rxConnection, sizeof rxConnection);
      }
      catch (int e)
      {
         cout << "Exception Occurred " << e << std::endl;
         cout << std::endl;
      }
      if (bytes_sent < 0)
      {
         cout << "sendto error! " << bytes_sent << std::endl;
         cout << std::endl;
      }
   }
}

/** ***************************************************************************
* \brief Receive thread for server
*/
void *udpServerMessageTransport::rxThread(void* umt)
{

	udpServerMessageTransport* cp_umt = (udpServerMessageTransport*)umt;

   while (true)
   {
      unsigned char currentMsg[UDP_TX_PACKET_MAX_SIZE];
      int size = cp_umt->receive(currentMsg, UDP_TX_PACKET_MAX_SIZE);
      if (size > 0)
      {
         BaseMessageClass *tmp = new BaseMessageClass(currentMsg);
         cp_umt->msgQueue.putMessage(tmp);
      }
   }
   return umt;
}

/** ***************************************************************************
* \brief Provide an indication if whether a message is available or not.
*/
bool udpServerMessageTransport::messageAvailable()
{
    return msgQueue.messageAvailable();
}

/** ***************************************************************************
* \brief Return a message from message queue.
*/
BaseMessageClass* udpServerMessageTransport::getMessage()
{
    return msgQueue.getMessage();
}

/** ***************************************************************************
* \brief Check UDP port for data grams
*/
int udpServerMessageTransport::receive(unsigned char* buffer, int length)
{
   int len = sizeof rxConnection;
   int size = recvfrom(sock, (char*)buffer, length, 0, &rxConnection,  &len);
   if (size>0)
   {
	   rxConnectionValid = true;
      return size;
   }
   return 0;
}

