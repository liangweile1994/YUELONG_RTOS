#include "sm1616_dev.h"
#include "sm1616_drv.h"



const uint8_t disp_table[] = {NUM_0,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9,CHR_A,CHR_B,CHR_C,CHR_D,CHR_E,CHR_F,CHR_B,CHR_O};
/*----------------------------- 0 -- 1 -- 2 -- 3 -- 4 -- 5 -- 6 -- 7 -- 8 -- 9 -- A -- b -- C -- d -- E -- F -- b -- o --*/

void sm1616_Display(uint8_t *disp_buf)
{
	SM1616_I2c_Send_NBytes(0x60, disp_buf, 16);
}

void sm1616_Brightness_Ctrl(void)
{
	SM1616_I2c_Send_OneByte(0x48, 1);
}
