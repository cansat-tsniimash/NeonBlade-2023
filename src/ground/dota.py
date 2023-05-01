import sys
import argparse
import time
import struct
import datetime

from RF24 import RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
from RF24 import RF24_1MBPS, RF24_250KBPS, RF24_2MBPS
from RF24 import RF24_CRC_16, RF24_CRC_8, RF24_CRC_DISABLED
from RF24 import RF24 as RF24_CLASS
from RF24 import RF24_CRC_DISABLED
from RF24 import RF24_CRC_8
from RF24 import RF24_CRC_16

radio2=RF24_CLASS(24, 1)


if __name__ == '__main__':
    static_payload_size = None

    radio2.begin()
    radio2.openReadingPipe(1, b'\xac\xac\xac\xac\xac')
    radio2.setAddressWidth(5)
    radio2.channel = 11
    radio2.setDataRate(RF24_250KBPS)
    radio2.setCRCLength(RF24_CRC_8)
    radio2.setAutoAck(True)

    if static_payload_size is not None:
        radio2.disableDynamicPayloads()
        radio2.payloadSize = static_payload_size
    else:
        radio2.enableDynamicPayloads()

    radio2.startListening()
    radio2.printDetails()

    while True:
        has_payload, pipe_number = radio2.available_pipe()
        #print(f'has_payload-{has_payload}, pipe_number={pipe_number}')

        if has_payload:
            payload_size = static_payload_size
            if payload_size is None:
                payload_size = radio2.getDynamicPayloadSize()

            data = radio2.read(payload_size)
            print('got data %s' % data)

            if data[0] == 255:
                print("словил 1 пакет МА")
                pack = struct.unpack("<BH2fh2fhHBH", data)
                print("Pack Num:", pack[1])
                print("Time", pack[2])
                print("Pressure", pack[3])
                print("Temperature", pack[4])
                print("Width", pack[5])
                print("Longitude", pack[6])
                print("Heught gps", pack[7])
                print("Fix", pack[8])
                print("Amount", pack[9])



            if data[0] == 10:
                print("словил 2 пакет МА")
                pack = struct.unpack("<BHI9hfBH", data)
                print("Pack Num:", pack[1])
                print("Time", pack[2])
                print("Axel", pack[3])
                print("Giro", pack[4])
                print("Magnet", pack[5])
                print("Heught bme", pack[6])
                print("Amount", pack[7])



            if data[0] == 25:
                print("словил 3 пакет МА")
                pack = struct.unpack("<BHI3hiH", data)
                print("Pack Num", pack[1])
                print("Time", pack[2])
                print("Voltage", pack[3])
                print("Curent", pack[4])
                print("State", pack[5])
                print("Photo", pack[6])
                print("Amount", pack[7])



            if data[0] == 77:
                print("словил 1 пакет ДА")
                pack = struct.unpack("<BH2Ii2fib2H", data)
                print("Pack Num:", pack[1])
                print("Time", pack[2])
                print("Pressure", pack[3])
                print("Temperature", pack[4])
                print("Width", pack[5])
                print("Longitude", pack[6])
                print("Heught gps", pack[7])
                print("Fix", pack[8])
                print("Amount", pack[9])



            if data[0] == 113:
                print("словил 2 пакет ДА")
                pack = struct.unpack("<BHI9hfH")
                print("Pack Num:", pack[1])
                print("Time", pack[2])
                print("Axel", pack[3])
                print("Giro", pack[4])
                print("Magnet", pack[5])
                print("Heught bme", pack[6])
                print("Amount", pack[7])



