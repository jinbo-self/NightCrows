// server.cpp
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

void sendFile(int new_socket) {
    std::string filename = "ML.dll"; // 仅作示例
    std::ifstream file(filename, std::ios::binary);

    if (file.is_open()) {
        char buffer[1024] = { 0 };
        while (!file.eof()) {
            file.read(buffer, sizeof(buffer));
            send(new_socket, buffer, file.gcount(), 0);
            memset(buffer, 0, sizeof(buffer));
        }
        file.close();
        std::cout << "File sent successfully" << std::endl;
    }
    else {
        std::cout << "Failed to open file" << std::endl;
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Listening on port " << PORT << "..." << std::endl;

    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    sendFile(new_socket);

    close(new_socket);
    return 0;
}