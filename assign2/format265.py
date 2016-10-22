#!/usr/bin/env python3
import fileinput
import sys

width = 0
margin = 0
spacing = 0
formatting = False
length = 0
new_line = False
def main():
	for line in fileinput.input():
		#split the string up into a list of strings
		li = line.split()
		#determine if theres a formatting key in the list
		if(format_set(li)):
			continue
		#format the line according to the flags
		if(formatting):	
			li = format_line(li)
		if(formatting == False):
			print(line, end="")
		if(line[-1] == "\n"):
			global new_line
			new_line = True
	if(formatting and new_line):
		print("")
def format_set(li):
	global width
	global margin
	global spacing
	global formatting
	global length
	if(len(li) < 1):
		return
	if(li[0] == ".LW"):
		# turn on width
		# check for the value
		width = li[1]
		formatting = True
		return True
	if(li[0] == ".LM"):
		# turn on margin
		# check list[1] for value
		# make sure the margin is greater then 0 and less than width -20
		if(li[1][0] == "+"):
			# adding to margin
			z = int(li[1][1:])
			if(margin + z <=  int(width) - 20):
				margin = margin + z
			else:
				margin = width - 20
		elif(li[1][0] == "-"):
			# subtracting from margin
			y = li[1][1:]
			y = int(y)
			if(margin - y >=0):
				margin = margin - y
			else:
				margin = 0
		else:
			# resetting margin
			x = li[1]
			x = int(x)
			if (int(width) > 0 and int(width) - 20 >= x):
				margin = x
			else:
				margin = width - 20
		return True
	if(li[0] == ".FT"):
		# turn on or off formatting
		if(li[1] == "on"):
			formatting = True
		else: 
			formatting = False
		return True
	if(li[0] == ".LS"):
		# turn on linespacing 
		spacing = int(li[1])
		return True
	return False

def format_line(line):
	global width
	global spacing
	global length
	global formatting
	global margin
	if(len(line) == 0):
		print("\n\n", end="")
		#add in linespacing
		length = 0
		if(spacing):
			for x in range(spacing+1):
				print("\n", end="")
#		if(margin):
#			for x in range(margin):
#				print(" ", end="")
	for word in line:
		if(length == 0 and margin > 0):
			for x in range(margin):
				print(" ", end="")
		if(len(word) + 1 + length <= int(width) - margin):
#		if(int(width) > 0 and len(word)+ 1 + length <= int(width)):
			if(length > 0):
				print(" ", end="")
				print(word, end="")
				length += len(word)+1
			else:
				print(word, end="")
				length += len(word)
		elif(int(width) > 0):
			length = 0
			print("\n", end="")
			if(spacing > 0):
				for x in range(spacing):
					print("\n", end="")
			
			if(margin > 0):
				for x in range(margin):
					print(" ", end="")
			print(word, end="")
			length += len(word)
			# check spacing and margin
			

if __name__ == "__main__":
	main()
