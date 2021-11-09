#include "net.h"

int main() {

    /* 建立套接字 */
    int sockfd[10];
    int iter = 0;
    for(; iter < 10; iter++)
        sockfd[iter] = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    iter = 0;

    for(; iter < 10; iter ++){
        /* 发送数据 */
        struct sockaddr_in server_addr = {0};
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(UDP_SERVER_ADDRESS);
        server_addr.sin_port = htons(UDP_SERVER_PORT);

        char *msg = "hello";
        Connect(sockfd[iter], (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
        Send(sockfd[iter], msg, strlen(msg), 0);

        /* 关闭套接字 */
        close(sockfd[iter]);
    }
    return 0;
}
