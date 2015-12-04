#include "protocols.h"

int main(void){
	FILE * fp = NULL;
	char filename[50];
	char destination[3];
	char pipeName[10];
	char buff[2];
	char packet[BUFFER_SIZE];
	int validDest;
	int flag;	
	int value;

	mkfifo(LINK1,0666); // pipe that goes to n2
	mkfifo(LINK2,0666); // pipe that goes to n3

	while(1){
		printf("Enter the filename and destination:\n");
		scanf("%s %s",filename, destination);

		fp = fopen(filename, "r");
		while( fp == NULL ){
			printf("Error opening file. Enter filename again:  ");
			scanf("%s",filename);
			fp = fopen(filename, "r");
		}
		
		validDest = validateDestination(destination); 
		if(validDest == 0){
			while(validDest == 0){
					printf("Not a valid destination. Enter a valid destination:  ");
					scanf("%s", destination);
					validDest = validateDestination(destination);
			}
		}

		// CHECK WHAT PIPE TO WRITE TO
		if(strcasecmp(destination, "n2") == 0 || strcasecmp(destination, "n4") == 0){
			strcpy(pipeName, LINK1);
		}
		else{
			strcpy(pipeName, LINK2);
		}

		// START SIMULATION OF SENDING AND RECEIVING PACKETS
		while(1){
			buff[0] = fgetc(fp);
			buff[1] = '\0';
			sendPacket("<N1>", buff, destination, pipeName);

			value = randomNumber();
			usleep(value);

			readPacket(packet,pipeName);

			if(strcasecmp(packet, "DONE") == 0){
				printf("<N1> Received DONE <N1>\n");
				printf("\n<N1> Message Received <N1> \n\n");

				if(buff[0] == EOF)
					break;
			}

			if(strcasecmp(packet, "ACK") == 0 ){
				printf("<N1> Received ACK <N1>\n\n");

				if(buff[0] == EOF)
					break;

				continue;
			}
		}

		flag = restartSim();
		// continue simulation
		if(flag == 1){ 
			fclose(fp);
			continue;
		}
		// exit simulation
		if(flag == 2){ 
			forwardPacket("<N1>","KILL",LINK1);
			forwardPacket("<N1>","KILL",LINK2);
			readPacket(packet,LINK1);
			if(strcasecmp(packet, "ACK") == 0){
				printf("<N1> Received ACK <N1>\n");
			}
			readPacket(packet,LINK2);

			if(strcasecmp(packet, "ACK") == 0){
				printf("<N1> Received ACK <N1>\n");
			}

			value = randomNumber();
			usleep(value);
			break;
		}
	}

	printf("SIMULATION TERMINATED\n");
	fclose(fp);
	unlink(LINK1);
	unlink(LINK2);

	return 0;
}