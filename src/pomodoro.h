#ifndef _POMODORO_H
#define _POMODORO_H

#include <time.h>

struct pomodoro {
	time_t		start;
	long		length;
	long		break_length;
	unsigned	num;
};

unsigned pomodoro_start(struct pomodoro *p);

void pomodoro_print_remaining(long t, char *buf, int buflen);

#endif	/* _POMODORO_H */
