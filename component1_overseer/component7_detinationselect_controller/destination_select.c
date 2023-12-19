#include "aid7.h"


void *start_module7_tcp() {
    // Create a TCP socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    // Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.5");  // Replace with the actual IP of Module 7
    bind(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(clientSocket, 5);
    
    printf("Module 7 (TCP) is waiting for a connection...\n");
    
    // Connect to Module 3
    while (1){
    int client1Socket = accept(clientSocket, NULL, NULL);
        
    // Receive data from Module 1
    char buffer[1024];
    recv(client1Socket, buffer, sizeof(buffer), 0);
    
    printf("Received by Module 7 (TCP): %s\n", buffer);
    char data[] = "Hello from Module 7 (TCP)!";
    send(client1Socket, data, sizeof(data), 0);

    close(client1Socket);
    }
    close(clientSocket);
}

int main(){
    pthread_t tcp_thread;

    pthread_create(&tcp_thread,NULL,start_module7_tcp,NULL);
    while (1) {
        sleep(5); // Sleep for 5 seconds to give the threads time to run
    }
    return 0;
}
