#!/usr/bin/env python3

from common import Device
from logger import log
from load_payload import load_payload
from functions import check_modemmanager


def dump_region(dev, addr, size, blocksize=0x2000):
    data = bytes()

    for i in range(0, size, blocksize):
        if i + blocksize > size:
            blocksize = size - i
        data += dev.mem_read(addr, blocksize)
        addr += blocksize

        print('[{} / {}]'.format(i + blocksize, size), end='\r')
        dev.kick_watchdog()
    print('')

    return data

def main(dev):
    load_payload(dev)

    log("Dump bootrom")
    with open("brom.mt8695.bin", "wb") as file:
        file.write(dump_region(dev, 0x000000, 0x20000))

    log("Dump SRAM")
    with open("sram.mt8695.bin", "wb") as file:
        file.write(dump_region(dev, 0x100000, 0x40000))

    log("Dump SRAM L2")
    with open("sram2.mt8695.bin", "wb") as file:
        file.write(dump_region(dev, 0x200000, 0x80000))

if __name__ == "__main__":

    check_modemmanager()

    dev = Device()
    dev.find_device()

    main(dev)
