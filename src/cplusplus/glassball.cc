#include "glassball.h"

#include <stdio.h>
#include <string.h>

#include "Server.h"
//#include "Client.h"
//#include "screen.h"
//#include "agent.h"

int main(int argc, char *argv[]) {
	char hostname[HOSTNAME_MAXLENGTH];
	int hostname_len = 0;

	while (1) {
	    puts("Welcome to glassball!");
	    puts("please type your name: ");
		if (fgets(hostname, HOSTNAME_MAXLENGTH, stdin) != NULL)
			break;
	}

	hostname_len = strlen(hostname)-1;
	hostname[hostname_len] = '\0';

	// select net mode
	while (1) {

	    printf("please select the mode (0=servrer,1=client):");
	    char input_str[10];
	    int mode;
	    fgets(input_str, 9, stdin);
	    sscanf(input_str, "%d", &mode);

	    switch (mode) {
	    case 0:
		//call server method in servor.h
	    {
		Server server(hostname);	
		server.start();
	        return 0;
		break;
	    }
	    case 1: 
		//call client method in client.h
//		client client(hostname);
//		client.start();
		return 0;
		break;

	    defaut:
		continue;
		break;
	    }
	}

    return 0;
}
