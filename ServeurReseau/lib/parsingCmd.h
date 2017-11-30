#ifndef PARSING_CMD
#define PARSING_CMD

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../ServeurBlackJack/lib/plateau.h"

#define MISE "/action/mise"
#define	TIRER "/action/tirer"
#define SPLIT "/action/split"

#define LEAVE "/action/leave"
#define DOUBLER "/action/doubler"
#define RESTER "/action/rester"
#define CONNECT "action/connect"

#define POST "POST"
#define GET "GET"

#define CREDIT 10000
#define DIALOGUE_SIZE 500
#define CMD_SIZE 100

char* parseur_REST(char *cmd, plateau *p, int *reinit);



#endif
