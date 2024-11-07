/*
 * LCD.h
 *
 *	Provides LCD functions such as initialization, sending
 *	commands and data, and basic functionalities
 *
 * Created on: July 26th, 2023
 *		Author: Jackie Huynh
 *
 */
 
#ifndef LCD_H_
#define LCD_H_
#include "util.h"

/*************PCF8574A Register*************/
#define LCD_WRITE_ADDR			(0x3FU)
#define PCF8574A_REG				(0x00U)

/**************LCD CMD Register*************/
#define INIT_REG_CMD				(0x30U) // Command to initialize in 8-bit mode
#define INIT_FUNC_CMD				(0x20U) // Function set base command (4-bit mode here)

#define FUNC_MODE           (0x28U) // Function set: DL = 1 (4-it interface), N = 1 (2 lines), F = 0 (5x8 characters)
  #define FUNC_4_BIT        (0x00U) // 4-bit interfaceb
  #define FUNC_2_ROW        (0x08U) // 2-line mode
  #define FUNC_5_7          (0x00U) // 5x7 dots character font
	
#define DISP_CMD            (0x08U) // Display ON/OFF Control
	#define DISP_ON           (0x04U) // Display on
	#define DISP_OFF          (0x00U) // Display off
	#define DISP_CURSOR_ON    (0x02U) // Cursor on
	#define DISP_CURSOR_OFF   (0x00U) // Cursor off
	#define DISP_BLINK_ON     (0x01U) // Blink on
	#define DISP_BLINK_OFF    (0x00U) // Blink off
	
#define CLEAR_DISP_CMD			(0x01U)

#define ENTRY_MODE_CMD			(0x04U)
	#define ENTRY_INC_CURSOR	(0x02U) // Cursor increment mode
//	#define ENTRY_DISP_SHIFT	()
	
#define RETURN_HOME_CMD			(0x02U)

#define FIRST_ROW_CMD       (0x80U) // Address of the first row
#define SECOND_ROW_CMD      (0xC0U) // Address of the second row

/* LCD Module Macros */
#define RS_Pin              (0x01U) // RS pin mask
#define RW_Pin              (0x02U) // RW pin mask
#define EN_Pin              (0x04U) // Enable pin mask
#define BACKLIGHT           (0x08U) // Backlight pin mask

/* General Macros */
#define UPPER_NIBBLE_MSK    (0xF0U) // Mask for the upper nibble
#define NIBBLE_SHIFT        (4U)    // Shift count for the nibble
#define ROW1								(0U)
#define ROW2								(1U)
#define LCD_ROW_SIZE        (16U)   // Number of characters per row

#include <stdint.h>

/*
 *	-------------------LCD_Init------------------
 *	Basic LCD Initialization Function
 *	Input: None
 *	Output: None
 */
void LCD_Init(void);

/*
 *	-------------------LCD_Clear------------------
 *	Clear the LCD Display by passing a command
 *	Input: None
 *	Output: None
 */
void LCD_Clear(void);

/*
 *	----------------LCD_Set_Cursor----------------
 *	Set Cursor to Desire Place
 *	Input: Desired Row and Column to place Cursor
 *	Output: None
 */
void LCD_Set_Cursor(uint8_t row, uint8_t col);

/*
 *	---------------LCD_Reset_Cursor---------------
 *	Reset Cursor back to Row 1 and Column 0
 *	Input: None
 *	Output: None
 */
void LCD_Reset_Cursor(void);

/*
 *	----------------LCD_Print_Char----------------
 *	Prints a Character to LCD
 *	Input: Character Hex Value
 *	Output: None
 */
void LCD_Print_Char(uint8_t data);

/*
 *	----------------LCD_Print_Str-----------------
 *	Prints a string to LCD
 *	Input: Pointer to Character Array
 *	Output: None
 */
void LCD_Print_Str(uint8_t* str);

#endif