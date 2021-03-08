from cs50 import get_string

# Read input
s = get_string("Text: ")

# Define variables
i = 0
l = 0
w = 0
j = 0

# Process input
while i < len(s):
    if s[i].isalpha():
        l += 1
    elif s[i] == ' ' and s[i - 1] != '.' and s[i - 1] != '!' and s[i - 1] != '?':
        w += 1
    elif s[i] == '.' or s[i] == '!' or s[i] == '?':
        j += 1
        w += 1
    i += 1

# Count grade
let = (l / w) * 100
sen = (j / w) * 100
idx = 0.0588 * let - 0.296 * sen - 15.8
index = round(idx)

# Output grade
if index < 1:
    print("Before Grade 1")
elif index < 16:
    print("Grade " + str(index))
else:
    print("Grade 16+")

