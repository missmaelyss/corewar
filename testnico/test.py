# -*- coding: utf-8 -*-
#!/usr/bin/env python

import os
import sys

files = os.listdir('test')

for file in files:
	index = file.rfind('.')
	if (index == -1 or file[index:] != '.s'):
		continue
	cor = file[:index] + '.cor'

	os.system('./mine test/' + file + ' > log')
	try:
		f = open('test/' + cor, 'r')
		mine = f.read()
		f.close()
		os.system('rm test/' + cor)
	except:
		mine = ''

	os.system('./real test/' + file + ' > log')
	try:
		f = open('test/' + cor, 'r')
		real = f.read()
		f.close()
		os.system('rm test/' + cor)
	except:
		real = ''

	if (mine != real):
		print('Error ' + file)
	elif (mine == '' or real == ''):
		print('Check ' + file)
	else:
		print('OK ' + file)

os.system('rm -rf log')
