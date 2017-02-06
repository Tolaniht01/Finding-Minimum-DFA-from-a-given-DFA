#!/usr/bin/python2
# coding: utf-8

from os import listdir, system, popen, mkdir
from os.path import isdir
from shutil import move
from os import remove
from sys import exit
from string import lower
import numpy as np
files = listdir('.')

for each in files:
    if each.endswith('.c') or each.endswith('.C'):
        if each.endswith('.c') or each.endswith('.C'):
            compiler = "gcc "
	p = popen(compiler+each+' -o '+each[:-2]).read()
        print p
        system('./'+each[:-2])
        
with open('output.txt') as f:				#-----------------------Load the graph name---------------------------------
		
	array = [[str(x) for x in line.split()] for line in f]
	#print array	
	string1= array[0][0]
	#print string1
	string2= string1.split('$')
	#print string2
	string3= string2[0]
	num=int(string3)
	#print num
	f3= open('output1.txt','w')					#---------------------specify output file name----------

	
	for i in range(1,len(array)):
		for j in range(0,num):
			f3.write(str(array[i][j])+'\t')
		f3.write('\n')

f.close()
f3.close()


with open('output1.txt') as f:				#-----------------------Load the graph name---------------------------------
		
	array = [[int(x) for x in line.split()] for line in f]

arr=np.array(array)
#print arr

state = 0
#print state
I = '0101110'
for k in range(0, len(I)):
	s= int(I[k])
	#print s
	row = s*num + state +1
        #print row
	for j in range(0, num):
		if arr[row][j] == 1:
			#print j 				
			state = j

flag1=1
if arr[0][state] == 1:
	flag1=0

state1=state
state=0


I = '0101010'
for k in range(0, len(I)):
	s= int(I[k])
	#print s
	row = s*num + state +1
        #print row
	for j in range(0, num):
		if arr[row][j] == 1:
			#print j 				
			state = j
flag2=1
if arr[0][state] == 0:
	flag2=0



if flag1 == flag2 :
	print 'True'
else:
	print 'False'
