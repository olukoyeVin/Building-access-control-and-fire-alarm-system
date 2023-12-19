#include "aid6.h"
void start_module6_tcp() {
        // Create a TCP socket
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        // Set up the server address
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(12345);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));                
        // Receive data from Module 1
        char buffer[1024];
        
        recv (clientSocket, buffer, sizeof(buffer), 0);
        
        printf("Received by Module 6 (TCP): %s\n", buffer);
        char componentIdentifier[] = "Module 6:";
        char message[400] ;
        char rfid[] = " FLOOR:1";

        strcpy(message, componentIdentifier);  
        strcat(message, "cae0efe252087308");// You can change the user acces code or  interface it to the hardware to extract the value
        strcat(message, rfid);
        printf("Message sent to the server: %s\n", message);

        int bytes_sent = sendto(clientSocket, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if (bytes_sent == -1) {
            perror("Message(id) for authorization sending failed");
        } else {
            printf("Message(id) for authorization sent successfully\n");
    }
    
// Close the socket
    close(clientSocket);
}


int main (){
    start_module6_tcp();
    return 0;
}