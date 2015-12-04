#include "protocols.h"

int main(void){
	char packet[BUFFER_SIZE];
	int value;

	mkfifo(LINK3, 0666); // named pipe to n4

	while(1){
		readPacket(packet,LINK1);

		// EXIT PROCESS
		if(strcasecmp(packet, "KILL") == 0){
			printf("<N2> Received KILL <N2>\n");

			forwardPacket("<N2>","KILL",LINK3);
			readPacket(packet,LINK3);

			if(strcasecmp(packet, "ACK") == 0){
				printf("<N2> Received ACK <N2>\n");
			}

			forwardPacket("<N2>","ACK", LINK1);

			value = randomNumber();
			usleep(value);
			break;
		}

		// PACKET IS SENT TO THIS NODE
		if(strstr(packet, "n2") != NULL){
			printf("<N2> Received: [%s] <N2>\n", packet);
			if(strstr(packet, "done") != NULL){
				forwardPacket("<N2>","DONE", LINK1);
				printf("<N2> End of message <N2>\n");
			}
			else{
				forwardPacket("<N2>","ACK", LINK1);
			}
		}

		// FORWARD TO CORRECT NODE
		else{
			forwardToDestination("<N2>",packet);
			readPacket(packet,LINK3);
			if(strcasecmp(packet, "ACK") == 0){
				printf("<N2> Received ACK <N2>\n");
				forwardPacket("<N2>","ACK", LINK1);
			}
			if(strcasecmp(packet, "DONE") == 0){
				printf("<N2> Received DONE <N2>\n");
				forwardPacket("<N2>","DONE", LINK1);
			}
		}

		value = randomNumber();
		usleep(value);
	}

	unlink(LINK3);

	return 0;
}