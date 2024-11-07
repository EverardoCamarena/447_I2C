/*
 * ModuleTest.c
 *
 *	Provides the testing functions all of individual peripheral testing
 *	and full system testing
 *
 * Created on: September 3rd, 2023
 *		Author: Jackie Huynh
 *
 */
 
#include "ModuleTest.h"
#include "TCS34727.h"
#include "MPU6050.h"
#include "UART0.h"
#include "Servo.h"
#include "LCD.h"
#include "I2C.h"
#include "util.h"
#include "ButtonLED.h"
#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static char printBuf[100];
static char angleBuf[LCD_ROW_SIZE];
static char colorBuf[LCD_ROW_SIZE];
static char colorString[6];

/* RGB Color Struct Instance */
RGB_COLOR_HANDLE_t RGB_COLOR;
	
/* MPU6050 Struct Instance */
MPU6050_ACCEL_t Accel_Instance;
MPU6050_GYRO_t 	Gyro_Instance;
MPU6050_ANGLE_t Angle_Instance;

static void Test_Delay(void){
	/*CODE_FILL*/				//Toggle Red Led
	/*CODE_FILL*/				//Delay for 0.5s using millisecond delay
	LEDs = RED;
	DELAY_1MS(500);
	LEDs = DARK;
}

static void Test_UART(void){
		// Variables to be included in the string
    int decimalNumber = 42;
    float floatingNumber = 3.14159;
	
    /*CODE_FILL*/                        
    // 1. Construct a string with letters, decimal numbers and floats using sprintf
		sprintf(printBuf, "hello world, Integer: %d, Float: %2f", decimalNumber, floatingNumber);
    // 2. Send the string to PC serial terminal for display
    UART0_OutString(printBuf);
		UART0_OutCRLF();
    // 3. Delay for 1s using ms delay function
    DELAY_1MS(1000);
}

static void Test_I2C(void){
	/*CODE_FILL*/						
	/* Check if RGB Color Sensor has been detected and display the ret value on PC serial terminal. */
	uint8_t ret = I2C0_Receive(TCS34727_ADDR, TCS34727_CMD|TCS34727_ID_R_ADDR);
	sprintf(printBuf, "Return string: %x\r\n", ret);
	UART0_OutString(printBuf);
	UART0_OutCRLF();
}

static void Test_MPU6050(void){
	/* Grab Accelerometer and Gyroscope Raw Data*/
	/*CODE_FILL*/
	MPU6050_Get_Accel(&Accel_Instance); // Fetch the raw accelerometer data
	MPU6050_Get_Gyro(&Gyro_Instance);   // Fetch the raw gyroscope data
	
	/* Process Raw Accelerometer and Gyroscope Data */
	/*CODE_FILL*/
	MPU6050_Process_Accel(&Accel_Instance); // Convert raw accelerometer data to physical values
	MPU6050_Process_Gyro(&Gyro_Instance);   // Convert raw gyroscope data to physical values
	
	/* Calculate Tilt Angle */
	/*CODE_FILL*/
	MPU6050_Get_Angle(&Accel_Instance, &Gyro_Instance, &Angle_Instance);
	
	/* Format buffer to print data and angle */
	/*CODE_FILL*/
	sprintf(printBuf, "Accel: X=%.2f Y=%.2f Z=%.2f, Gyro: X=%.2f Y=%.2f Z=%.2f, Angles: X=%.2f Y=%.2f Z=%.2f\r\n",
	        Accel_Instance.Ax, Accel_Instance.Ay, Accel_Instance.Az,
	        Gyro_Instance.Gx, Gyro_Instance.Gy, Gyro_Instance.Gz,
	        Angle_Instance.ArX, Angle_Instance.ArY, Angle_Instance.ArZ);
	
	UART0_OutString(printBuf);
	DELAY_1MS(50);
}

static void Test_TCS34727(void){
	
	/* Grab Raw Color Data From Sensor */
	/*CODE_FILL*/
	RGB_COLOR.C_RAW = TCS34727_GET_RAW_CLEAR();  // Get clear channel data
	RGB_COLOR.R_RAW = TCS34727_GET_RAW_RED();    // Get red channel data
	RGB_COLOR.G_RAW = TCS34727_GET_RAW_GREEN();  // Get green channel data
	RGB_COLOR.B_RAW = TCS34727_GET_RAW_BLUE();   // Get blue channel data
		
	/* Process Raw Color Data to RGB Value */
	/*CODE_FILL*/
	TCS34727_GET_RGB(&RGB_COLOR);
	
	/* Change Onboard RGB LED Color to Detected Color */
	COLOR_DETECTED detectedColor = Detect_Color(&RGB_COLOR);
	switch(detectedColor){
		case RED_DETECT:
			LEDs = RED;
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			break;
		}
		
	/* Format String to Print */
	/*CODE_FILL*/
  sprintf(printBuf, "R: %.2f, G: %.2f, B: %.2f, Detected: %d\r\n", 
		RGB_COLOR.R, RGB_COLOR.G, RGB_COLOR.B, detectedColor);
		
	/* Print String to Terminal through USB */
	/*CODE_FILL*/
	UART0_OutString(printBuf);
	DELAY_1MS(10);
}

static void Test_Servo(void){
	/*
	 * In this test, follow the series of steps below (each step requires a 1s delay after)
	 * 1. Drive Servo to 0 degree
	 * 2. Drive Servo to 45 degree (Adjusted from -45 to keep within 0-180 range)
	 * 3. Drive Servo to 0 degree
	 * 4. Drive Servo to 90 degree (Equivalent of 45 degrees in another direction)
	 * 5. Drive Servo to 0 degree
	 * 6. Drive Servo to 135 degree (Adjusted from -90 to keep within 0-180 range)
	 * 7. Drive Servo to 0 degree
	 * 8. Drive Servo to 180 degree
	 */ 
	Drive_Servo(0);       // Drive servo to 0 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(-45);     // Drive servo to -45 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(0);       // Drive servo back to 0 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(45);      // Drive servo to 45 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(0);       // Drive servo back to 0 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(-90);     // Drive servo to -90 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(0);       // Drive servo back to 0 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(90);      // Drive servo to 90 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
	Drive_Servo(0);       // Drive servo back to 0 degrees
	DELAY_1MS(1000);      // Delay for approximately 1 second
}

static void Test_LCD(void){
	/* Print Name to LCD at Center Location */
	/*CODE_FILL*/
	LCD_Clear();  // Clear the LCD before printing anything new
	DELAY_1MS(2); // Short delay after clearing the LCD

	// Centering "Ever" on a 16 character wide LCD
	LCD_Set_Cursor(ROW1, 6);  // Set cursor to the first row, sixth column
	LCD_Print_Str((uint8_t*)"Ever");
	LCD_Set_Cursor(ROW2, 6);

	// Print "Ever" to the LCD
	LCD_Print_Str((uint8_t*)"test");
	DELAY_1MS(2); // Safety delay after writing to the LCD
}

static void Test_Full_System(void){
	/* Grab Accelerometer and Gyroscope Raw Data*/
	/*CODE_FILL*/
	MPU6050_Get_Accel(&Accel_Instance);
	MPU6050_Get_Gyro(&Gyro_Instance);
	
	/* Process Raw Accelerometer and Gyroscope Data */
	/*CODE_FILL*/
	MPU6050_Process_Accel(&Accel_Instance);
	MPU6050_Process_Gyro(&Gyro_Instance);
		
	/* Calculate Tilt Angle */
	/*CODE_FILL*/
	MPU6050_Get_Angle(&Accel_Instance, &Gyro_Instance, &Angle_Instance);
		
	/* Drive Servo Accordingly to Tilt Angle on X-Axis*/
	/*CODE_FILL*/
	Drive_Servo((int)Angle_Instance.ArX);
		
	/* Format buffer to print MPU6050 data and angle */
	/*CODE_FILL*/
	sprintf(printBuf, "MPU6050 - Ax: %.2f, Ay: %.2f, Az: %.2f, Gx: %.2f, Gy: %.2f, Gz: %.2f, AngleX: %.2f\r\n",
	        Accel_Instance.Ax, Accel_Instance.Ay, Accel_Instance.Az,
	        Gyro_Instance.Gx, Gyro_Instance.Gy, Gyro_Instance.Gz,
	        Angle_Instance.ArX);
	UART0_OutString(printBuf);
	UART0_OutCRLF();
		
	/* Grab Raw Color Data From Sensor */
	/*CODE_FILL*/
	RGB_COLOR.C_RAW = TCS34727_GET_RAW_CLEAR();
	RGB_COLOR.R_RAW = TCS34727_GET_RAW_RED();
	RGB_COLOR.G_RAW = TCS34727_GET_RAW_GREEN();
	RGB_COLOR.B_RAW = TCS34727_GET_RAW_BLUE();
		
	/* Process Raw Color Data to RGB Value */
	/*CODE_FILL*/
	TCS34727_GET_RGB(&RGB_COLOR);
		
	/* Change Onboard RGB LED Color to Detected Color */
	COLOR_DETECTED detectedColor = Detect_Color(&RGB_COLOR);
	switch(detectedColor){
		case RED_DETECT:
			LEDs = RED;
			strcpy(colorString, "RED");
			break;
		case GREEN_DETECT:
			LEDs = GREEN;
			strcpy(colorString, "GREEN");
			break;
		case BLUE_DETECT:
			LEDs = BLUE;
			strcpy(colorString, "BLUE");
			break;
		case NOTHING_DETECT:
			LEDs = DARK;
			strcpy(colorString, "NA");
			break;
	}
		
	/* Format String to Print RGB value*/
	/*CODE_FILL*/
	sprintf(printBuf, "Color R: %.2f, G: %.2f, B: %.2f, Detected: %s", 
		RGB_COLOR.R, RGB_COLOR.G, RGB_COLOR.B, colorString);
		
	/* Print String to Terminal through USB */
	/*CODE_FILL*/
	UART0_OutString(printBuf);
	UART0_OutCRLF();
		
	/* Update LCD With Current Angle and Color Detected */
	sprintf(angleBuf, "Angle:%0.2f", Angle_Instance.ArX);				//Format String to print angle to 2 Decimal Place
	sprintf(colorBuf, "Color:%s", colorString);									//Format String to print color detected
	
	/*CODE_FILL*/						//Clear LCD
	/*CODE_FILL*/						//Safety Delay of 2ms
	/*CODE_FILL*/						//Set Cursor to Row 1 Column 0
	/*CODE_FILL*/						//Print angleBuf String on LCD
	/*CODE_FILL*/						//Safety Delay of 2ms
	/*CODE_FILL*/						//Set Cursor to Row 2 Column 1
	/*CODE_FILL*/						//Print colorBuf String on LCD	
	
	LCD_Clear();                      // Clear LCD
	DELAY_1MS(2);                     // Safety Delay of 2ms
	LCD_Set_Cursor(ROW1, 0);          // Set Cursor to Row 1 Column 0
	LCD_Print_Str((uint8_t*)angleBuf);// Print angleBuf String on LCD
	DELAY_1MS(2);                     // Safety Delay of 2ms
	LCD_Set_Cursor(ROW2, 0);          // Set Cursor to Row 2 Column 0
	LCD_Print_Str((uint8_t*)colorBuf);// Print colorBuf String on LCD
	
	DELAY_1MS(20);
}

void Module_Test(MODULE_TEST_NAME test){
	
	switch(test){
		case DELAY_TEST:
			Test_Delay();
			break;
		
		case UART_TEST:
			Test_UART();
			break;
		
		case I2C_TEST:
			Test_I2C();
			break;
		
		case MPU6050_TEST:
			Test_MPU6050();
			break;
		
		case TCS34727_TEST:
			Test_TCS34727();
			break;
		
		case SERVO_TEST:
			Test_Servo();
			break;
		
		case LCD_TEST:
			Test_LCD();
			break;
			
		case FULL_SYSTEM_TEST:
			Test_Full_System();
			break;
		
		default:
			break;
	}
}
