from cs50 import get_float

# Define coins value
quarters = 25
dimes = 10
nickels = 5
pennies = 1
coins = 0

# Read change
dollars = get_float("Change owed: ")
cents = round(dollars * 100)
while (dollars < 0):
    dollars = get_float("Change owed: ")
    cents = round(dollars * 100)

# Count coins
if (cents % quarters) < cents:
    coins += cents // quarters
    cents -= quarters * (cents // quarters)
if (cents % dimes) < cents:
    coins += cents // dimes
    cents -= dimes * (cents // dimes)
if (cents % nickels) < cents:
    coins += cents // nickels
    cents -= nickels * (cents // nickels)
if (cents % pennies) < cents:
    coins += cents // pennies
    cents -= pennies * (cents // pennies)
print(coins)

