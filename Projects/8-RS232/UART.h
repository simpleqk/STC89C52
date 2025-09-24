#ifndef _UART_H_
#define _UART_H_

typedef void (*LPUART_RECEIVEBYTE)(unsigned char byte);

void UART_Init(LPUART_RECEIVEBYTE pf);
void UART_SendByte(unsigned char byte);

#endif
