#include "TM4C123.h"

// HERE put LCDdriver files 
// so, everything will work fine with you 




#define K_ROW GPIOE
#define k_col GPIOC


void KEYPAD_init()
{
	SYSCTL->RCGCGPIO |= 0x04;
	SYSCTL->RCGCGPIO |= 0x10;
	
	K_ROW->DIR |= 0x0F;
	K_ROW->DEN |= 0x0F;
	K_ROW->ODR |= 0x0F;


	K_COL->DIR  &=~0xF0;
	k_COL->DEN  |=0xF0;
	K_COL->PUR  |=0xF0;
}

unsigned char getKey(void){
	
	const unsigned char keymap[4][4]={
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'}
	};

	uint8_t k_row, k_col;
	K_ROW->DATA=0;
	k_col = K_COL->DATA & 0xF0;
	
	if(k_col == 0xF0)
		return 0;
	for(;;){
		k_row=0;
		K_ROW->DATA = 0x0E;
		delayUs(10);
		k_col = K_COL->DATA & 0xF0;
		if(k_col != 0xF0)
			break;
		k_row=1;
		K_ROW->DATA = 0x0D;
		delayUs(10);
		k_col = K_COL->DATA & 0xF0;
		if(k_col != 0xF0)
			break;
		k_row=2;
		K_ROW->DATA = 0x0B;
		delayUs(10);
		k_col = K_COL->DATA & 0xF0;
		if(k_col != 0xF0)
			break;
		k_row=3;
		K_ROW->DATA = 0x07;
		delayUs(10);
		k_col = K_COL->DATA & 0xF0;
		if(k_col != 0xF0)
			break;
	
	return 0;
	}
		if(k_col == 0xE0)
			return keymap[k_row][0];
		if(k_col == 0xD0)
			return keymap[k_row][1];
		if(k_col == 0xB0)
			return keymap[k_row][2];
		if(k_col == 0x70)
			return keymap[k_row][3];

}
int main(){
	KEYPAD_init();
	LCD4bit_Init();
	LCD4bit_Cmd(1);
	LCD4bit_Cmd(0x80);
	delayMs(500);
	unsigned char key;

	uint8_t key_count = 0;
	while(1){
		key = getkey();
		delayMs(500);
		if(key!=0){
			key_count++;
		if(key_count>=16){
			LCD4bit_Data(key);
			delayMs(500);
			LCD4bit_Cmd(0xC0);
			key_count = 0;
		}
		if(key = "*"){
			LCD4bit_Cmd(0x01);
			LCD4bit_Cmd(0x08);
			key_count = 0;
		}
		LCD4bit_Data(key);
		delayMs(100);
		}
	}
}
