#include "protocols.h"

int main(void){
	char packet[BUFFER_SIZE];
	int value;

	while(1){
		readPacket(packet,LINK4);

		// EXIT PROCESS
		if(strcasecmp(packet, "KILL") == 0){
			printf("<N5> Received KILL <N5>\n");
			forwardPacket("<N5>","ACK", LINK4);
			break;
		}
		if(strstr(packet, "done") != NULL){
			forwardPacket("<N5>","DONE", LINK4);
			printf("<N5> End of message <N5>\n");
		}
		else{
			printf("<N5> Received: [%s] <N5>\n", packet);
			forwardPacket("<N5>","ACK", LINK4);
		}
		value = randomNumber();
		usleep(value);
	}

	return 0;
}