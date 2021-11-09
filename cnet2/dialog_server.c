#include "net.h"

int main(){
    /* 建立服务端套接字 */
    int server_sockfd = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int enable = 1;
    Setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    /* 绑定端口 */
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(TCP_SERVER_ADDRESS);
    server_addr.sin_port = htons(TCP_SERVER_PORT);

    Bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    /* 监听端口 */
    Listen(server_sockfd, CONNECTION_NUMBER);

    /* 建立tcp连接 */
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(struct sockaddr_in);
    int client_sockfd = Accept(server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    printf("Accept client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    /* 父子进程定义 */
    pid_t pid;
    if((pid = fork()) < 0)
        printf("Child process failed.\n");
    else if (pid != 0){
        /* 父进程接受数据并显示 */
        char recv_buf[TCP_BUF_LENGTH];
        size_t pkt_len = 0;
        while (pkt_len = Recv(client_sockfd, recv_buf, TCP_BUF_LENGTH, 0)) {
            recv_buf[pkt_len] = '\0';
            printf("[CLIENT]:%s",recv_buf);
        }
        printf("Connection closed.\n");
    } else {
        /* 子进程读取stdin并发送数据 */
        char send_buf[TCP_BUF_LENGTH];
        while(fgets(send_buf,TCP_BUF_LENGTH,stdin))
            Send(client_sockfd, send_buf, strlen(send_buf), 0);
    }
    close(server_sockfd);
    close(client_sockfd);
    return 0;
}