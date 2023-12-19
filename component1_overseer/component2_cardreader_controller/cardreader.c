#include "aid1.h"

void start_module2_tcp() {
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
    
    printf("Received by Module 2 (TCP): %s\n", buffer);
    char componentIdentifier[] = "Module 2:";
    char message[400];
    char RFID[] = " DOOR:202"; // You can change the RFID code and the door number or interface it to the hardware to extract

    strcpy(message, componentIdentifier);  
    strcat(message, "4b6f9c1d4d55506c");// You can change the user acces code or  interface it to the hardware to extract the value
    strcat(message, RFID); 

    printf("Message sent to the server: %s\n", message);

    int bytes_sent = sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bytes_sent == -1) {
        perror("Message(id) for authorization sending failed");
    } else {
        printf("Message(id) for authorization sent successfully\n");
    }

    close(clientSocket);
}

int main(){
    start_module2_tcp();
    return 0;
}
