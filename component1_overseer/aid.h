#ifndef MODULE1_H
#define MODULE1_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
struct UserAccess {
    char cardCode[30];
    char *authorizedDoorsAndFloors[300];
};
void sendfireAlarmSignal(const char *firealarmSignal);
struct sockaddr_in serverAddr;
void checkElevatorAccess(struct UserAccess *userAccess, char rfid[]);
void sendElevatorAccessSignal(const char *accessCode,char *doorFloor);
void sendAccessSignal(const char *accessCode,char *doorFloor);
void removeSpaces(char *str);
void checkAccess(struct UserAccess *userAccess, char rfid[]);
void *start_module1_tcp();
void *start_module1_udp();

#endif
