#include "aid_10.h"

void start_module10_udp(int resend_delay, const char* shmPath, const char* fire_alarm_unit) {
    // Create a TCP socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12346);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.4");  // Replace with the actual IP of Module 1

    // Connect to Module 1
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    // Receive data from Module 1
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);

    printf("Received by Module 10 (TCP): %s\n", buffer);
    char componentIdentifier[] = "Module 10:";
    char alarm_signal[] = " TRIGGER#";

    strcat(alarm_signal, componentIdentifier); // You can change the user access code or interface it to the hardware to extract the value

    printf("Message sent to the server: %s\n", alarm_signal);

    int bytes_sent = sendto(clientSocket, alarm_signal, strlen(alarm_signal), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bytes_sent == -1) {
        perror("Message(id) for authorization sending failed");
    } else {
        printf("Message(id) for authorization sent successfully\n");
    }

    close(clientSocket);
}

int main(int argc, char* argv[]) {
    // if (argc < 5) {
    //     fprintf(stderr, "Usage: %s <resend delay> <shared memory path> <shared memory offset> <fire alarm unit address:port>\n", argv[0]);
    //     return 1;
    // }

    // Assuming the arguments are provided correctly as 'resend delay', 'shared memory path', and 'fire alarm unit address:port'.
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <resend delay> <shared memory path> <fire alarm unit address:port>\n", argv[0]);
        return 1;
    }

    int resend_delay = atoi(argv[1]);
    const char* shmPath = argv[2];
    const char* fire_alarm_unit = argv[3];

    start_module10_udp(resend_delay, shmPath, fire_alarm_unit);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}
