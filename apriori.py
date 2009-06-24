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

     # for each line in file:
    for line in file.readlines():
        if line == '\n':
            if parse_list != []:
                # if line is newline and parse_list is empty, make a Transaction
                # that is passed in the parse_list and put the Transactions in
                # the transaction_list
                trans = Transaction(parse_list)
                transaction_list.append(trans)
                parse_list = []
        else:
            # if line is not newline, change the line into an integer
            # and add it to the parse_list
            item_read = int(line)
            parse_list.append(item_read)

    # add the last Transaction to the transaction list (since for
    # loop exits once it sees an end of file)
    trans = Transaction(parse_list)
    transaction_list.append(trans)


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
