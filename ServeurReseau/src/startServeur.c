#include "../lib/ServeurUDP.h"
#include "../lib/ServeurTCP.h"

int main(){
	pthread_t udpThread = startServeurUDP();
	pthread_t tcpThread = startServeurTCP();

    if (pthread_join(tcpThread, NULL)) {
		perror("pthread_join");
		return EXIT_FAILURE;
    }

	return 0;
}



