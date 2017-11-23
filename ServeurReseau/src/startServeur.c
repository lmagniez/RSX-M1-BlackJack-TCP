#include "../lib/ServeurUDP.h"
#include "../lib/ServeurTCP.h"
#include "../lib/parsingCmd.h"


int main(){
	
	plateau p;
	init_plateau(&p);
	
	parseur_REST("POST /action/connect\n\
host: 192.123.23.32", &p);
	
	parseur_REST("POST /action/mise\n\
host: 192.123.23.32\n\
200", &p);

	parseur_REST("POSTGET", &p);
	
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



