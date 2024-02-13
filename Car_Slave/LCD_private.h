
#ifndef LCD_LCD_PRIVATE_H_
#define LCD_LCD_PRIVATE_H_




#define FUNCTION_SET_8BIT_2LINES_5X7_DOTS  (u8) 0x38
#define FUNCTION_SET_4BIT_2LINES_5X7_DOTS  (u8) 0x28

#define DISPLAY_ON_CURSOR_ON_BLink_OFF     (u8) 0x0E
#define DISPLAY_ON_CURSOR_OFF              (u8) 0x0C

#define DISPLAY_CLEAR                      (u8) 0x01
#define ENTRY_MODE_SET                     (u8) 0x06
#define RETURN_HOME                        (u8) 0x02

#define MOVE_CURSOR_RIGHT                  (u8) 0x14
#define MOVE_CURSOR_LEFT                   (u8) 0x10



static void LCD_voidWriteBitsToSend(u8 copy_u8Byte) ;

#define SET_CGRAM_ADDRESS  (u8)(0x40)

#define SET_DDRAM_ADDRESS  (u8)(0x80)

#endif /* LCD_LCD_PRIVATE_H_ */
