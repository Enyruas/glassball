#include "screen.h"

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT_MAXLEN 100

pthread_t screen_read_tid;

void sendout(char *buf, int buf_len) {
	int i;
	char Buff[200];
	strcpy(Buff, "127.0.0.1: ");
	strcat(Buff, buf);
	for (i = 0; i < con_num; i++) {
		write(confds[i], Buff, strlen(Buff));
	}
}

void *screen_read_thread(void *arg) {
	char input_str[INPUT_MAXLEN+1];
	int input_len;
	char Buff[200];
	while (1) {
		fgets(input_str, INPUT_MAXLEN, stdin);
		input_len = strlen(input_str);

		strcpy(Buff, "Me: ");
		fputs(strcat(Buff, input_str), stdout);
		sendout(input_str, input_len);
	}	
}

#ifdef __cplusplus

#endif
