#include "aid.h"

void sendAccessSignal(const char *accessCode,char rfid[]) {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.2");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    char buffer[1024];

    snprintf(buffer, sizeof(buffer), "%s%s", accessCode,rfid);
    printf("Sending access signal: %s\n", buffer);

    send(clientSocket, buffer, strlen(buffer), 0);

    // Close the client socket
    close(clientSocket);
}
void sendElevatorAccessSignal(const char *accessCode,char rfid[]) {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.5");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    char buffer[1024];

    snprintf(buffer, sizeof(buffer), "%s%s", accessCode,rfid);
    printf("Sending Elevator access signal: %s\n", buffer);

    send(clientSocket, buffer, strlen(buffer), 0);

    // Close the client socket
    close(clientSocket);
}

void *start_module1_tcp() {
    // Create a TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Bind the socket
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // Listen for incoming connections
    listen(serverSocket, 5);
    
    printf("Module 1 (TCP) is waiting for a connection...\n");
    
    // Accept a client connection
    while (1){
    int clientSocket = accept(serverSocket, NULL, NULL);
    
    // Send data to the client
    char data[] = "Hello from Module 1 (TCP)!";
    send(clientSocket, data, sizeof(data), 0);

    char buffer[1024];
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    int bytes_received = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrLen);


    if (bytes_received == -1) {
    perror("Message receiving failed");
    }

    buffer[bytes_received] = '\0';
    char componentIdentifier[20];
    char* messageContent = strchr(buffer, ':');
    if (messageContent != NULL) {
        strncpy(componentIdentifier, buffer, messageContent - buffer);
        componentIdentifier[messageContent - buffer] = '\0';
        messageContent++;
        printf("Component identifier: %s\n", componentIdentifier);
        printf("Message content: %s\n", messageContent);
        if (strcmp(componentIdentifier, "Module 6") == 0) {
            char *Rfid = strchr(messageContent, ' ');
            char rfid[20];

            if(Rfid != NULL){
                Rfid[Rfid - messageContent] = '\0';
                strcpy(rfid, Rfid);
                removeSpaces(rfid);
            }
            else{
                printf("Rfid not found\n");
            }
            char *token1 = strtok(messageContent, " ");
            if (token1 != NULL) {
                printf("Card code: %s\n", token1);
            }
            else{
                printf("Card code not found\n");
            }
            checkElevatorAccess((struct UserAccess *)messageContent, rfid);
        } else if (strcmp(componentIdentifier, "Module 2") == 0 ) {
            char *Rfid = strchr(messageContent, ' ');
            char rfid[20];

            if(Rfid != NULL){
                Rfid[Rfid - messageContent] = '\0';
                strcpy(rfid, Rfid);
                removeSpaces(rfid);
            }
            else{
                printf("Rfid not found\n");
            }
            char *token1 = strtok(messageContent, " ");
            if (token1 != NULL) {
                printf("Card code: %s\n", token1);
            }
            else{
                printf("Card code not found\n");
            }
            checkAccess((struct UserAccess *)messageContent, rfid);
        }
    } else {
        printf("Message content: %s\n", buffer);
    }
    close(clientSocket);
    }

    close(serverSocket);
}

void *start_module1_udp() {
    // Create a UDP socket
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12346);  // Different port for UDP
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Bind the socket
    bind(udpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    printf("Module 1 (UDP) is waiting for data...\n");
    
    // Receive data from the client
    while(1){
    char buffer[1024];
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    recvfrom(udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrLen);
     char componentIdentifier[20];
    char* messageContent = strchr(buffer, ':');
    if (messageContent != NULL) {
        strncpy(componentIdentifier, buffer, messageContent - buffer);
        componentIdentifier[messageContent - buffer] = '\0';
        messageContent++;
        printf("Component identifier: %s\n", componentIdentifier);
        if (strcmp(componentIdentifier, "Module 9") == 0) {
            removeSpaces(messageContent);
            printf("Temperature received from sensors: %s Farenheit\n", messageContent);
            if (atoi(messageContent) >= 130) {
                printf("Temperature is too high. Sending signal to Module 4...\n");
                const char *firealarmSignal = "FIRE#";
                sendfireAlarmSignal(firealarmSignal);
                sleep(10);//give time to trigger the fire alarm
            }
            else{
                printf("Temperature is normal\n");
            }

    }
    }
    }
    close(udpSocket);
}
void removeSpaces(char str[]) {
    if (str == NULL || str[0] == '\0') {
        return; // Handle empty string or NULL pointer
    }

    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = str[i + 1];
    } // Null-terminate the modified string
}
void checkAccess(struct UserAccess *userAccess, char rfid[]) {
    FILE *fp = fopen("authorisation.txt", "r");
    if (fp == NULL) {
        perror("Unable to open authorization file");
        return;
    }

    char line[1024];
    int doorFloorCount = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, " ");
        if (token != NULL && strcmp(token, userAccess->cardCode) == 0) {
            while (token != NULL) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    userAccess->authorizedDoorsAndFloors[doorFloorCount] = strdup(token);
                    doorFloorCount++;
                }
            }
        }
    }

    fclose(fp);
    for (int i = 0; i < doorFloorCount; i++) {

        if (strcmp(userAccess->authorizedDoorsAndFloors[i], rfid) == 0){
            printf("Access granted to %s has been granted to %s\n", rfid, userAccess->cardCode);
            const char* accessSignal = "OPEN#";
            sendAccessSignal(accessSignal,rfid);
            sleep(5);
            accessSignal = "CLOSE#";
            sendAccessSignal(accessSignal,rfid);
            break;
        }
        else if(i == doorFloorCount - 1){
            printf("Access denied to %s has been denied to %s\n", rfid, userAccess->cardCode);
            const char* accessSignal = "DENY#";
            sendAccessSignal(accessSignal,rfid);
            break;
        }
    }
    
}
void checkElevatorAccess(struct UserAccess *userAccess, char rfid[]) {
    FILE *fp = fopen("authorisation.txt", "r");
    if (fp == NULL) {
        perror("Unable to open authorization file");
        return;
    }

    char line[1024];
    int doorFloorCount = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, " ");
        if (token != NULL && strcmp(token, userAccess->cardCode) == 0) {
            while (token != NULL) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                    userAccess->authorizedDoorsAndFloors[doorFloorCount] = strdup(token);
                    doorFloorCount++;
                }
            }
        }
    }

    fclose(fp);
    printf("floorcount: %d\n", doorFloorCount);

    for (int i = 0; i < doorFloorCount; i++) {

        if (strcmp(userAccess->authorizedDoorsAndFloors[i], rfid) == 0){
            printf("Access granted to %s has been granted to %s\n", rfid, userAccess->cardCode);
            const char* accessSignal = "ALLOWED#";
            sendElevatorAccessSignal(accessSignal,rfid);
            sleep(5);
            accessSignal = "CLOSE#";
            sendElevatorAccessSignal(accessSignal,rfid);
            break;
        }
        else if(i == doorFloorCount - 1){
            printf("Access denied to %s has been denied to %s\n", rfid, userAccess->cardCode);
            const char* accessSignal = "DENIED#";
            sendElevatorAccessSignal(accessSignal,rfid);
            break;
        }
    }
    
}
void sendfireAlarmSignal(const char *firealarmSignal) {
    printf("Sending fire alarm signal to Module 4...\n");
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12346);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.4");
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    char buffer[1024];

    snprintf(buffer, sizeof(buffer), "%s", firealarmSignal);
    printf("Sending access signal: %s\n", buffer);

    send(clientSocket, buffer, strlen(buffer), 0);

    // Close the client socket
    close(clientSocket);
}



int main() {
    pthread_t tcp_threads[8]; // Define an array of pthreads for TCP running for communication with other modules
    pthread_t udp_threads[3]; // Define an array of pthreads for UDP running for communication with other modules
    int d = sizeof(udp_threads) / sizeof(udp_threads[0]);
    int c = sizeof(tcp_threads) / sizeof(tcp_threads[0]);
    for (int i = 0; i < c; i++) {
        pthread_create(&tcp_threads[i], NULL, start_module1_tcp, NULL);
    }

    for (int i = 0; i < d; i++) {
        pthread_create(&udp_threads[i], NULL, start_module1_udp, NULL);
    }

    for (int i = 0; i < c; i++) {
        pthread_join(tcp_threads[i], NULL);
    }

    for (int i = 0; i < d; i++) {
        pthread_join(udp_threads[i], NULL);
    }

    return 0;
}
