#include "screen.h"

#include <string.h>

#include "agent.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT_MAXLEN 100

pthread_t screen_read_tid;

void *screen_read_thread(void *arg) {
	char input_str[INPUT_MAXLEN+1];
	int input_len;
	char buf_tosend[INPUT_MAXLEN+1 + HOSTNAME_MAXLENGTH];

	while (fgets(input_str, INPUT_MAXLEN, stdin) != NULL) {
		input_len = strlen(input_str);

		//write(fileno(stdout), input_str, input_len);
		
		memset(buf_tosend, 0, sizeof(buf_tosend));
		sprintf(buf_tosend, "%s: %s", hostname, input_str);
		sendout(buf_tosend, input_len + hostname_len+2, -1);
	}	
}

#ifdef __cplusplus

#endif
