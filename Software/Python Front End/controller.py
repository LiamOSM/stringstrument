from time import sleep
import serial

pitches = [174,183,197,209,218,229,241,268,279,296,316,325]
notes   = ['a','b','c','d','e','f','g','h','i','j','k','l']

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
    ones = int(pitch - 10 * tens)
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

def turn_on(address):
    data = [ord(address), ord('9')]
    ser.write(bytes(data))
    print("Done")

def turn_off(address):
    data = [ord(address), ord(':')]
    ser.write(bytes(data))
    print("Done")

for i in range(12):
    set_pitch(notes[i],pitches[i])
