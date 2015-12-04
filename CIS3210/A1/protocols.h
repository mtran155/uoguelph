#ifndef PROTOCOLS_H_
#define PROTOCOLS_H_

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define BUFFER_SIZE 20
#define LINK1 "link1"
#define LINK2 "link2"
#define LINK3 "link3"
#define LINK4 "link4"
#define LINK5 "link5"
#define LINK6 "link6"

int randomNumber();
void sendPacket(char * node, char * buff, char * destination, char * link);
void readPacket(char * packet, char * link);
void forwardToDestination(char * node, char * packet);
void forwardPacket(char * node, char * packet, char * link);
int validateDestination(char * destination);
int checkAns(char * answer);
int restartSim();

#endif