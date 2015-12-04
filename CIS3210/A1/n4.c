#include "protocols.h"

int main(void){
	char packet[BUFFER_SIZE];
	int value;

	while(1){
		readPacket(packet,LINK3);
		
		//EXIT PROCESS
		if(strcasecmp(packet, "KILL") == 0){
			printf("<N4> Received KILL <N4>\n");
			forwardPacket("<N4>","ACK", LINK3);
			break;
		}
		if(strstr(packet, "done") != NULL){
			forwardPacket("<N4>","DONE", LINK3);
			printf("<N4> End of message <N4>\n");
		}
		else{
			printf("<N4> Received: [%s] <N4>\n", packet);
			forwardPacket("<N4>","ACK", LINK3);
		}
		value = randomNumber();
		usleep(value);
	}

	return 0;
}