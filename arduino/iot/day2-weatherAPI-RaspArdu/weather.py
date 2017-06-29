import urllib2 as ur2
import json
from time import *


import platform

#part of platform.uname()
if platform.node() != 'raspberrypi':
	print('ERROR: You should be on a raspberry to run this.')
	exit()

if platform.release()[:3] == '4.9':
	print('\n\nERROR: You will have problems with WiringPi if you have a kernel >= 4.9')
	print('One possible solution is: https://github.com/WiringPi/WiringPi-Python/pull/51 \n');
	print('If you want this problem fixed, contact the first 2 contributors:')
	print('\thttps://github.com/WiringPi/WiringPi-Python/graphs/contributors \n\n');
	exit()


code = -1
try:
	from wyliodrin import *
except ImportError, e:
	print('\n\nERROR: ', e)
	print('\twyliodrin not present, trying wiringpi as fallback...')
	try:
		from wiringpi import *
	except ImportError, e:
		print('\tdid not find either wyliodrin or wiringpi')
	else:
		print('\nWiringpi imported succesfully')
		code = 1
else:
	print('\nWyliodrin imported succesfully')
	code = 0
finally:
	print 'Try installing ...'


import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
print("\nSerial opened !")

def interm_led(led_port):

	# if wiringpi has been imported
	if code == 1:
		wiringPiSetupGpio()
	pinMode (led_port, OUTPUT)

	i = 0
	repeat = 2
	while i < repeat:
		digitalWrite (led_port, 1)
		sleep ((500)/1000.0)
		digitalWrite (led_port, 0)
		sleep ((500)/1000.0)
		i += 1
	# 1s * repeat = 2s ...

# looping
while True:
	print("readline: %s" % ser.readline())
	check = int(ser.readline())

	# if wyliodrin has been imported
	if code == 0:
		sendSignal ("sgndist", check)

	if check < 100:
		print("Distance sensor triggered !")
		response = ur2.urlopen("http://api.openweathermap.org/data/2.5/weather?q=Iasi,RO&units=metric&appid=63b68e2ec15393a891508a5796f9f1ac")
		json_response = response.read()#.decode(response.info().get_param('charset') or 'utf-8') #py3

		resp = json.loads(json_response)
		temp_val = resp["main"]["temp"]
		print('Temperature: %s' % temp_val)

		if code == 0:
			sendSignal ("sgntemp", temp_val)

		if temp_val < 10:
			# open green
			print("Green LED opened !")
			interm_led(1)
		elif temp_val < 25:
			# open yellow
			print("Yellow LED opened !")
			interm_led(16)
		else:
			# open red
			print("Red LED opened !")
			interm_led(15)
		#sleep ((500)/1000.0)
