#!/usr/bin/python


import string,sys

#############################################################################
#                           Transaction Class                               #
#############################################################################

# Transactions are sets of items
class Transaction:
    item_set = set([])              # used to hold the set of items

    count = 0                       # initialize its count to zero

    def __init__(self,item_set):    # function to initialize a
                                    #Transaction
        self.item_set = item_set

    def subset(self, transaction):
        # check if transaction's item_set is a subset of this
        # transaction's item_set
        return transaction.item_set.issubset(self.item_set)









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

   # for num in cand_trans_set:
   #     print num.item_set

    return cand_trans_set


############################################################################
#                               Subset Function                            #
############################################################################
 # function takes in candidate transaction list and a transaction

def Subset(cand_trans_list, trans_looking_for):

    cand_list_final = set([])   # initialize the final candidate list
                               # (with candidates found in T only)
    # Look through the trans_looking_for in the cand_trans_list
    for transaction in cand_trans_list:
        if trans_looking_for.subset(transaction):
            # if its found, check if its already in the final candidate
            # list.
           # if transaction not in cand_list_final:
                # if its not already there, add it to the final
                # candidate list
            cand_list_final.add(transaction)
    return cand_list_final



############################################################################
#                               Main                                       #
############################################################################

minsup = 3
transaction_list =  parser()
#print transaction_list[0].item_set
L_kminusone_set = one_item_sets(transaction_list,minsup)      #
k = 2
cand_trans_list = []
cand_list_final = set([])

while L_kminusone_set != []:
    cand_trans_list = generate(transaction_list,L_kminusone_set)
    for trans in transaction_list:
        cand_list_final = Subset(cand_trans_list,trans)
        for candidates in cand_list_final:
            candidates.count += 1
    L_k_set = []
    for c in cand_trans_list:
        if c.count >= minsup:
            L_k_set.append(c)
    #for l in L_k_set:
    #    print l.item_set

    L_kminusone_set = L_k_set

print "__________________________________________________"
print L_k_set

#for candidates in cand_list_final:
#    print candidates.item_set , " has this count: " ,
#    print candidates.count
#    print "______________________________________________________"
#print '____________________________________________________________________'
#print cand_list_final
#for thing in cand_list_final:
#    print 'hi'
#    print thing.item_set
