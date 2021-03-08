from cs50 import get_int
ones = 0
twos = 0
click = 0
idx = 0
digits = 0

# Read number
card = get_int("Number: ")
while (card < 0):
    card = get_int("Number: ")

# Count digits
card_copy = card
while card_copy > 0:
    card_copy = card_copy // 10
    digits += 1

# Check validity
if digits == 13 or digits == 15 or digits == 16:
    # Loop over card
    while card > 0:
        if card < 100 and idx == 0:
            idx = card
        if click == 0:
            ones += card % 10
            card = card // 10
            click = 1
        elif click == 1:
            pre_twos = (card % 10) * 2
            if pre_twos > 9:
                pre_twos = pre_twos % 10 + (pre_twos // 10)
            twos += pre_twos
            card = card // 10
            click = 0
    # Define output
    if (twos + ones) % 10 == 0:
        if (idx == 34 or idx == 37) and digits == 15:
            print("AMEX")
        elif (idx >= 51 and idx <= 55) and digits == 16:
            print("MASTERCARD")
        elif (idx >= 40 and idx <= 49) and (digits == 13 or digits == 16):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")

