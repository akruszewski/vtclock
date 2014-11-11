#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <termbox.h>

static int get_current_time(char *buff) {
	time_t current_time = time(NULL);

	if(strftime(buff, 10, "%H:%M:%S", localtime(&current_time)))
		return 0;
	else
		return 1;
}

static void draw_line_clock(char *buff) {
	int x, y, i;
	tb_clear();
	x = (tb_width()/2)-5;
	y = tb_height()/2;
	for(i=0;i<10;i++){
		tb_change_cell(x + i, y, buff[i], TB_WHITE, TB_DEFAULT);
	}
	
}

int main(void) {
	char buff[75], c;
	int ret;
	struct tb_event ev;
	ret = tb_init();
	if(ret){
		fprintf(stderr, "tb_init() failed with error code %d\n", ret);
		return 1;
	}
	while(1) {
		tb_peek_event(&ev, 1);
		tb_clear();
		switch(ev.type) {
		case TB_EVENT_KEY:
			switch(ev.key) {
			case TB_KEY_ESC:
				goto done;
				break;
			}
		default:
			get_current_time(buff);
			draw_clock(buff);
			tb_present();
			sleep(1);
			break;
		}
	}
done:
	tb_shutdown();
	return 0;
}