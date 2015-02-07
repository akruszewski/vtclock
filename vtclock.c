#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <termbox.h>

static 
int get_current_time(char *buff) {
	time_t current_time = time(NULL);

	if(strftime(buff, 10, "%H:%M:%S", localtime(&current_time)))
		return 0;
	else
		return 1;
}

static 
void draw_line_clock(char *buff) {
	int x, y, i;
	tb_clear();
	x = (tb_width()/2)-5;
	y = tb_height()/2;
	for(i=0;i<10;i++){
		tb_change_cell(x + i, y, buff[i], TB_BLACK, TB_DEFAULT);
	}
	
}

int main(void) {
	char buff[8];
	int ret, q=1;
	struct tb_event ev;
	ret = tb_init();
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
			draw_line_clock(buff);
			tb_present();
			break;
		}
		tb_peek_event(&ev, 100);
		tb_clear();
	}
	tb_shutdown();
	return 0;
}
