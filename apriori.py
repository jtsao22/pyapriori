#!/usr/bin/python

# Create Transaction class.
# Transactions are sets of items

import string,sys

class Transaction:
    item_set = []
    def __init__(self,item_set):
        self.item_set = item_set
    def subset(self, set_looking_for):
        print 'This will be implemented later'


def parser():       #Used to get information and put the data into
                    # transactions

#Check for correct amount of parameters
    if len(sys.argv)!=2:
        print 'Usage: count_digits [FILE]'
        sys.exit(0)

    file=open(sys.argv[1],'r')                  # Open the file

    parse_list = []      # create a list that parses the items
    transaction_list = []    # create a list that holds the transactions


    for line in file.readlines():
        if line != '\n':
            item_read = int(line)
            parse_list.append(item_read)
        else:
            transaction_list.append(parse_list)
            del parse_list[:]
    print parse_list

#item_read = file.readline()          # Read first item
#    item_read = item_read.strip("\n")   # strip the newline at the end
#
#    while item_read != "":
#
#        while item_read != "\n" or item_read != "":    # Loop through each item until
#                                              # newline or end of file
#            item_number = int(item_read)
#            #print item_read
#            print item_number
#            print "____________________________________________"
#            item_read = file.readline()
#            item_read = item_read.strip("\n")
#            #print "after: "
            #print item_read
            #print "88888888888"
            #if item_read == "\n\n":
            #   print "yo"


parser()
