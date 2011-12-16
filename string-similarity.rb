# Problem:
#
# For two strings A and B, we define the similarity of the strings to be the length of the longest prefix common to both strings. 
# For example, the similarity of strings "abc" and "abd" is 2, while the similarity of strings "aaa" and "aaab" is 3.
# Calculate the sum of similarities of a string S with each of it's suffixes.

# Sample input:
# 2
# ababaa
# aa

# Expected output:
# 3
# 11

# Run: echo -e "2\nababaa\naa" | ruby string-similarity.rb

lines = STDIN.read.split("\n")
lines = lines[1, lines.length - 1]

# Get the similarity of two strings as a number
def get_similarity(first, second)
	first_prefixes = Array.new(first.length) {|i| first[0, i + 1]}
	second_prefixes = Array.new(second.length) {|i| second[0, i + 1]}

	longest = 0
	first_prefixes.each do |prefix|
		second_prefixes.each do |second|
			longest = second.length if second == prefix && second.length > longest
		end
	end

	return longest
end

def get_suffixes(str)
	suffixes = Array.new(str.length) {|i| str[str.length - 1 - i, i + 1]}
end

# Sum all the similarities of string compared to each of it's suffixes
def get_string_similarity(str)
	suffixes = get_suffixes(str)

	total = 0
	suffixes.each do |suffix|
		total += get_similarity(str, suffix)
	end

	return total
end

lines.each do |line|
	puts get_string_similarity(line)
end
