#include "../lib/ServeurUDP.h"
#include "../lib/ServeurTCP.h"
#include "../lib/parsingCmd.h"


extern plateau p;

int main(){

	init_plateau(&p);
	pthread_t udpThread = startServeurUDP();
	pthread_t tcpThread = startServeurTCPConnection();


    if (pthread_join(tcpThread, NULL)) {
		perror("pthread_join");
		return EXIT_FAILURE;
    }

    if (pthread_join(udpThread, NULL)) {
		perror("pthread_join");
		exit(0);
    }

	return 0;
}



