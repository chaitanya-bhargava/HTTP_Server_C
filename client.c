#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

int main(){

    //server info

    struct sockaddr_in server_info = {0};
    server_info.sin_family=AF_INET;
    server_info.sin_port=htons(1338);
    server_info.sin_addr.s_addr=htonl(0x7f000001);

    socklen_t server_info_len = sizeof(server_info);

    //create socket
    int tcp_socket = socket(AF_INET,SOCK_STREAM,0);
    if(tcp_socket<0){
        perror("socket");
        return -1;
    }

    //connect to server
    int con = connect(tcp_socket,(struct sockaddr *)&server_info,server_info_len);
    if(con<0){
        perror("connect");
        return -1;
    }

    //do client stuff
    char buffer[1024];
    recv(tcp_socket,(void *)buffer,1023,0);

    printf("%s\n",buffer);

    //clean up
    close(tcp_socket);

    return 0;
}