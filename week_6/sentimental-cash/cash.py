from cs50 import get_float

coins = [25, 10, 5, 1]

while True:
    change = get_float("Change owed: ")
    if change > 0.0:
        break
change = int(change * 100)
sum = 0
while change != 0:
    for coin in coins:
        if change - coin >= 0:
            change -= coin
            sum += 1
            break
print(sum)
