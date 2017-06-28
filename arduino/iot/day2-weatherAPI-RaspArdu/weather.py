import urllib2 as ur2
import json
from time import *

from wyliodrin import *
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
print("Serial opened !")

def interm_led(led_port):
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

while True:

	print("readline: %s" % ser.readline())
	check = int(ser.readline())
	sendSignal ("sgndist", check)

	if check < 100:
		print("Open API")
		response = ur2.urlopen("http://api.openweathermap.org/data/2.5/weather?q=Iasi,RO&units=metric&appid=<<>>")
		json_response = response.read()#.decode(response.info().get_param('charset') or 'utf-8') #py3

		resp = json.loads(json_response)
		temp_val = resp["main"]["temp"]
		print('\nTemperature: %s' % temp_val)

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
