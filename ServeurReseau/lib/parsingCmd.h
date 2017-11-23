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


void parseur_REST(char *cmd, plateau *p);



#endif
