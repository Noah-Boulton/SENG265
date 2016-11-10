import fileinput
import sys

class Formatter(object):
	def __init__(self, arg1, arg2):
		self.width = 0
		self.margin = 0
		self.spacing = 0
		self.formatting = False
		self.length = 0
		self.formatted_output = []
		self.formatted_line= []
		if(str(arg1) == "None"):
			#this means a list will be formatted
			for line in arg2:
				li = line.split()
				if(self.format_set(li)):
					continue
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
			if(self.formatted_line):
				self.formatted_output.append("".join(self.formatted_line))	
	def format_set(self, li):
	#this is where I should add regex matching
		if(len(li) < 1 or len(li) > 2):
			return
		if(li[0] == ".LW"):	#could do some more error checking here
			self.width = li[1]	#and more here
			self.formatting = True
			return True
		if(li[0] == ".LM"):
			if(li[1][0] == "+"):
				z = int(li[1][1:])
				if(self.margin + z <= int(self.width) - 20):
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
				self.formatting = True
				return True
			elif(li[1] == "off"):
				self.formatting = False
				return True
		if(li[0] == ".LS"):
			self.spacing = int(li[1])
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

