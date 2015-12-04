#include "protocols.h"

int main(void){
	char packet[BUFFER_SIZE];
	int value;

	while(1){
		readPacket(packet,LINK5);

		// EXIT PROCESS
		if(strcasecmp(packet, "KILL") == 0){
			printf("<N6> Received KILL <N6>\n");
			forwardPacket("<N6>","ACK", LINK5);
			break;
		}
		if(strstr(packet, "done") != NULL){
			forwardPacket("<N6>","DONE", LINK5);
			printf("<N6> End of message <N6>\n");
		}
		else{
			printf("<N6> Received: [%s] <N6>\n", packet);
			forwardPacket("<N6>","ACK", LINK5);
		}
		value = randomNumber();
		usleep(value);
	}
	
	return 0;
}