import serial
import win32com.client
import time
import re
ser = serial.Serial('COM3', 9600, timeout=0)
shell = win32com.client.Dispatch("WScript.Shell")

combos = {
    1: "^%{TAB}",
    2: "^{TAB}",
    3: "^n"
}

def do_combo(digit):
  # print(type(digit))
  if digit in combos.keys():
      shell.SendKeys(combos[digit])
      print('#*$ Called - ', combos[digit])

while 1:
 try:
  line = str(ser.readline())
  print(line)

  pattern = re.compile(r'b\'(?P<digit>\d)\\r\\n\'')
  match = re.match(pattern, line)
  print('match - ', match)
  if match is not None:
      digit = int(match.group('digit'))
      print('#digit -> ', digit)
      do_combo(digit)
  
  time.sleep(1)
 except ser.SerialTimeoutException:
  print('Data could not be read')
  time.sleep(1)


