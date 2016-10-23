#!/usr/bin/env python3
import fileinput
import sys

width = 0
margin = 0
spacing = 0
formatting = False
length = 0
new_line = False
newline_flag = False
#secondary_formatting = False
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
#			global secondary_formatting
#			if(secondary_formatting == True):
#				print("\n", end="")
#				secondary_formatting = False
			print(line, end="")
		if(line[-1] == "\n" and len(line) > 1):
			global new_line
			new_line = True
	if(formatting and new_line):
		print("\n", end="")
def format_set(li):
	global width
	global margin
	global spacing
	global formatting
	global length
#	global secondary_formatting
	if(len(li) < 1):
		return
	if(li[0] == ".LW"):
		# turn on width
		# check for the value
		width = li[1]
		formatting = True
#		secondary_fromatting = True
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
#			secondary_fromatting = True
		else: 
			formatting = False
			global newline_flag
			if(newline_flag == True):
				print("\n", end ="")
			newline_flag = False
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
	global newline_flag
	if(len(line) == 0):
		print("\n", end="")
		#add in linespacing
		length = 0
		newline_flag = True
		if(spacing > 0):
			for x in range(2*spacing):
				print("\n", end="")
		return
	if(newline_flag == True):
		print("\n", end="")
		newline_flag = False
	for word in line:
		if(length == 0 and margin > 0):
			for x in range(margin):
				print(" ", end="")
		if(len(word) + 1 + length <= int(width) - margin):
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
			

if __name__ == "__main__":
	main()
