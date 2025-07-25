# Readability, just translate from .c coded before


def countSentences(string):
    sentence = 0

    for _ in range(len(string)):
        temp = string[_]
        if temp in ['.', '?', '!']:
            sentence = sentence + 1
    return sentence


def countWords(string):
    words = 0

    for _ in range(len(string)):
        temp = string[_]
        if temp == ' ':
            words = words + 1
    return words + 1


def countLetters(string):
    letters = 0

    for _ in range(len(string)):
        if string[_].isalpha():
            letters = letters + 1
    return letters


def countScore(x, y):
    score = (0.0588 * x) - (0.296 * y) - 15.8
    return score


def printAnswer(x):
    if x < 1:
        print("Before Grade 1")
    elif x >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {x}")


text = input("Text: ")
words = countWords(text)
sentences = countSentences(text)
letters = countLetters(text)

x = (letters/words)*100
y = (sentences/words)*100

score = countScore(x, y)

printAnswer(round(score))
