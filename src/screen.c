#include "screen.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT_MAXLEN 100

pthread_t screen_read_tid;

void sendout(char *buf, int buf_len) {
	int i;
	for (i = 0; i < con_num; i++) {
		write(confds[i], buf, buf_len);
	}
}

void *screen_read_thread(void *arg) {
	char input_str[INPUT_MAXLEN+1];
	int input_len;
	while (1) {
		fgets(input_str, INPUT_MAXLEN, stdin);
		input_len = strlen(input_str);

		fputs(input_str, stdout);
		sendout(input_str, input_len);
	}	
}

#ifdef __cplusplus

#endif
