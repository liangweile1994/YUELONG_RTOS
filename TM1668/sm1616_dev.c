#include "sm1616_dev.h"
#include "sm1616_drv.h"



const uint8_t Num_Table[] = {0xBB,0x12,0xA7,0x37,0x1E,0x3D,0xBD,0x13,0xBF,0x3F,0x9F,0xBC,0xA9,0xB6,0xAD,0x8D,0x00};
/*----------------------------- 0 -- 1 -- 2 -- 3 -- 4 -- 5 -- 6 -- 7 -- 8 -- 9 -- A -- b -- C -- d -- E -- F --*/

uint8_t Disp_List[] = {0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB};

void sm1616_Display(uint8_t *disp_buf)
{
	SM1616_I2c_Send_NBytes(disp_buf, 16);
}

void sm1616_Brightness_Ctrl(void)
{
	SM1616_I2c_Send_OneByte(0x48, 1);
}
