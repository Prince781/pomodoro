#include "pomodoro.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define BUFLEN	1024

static unsigned pomodori = 0;
static unsigned p_length = 25 * 60;
static unsigned b_length = 5 * 60;
static unsigned eb_length = 15 * 60;

void clear_msg(char *buf);
void print_msg(char *buf, int buflen, const char *msg);
void print_help(const char *prog);

int main(int argc, char *argv[])
{
	int c;
	int i = -1;
	struct pomodoro p;
	char buf[BUFLEN] = {0};
	long t;

	static struct option opts[] = {
		{ "help", no_argument, 0, 'h' },
		{ "length", required_argument, 0, 'l' },
		{ "break", required_argument, 0, 'b' },
		{ "extendedbreak", required_argument, 0, 'e'},
		{ 0, 0, 0, 0 }
	};
	while ((c = getopt_long(argc, argv, "h::l:b:e:", opts, &i)) != -1)
		switch (c) {
			case 'h':
				print_help(argv[0]);
				_exit(1);
				break;
			case 'l':
				p_length = (unsigned) atoi(optarg) * 60;
				break;
			case 'b':
				b_length = (unsigned) atoi(optarg) * 60;
				break;
			case 'e':
				eb_length = (unsigned) atoi(optarg) * 60;
				break;
			default:
				print_help(argv[0]);
				_exit(1);
				break;
		}
	for (;;) {
		pomodoro_start(&p);
		print_msg(buf, BUFLEN, "Time to work!");
		while ((t=difftime(p.start+p.length, time(NULL))) >= 0)
			pomodoro_print_remaining(t, buf, BUFLEN);
		clear_msg(buf);
		print_msg(buf, BUFLEN, "Break time!");
		while ((t=difftime(p.start+p.length+p.break_length,
			time(NULL))) >= 0)
			pomodoro_print_remaining(t, buf, BUFLEN);
		clear_msg(buf);
	}
		
}

unsigned pomodoro_start(struct pomodoro *p)
{
	time(&p->start);
	p->length = p_length;
	p->break_length = (pomodori+1) % 4 ? b_length : eb_length;
	p->num = pomodori++;
}

void pomodoro_print_remaining(long t, char *buf, int buflen)
{
	clear_msg(buf);
	snprintf(buf, buflen, "Remaining time: %d:%02d", t/60, t%60);
	printf(buf);
}

void clear_msg(char *buf)
{
	int len = strlen(buf) - 1;
	for (; len >= 0; --len)
		buf[len] = '\b';
	printf(buf);
}

void print_msg(char *buf, int buflen, const char *msg)
{
	int l = snprintf(buf, buflen, msg);
	char *pc = buf + l;
	while (--l >= 0)
		*pc++ = ' ';
	*pc++ = '\n';
	*pc = '\0';
	printf(buf);
}

void print_help(const char *prog)
{
	printf("Usage: %s\n", prog);
	printf("\t--help | -h\t\tShow this message\n");
	printf("\t--length | -l\t\tSpecify pomodoro length\n");
	printf("\t--break | -b\t\tSpecify break length\n");
	printf("\t--extendedbreak | -e\t\tSpecify extended break length\n");
}
