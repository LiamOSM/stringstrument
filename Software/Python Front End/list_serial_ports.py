# Short bit of code to list the serial ports
import serial.tools.list_ports
print([comport.device for comport in serial.tools.list_ports.comports()])
