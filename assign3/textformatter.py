import fileinput
import sys
import re

class Formatter(object):
	def __init__(self, arg1, arg2):
		self.width = 0
		self.margin = 0
		self.spacing = 0
		self.formatting = False
		self.length = 0
		self.formatted_output = []
		self.formatted_line= []
		self.line_number = 0
		if(str(arg1) == "None"):
			#this means a list will be formatted
			for line in arg2:
				li = line.split()
				if(self.format_set(li)):
					continue
			#	control = self.format_set(li)
			#	if(control == None):
			#		return
			#	if(control):
			#		continue
				if(self.formatting):
					li = self.format_line(li)
				if(self.formatting == False):
					if(self.formatted_line):
						self.formatted_output.append("".join(self.formatted_line))
					del self.formatted_line[:]
					self.length = 0
					self.formatted_output.append(line)
			if(self.formatted_line):
				self.formatted_output.append("".join(self.formatted_line))
		elif(str(arg2) == "None"):
			input_file = open(arg1, "r")
			for line in input_file:
				li = line.split()
			#	control = self.format_set(li)
			#	if(control is  None):
			#		break
			#	if(control == True):
			#		continue
				if(self.format_set(li)):
					continue
				if(self.formatting):
					li = self.format_line(li)
				if(self.formatting == False):
					if(self.formatted_line):
						self.formatted_output.append("".join(self.formatted_line))
					del self.formatted_line[:]
					self.length = 0		
					self.formatted_output.append(line.rstrip('\n'))
				self.line_number += 1
			if(self.formatted_line):
				self.formatted_output.append("".join(self.formatted_line))	
	def format_set(self, li):
		if(len(li) < 1 or len(li) > 2):
			return
		tmpli= ' '.join(li)
		LW = re.search(r'^\.LW (-?\d+)', tmpli)
		if (LW):
			k = int(LW.group(1))
			if(k < 0):
				print("Error on line:", str(self.line_number), file = sys.stderr)
				print("Negative integer specified for line width, please only use positive integers.", file = sys.stderr)
				return None 
			self.width = k
			self.formatting = True
			return True
		LM = re.search('^\.LM ([+-]?)(\d+)', tmpli)
		if (LM):
			if(LM.group(1) == "+"):
				z = int(LM.group(2))
				if(self.margin + z <= int(self.width) - 20):
					self.margin += z
				else:
					self.margin = self.width - 20
			elif(LM.group(1) == "-"):
				y = int(LM.group(2))
				if(self.margin - y >= 0):
					self.margin -= y
				else:
					self.margin = 0
			else:
				x = int(LM.group(2))
				if(int(self.width) > 0 and int(self.width) - 20 >= x):
					self.margin = x
				else:
					self.margin = self.width - 20
			return True
		FT = re.search('^.FT (on|off)', tmpli)
		if (FT):
			if(FT.group(1) == "on"):
				self.formatting = True
				return True
			elif(FT.group(1) == "off"):
				self.formatting =False
				return True
		FT2 = re.search('^.FT (ON|OFF)', tmpli)
		if (FT2):
			print("Error on line:", str(self.line_number), file = sys.stderr)
			print("Capitals used for on and off formatting control. Please use lowercase.", file = sys.stderr)
			return None
		LS = re.search('^.LS (-?\d+)', tmpli)
		if (LS):
			j = int(LS.group(1))
			if (j < 0):
				print("Error on line:", str(self.line_number), file = sys.stderr)
				print("Negative integer specified for line spacing, please only use positive integers.", file = sys.stderr)
				return None
			self.spacing =j
			return True
		return False
	def format_line(self, line):
		if(not line):
			if(self.formatted_line):
				self.formatted_output.append("".join(self.formatted_line))
			del self.formatted_line[:]
			self.formatted_output.append("")
			self.length = 0
			if(self.spacing > 0):
				for x in range(self.spacing*2):
					self.formatted_output.append("")
			return
		for word in line:
			if(len(word) > self.width):
				print("Error on line:", str(self.line_number), file = sys.stderr)
				print("Length of word is greater then the width of the line.", file = sys.stderr)
				print(word, "Length:", len(word), file = sys.stderr)
				print("Page width:",self.width, file = sys.stderr)
				return None
			if(len(word) > self.width - self.margin):
				print("Error on line:", str(self.line_number), file = sys.stderr)
				print("Length of word is greater then the width of the line minus the margin.", file = sys.stderr)
				print(word, "Length:", len(word), file = sys.stderr)
				print("Page width minus margin:",self.width - self.margin, file = sys.stderr)
				return None
			if(self.length == 0 and self.margin > 0):
				for x in range(self.margin):
					self.formatted_line.append(" ")
			if(len(word) + 1 + self.length <= int(self.width) - self.margin):
				if(self.length > 0):
					self.formatted_line.append(" ")
					self.formatted_line.append(word)
					self.length += len(word) + 1
				else: 
					self.formatted_line.append(word)
					self.length += len(word)
			elif(int(self.width) > 0):
				self.length = 0
				self.formatted_output.append("".join(self.formatted_line))
				del self.formatted_line[:]
				if(self.spacing > 0):
					for x in range(self.spacing):
						self.formatted_line.append("\n")
				if(self.margin > 0):
					for x in range(self.margin):
						self.formatted_line.append(" ")
				self.formatted_line.append(word)
				self.length += len(word)
	def get_lines(self):
		return self.formatted_output

