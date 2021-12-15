/*************************************************
  Filename: server.cc
  Creator: yongdol503
  Description: linux socket(UDP) server
*************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_DATA_SIZE 1024

#define ERROR(func_name) (printf("ERROR in function '%s'.\n", (func_name)))

typedef struct sockaddr sockaddr;       // socket address
typedef struct sockaddr_in sockaddr_in; // ipv4 socket address

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("socket error\n");
        return -1;
    }
    sockaddr_in addr;
    bzero(&addr, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &addr.sin_addr);
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(50000);

    if (-1 == bind(sockfd, (sockaddr *)&addr, sizeof(sockaddr_in)))
    {
        ERROR("bind");
        return -1;
    }

    char *p_buffer = new char[MAX_DATA_SIZE];

    socklen_t socklen = sizeof(sockaddr_in);

    while (true)
    {
        printf("waiting for client...\n");
        int len_data = recvfrom(sockfd, p_buffer, MAX_DATA_SIZE, 0, (sockaddr *)&addr, &socklen);
        if (0 < len_data)
        {
            p_buffer[len_data] = '\0';
            printf("Receive data: %s.\n", p_buffer);
            if (0 == strcmp(p_buffer, "exit"))
            {
                break;
            }
            if (-1 != sendto(sockfd, p_buffer, strlen(p_buffer), 0, (sockaddr *)&addr, sizeof(sockaddr_in)))
            {
                printf("Send data: %s.\n", p_buffer);
            }
            else
            {
                ERROR("sendto");
                break;
            }
        }
    }

    printf("Server Exit\n");
    return 0;
}