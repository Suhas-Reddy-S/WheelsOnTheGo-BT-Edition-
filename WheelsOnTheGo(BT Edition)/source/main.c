#include "tpm.h"
#include "sysclock.h"
#include "uart.h"
#include "MKL25Z4.h"
#include "stdio.h"
#include "motor_control.h"
#include "stdbool.h"

int main(void) {
	sysclock_init();
	Init_UART0();
	Init_TPM();
	// Send escape sequence to clear the terminal
	UART0_Transmit_String("\033[2J");
	// Move the cursor to the top-left corner
	UART0_Transmit_String("\033[H");
	UART0_Transmit_String("Initiating Wheels On The Web.....");

	Set_RGB(0x888888);
	Start_Motor(0xff, 0xff);
	char ch;

	// enter infinite loop and poll bluetooth output
	while (1) {
		ch = UART0_Receive_Byte();
		UART0_Transmit_Char(ch);
		state_machine(ch);
	}
	return 0;
}

