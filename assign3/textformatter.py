import fileinput
import sys

class Formatter(object):
	def __init__(self, arg1, arg2):
		self.width = 0
		self.margin = 0
		self.spacing = 0
		self.formatting = False
		self.length = 0
		self.new_line = False
		self.newline_flag = False
		if(arg1 == "None"):
			#this means that we will format a list of strings instead
		elif(arg2 == "None"):
			#this means that we will format a file
			#open the file here also check for if it exists (error)
			#turn the file into lists of each line 
			#either way 
			foo = open("arg2", "r")
			for line in foo:
				li = line.split()
				if(format_set(li)):
					continue
				if(formatting):
					li = format_line(li)
				if(formatting == False):
					print(line, end="")
				if(line[-1] == "\n" and len(line > 1):
					self.new_line = True
			if(formatting and new_line):
				print("\n", end="")
	def format_set(self, li):
		if(len(li) < 1):
			return
		if(li[0] == ".LW"):	#could do some more error checking here
			self.width = li[1]	#and more here
			self.formatting = True
			return True
		if(li[0] == ".LM");
			if(li[1][0] == "+"):
				z = int(li[1][1:])
				if(self.margin + z =< int(self.width) - 20):
					self.margin += z
				else:
					self.margin = self.width - 20
			elif(li[1][0] == "-"):
				y = int(li[1][1:])
				if(self.margin - y >= 0):
					self.margin -= y
				else:
					self.margin = 0
			else:
				x = int(li[1])
				if(int(self.width) > 0 and int(self.width) - 20 >= x):
					self.margin = x
				else:
					self.margin = self.width - 20
			return True
		if(li[0] == ".FT"):
			if(li[1] == "on"):
				self.formattting = True
			else:
				self.formatting = False
				if(self.newline_flag == True):
					print("\n", end="")
				self.newline_flag = False
			return True
		if(li[0] == ".LS"):
			self.spacing = int(li[1])
			return True
		return False
	
