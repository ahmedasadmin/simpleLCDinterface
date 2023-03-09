#include <TM4c123.h>


void delay_milli(int n);
void LCD_init(void);
void LCD_Cmd(unsigned char command);
void delay_micro(int n);
void LCD_data(unsigned char data)

int main(){
	
	LCD_init();
	LCD_Cmd(0x01);
	LCD_milli(500);
	LCD_Data('C');
	delay(1);
	LCD_Data('M');
	delay_milli(500);

	return 0;
}

/* init LCD to work */

void LCD_init(void){
	SYSCTL->RCGCGPIO  = 0x01;
	SYSCTL->RCGCGPIO |= 0x02;
	GPIOA->DIR       |= 0xE0;
	GPIOA->DEN	 |= 0xE0;
	GPIOB->DIR	 |= 0xFF;
	GPIOB->DEN	 |= 0xFF;
	LCD_Cmd(0x38);
	LCD_Cmd(0x06);
	LCD_Cmd(0x0F);
	LCD_Cmd(0x01);
}
void LCD_Cmd(unsigned char command){
	
	GPIOA-DATA  = 0x00;      // RS=0, RW=0, E=0
	GPIOB-DATA  = command;
	GPIOA->DATA = 0x80;
       	delay_micro(0);
	GPIOA->DATA = 0x00;
	if(command<4)
		delay_milli(2);
	else
		delay_micro(40); 
}
void delay_micro(int n){
	int i,j;
	for(i=0; i<n; i++)
		for(j=0;j<3;j++){
		// wait..
		}
}
void delay_milli(int n){
	
	int i, j;
	for(i=0; i<n; i++)
		for (j=0;j<3180; j++){
			// wait...
		}
}

void LCD_data(unsigned char data){
	GPIOA->DATA = 0x20;
	GPIOB->DATA = data;
	GPIOA->DATA = 0x80;
	delay_micro(0);
	GPIOA->DATA = 0x00;
	delay_micro(0);
}
