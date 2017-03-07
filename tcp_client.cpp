
#include "XTcp.h"

   #ifdef _WIN32
   #include <windows.h>
   #endif
   
int main ()
{
	
   XTcp client;
   client.socketCreat();
   client.setBlock(false) ;
   //printf("hhhhhhh"); 
   client.socketConnect_client("192.168.61.128", 8085,5000);
   
   client.socketSend("client",7) ;
   
   char sendBuf[256]={'\0'};
   
   client.socketRecv(sendBuf,256);
   
   printf("service:>%s",sendBuf);
   
   client.socketClose();
   
   #ifdef _WIN32
   
   WSACleanup(); 
   //closesocket(client.socket);
   #endif

  return 0;
}
