#include "glassball.h"

#include <stdio.h>
#include <string.h>

#include "screen.h"
#include "agent.h"

#ifdef __cplusplus
extern "C" {
#endif

int mode;

char hostname[HOSTNAME_MAXLENGTH];
int hostname_len;

con_info_t con_infos[CONNECT_MAXNUM];
int con_num;

void store_con(int confd, char hostname[], int hostname_len, char ipaddress[], int ipaddress_len) {
	con_infos[con_num].confd = confd;
	strncpy(con_infos[con_num].hostname, hostname, hostname_len);
	strncpy(con_infos[con_num].ipaddress, ipaddress, ipaddress_len);
	con_num++;
}

int delete_con(int confd) {
	int i;
	while (i < con_num && con_infos[i].confd != confd);
	if (i == con_num)
		return -1;

	while (i + 1 < con_num) {
		con_infos[i].confd = con_infos[i+1].confd;
		strcpy(con_infos[i].hostname, con_infos[i+1].hostname);
		strcpy(con_infos[i].ipaddress, con_infos[i+1].ipaddress);
	}
	con_num--;

	return 1;
}

int get_con(int confd, char hostname[], char ipaddress[]) {
	int i;
	for (i = 0; i < con_num; i++) {
		if (con_infos[i].confd == i) {
			//strcpy(hostname, con_infos[i].hostname);
			//strcpy(ipaddress, con_infos[i].ipaddress);
			return 1;
		}
	}
	return -1;
}

int main(int argc, char *argv[]) {
	char input_str[10];

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
		fgets(input_str, 9, stdin);
    	sscanf(input_str, "%d", &mode);

		switch (mode) {
		case 0:
	    	//call server method in servor.h
			server();	
    		break;
    
		case 1: 
		    //call client method in client.h
			client();
			break;

		defaut:
			;
	    }

  }

  return 0;
}

#ifdef __cplusplus
}
#endif
