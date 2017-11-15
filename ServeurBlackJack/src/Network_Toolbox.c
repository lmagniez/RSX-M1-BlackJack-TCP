#include "../lib/Network_Toolbox.h"
#define MAX_LENGTH 1024
#define MAX_MSG 100
#define BUFF_SIZE 20
#define MAX_BACKLOG 9


//===============================================
//===================== UDP =====================
//===============================================
int socket_UDP(){

	int fd;
	//int socket(int domain, int type, int protocol);
	fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd==-1){
		perror("socket open");
		exit(-1);
	}
	return fd;

}

void close_UDP(int fd){
	if(close(fd)==-1)
		perror("close UDP");
}

void send_UDP(int sock, char* host, int port, char* msg){

	struct hostent* he = gethostbyname(host);
	if(he == NULL){
		perror("Send_UDP() -- gethostbyname");
		exit(h_errno);
	}

	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(struct sockaddr_in));

	dest.sin_family = he->h_addrtype;
	dest.sin_port = htons(port);
	memcpy(&(dest.sin_addr.s_addr),he->h_addr,he->h_length);

	printf("Sending message \"%s\" to host \"%s\" on port \"%d\"\n",msg, host, port);

	sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&dest, sizeof(dest));
}

void recv_UDP(int sock, int port){
	struct sockaddr_in src;
	memset(&src, 0, sizeof(struct sockaddr_in));


	char* buf= malloc(sizeof(char)*MAX_LENGTH);
	socklen_t size_src = sizeof(src);
	int res = recvfrom(sock, buf, MAX_LENGTH, 0, (struct sockaddr*)&src, &size_src );

	if(res == -1){
		perror("recv_UDP() -- recvfrom");
		exit(h_errno);
	}
	buf[res]='\0';

	char * host_ip = inet_ntoa(src.sin_addr);
	if(host_ip == NULL){
		perror("recv_UDP() -- inet_ntoa");
		exit(h_errno);
	}

	printf("Received UDP message \"%s\" from %s on port \"%d\"\n",
		buf,host_ip, port);
}

void UDP_bind_server(int sock, int port){


	struct sockaddr_in serv;
	memset(&serv, 0, sizeof(struct sockaddr_in));
	socklen_t size_serv = sizeof(serv);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(port);

	int res_bind = bind(sock, (struct sockaddr*)&serv, size_serv);
	if(res_bind==-1){
		perror("UDP_bind_server()");
		exit(h_errno);
	}
	printf("UDP socket bound on port %d\n", port);

	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

}







































//client message, addr ip, port
//serveur que port pour le bind dessus

/*
 *
 * TCP
 *
 */


int socket_TCP(){

	int res;
	//int socket(int domain, int type, int protocol);
	res = socket(AF_INET,SOCK_STREAM,0);
	if(res==-1){
		perror("socket open");
		exit(-1);
	}
	return res;
}



void connect_TCP(int sock, char *host, int port){


	struct hostent *he = gethostbyname(host);
	if(he == NULL) {
		herror("connect_TCP() -- gethostbyname");
		exit(h_errno);
	}


	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(struct sockaddr_in));
	dest.sin_family = he->h_addrtype;
	dest.sin_port = htons(port);
	memcpy(&(dest.sin_addr.s_addr), he->h_addr, he->h_length);
	printf("Connection attempt to %s on port %d...\n", host, port);

	if(connect(sock, (struct sockaddr*)&dest,sizeof(dest))==-1){
		perror("Connect_TCP()");
	}
	printf("Done\n");

}


void send_data_TCP(int sock, char* msg){

	int nb_envoyes = 0 ;
	int nb_total = strlen(msg)+1;

	for(; nb_envoyes < nb_total;){
		int nb_send = send(sock, msg+nb_envoyes, nb_total - nb_envoyes, 0);
		printf("Send tmp TCP message \"%.*s\" (%d bytes)\n", nb_send, msg + nb_envoyes, nb_send);
		//nb_total += nb_send;
		nb_envoyes += nb_send;

		printf("%d %d %d\n", nb_send, nb_envoyes, nb_total);

		if(nb_send == -1)
			perror("send_data_TCP() -- send");
	}

	printf("Send TCP message \"%s\" (%lu bytes)\n", msg, strlen(msg));
	/*
	while(nb_envoyes<nb_total){

		int size = send(int sock, msg+nb_envoyes, strlen(msg+nb_envoyes), 0);
		nb_envoyes += size;
	}*/

}

void handler_tcp(int arg){
	printf("No response !! %d\n", arg);
	exit(0);
}

//envoie signal au bout 5 sec si rien reçu
void receive_data_TCP(int sock){
	char *msg = malloc(sizeof(char)*MAX_MSG);
	char buffer[BUFF_SIZE];

	int nb_lu_total = 1;
	int nb_max = MAX_MSG;
	msg[0]='\0';

	int nb_lu;

	alarm(5);
	signal(SIGALRM, handler_tcp);

	for(;;){
		signal(SIGALRM, handler_tcp);
		alarm(5);
		nb_lu=recv(sock, buffer, BUFF_SIZE, 0);
		alarm(0);

		if(nb_lu == -1)
			perror("erreur receive TCP");
		buffer[nb_lu_total] = '\0';

		if(nb_lu > 0){
			nb_lu_total += nb_lu;
			if(nb_lu_total > nb_max)
				msg = realloc(msg, nb_lu_total * sizeof(char));
			strcat(msg, buffer);
			printf("Recerive tmp TCP message \"%s\" (%lu bytes)\n", buffer, strlen(buffer));
		}
		else{
			printf("Received TCP messagre \"%s\" (%d bytes)\n", msg, nb_lu_total);
			free(msg);
			//close(sock);
			return;
		}

	}

}

void close_TCP(int fd){

	if(close(fd)==-1)//shutdown pour un seul coté
		perror("close UDP");

}

void TCP_bind_server(int sock, int port){


	int optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));

	struct sockaddr_in serv;
	memset(&serv, 0, sizeof(struct sockaddr_in));
	socklen_t size_serv = sizeof(serv);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(port);

	int res_bind = bind(sock, (struct sockaddr*)&serv, size_serv);
	if(res_bind==-1){
		perror("UDP_bind_server()");
		exit(h_errno);
	}

	if(listen(sock, MAX_BACKLOG) == -1){
		perror("ERROR on listen");
		exit(h_errno);
	}
	printf("UDP socket bound on port %d\n", port);

}


int wait_connection_TCP(int sock){

	struct sockaddr_in serv;
	memset(&serv, 0, sizeof(struct sockaddr_in));
	socklen_t size_serv = sizeof(serv);

	int res = accept(sock, (struct sockaddr*)&serv, &size_serv);
	if(res == -1){
		perror("wait_connection_TCP() -- accept");
	}
	return res;
}


