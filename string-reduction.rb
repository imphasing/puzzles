
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

def find_all_reductions(str, matches, running_minimum)
	matches.each do |start|
		reduction = replace_match(str, start)
		sub_matches = find_matches(reduction)

		if sub_matches.length == 0
			running_minimum = reduction.length if reduction.length < running_minimum
		else
			running_minimum = find_all_reductions(reduction, sub_matches, running_minimum)
		end
	end

	return running_minimum
end


str = "cabbabbabbcabbabbabb"
puts find_all_reductions(str, find_matches(str), str.length).inspect
