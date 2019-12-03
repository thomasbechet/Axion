#Simple python script to change lower camel case strings in a file to snake case
import sys
import re

#detect if the string is lower camel case
def is_camel(word):
    bol = re.search('\w([a-z][A-Z])', word)
    return bol

#convert string to snake case
def convert(word):
    word = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', word)
    word = re.sub('([a-z0-9])([A-Z])', r'\1_\2', word).lower()
    return word

FILE_NAME = sys.argv[1]
OLD_FILE = open(FILE_NAME).read()
NEW_FILE = open(FILE_NAME, 'w')
for w in OLD_FILE.split():
    if is_camel(w) != None:
        OLD_FILE = OLD_FILE.replace(w, convert(w))
NEW_FILE.write(OLD_FILE)

print("Convention changed to snake case successfully!")