import fileinput, sys

""" getch for python """
try:
	# Win32
	from msvcrt import getch
except ImportError:
	# UNIX
	def getch():
		import sys, tty, termios
		fd = sys.stdin.fileno()
		old = termios.tcgetattr(fd)
		try:
			tty.setraw(fd)
			return sys.stdin.read(1)
		finally:
			termios.tcsetattr(fd, termios.TCSADRAIN, old)

""" Whitelist of brainfuck instructions """
valid_instructions = "><+-.,[]";

instructions = "" 
data = [0] * 30000

instruction_pointer = 0
data_pointer = 0

for line in fileinput.input():
	instructions += "".join(c for c in line if c in valid_instructions)


""" match closing ']'s to find the instruction after the last closing ']' """
def conditional_forward(instrp, instrs):
	needed_closing = 1

	for index in range(instrp + 1, len(instrs)):
		if instrs[index] == ']':
			needed_closing = needed_closing - 1;
		elif instrs[index] == '[':
			needed_closing = needed_closing + 1;

		if needed_closing == 0:
			return index + 1;

""" match opening '['s backwards, to find the instruction after the first opening '[' """
def conditional_backward(instrp, instrs):
	needed_opening = 1

	for index in range(instrp - 1, -1, -1):
		if instrs[index] == '[':
			needed_opening = needed_opening - 1
		elif instrs[index] == ']':
			needed_opening = needed_opening + 1

		if needed_opening == 0:
			return index + 1;

""" Evaluate until we've reached the end of the instruction list """
while (instruction_pointer < len(instructions)):
	next_instruction = instructions[instruction_pointer]

	if next_instruction == '>':
		data_pointer = data_pointer + 1
		instruction_pointer = instruction_pointer + 1
	elif next_instruction == '<':
		data_pointer = data_pointer - 1
		instruction_pointer = instruction_pointer + 1
	elif next_instruction == '+':
		data[data_pointer] = data[data_pointer] + 1
		instruction_pointer = instruction_pointer + 1
	elif next_instruction == '-':
		data[data_pointer] = data[data_pointer] - 1
		instruction_pointer = instruction_pointer + 1
	elif next_instruction == '.':
		sys.stdout.write(chr(data[data_pointer]))
		instruction_pointer = instruction_pointer + 1
	elif next_instruction == ',':
		data[data_pointer] = ord(getch())
		instruction_pointer = instruction_pointer + 1
	elif next_instruction == '[':
		if data[data_pointer] == 0:
			instruction_pointer = conditional_forward(instruction_pointer, instructions)
		else:
			instruction_pointer = instruction_pointer + 1
	elif next_instruction == ']':
		if data[data_pointer] != 0:
			instruction_pointer = conditional_backward(instruction_pointer, instructions)
		else:
			instruction_pointer = instruction_pointer + 1
