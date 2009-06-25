#!/usr/bin/python


import string,sys

#############################################################################
#                           Transaction Class                               #
#############################################################################

# Transactions are sets of items
class Transaction:
    item_set = set([])              # used to hold the set of items
    def __init__(self,item_set):    # function to initialize a
                                    #Transaction
        self.item_set = item_set

    def subset(self, set_looking_for):
        counter = 0                 # initialize counter to zero
        print type(set_looking_for.item_set)
        if set_looking_for.item_set.issubset(self.item_set):
                print 'its a subset!'

############################################################################
#                       Parser Function                                    #
############################################################################

def parser():       #Used to get information and put the data into
                    # transactions

#Check for correct amount of parameters
    if len(sys.argv)!=2:
        print 'Usage: apriori.py [FILE]'
        sys.exit(0)

    file=open(sys.argv[1],'r')                  # Open the file

    parse_list = set([])      # create a list that parses the items
    transaction_list = []    # create a list that holds the transactions

     # for each line in file:
    for line in file.readlines():
        if line == '\n':
            if parse_list != ([]):
                # if line is newline and parse_list is empty, make a Transaction
                # that is passed in the parse_list and put the Transactions in
                # the transaction_list
                trans = Transaction(parse_list)
                transaction_list.append(trans)
                parse_list = set([])
        else:
            # if line is not newline, change the line into an integer
            # and add it to the parse_list

            print type(parse_list)
            item_read = int(line)
            parse_list.add(item_read)

    # add the last Transaction to the transaction list (since for
    # loop exits once it sees an end of file)
    trans = Transaction(parse_list)
    transaction_list.append(trans)

    return transaction_list


#############################################################################
#                           One Item Sets Function                          #
#############################################################################

def one_item_sets(T, minsup):

    # initialize item dictionary to empty set
    item_dict = {}

    for transaction in T:
        for item in transaction.item_set:
            # Increment the counts of each number 0 to 9 by looking
            # through each item of each transaction in the
            # transaction_list T
            if item in item_dict:
                item_dict[item] += 1
            else:
                item_dict[item] = 1

    # call frequency_qualifier to remove items whose counts are < minsup
    item_dict = frequency_qualifier(item_dict,minsup)

    #for num in item_dict:
    #    print '%i %i' % (num,item_dict[num])


    return item_dict


#############################################################################
#                           Frequency Qualifier Function                    #
#############################################################################

def frequency_qualifier(item_dict, minsup):

    # create the item dictionary with only frequent counts
    f_item_dict = {}


    # for each item, add the item to the frequent item dictionary if
    # the item's count is greater than or equal to minsup
    for item in item_dict:
        if item_dict[item] >= minsup:
            f_item_dict[item] = item_dict[item]

    # return the item dictionary with frequent counts
    return f_item_dict


############################################################################
#                           Generate Function                              #
############################################################################

def generate(T,f_item_dict):

    cand_item_list = set([])      # initialize candidate item set
    cand_trans_set = set([])    # initialize the candidate transaction list
                            # that holds the candidate item sets

    for itemset_1 in f_item_dict:
        cand_item_list = set([])
        for i in f_item_dict:
            # for each item or set, pair it with a item that is not the
            # item or in the set (last part implement later)
            # put them all in a list called cand_item_set and add the
            # cand_item_set to the cand_trans_list, which holds all the
            # cand_item_sets
            if i != itemset_1:
                if i > itemset_1:
                    cand_item_list.add(itemset_1)
                    cand_item_list.add(i)
                    trans = Transaction(cand_item_list)
                    cand_trans_set.add(trans)
    #                print cand_item_set
                    cand_item_list = set([])

    #for num in cand_trans_set:
    #    print num.item_set

    return cand_trans_set

############################################################################
#                               Main                                       #
############################################################################

transaction_list =  parser()
#print transaction_list[0].item_set
L_kminusone_set = one_item_sets(transaction_list,2)      #
k = 2
cand_trans_list = []

#while L_kminusone_set != {}:
cand_trans_list = generate(transaction_list,L_kminusone_set)
for trans in transaction_list:
    for ctrans in cand_trans_list:
        trans.subset(ctrans)
