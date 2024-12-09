#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

int main(){

    //socket info struct
    struct sockaddr_in server_info = {0};

    server_info.sin_family=AF_INET;
    server_info.sin_port=htons(1338);

    socklen_t server_info_len = sizeof(server_info);

    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);

    //create socket
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket<0){
        perror("socket");
        return -1;
    }

    //bind
    int bind_socket = bind(tcp_socket,(struct sockaddr*)&server_info,server_info_len);
    if(bind_socket<0){
        perror("bind");
        return -1;
    }

    //listen
    int listen_socket = listen(tcp_socket,0);
    if(listen_socket<0){
        perror("listen");
        return -1;
    }

    //accept
    int accept_con = accept(tcp_socket,&client_info,&client_info_len);
    if(accept_con<0){
        perror("accept");
        return -1;
    }

    //do client stuff
    char * str = "Hello World!";
    send(accept_con,(void* )str,strlen(str),0);

    //clean up
    close(accept_con);

    return 0;
}