#ifndef  _SM1616_DEV_H
#define	 _SM1616_DEV_H

#include "main.h"

/***** bitŒª∫Í∂®“Â*****/
#define	BIT_0					0
#define	BIT_1					1
#define	BIT_2					2
#define	BIT_3					3
#define	BIT_4					4
#define	BIT_5					5
#define	BIT_6					6
#define	BIT_7					7
#define	BIT_8					8
#define	BIT_9					9
#define	BIT_10				10
#define	BIT_11				11
#define	BIT_12				12
#define	BIT_13				13
#define	BIT_14				14
#define	BIT_15				15

#define	BOOST_GEAR		16

#define SEG_A                   ((uint8_t)(1<<BIT_0))
#define SEG_B                   ((uint8_t)(1<<BIT_1))
#define SEG_C                   ((uint8_t)(1<<BIT_4))
#define SEG_D                   ((uint8_t)(1<<BIT_5))
#define SEG_E                   ((uint8_t)(1<<BIT_7))
#define SEG_F                   ((uint8_t)(1<<BIT_3))
#define SEG_G                   ((uint8_t)(1<<BIT_2))
#define SEG_P                   ((uint8_t)(1<<BIT_6))

#define SEG_ALL                 ((uint8_t)0xFF) //                      ;"8."
#define CHR_BLANK               ((uint8_t)0x00) //                      ;" "

#define CHR_DOT                 ((uint8_t)SEG_P)//                      ;"."
                               
#define CHR_SQL                 ((uint8_t)SEG_D|(uint8_t)SEG_E)  //          ;"("
#define CHR_SQR                 ((uint8_t)SEG_A|(uint8_t)SEG_B)  //          ;")"
                                
#define NUM_8                   ((uint8_t)SEG_ALL&~(uint8_t)SEG_P)  //       ;"8"
#define NUM_1                   ((uint8_t)SEG_B|(uint8_t)SEG_C)   //         ;"1"
#define NUM_9                   ((uint8_t)NUM_8&~(uint8_t)SEG_E)   //        ;"9"
#define NUM_0                   ((uint8_t)NUM_8&~(uint8_t)SEG_G)   //        ;"0"
#define NUM_6                   ((uint8_t)NUM_8&~(uint8_t)SEG_B)   //        ;"6"
#define NUM_5                   ((uint8_t)NUM_6&~(uint8_t)SEG_E)   //        ;"5"
#define CHR_A                   ((uint8_t)NUM_8&~(uint8_t)SEG_D)   //        ;"A"
#define CHR_Q                   ((uint8_t)NUM_9&~(uint8_t)SEG_D)   //        ;"q"
#define NUM_4                   ((uint8_t)CHR_Q&~(uint8_t)SEG_A)   //        ;"4"
#define NUM_3                   ((uint8_t)NUM_9&~(uint8_t)SEG_F)   //        ;"3"
#define CHR_E                   ((uint8_t)NUM_8&~(uint8_t)NUM_1)   //        ;"E"
#define CHR_F                   ((uint8_t)CHR_E&~(uint8_t)SEG_D)   //        ;"F"
#define NUM_7                   ((uint8_t)CHR_Q&~(uint8_t)SEG_G)   //        ;"7"
#define CHR_C                   ((uint8_t)CHR_SQL|SEG_G)   //           ;"c"
#define NUM_2                   ((uint8_t)CHR_C|(uint8_t)CHR_SQR)//          ;"2"
#define CHR_B                   ((uint8_t)NUM_6&~(uint8_t)SEG_A)//           ;"B"
#define CHR_D                   ((uint8_t)CHR_C|(uint8_t)NUM_1)//            ;"D"
#define CHR_G                   ((uint8_t)NUM_6&~(uint8_t)SEG_G)//           ;"G"
#define CHR_H                   ((uint8_t)NUM_4|(uint8_t)SEG_E) //           ;"H"
#define CHR_HL                  ((uint8_t)CHR_B&~(uint8_t)SEG_D) //          ;"h"
#define CHR_I                   ((uint8_t)SEG_E|(uint8_t)SEG_F) //           ;"I"
#define CHR_IL                  ((uint8_t)SEG_E)    //                  ;"i"
#define CHR_J                   ((uint8_t)CHR_D&~(uint8_t)SEG_G) //          ;"J"
#define CHR_K                   ((uint8_t)CHR_I|(uint8_t)SEG_G)//            ;"K"
#define CHR_L                   ((uint8_t)CHR_I|(uint8_t)SEG_D)//            ;"L"
#define CHR_O                   ((uint8_t)CHR_D&~(uint8_t)SEG_B)//           ;"O"
#define CHR_P                   ((uint8_t)CHR_F|(uint8_t)SEG_B)//            ;"P"
#define CHR_R                   ((uint8_t)SEG_E|(uint8_t)SEG_G)//            ;"r"
#define CHR_S                   ((uint8_t)NUM_5)      //                ;"S"
#define CHR_T                   ((uint8_t)CHR_E&~(uint8_t)SEG_A)  //         ;"t"
#define CHR_U                   ((uint8_t)NUM_0&~(uint8_t)SEG_A)  //         ;"U"
#define CHR_UL                  ((uint8_t)CHR_O&~(uint8_t)SEG_G)  //         ;"u"
#define CHR_Y                   ((uint8_t)NUM_4|(uint8_t)SEG_D)  //          ;"y"
#define CHR_V                   ((uint8_t)CHR_Y&~(uint8_t)SEG_C)  //         ;"v"
#define CHR_N                   ((uint8_t)NUM_0&~(uint8_t)SEG_D)  //         ;"N"
#define CHR_NL                  ((uint8_t)CHR_O&~(uint8_t)SEG_D)  //         ;"n"
#define CHR_M                   ((uint8_t)CHR_NL|(uint8_t)SEG_A)  //         ;"M"


#define	BLK_								CHR_BLANK
#define	DIS_A								CHR_A
#define	DIS_L								CHR_L
#define	DIS_o								CHR_O
#define	DIS_NO_POT					(CHR_B|CHR_D|CHR_F|CHR_G)
#define	DIS_SEG_G						SEG_G
#define	DIS_DOT							CHR_DOT
#define DIS_B               CHR_B
#define DIS_Q               CHR_Q
#define DIS_PAUSE           (SEG_B|SEG_C|SEG_E|SEG_F)

#define TUBE1 	10
#define TUBE2 	8
#define TUBE3 	11
#define TUBE4 	7
#define TUBE5 	15
#define TUBE6 	0
#define TUBE7 	14
#define TUBE8 	1
#define TUBE9 	13
#define TUBE10 	2
#define TUBE11 	12
#define TUBE12 	3
#define TUBE13 	4
#define TUBE14 	6
#define LED 		9


extern const uint8_t disp_table[];

void sm1616_Display(uint8_t *disp_buf);
void sm1616_Brightness_Ctrl(void);

#endif
