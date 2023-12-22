#include <netinet/in.h>
#include <cerrno>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    int server_fd;
    int client_fd;
    int bytes_read;
    char buffer[1024];
    sockaddr_in addr;
    socklen_t addlen = sizeof(addr);
    printf("Starting server...\n");

    // create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        // TODO: check errno
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }
    printf("Socket created. fd = %d\n", server_fd);

    // bind socket to a port
    addr.sin_family = AF_INET,
    addr.sin_port = htons(8888),
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        // TODO: check errno
        fprintf(stderr, "Failed to bind socket\n");
        return 1;
    }

    // listen for incoming connections
    if(listen(server_fd, 10) < 0) {     // TODO: magic number for backlog
        // TODO: check errno
        fprintf(stderr, "Error listening for new connections\n");
        return 1;
    }

    // accept new connection
    printf("Awaiting new connection...\n");
    client_fd = accept(server_fd, (sockaddr*)&addr, &addlen);
    if(client_fd < 0) {
        // TODO: check errno
        fprintf(stderr, "Error accepting new connetion\n");
        return 1;
    }
    printf("Connected! client_fd = %d\n", client_fd);

    // read the connection, print it, and echo
    bytes_read = read(client_fd, buffer, 1024-1);
    printf("%d bytes read - %s\n", bytes_read, buffer);
    send(client_fd, buffer, bytes_read, 0);

    // close sockets
    close(client_fd);
    close(server_fd);
    return 0;
}
