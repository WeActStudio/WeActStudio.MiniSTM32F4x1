from pyb import UART
from time import sleep

uart2 = UART(2, 9600)
uart2.write('hello')
aa=uart2.read(5)
while True:
    aa=uart2.read(50)
    if aa != None:
        for t in aa:
            print('%#x '%t,end='')
        print('\r\n')
    sleep(0.1)