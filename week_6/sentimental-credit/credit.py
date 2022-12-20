from cs50 import get_string
from sys import exit

def main():
    lengths = [13, 15, 16]

    types ={
        1 : "VISA",
        2 : "AMEX",
        3 : "MASTERCARD"
    }

    while True:
        card = get_string("Number: ")
        if card.isdecimal() and len(card) in lengths:
            break;

    typ = ft_type(card)
    if typ == 0 or not ft_valid(card):
        print("INVALID")
        exit(0)

    print(types[typ])

def ft_type(card):
    if len(card) == 13 and card[0] == "4":
        return 1
    elif len(card) == 15 and (card[0:2] == "34" or card[0:2] == "37"):
        return 2
    elif len(card) == 16 and card[0] == "4":
        return 1
    elif len(card) == 16 and 50 < int(card[0:2]) < 56:
        return 3
    else:
        return 0

def ft_valid(card):
    card = card[::-1]
    sum = 0
    for i in range(len(card)):
        if i % 2 == 1:
            if int(card[i]) < 5:
                sum += 2 * int(card[i])
            else:
                sum = sum + 2 * int(card[i]) - 9
        else:
            sum += int(card[i])
    if sum % 10 == 0:
        return True
    else:
        return False

main()
