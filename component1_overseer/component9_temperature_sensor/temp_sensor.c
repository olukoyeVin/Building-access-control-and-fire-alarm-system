#include "aid9.h"

void start_module9_udp() {
    // Create a UDP socket
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12346);  // Use the same port as Module 1 (UDP)
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Replace with the actual IP of Module 1
    printf("Module 9 (UDP) is sending data...\n");
    
    // Send data to Module 1
    char data[400] ;
    char componentIdentifier[] = "Module 9:";
    char temperature[] = " 135";
    strcat(data, componentIdentifier);
    strcat(data, temperature);
    printf("Message sent to the server: %s\n", data);
    sendto(udpSocket, data, sizeof(data), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // Close the socket
    close(udpSocket);
}


int main (){
    start_module9_udp();
    return 0;
}