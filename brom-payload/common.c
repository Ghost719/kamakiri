#include "common.h"

void (*jump_bl)(void) = (void*) 0xADD5; // untested
void (*send_usb_response)(int, int, int) = (void*)0x62E5;
void (**ptr_send)() = (void*)0x1027A4;
void (**ptr_recv)() = (void*)0x1027A0;
void (*orig_ptr_send)();
void (*orig_ptr_recv)();

int (*send_dword)() = (void*)0xB527;
int (*recv_dword)() = (void*)0xB4F3;
// addr, sz
int (*send_data)() = (void*)0xB5EF;
// addr, sz, flags (=0)
int (*recv_data)() = (void*)0xB569;

void low_uart_put(int ch) {
    volatile uint32_t *uart_reg0 = (volatile uint32_t*)0x11005014;
    volatile uint32_t *uart_reg1 = (volatile uint32_t*)0x11005000;

    while ( !((*uart_reg0) & 0x20) )
    {}

    *uart_reg1 = ch;
}

void _putchar(char character)
{
    if (character == '\n')
        low_uart_put('\r');
    low_uart_put(character);
}
