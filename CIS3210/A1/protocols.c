#include "protocols.h"

int randomNumber(){
	srand(time(NULL));
	int r = (rand() % (2000001 - 1000)) + 1000;
	return r;
}

void sendPacket(char * node, char * buff, char * destination, char * link){
	char * packet = NULL;
	int fd;
	int value = 0;

	packet = calloc(15,sizeof(char));
	value = randomNumber();

	if(buff[0] == EOF){
		strcat(packet, "done");
	 	strcat(packet, " ");
	 	strcat(packet, destination);
	 	strcat(packet, "\0");
	}else{
	 	strcat(packet, buff);
		strcat(packet, " ");
	 	strcat(packet, destination);
	 	strcat(packet, "\0");
	}

	printf("%s Sending: [%s] %s\n",node, packet, node);

	usleep(value);
	fd = open(link,O_WRONLY);
	write(fd, packet, BUFFER_SIZE);
	close(fd);
	free(packet);
}

void readPacket(char * packet, char * link){
	int fd;
	
    fd = open(link, O_RDONLY);
    read(fd, packet, BUFFER_SIZE);
    close(fd);
}

void forwardToDestination(char * node, char * packet){
	if(strstr(packet, "n4") != NULL){
		forwardPacket(node, packet, LINK3);
		printf("Forwarding packet [%s] to <N4>\n", packet);
	}
	if(strstr(packet, "n5") != NULL){
		forwardPacket(node, packet, LINK4);
		printf("Forwarding packet [%s] to <N5>\n", packet);
	}
	if(strstr(packet, "n6") != NULL){
		forwardPacket(node, packet, LINK5);
		printf("Forwarding packet [%s] to <N6>\n", packet);
	}
	if(strstr(packet, "n7") != NULL){
		forwardPacket(node, packet, LINK6);
		printf("Forwarding packet [%s] to <N7>\n", packet);
	}
}

void forwardPacket(char * node, char * packet, char * link){
	int fd;
	int value = 0;

	value = randomNumber();

	printf("%s Sending: [%s] %s\n",node, packet, node);

	usleep(value);
	fd = open(link,O_WRONLY);
	write(fd, packet, BUFFER_SIZE);
	close(fd);
}

int validateDestination(char * destination){
	if(strcmp(destination, "n2") == 0){
		return 1;
	}
	else if(strcmp(destination, "n3") == 0){
		return 1;
	}
	else if(strcmp(destination, "n4") == 0){
		return 1;
	}
	else if(strcmp(destination, "n5") == 0){
		return 1;
	}
	else if(strcmp(destination, "n6") == 0){
		return 1;
	}
	else if(strcmp(destination, "n7") == 0){
		return 1;
	}
	else
		return 0;
}

int checkAns(char * answer){
	if(strcasecmp(answer, "Y") == 0){
		return 0;
	}
	if(strcasecmp(answer, "N") == 0){
		return 1;
	}
	else
		return 2;
}

int restartSim(){
	int restartSim;
	char restart;
	int flag;

	printf("Would you like to continue Y/N\n");
	scanf("%s", &restart);
	restartSim = checkAns(&restart);

	// RESTART SIM
	if(restartSim == 0){
		flag = 1; 
	}
	// EXIT SIM
	else if (restartSim == 1){
		flag = 2; 
	}
	else{
		while(restartSim == 2){
			printf("Not a valid answer. Would you like to continue Y/N:  ");
			scanf("%s", &restart);
			restartSim = checkAns(&restart);
		}
		if (restartSim == 1)
			flag = 2;
	}

	return flag;
}