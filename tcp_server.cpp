#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "XTcp.h"

#ifdef _WIN32
#include <windows.h>
#endif

//#include <iostream>

#include <thread>
using namespace std;


class tcpThread {
public:
    //unsigned int sock_connect;
    XTcp socketConnect_1;
    void Main() {
    	
        /*********************************recv and send()************************************************/ 	
		char recvBuf[256] ={'\0'};
	     
		while(1) {
			int recvLen=socketConnect_1.socketRecv(recvBuf, sizeof(recvBuf)-1);
		//	if(recvLen!=sizeof(recvBuf)-1) break;
		
		    if(recvLen<0) break;	
		    recvBuf[recvLen] ='\0';
		    
//		    if(recvlen<0||strcmp(buf,"quit")==0) {
//			      break; 
//			} 
//					buf[recvlen] ='\0';
//				 	if(strcmp(recvBuf,"quit")==0 )  {
//				 		char send_[256]="service has quitted successful";
//				 		send(sock_connect,send_,strlen(send_)+1,0);
//					    break; 
//				    }
		                      	//	buf[recvLen] ='\0';
		 	if(strstr(recvBuf,"quit"))  {
		 		
		 		char sendBuf[256]="service has quitted successful";
		 		socketConnect_1.socketSend(sendBuf,strlen(sendBuf)+1);   //strlen();
		 		
			    break; 
		    }
    
		    int sendlen=socketConnect_1.socketSend("ok\n",4);
		   // printf (" K%dK\n ",sendlen);
			//if(buf[0]=='\0') continue; 
		    printf("\nclient:>%s\n",recvBuf);  
		} 
		
	    socketConnect_1.socketClose();
	    delete this;
	}
	
};

int main(int argc, char** argv) 
{
//	#ifdef _WIN32
//	WSADATA ws;
//	WSAStartup(MAKEWORD(2,2),&ws);
//	#endif 
//	//SOCKET sock;
//	

	
		XTcp socketMonitor;
		socketMonitor.socketCreat();
		socketMonitor.port=8080;
		if(argc>1) {
		  socketMonitor.port=atoi(argv[1]);  //argv[0] contained the name of main function;
		};
		 
        	printf("\n%d\n",socketMonitor.socket);
        	
        socketMonitor.socketBind();
        socketMonitor.socketListen(10);
		 
		/*************************************** accept()******************************************/ 
		while(1) {
			     
				 XTcp socketConnect;
				  
				 socketConnect=socketMonitor.socketAccept();  
				 
				 
			     //int sock_connect;   //int temp=sizeof(sockaddr); 
			                           //  socklen_t T=sizeof(sockaddr); 
				//sock_connect=accept(sock1,(sockaddr*)&cliAddr,&T);                 //(sockaddr*)&cliAddr, &temp); 
				//if(sock_connect<0 ) { break;}
				
				printf("Creat a new socket [%d]\n",socketConnect.socket); 
//				
//				char * p=inet_ntoa(cliAddr.sin_addr); 
				printf("ClientAddress ip addr:>%s   port:>%d",socketConnect.ip.c_str(), socketConnect.port ); 
				
			    tcpThread * th=new tcpThread();               //	tcpThread tThread;
				th->socketConnect_1=socketConnect;
				
				    thread sth(&tcpThread::Main ,th);   // beginning this thread;
				    sth.detach();
				
	    }

		
	   //	printf("[%d]\n",sock1);
		
     	socketMonitor.socketClose();
     	
	#ifdef _WIN32
	WSACleanup();
	#endif
	
	return 0;
}
