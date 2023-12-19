#include "aid4.h"

void start_module5_tcp() {
    // Create a TCP socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Replace with the actual IP of Module 1
    
    // Connect to Module 1
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // Receive data from Module 1
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    
    printf("Received by Module 5 (TCP): %s\n", buffer);
    char data[] = "Hello from Module 5 (TCP)!";
    sendto(clientSocket, data, sizeof(data), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // Close the socket
    close(clientSocket);
}

int main(){
    start_module5_tcp();
    return 0;
}
