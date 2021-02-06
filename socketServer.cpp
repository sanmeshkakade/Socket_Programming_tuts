#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 9909

//declaring the sockaddr_in structure
struct sockaddr_in srv;

//fd_set is a structure which contains 2 elements 
//1 unsigned int fd_count no of file descriptors which we are going to set in fd_set
//2 SOCKET fd_array[FD_SETSIZE]; which is where we are going to                                                                          7
fd_set fr,fw,fe;

int main(){

    //variable declaration
    int nRet = 0;

    //initializing the socket 

    int nSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    //checking for success of call
    if(nSocket<0){
        cout<<endl<<"The Socket Call failed.";
        exit(EXIT_FAILURE);
    }
    else{
        cout<<endl<<"The Socket Successfully Assigned. :)";
    }
    cout<<endl<<"The Socket Opened :"<<nSocket;

    //Initialising the environment for sockaddr structure

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    //below line is used to assign a particular ip address for server
    //srv.sin_addr.s_addr = inet_addr("192.168.0.2");
    srv.sin_addr.s_addr = INADDR_ANY;
    memset(&(srv.sin_zero),0,8);

    //Binding the socket to local port

    nRet = bind(nSocket, (sockaddr*) &srv, sizeof(sockaddr));
    //checking the bind call
    if(nRet<0){
        cout<<endl<<"Failed to bind to local port.";
        exit(EXIT_FAILURE);
    }
    else{
        cout<<endl<<"Successfully Binded to local port.";
    }
    
    //Listen the request from client (queues the requests)

    nRet = listen(nSocket,5);
    //Checking the listen call
    if(nRet<0){
        cout<<endl<<"Failed to start to listen to local port.";
        exit(EXIT_FAILURE);
    }
    else{
        cout<<endl<<"Listning to local port.";
    }

    //keep waiting for new requests and proceed as per request which are coming

    return 0;
}