#!/usr/bin/env python 
import socket
import serial
import time
import sys
 

TCP_IP = '192.168.0.10'
TCP_PORT = 8080
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
s.settimeout(5)

ser = serial.Serial("COM5", 115200)

f = open("times.txt",'w')

timeHisto = [0]*100

testStr =  "".join(["*"+str(x) for x in range(200)])
print testStr
print len(testStr)

time.sleep(1)

for i in range(200):
  print "test %4d : " % i,
  ser.write(testStr)
  
  start = time.time()
  ret = ""
  while len(ret) < len(testStr) and time.time()-start < 5.0 :
    r = s.recv(1)
    sys.stdout.write(r)
    ret += r

  timetaken = time.time()-start    
  print " %.3fs" % (timetaken)
  f.write("%.3f\n" % timetaken)
  timeHisto[int(timetaken/.1)+1] += 1

  if (ret != testStr):
    print "FAIL"
    break

  time.sleep(1)

fh = file("timeHisto.csv", 'w')
for i in range(len(timeHisto)):
  fh.write("%1.2f,%3d\n" % (i*.05,timeHisto[i]))
fh.close()
  
  
