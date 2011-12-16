# Problem: 
#
# Given a string consisting of a,b and c's, we can perform the following operation: 
# Take any two adjacent distinct characters and replace it with the third character. 
# For example, if 'a' and 'c' are adjacent, they can replaced with 'b'. 
# What is the smallest string which can result by applying this operation repeatedly?

# Sample input:
# 3
# cab
# bcab
# ccccc

# Sample output:
# 2
# 1
# 5

# Run: echo -e "3\ncab\nbcab\nccccc" | ruby string-reduction.rb

lines = STDIN.read.split("\n")
lines = lines[1, lines.length - 1]


def find_other(str)
	map = {"ab" => "c", "ac" => "b", "ba" => "c", "bc" => "a", "ca" => "b", "cb" => "a"}
	return map[str]
end


def get_match(str, start)
	return str[start, 2]
end

def replace_match(str, start)
	before = str.slice(0, start)
	after = str.slice(start + 2, str.length)

	return before + find_other(get_match(str, start)) + after
end


def find_matches(str)
	chars = str.split(//)
	matches = []

	chars.each_with_index do |char, i|
		if i + 1 < chars.length
			if char != chars[i + 1]
				matches << i
			end
		end
	end

	return matches
end

# Bruteforce all the things!
def find_smallest_reduction(str, matches, running_minimum)
	matches.each do |start|
		reduction = replace_match(str, start)
		sub_matches = find_matches(reduction)

		if sub_matches.length == 0
			running_minimum = reduction.length if reduction.length < running_minimum
		else
			running_minimum = find_smallest_reduction(reduction, sub_matches, running_minimum)
		end
	end

	return running_minimum
end

# Actually FIND all the possible reductions, so we can determine what the optimal reduction path actually is at some point
def get_sub_reductions(str, matches)
	reductions = {} 
	matches.each do |start|
		reduction = replace_match(str, start)
		sub_matches = find_matches(reduction)

		reductions[reduction] = get_sub_reductions(reduction, sub_matches)
	end

	return reductions
end

def all_reductions(str)
	sub_reductions = get_sub_reductions(str, find_matches(str));
	return {str => sub_reductions}
end

def smallest_reduction(str)
	return find_smallest_reduction(str, find_matches(str), str.length)
end

lines.each do |line|
	puts smallest_reduction(line)
	#puts all_reductions(line).inspect
end
