#!/usr/bin/python3

import subprocess


a = 8
if a > 5:
	subprocess.call(" python3 b.py", shell=True)
else:
	print('end!')