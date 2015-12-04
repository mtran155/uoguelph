#include "protocols.h"

int main(void){
	char packet[BUFFER_SIZE];
	int value;

	mkfifo(LINK4, 0666); // named pipe to n5
	mkfifo(LINK5, 0666); // named pipe to n6
	mkfifo(LINK6, 0666); // named pipe to n7

	while(1){
		readPacket(packet,LINK2);

		// EXIT PROCESS
		if(strcasecmp(packet, "KILL") == 0){
			printf("<N3> Received KILL <N3>\n");
			forwardPacket("<N3>","KILL",LINK4);
			forwardPacket("<N3>","KILL",LINK5);
			forwardPacket("<N3>","KILL",LINK6);

			readPacket(packet,LINK4);
			readPacket(packet,LINK5);
			readPacket(packet,LINK6);

			if(strcasecmp(packet, "ACK") == 0){
				printf("<N3> Received ACK <N3>\n");
			}

			forwardPacket("<N3>","ACK", LINK2);

			value = randomNumber();
			usleep(value);
			break;
		}

		// PACKET IS SENT TO THIS NODE
		if(strstr(packet, "n3") != NULL){
			printf("<N3> Received: [%s] <N3>\n", packet);
			if(strstr(packet, "done") != NULL){
				forwardPacket("<N3>","DONE", LINK2);
				printf("<N3> End of message <N3>\n");
			}
			else{
				forwardPacket("<N3>","ACK", LINK2);
			}
		}

		// FORWARD TO CORRECT NODE
		else if (strstr(packet, "n5") != NULL){
			forwardToDestination("<N3>",packet);
			readPacket(packet,LINK4);
			if(strcasecmp(packet, "ACK") == 0){
				printf("<N3> Received ACK <N3>\n");
				forwardPacket("<N3>","ACK", LINK2);
			}
			if(strcasecmp(packet, "DONE") == 0){
				printf("<N3> Received DONE <N3>\n");
				forwardPacket("<N3>","DONE", LINK2);
			}
		}
		else if (strstr(packet, "n6") != NULL){
			forwardToDestination("<N3>",packet);
			readPacket(packet,LINK5);
			if(strcasecmp(packet, "ACK") == 0){
				printf("<N3> Received ACK <N3>\n");
				forwardPacket("<N3>","ACK", LINK2);
			}
			if(strcasecmp(packet, "DONE") == 0){
				printf("<N3> Received DONE <N3>\n");
				forwardPacket("<N3>","DONE", LINK2);
			}
		}
		else if (strstr(packet, "n7") != NULL){
			forwardToDestination("<N3>",packet);
			readPacket(packet,LINK6);
			if(strcasecmp(packet, "ACK") == 0){
				printf("<N3> Received ACK <N3>\n");
				forwardPacket("<N3>","ACK", LINK2);
			}
			if(strcasecmp(packet, "DONE") == 0){
				printf("<N3> Received DONE <N3>\n");
				forwardPacket("<N3>","DONE", LINK2);
			}
		}

		value = randomNumber();
		usleep(value);
	}
	
	// closes named pipe
	unlink(LINK4);
	unlink(LINK5);
	unlink(LINK6);

	return 0;
}