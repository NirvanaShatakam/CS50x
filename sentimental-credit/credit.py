# Recreate the credit problem in python

# get input from the user (conditionals: length is 13,15 or 16; check if it completes the luna)


def checklen(string):
    if len(string) in [13, 15, 16] and string.isdigit():
        return True
    else:
        return False


def checkval(string):
    # i = len(string) - 1

    i = len(string) - 2
    ganit = 0

    while i >= 0:
        if int(string[i])*2 >= 10:
            pakya = (int(string[i])*2) - 9
        else:
            pakya = int(string[i])*2

        ganit = ganit + pakya
        i = i - 2

    j = len(string) - 1
    temp_sum = 0
    while j >= 0:
        temp_sum = temp_sum + int(string[j])
        j = j - 2

    total = ganit + temp_sum

    if total % 10 == 0:
        return True
    else:
        return False


def printcard(string):
    if int(string[0]) in [3] and int(string[1]) in [4, 7] and len(string) == 15:
        print("AMEX")
    elif int(string[0]) in [5] and int(string[1]) in [1, 2, 3, 4, 5] and len(string) == 16:
        print("MASTERCARD")
    elif int(string[0]) in [4] and len(string) in [13, 16]:
        print("VISA")
    else:
        print("INVALID")


card = input("Card Number: ")
checklen(card)
if checkval(card):
    printcard(card)
else:
    print("INVALID")
