#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#define KEYBOARD_BUFFER_SIZE 0x20
#define	bool	int
void key_init();
void key_interrupt();
bool key_isEmpty();
char key_get();
int key_special(unsigned char code);
	
#endif
