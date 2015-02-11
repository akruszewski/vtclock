#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termbox.h>

#include "config.h"

static 
int get_current_time(char *buff) {
	time_t current_time = time(NULL);

	if(strftime(buff, 10, "%H:%M:%S", localtime(&current_time)))
		return 0;
	else
		return 1;
}

static 
void draw_line_clock(char *buff, int fg, int bg) {
	int x, y, i;
	tb_clear();
	x = (tb_width()/2)-5;
	y = tb_height()/2;
	for(i=0;i<10;i++){
		tb_change_cell(x + i, y, buff[i], fg, bg);
	}
	
}

void
usage(void) {
	tb_shutdown();
	fputs("vtclock " VERSION " (c) 2014-2015 Adrian Kruszewski\n" \
		  "usage: vtclock [-fg color] [-bg color]\n", stderr);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	char buff[8];
	int ret, q=1, i;
	struct tb_event ev;
	ret = tb_init();
	for(i = 1; i < argc; i++)
		if(!strcmp(argv[i], "-fg"))
			fg = atoi(argv[++i]);
		else if(!strcmp(argv[i], "-bg"))
			bg = atoi(argv[++i]);
		else
		   	usage();

	if(ret){
		fprintf(stderr, "tb_init() failed with error code %d\n", ret);
		return 1;
	}
	while(q) {
		switch(ev.type) {
		case TB_EVENT_KEY:
			if(ev.ch=='q') {
				q = 0;
			}
		default:
			get_current_time(buff);
			draw_line_clock(buff, fg, bg);
			tb_present();
			break;
		}
		tb_peek_event(&ev, 100);
		tb_clear();
	}
	tb_shutdown();
	return 0;
}
