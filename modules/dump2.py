#!/usr/bin/env python3

from common import Device
from logger import log
from load_payload import load_payload
from functions import check_modemmanager


def main(dev):
    load_payload(dev)

    log("Dump bootrom")
    with open("brom.mt8695.bin", "wb") as file:
        data = dev.mem_read(0x000000, 0x20000)
        file.write(data)

    log("Dump SRAM")
    with open("sram.mt8695.bin", "wb") as file:
        data = dev.mem_read(0x100000, 0x40000)
        file.write(data)

    log("Dump SRAM L2")
    with open("sram2.mt8695.bin", "wb") as file:
        data = dev.mem_read(0x200000, 0x80000)
        file.write(data)

if __name__ == "__main__":

    check_modemmanager()

    dev = Device()
    dev.find_device()

    main(dev)
