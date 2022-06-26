import re
import string
import collections


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def MultiplicationTable(v):
    v = int(v)
    for i in range (1, 11):
        print(v, 'X', i, '=', (v * i))
    return 0

def doublevalue(v):
    return v * 2

def CountAll():
    # Open file and store the values as a dictionary
    with open("CS210_Project_Three_Input_File.txt") as fp:
        dictionary = collections.Counter(line.strip() for line in fp)

    # For every key, print the item and amount sold
    for key in dictionary:
        print('%s %d' % (key, dictionary[key]))

def CountNumInstances(v):

    # Convert user input to lowercase
    v = v.capitalize()

    # Open file 
    with open("CS210_Project_Three_Input_File.txt") as fp:
        f = fp.read()
        instances = f.count(v)
        return instances

    # Declare variable to store how many times search word has been found
    #wordCount = 0

    # Check each line of input
    #for line in text:
        #line = line.strip()  # remove unwarranted spaces and n/l characters

        #word = line.lower()  # Convert characters to lowercase

        # Check if found word is equal to user input
        #if word == userInput:
            # Increment number of times the word appears
            #wordCount += 1

    # return the number of times the search word has been found
    #return wordCount

    # Close the file
    text.close()


def ItemWriteFile():
    # Open both the read and write files
    with open('frequency.dat', "w") as wp:
        with open('CS210_Project_Three_Input_File.txt') as fp:
            frequency = collections.Counter(line.strip() for line in fp)

        for key in frequency:
            wp.write('%s %d\n' % (key, frequency[key]))


