#include "protocols.h"

int main(void){
	char packet[BUFFER_SIZE];
	int value;

	while(1){
		readPacket(packet,LINK6);

		// EXIT PROCESS
		if(strcasecmp(packet, "KILL") == 0){
			printf("<N7> Received KILL <N7>\n");
			forwardPacket("<N7>","ACK", LINK6);
			break;
		}
		if(strstr(packet, "done") != NULL){
			forwardPacket("<N7>","DONE", LINK6);
			printf("<N7> End of message <N7>\n");
		}
		else{
			printf("<N7> Received: [%s] <N7>\n", packet);
			forwardPacket("<N7>","ACK", LINK6);
		}
		value = randomNumber();
		usleep(value);
	}

	return 0;
}