#!/usr/bin/python

import getopt
import string,sys
import hash_tree

#############################################################################
#                           Transaction Class                               #
#############################################################################

# Transactions are sets of items
class Transaction:

    def __init__(self,item_set):    # function to initialize a
                                    #Transaction
        self.item_set = item_set
        self.count = 0                       # initialize its count to zero

    def __repr__(self):
        out_string = ""
        out_string += str(self.item_set)
        out_string += " "
        out_string += str(self.count)
        return out_string

    def subset(self, transaction):
        # check if transaction's item_set is a subset of this
        # transaction's item_set
        return transaction.item_set.issubset(self.item_set)


############################################################################
#                       Parser Function                                    #
############################################################################

def parser(w_size,file_name,d_wind):   # Used to get information from file
                                        #and put the data into transactions

    file=open(file_name,'r')                  # Open the file

    transaction_list = []    # create a list that holds the transactions


    # read in the line from file
    line = file.readline()

    token_list = line.split()
    parse_list = set([])      # create a list that parses the items

    iter = 0
    i = 0

    if d_wind == 0:
        for start_t in token_list[:-w_size + 1]:
            for token in token_list[i:i+w_size]:
                parse_list.add(token)
                if iter < w_size -1:
                    iter += 1
                else:
                    trans = Transaction(parse_list)
                    transaction_list.append(trans)
                    parse_list = set([])
                    iter = 0
            i += 1
    else:
        for index,start_t in enumerate(token_list):
            for ind, token in enumerate(token_list[index:]):
                if token == start_t and ind != 0:
                    trans = Transaction(parse_list)
                    transaction_list.append(trans)
                    parse_list = set([])
                    break
                else:
                    parse_list.add(token)
            if parse_list != set([]) or token != start_t:
                trans = Transaction(parse_list)
                transaction_list.append(trans)
                parse_list = set([])

    total_window_size = 0
    max_window_size = 0
    for trans in transaction_list:
        total_window_size += len(trans.item_set)
        if max_window_size < len(trans.item_set):
            max_window_size = len(trans.item_set)
    print "average_window_size: "
    print total_window_size/len(transaction_list)

    print "max window size: "
    print  max_window_size

    return transaction_list

#############################################################################
#                        Dynamic Search Window Function                     #
#############################################################################

def dyn_search_window(item,token_list):
    transaction_list = []
    parse_list = set([])

    counter = 0
    # parse through token_list until the item is encountered
    for iter in token_list:
        if iter == item:
            counter += 1
            parse_list.add(item)
            break
        counter += 1
    # go through rest of list and add a transaction everytime the item
    # is repeated
    for iter in token_list[counter:]:
        parse_list.add(iter)
        if iter == item:
            trans = Transaction(parse_list)
            transaction_list.append(trans)
            parse_list = set([item])

    # add last transaction if token_list didn't have an ending token
    # corresponding to item
    if parse_list != set([]):
        trans = Transaction(parse_list)
        transaction_list.append(trans)
    return transaction_list
#############################################################################
#                           One Item Sets Function                          #
#############################################################################

def one_item_sets(T, minsup): # this function gets L_1 using the
                              # transaction list and minsup

    # initialize item list to empty set
    item_list = []

    all_transactions_list = []

    for transaction in T:
        #all_transactions_set.update(transaction.item_set)
        all_transactions_list += transaction.item_set

    all_transactions_set = set(all_transactions_list)


    for item in all_transactions_set:
        temp = Transaction(set([item]))
        temp.count = all_transactions_list.count(item)

        item_list.append(temp)


    # call frequency_qualifier to remove items whose counts are < minsup
    item_dict = frequency_qualifier(item_list,minsup)

    return item_dict


#############################################################################
#                           Frequency Qualifier Function                    #
#############################################################################

def frequency_qualifier(item_list, minsup): # functions removes items
                                    # whose counts are less than minsup

    # create the item list with only frequent counts
    f_item_list = []

    # for each item, add the item to the frequent item dictionary if
    # the item's count is greater than or equal to minsup
    for item in item_list:
        if item.count >= minsup:
            f_item_list.append(item)

    # return the item dictionary with frequent counts
    return f_item_list


############################################################################
#                           Generate Function                              #
############################################################################

def generate(f_item_list,L_1, minsup,ht): # used to find the candidate
                                       # transaction set Ck

    cand_trans_set = set([])    # initialize the candidate transaction list
                            # that holds the candidate item sets

    for transaction1 in f_item_list:
        cand_item_set = set([])
        for transaction2 in L_1:
            # for each item or set, pair it with a item that is not the
            # item or in the set (last part implement later)
            # put them all in a list called cand_item_set and add the
            # cand_item_set to the cand_trans_list

            #if not transaction2.item_set.issubset(transaction1.item_set):
            add_numbers_set = transaction2.item_set -\
                    transaction1.item_set
            for num in add_numbers_set:
                cand_item_set = transaction1.item_set.copy()
                cand_item_set.add(num)
                trans = Transaction(cand_item_set)
                already_in = 0      # use already_in to say if
                       #the transaction is already in cand_trans_set
                for trans_already in cand_trans_set:
                    if trans_already.item_set == trans.item_set:
                        already_in = 1 # set already_in to true
                                            # if it is already in
                                            # the set
                        break
                if already_in == 0:
                    cand_trans_set.add(trans)
                    ht.add_trans(trans)


    return cand_trans_set


############################################################################
#                               Subset Function                            #
############################################################################

 # function takes in candidate transaction list and a transaction
 # and returns the final candidate transaction list, which is the list with
 # candidates found in T only
def Subset(cand_trans_list, trans_looking_for):

    cand_list_final =[]   # initialize the final candidate list
                               # (with candidates found in T only)
    # Look through the trans_looking_for in the cand_trans_list
    #for transaction in cand_trans_list:
    #    if trans_looking_for.subset(transaction):
    #        cand_list_final.append(transaction)

    for transaction in cand_trans_list:
        if transaction.item_set.issubset(trans_looking_for.item_set):
            cand_list_final.append(transaction)

    return cand_list_final



############################################################################
#                               Apriori                                    #
############################################################################


def apriori(minsup, w_size,file, d_window,node_threshold):

    # minsup is the minimum frequency support, w_size is the window
    # size, file is the file taken in as input, d_window specifies if
    # the dynamic windowing option should be used or not
    # Get the transaction_list T using the parser function (read from
    # file)
    transaction_list =  parser(w_size,file,d_window)

    # Get L_1, the large 1-itemsets that appear more than minsup
    L_1 = one_item_sets(transaction_list,minsup)
    L_kminusone_set = L_1

    # all_Lk_dict holds all frequent itemsets with item_count mapped to
    # the itemsets
    all_Lk_dict = {}

    # initialize k, the Candidate Transaction List, Ck, and the
    # Final Candidate Transaction List, Ct
    k = 2
    cand_trans_list = []
    cand_list_final = set([])

    ht = hash_tree.Hash_tree(node_threshold)

    all_Lk_dict[1] = L_1

    while L_kminusone_set != []:
        # call generate to make the candidate transaction list

        ht.reinitialize()
        cand_trans_list = generate(L_kminusone_set,L_1,minsup,ht)


        for trans in transaction_list:
            # call Subset to form the final candidate transaction list
            #cand_list_final = Subset(cand_trans_list,trans)
            ht.cand_list_final = []
            ht.subset(trans)
            debuga(str(len(ht.cand_list_final)))

            for candidates in ht.cand_list_final:
                # increment the count for candidates in the final list
                candidates.count += 1


        ht.L_k_set = []
        # create the Lk set, which is made up of candidates from the
        # candidate transaction list that have counts >= minsup
        #for c in cand_trans_list:
        #    print "c in cand_trans_list: ", c
        #    if c.count >= minsup:
        #        L_k_set.append(c)

        ht.check_minsup(ht.root,minsup)
        #L_k_set = ht.L_k_set

        debuga("L_k_set: ")
        debuga(ht.L_k_set)
        if ht.L_k_set != []:
            # add the set to the all_Lk_dict if its not an empty set
            all_Lk_dict[k] = ht.L_k_set

        # increment to the next iteration

        L_kminusone_set = ht.L_k_set
        debuga("length of L_kminusone_set: " +
                str(len(L_kminusone_set)))
        debuga("L_kminusone_set: " + str(L_kminusone_set))
        debuga("cand_list_Final: " + str(ht.cand_list_final))
        k += 1
        debuga("___________________new iteration_____________")




    # Send the data to an output file showing each set on a line. Sets
    # are shown from the most items to the least items
    outputfile = open ('outputfile.txt', 'w')
    for k in sorted(all_Lk_dict.keys(),reverse=True):
        for i in all_Lk_dict[k]:
            output_string = str(sorted(i.item_set)) + "\n occurs\
                    this many times: " + str(i.count)
            outputfile.write(output_string)
            outputfile.write('\n')

###########################################################################
#                           Debug Function                                #
###########################################################################

def debuga(data):
    if False:
#        sys.stderr.write(str(data))
#        sys.stderr.write('\n')
        print data

def debuga2(data):
    if True:
        print data





############################################################################
#                               Main                                       #
############################################################################

# Call Apriori Algorithm
if __name__ == '__main__':

    try:
        opts,args = getopt.getopt(sys.argv[2:], "d")
    except getopt.GetoptError, err:
        debuga(str(err))
        sys.exit(2)

    dynamic_window = 0
    for o,a in opts:
        if o == "-d":
            dynamic_window = 1
        else:
            print "Unhandled option"

    apriori(3,5,sys.argv[1],dynamic_window,3)

