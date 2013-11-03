#include "glassball.h"

#include <stdio.h>
#include <string.h>

#include <iostream>

#include "Stream.h"
#include "Server.h"
#include "Client.h"

int main(int argc, char *argv[]) {
	char hostname[HOSTNAME_MAXLENGTH];
	int hostname_len = 0;

	while (1) {
	    SCREENSTREAM<<"Welcome to glassball!\n";
	    SCREENSTREAM<<"please type your name: ";
		if (fgets(hostname, HOSTNAME_MAXLENGTH, stdin) != NULL)
			break;
	}

	hostname_len = strlen(hostname)-1;
	hostname[hostname_len] = '\0';

	// select net mode
	while (1) {

	    SCREENSTREAM<<"please select the mode (0=server,1=client, 2=quit):";
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
	    }
		break;
	    case 1: 
		//call client method in client.h
		{
			SCREENSTREAM<<"input the server address: ";
			char address[16];
			fgets(address, 16, stdin);

			Client client(hostname, address);
			client.start();
		}
		break;
	    case 2:
		SCREENSTREAM<<"Quit glassball\n";
		return 0;
		break;

	    defaut:
		break;
	    }
	}

    return 0;
}
