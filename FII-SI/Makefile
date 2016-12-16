INC=/usr/local/ssl/include/
LIB=/usr/local/ssl/lib/


all: enc-example dec-example

enc-example:
	openssl enc -aes-128-ecb -e -in input.txt -out input.enc

dec-example:
	openssl enc -aes-128-ecb -d -in input.enc -out output-dec.txt
