from cs50 import get_string

text = get_string("Text: ")
letters = 0
for letter in text:
    if letter.isalnum():
        letters += 1
words = len(text.split(" "))
text = text.replace("?", ".").replace("!", ".")
sentences = len(text.split(".")) - 1
l = letters / words * 100.0
s = sentences / words * 100.0
c_l_index = 0.0588 * l - 0.296 * s - 15.8
if c_l_index < 1:
    print("Before Grade 1")
elif c_l_index > 15:
    print("Grade 16+")
else:
    print(f"Grade {c_l_index:.0f}")
