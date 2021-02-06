#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
using namespace std;

#define PORT 9909

//declaring the sockaddr_in structure
struct sockaddr_in srv;

//fd_set is a structure which contains 2 elements 
//1 unsigned int fd_count no of file descriptors which we are going to set in fd_set
//2 SOCKET fd_array[FD_SETSIZE]; which is where we are going to store socket descriptors                                                                          7
fd_set fr,fw,fe;

//fr -collection of those who are ready to read on network
//fw -collection of those who are ready to write on network
//fe -collection of those socket descriptors who are throwing execptions on network

int main(){

    //variable declaration
    int nRet = 0;
    int nMaxFd;

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

    nMaxFd = nSocket;

    fd_set fr,fw,fe;

//fr -collection of those who are ready to read on network
//fw -collection of those who are ready to write on network
//fe -collection of those socket descriptors who are throwing execptions on network


    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    FD_ZERO(&fr);
    FD_ZERO(&fw);
    FD_ZERO(&fe);

    FD_SET(nSocket, &fr);
    FD_SET(nSocket, &fe);
    
    cout<<endl<<"Before select call :"<<fr.fd_count;

    //keep waiting for new requests and proceed as per request which are coming
    nRet = select(nMaxFd+1, &fr, &fw, &fe, &tv);
    if(nRet>0){
        //case when someone connects or communicates with  messge over a dedicted connection
    }
    else if(nRet==0){
        //no connection or any communiction request made 
        //or none of the socket descriptors re ready
        cout<<endl<<"Nothing on port :"<< PORT ;
    }
    else{
        //it failed and your application should show some useful message
    }

    cout<<endl<<"After select call :"<<fr.fds_bits;


    return 0;
}