import csv
import sys

# Check arguments count
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")

# Save filenames to variables
data = sys.argv[1]
sequence = sys.argv[2]
people = []

# Open database and save to memory
with open(data, "r") as f:
    reader = csv.DictReader(f)
    for person in reader:
        people.append(person)

# Open dna sequence and save to dna variable
with open(sequence, "r") as f:
    dna = f.readlines()
    dna = dna[0].strip()

# Create STR list
STR = list(people[0].keys())
STR.pop(0)

# Count the longest run of consecutive repeats for each STR
di = {}
for i in STR:
    cur_max = 0
    for j in range(0, len(dna)):
        tmp = 0
        if dna[j: j + len(i)] == i:
            for k in range(j, len(dna), len(i)):
                if dna[k: k + len(i)] != i:
                    break
                tmp += 1
            if cur_max < tmp:
                cur_max = tmp
    di[i] = str(cur_max)

is_found = False

# Compare people
for i in range(len(people)):
    is_match = True
    for j in STR:
        if people[i][j] != di[j]:
            is_match = False
            break
    if is_match:
        print(people[i]["name"])
        is_found = True
        break

# If not match print
if not is_found:
    print("No match")
