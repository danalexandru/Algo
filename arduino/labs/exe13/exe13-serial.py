import serial
import win32com.client
import time
import re
ser = serial.Serial('COM3', 9600, timeout=0)
shell = win32com.client.Dispatch("WScript.Shell")

combos = {
    "FF42BD": "^{TAB}", #'*' - change tab
    "FF52AD": "^o", #'#' - open file
    "FF22DD": "{LEFT}", #'PREV' - media - go 5 secs before
    "FFC23D": "{RIGHT}", #'NEXT' - media - go 5 secs after
    "FFA857": "{DOWN}", #'VOL-' - same as tag
    "FF629D": "{UP}", #'VOL+' - same as tag
    "FF02FD": " " #'OK' - spacebar-play/pause
}

def do_combo(HEXcode):
  # print(type(HEXcode))
  if HEXcode in combos.keys():
      shell.SendKeys(combos[HEXcode])
      print('#*$ Called - ', combos[HEXcode])

while 1:
 try:
  line = str(ser.readline())
  print(line)

  pattern = re.compile(r'b\'(?P<code>\w+)\\r\\n\'')
  match = re.match(pattern, line)
  print('match - ', match)
  if match is not None:
      HEXcode = str(match.group('code'))
      print('#HEXcode -> ', HEXcode)
      do_combo(HEXcode)
  
  time.sleep(0.1)
 except ser.SerialTimeoutException:
  print('Data could not be read')
  time.sleep(1)


