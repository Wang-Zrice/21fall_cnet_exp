#include "net.h"

int main() {

    /* 建立套接字 */
    int sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* 建立tcp连接 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(TCP_SERVER_ADDRESS);
    server_addr.sin_port = htons(TCP_SERVER_PORT);

    Connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /* 发送数据 */
    char send_buf[TCP_BUF_LENGTH];
    while(fgets(send_buf,TCP_BUF_LENGTH,stdin)){
        Send(sockfd, send_buf, strlen(send_buf), 0);
        /* 接收回显数据 */
        char buf[TCP_BUF_LENGTH];
        size_t pkt_len = 0;
        if (pkt_len = Recv(sockfd, buf, TCP_BUF_LENGTH, 0)) {
            buf[pkt_len] = '\0';
            printf("%s",buf);
        } 
    }

    /* 关闭套接字 */
    close(sockfd);

    return 0;
}
