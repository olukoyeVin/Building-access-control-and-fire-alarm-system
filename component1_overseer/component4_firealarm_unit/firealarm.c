#include "aid3.h"

void start_module4_tcp() {
    // Create a TCP socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    
    printf("Received from Module 1 (TCP): %s\n", buffer);
    char data[] = "Hello from Module 4 (TCP)!";
    sendto(clientSocket, data, sizeof(data), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

 // Close the socket
    close(clientSocket);

}
void *start_module4_udp() {
    // Create a UDP socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12346);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.4");  // Replace with the actual IP of Module 1
    bind(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(clientSocket, 5);
    
    printf("Module 4 (UDP) is waiting for a connection...\n");
    
    // Connect to Module 3
    while (1){
    int client1Socket = accept(clientSocket, NULL, NULL);
        
    // Receive data from Module 1
    char buffer[1024];
    recv(client1Socket, buffer, sizeof(buffer), 0);
    
    printf("Received by Module 4 (UDP): %s\n", buffer);
    char data[] = "Hello from Module 4 (UDP)";
    send(client1Socket, data, sizeof(data), 0);

    close(client1Socket);
    }
    close(clientSocket);
}
int main(){
    pthread_t udp_thread;
    start_module4_tcp();

    pthread_create(&udp_thread,NULL,start_module4_udp,NULL);
    while (1) {
        sleep(5); // Sleep for 5 seconds to give the threads time to run
    }
    return 0;
}