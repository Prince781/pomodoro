#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define POMODORO_LENGTH (25*60)

struct pomodoro {
	time_t		start;
	long		length;
	long		break_length;
	long		num;
};

void pomodoro_start(struct pomodoro *p);

int main(int argc, char *argv[])
{
	struct pomodoro pom;
	double t = 0;

	pom.num = 0;
	for (;;) {
		pomodoro_start(&pom);
		printf("work for %.1f minutes\n", pom.length/60.f);
		while ((t=difftime(time(NULL), pom.start)) < pom.length)
			sleep((unsigned)(pom.length - t));
		printf("break time (%.1f minutes)\n", pom.break_length/60.f);
		while ((t=difftime(time(NULL),
			pom.start+pom.length)) < pom.break_length)
			sleep((unsigned)(pom.break_length - t));
		++pom.num;
	}
	return 0;
}

void pomodoro_start(struct pomodoro *p)
{
	time(&p->start);
	p->length = POMODORO_LENGTH;
	p->break_length = (p->num + 1)%4 ? 5*60 : 15*60;
}
