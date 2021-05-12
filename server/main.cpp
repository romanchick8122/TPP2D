#ifdef WIN32
#include <ctime>
#include "winsock2.h"
#else
#include "sys/socket.h"
#define SOCKET int
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include "iostream"
#include "vector"
#include <cstring>
int main(int argc, char *argv[]) {
    //init sockets
#ifdef WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    SOCKET worker = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in settings;
    settings.sin_family = AF_INET;
    settings.sin_addr.s_addr = INADDR_ANY;
    settings.sin_port = htons(9587);
    bind(worker, (struct sockaddr*)&settings, sizeof(settings));
    int numberOfConnections;
    if (argc == 1) {
        std::cin >> numberOfConnections;
    } else {
        numberOfConnections = std::stoi(argv[1]);
    }
    listen(worker, numberOfConnections);
    std::vector<SOCKET> clients(numberOfConnections);
    srand(time(nullptr));
    uint32_t gameRng = abs(1LL * rand() * rand() * rand()) % UINT32_MAX;
    for (int i = 0; i < numberOfConnections; ++i) {
        std::cout << "Waiting for " << i << "... ";
        struct sockaddr_in client;
#ifdef WINNT
        int tmp = sizeof(struct sockaddr_in);
#else
        socklen_t tmp = sizeof(struct sockaddr_in);
#endif
        clients[i] = accept(worker, (struct sockaddr*)&client, &tmp);
        char* buff = new char[6];
        buff[0] = static_cast<char>(i);
        buff[1] = static_cast<char>(numberOfConnections);
        *reinterpret_cast<uint32_t*>(buff + 2) = gameRng;
        send(clients[i], buff, 6, 0);
        buff[0] = 0;
        send(clients[i], buff, 1, 0);
        delete[] buff;
        std::cout << "accepted\n";
    }
    std::vector<char*> answers(numberOfConnections);
    for (int client = 0; client < numberOfConnections; ++client) {
        answers[client] = new char[4096];
    }
    std::vector<int> sizes(numberOfConnections);
    while(true) {
        int totalSize = 0;
        int genCnt = 0;
        for (int client = 0; client < numberOfConnections; ++client) {
            sizes[client] = recv(clients[client], answers[client], 4096, 0);
            totalSize += sizes[client] - 1;
            genCnt += answers[client][0];
        }
        if (genCnt > 256) {
            break;
        }
        char* broadcast = new char[totalSize + 1];
        broadcast[0] = static_cast<char>(genCnt);
        int car = 1;
        for (int client = 0; client < numberOfConnections; ++client) {
            memcpy(broadcast + car, &(answers[client][1]), sizes[client] - 1);
            car += sizes[client] - 1;
        }
        for (int client = 0; client < numberOfConnections; ++client) {
            send(clients[client], broadcast, totalSize + 1, 0);
        }
        delete[] broadcast;
    }
}