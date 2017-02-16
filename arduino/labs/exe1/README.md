# Algo
a bit of everything
    
  
### hex draw digits

start with a vector of bits of 1s
read from right to left and make bits 0 only if their respective letter is mentioned

![7-segment display](https://upload.wikimedia.org/wikipedia/commons/thumb/0/02/7_segment_display_labeled.svg/220px-7_segment_display_labeled.svg.png)

Basically, this:  
![](https://upload.wikimedia.org/wikipedia/commons/9/97/7-segments_Indicator.gif)

Some examples (re-check !): 
+ 3 = adefg  
+ 6 = abcdfg = 10010000  
+ 7 = bcd = 1110001  
+ 8 = all light up = 00000000  
+ 9 = abcdeg = 10100000  
