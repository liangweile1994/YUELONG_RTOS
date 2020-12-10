#ifndef  _SM1616_DEV_H
#define	 _SM1616_DEV_H

#include "main.h"


extern const uint8_t Num_Table[];
extern uint8_t Disp_List[];

void sm1616_Display(uint8_t *disp_buf);
void sm1616_Brightness_Ctrl(void);

#endif
