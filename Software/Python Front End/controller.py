from time import sleep
import serial

pitches = [175,185,196,208,220,233,247,262,277,294,311,330]

# serial setup
ser = serial.Serial(
	port = '/dev/cu.usbmodem14101',
	baudrate = 2400,
)

# set the pitch of a particular note
# address must be a string of length 1
def set_pitch(address, pitch):
    address = ord(address)
    data = [address, ord('0')]
    ser.write(bytes(data))
    #print(bytes(data))
    hundreds = int(pitch/100)
    pitch = pitch - 100 * hundreds
    tens = int(pitch/10)
    ones = pitch - 10 * tens
    for i in range(hundreds):
        data = [address, ord('6')]
        ser.write(bytes(data))
        #print(bytes(data))
    for i in range(tens):
        data = [address, ord('5')]
        ser.write(bytes(data))
        #print(bytes(data))
    for i in range(ones):
        data = [address, ord('4')]
        ser.write(bytes(data))
        #print(bytes(data))
    print("Done")
