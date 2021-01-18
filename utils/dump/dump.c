#include "common.h"

volatile unsigned int * const MEMORY = (volatile unsigned int * const)0x00000000;

int print(char* s){
    char c = s[0];
    int i = 0;
    while(c){
        _putchar(c);
        c = s[++i];
    }
    return i;
}

/*
void hex_dump(unsigned int start, unsigned int size) {
    unsigned int data = 0;
    unsigned int data2 = 0;
    static char TABLE[] = "0123456789ABCDEF";
    char buf[3 + 1]; // 3 = 1 space + 2 chars, 1 = null
    char addressbuf[2 + 8 + 1]; // 0x + size of uint32_t + null
    int sz;
    int addr;

    start = start - start % 4;
    size = size + 4 - size % 4;

    for (unsigned int i=0; i <= size; i++) {
        if (i % 16 == 0 && i == size) {
            print("\n");
            break;
        }

        if (i % 16 == 0) {
            print("\n");

            addr = start + i;

            addressbuf[0] = '0';
            addressbuf[1] = 'x';

            for (sz = 9; sz >= 2; sz--) {
                addressbuf[sz] = TABLE[ addr % 16 ];
                addr = (addr / 16);
            }
            addressbuf[10] = '\0';

            print(addressbuf);
            print(":");
        }

        addr = start + i;
        data = MEMORY[addr/4];

        buf[m * 3 + 0] = ' ';
       	buf[m * 3 + 1] = TABLE[ data2 / 16 ];
        buf[m * 3 + 2] = TABLE[ data2 % 16 ];
        buf[12] = '\0';

        print(buf);
    }

    print("\n");
}
*/

void hex_dump2(uint32_t start, uint32_t count) {
    uint32_t tmp = 0;
    uint32_t tmp2 = 0;
    char buf[3 + 1]; // 3 = 1 space + 2 chars, 1 = null
    char addressbuf[2 + 8 + 1]; // 0xZZZZZZZZ + '\0'
    static char TABLE[] = "0123456789ABCDEF";
    uint32_t addr = (uint32_t)(start);
    uint32_t end = (uint32_t)(start + count);
    const uint8_t *mem = (void *)start;

    while (addr <= end) {
        if (addr % 16 == 0 || addr == start) {
            addressbuf[0] = '0';
            addressbuf[1] = 'x';

            tmp = (uint32_t)addr;

            for (tmp2 = 9; tmp2 >= 2; tmp2--) {
		        addressbuf[tmp2] = TABLE[ tmp % 16 ];
		        tmp = tmp / 16;
		    }

            addressbuf[10] = '\0';

            print("\n");
            print(addressbuf);
            print(":");
	    }

        tmp = mem[addr];

        buf[0] = ' ';
        buf[1] = TABLE[ (tmp / 16) % 16 ];
        buf[2] = TABLE[ tmp % 16 ];
        buf[3] = '\0';

        print(buf);

        addr++;
    }
}

int main() {

#ifdef USE_BROM_SEND_DATA
        send_data(0x00000000, 0x20000);
        send_data(0x00100000, 0x40000);
        send_data(0x00200000, 0x80000);
#else
    while (1) {
        hex_dump2(0x00000000, 0x20000);
        hex_dump2(0x00100000, 0x40000);
        hex_dump2(0x00200000, 0x80000);
    }
#endif
}
