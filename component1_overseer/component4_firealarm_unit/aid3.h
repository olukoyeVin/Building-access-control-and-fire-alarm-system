#ifndef MODULE4_H
#define MODULE4_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

void start_module4_tcp();
void *start_module4_udp();

#endif