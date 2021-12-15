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

#define MAX_DATA_SIZE 1024

#define ERROR(func_name) (printf("ERROR in function '%s'.\n", (func_name)))

typedef struct sockaddr sockaddr;       // socket address
typedef struct sockaddr_in sockaddr_in; // ipv4 socket address

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == -1)
    {
        ERROR("socket");
        return -1;
    }

    sockaddr_in addr;
    bzero(&addr, sizeof(sockaddr_in));
    addr.sin_family = AF_INET;
    inet_aton("127.0.0.1", &addr.sin_addr);
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(50000);

    char *p_buffer = new char[MAX_DATA_SIZE];

    socklen_t addr_len = sizeof(sockaddr_in);

    while (true)
    {
        int idx = 0;
        char ch;
        printf("Please input your data: ");
        while ((ch = getchar()) != '\n')
            p_buffer[idx++] = ch;
        p_buffer[idx] = '\0';
        if (-1 != sendto(sockfd, p_buffer, strlen(p_buffer), 0, (sockaddr *)&addr, addr_len))
        {
            printf("send data: %s\n", p_buffer);
            bzero(p_buffer, MAX_DATA_SIZE);
            int len_data = recvfrom(sockfd, p_buffer, MAX_DATA_SIZE, 0, (sockaddr *)&addr, &addr_len);
            if (0 < len_data)
            {
                p_buffer[len_data] = '\0';
                printf("receive data: %s\n", p_buffer);
            }
        }
        else
        {
            ERROR("sendto");
            break;
        }
    }
    delete p_buffer;

    close(sockfd);
    return 0;
}