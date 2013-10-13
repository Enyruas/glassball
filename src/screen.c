#include "screen.h"

#include <string.h>

#include "agent.h"
#include "server.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT_MAXLEN 100

pthread_t screen_read_tid;

int screen_read_open;

void open_screen_read() {
	screen_read_open = 1;
}

void close_screen_read() {
	screen_read_open = 0;
}

int get_screen_read_open() {
	return screen_read_open;
}

void *screen_read_thread(void *arg) {
	char input_str[INPUT_MAXLEN+1];
	int input_len;
	char buf_tosend[INPUT_MAXLEN+1 + HOSTNAME_MAXLENGTH];

	open_screen_read();

	while (fgets(input_str, INPUT_MAXLEN, stdin) != NULL) {
		input_len = strlen(input_str);
		
		if (input_len == 1 && input_str[0] == '\n') {
			close_screen_read();				

			if (getmode() == 0) {
				shutdown_cons();
				close_cons();
				shutdown(listenfd, SHUT_RDWR);
				close(listenfd);
			}
			else {
				shutdown_cons();
			}
			break;
		}
		memset(buf_tosend, 0, sizeof(buf_tosend));
		sprintf(buf_tosend, "%s: %s", gethostname(), input_str);
		sendout(buf_tosend, input_len + gethostnamelen()+2, -1);
	}	
}

#ifdef __cplusplus

#endif
