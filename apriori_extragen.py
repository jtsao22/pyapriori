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
        self.item_list = list(sorted(item_set))
        self.count = 0                      # initialize its count to zero

    def __cmp__(self, other):
        return cmp(self.item_list,other.item_list)



    def __repr__(self):
        out_string = ""
        out_string += str(self.item_list)
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


    # create a list that has parse_lists as its elements
    list_of_parses = []

    # read in the line from file
    line = file.readline()

    token_list = line.split()
    parse_list = set([])      # create a list that parses the items

    iter = 0
    i = 0

    # create a hash dictionary to map hashed number to functions names
    hash_dict = {}

    if d_wind == 0:
        for start_t in token_list[:-w_size + 1]:
            for token in token_list[i:i+w_size]:
                parse_list.add(hash(token))
                hash_dict[hash(token)] = token
                if iter < w_size -1:
                    iter += 1
                else:
                    list_of_parses.append(sorted(list(parse_list)))
                    parse_list = set([])
                    iter = 0
            i += 1
    else:
        for index,start_t in enumerate(token_list):
            for ind, token in enumerate(token_list[index:]):
                if token == start_t and ind != 0:
                    parse_list = set([])
                    break
                else:
                    parse_list.add(hash(token))
                    hash_dict[hash(token)] = token

            if parse_list != set([]) or token != start_t:
                parse_list = set([])

    list_of_parses.sort()

    total_window_size = 0
    max_window_size = 0

    for parse_list in list_of_parses:
        total_window_size += len(parse_list)
        if max_window_size < len(parse_list):
            max_window_size = len(parse_list)
        trans = Transaction(parse_list)
        transaction_list.append(trans)

    print "average_window_size: "
    print total_window_size/len(transaction_list)

    print "max window size: "
    print max_window_size


    return transaction_list,hash_dict

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
        temp = Transaction([item])
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

def generate(f_item_list,minsup,ht): # used to find the candidate
                                       # transaction set Ck

    f_item_list.sort()
    debuga("f_item_list: " + str(f_item_list))
    assert(check_item_last(Transaction(set([1,3,4])),Transaction(set([1,2,3])))==[])
    assert(check_item_last(Transaction(set([1,2,3])),Transaction(set([1,2,4])))==
            [1,2,3,4])

    # Join Step of Generate function
    cand_trans_list = []    # initialize the candidate transaction list
                            # that holds the candidate item lists

    index = 1

    for trans1 in f_item_list:
        for trans2 in f_item_list[index:]:
            check = check_item_last(trans1,trans2)
            if check != []:
                cand_trans_list.append(check)
        index += 1


    debuga("cand_trans_list: " + str(cand_trans_list))

    # Prune Step of Generate function
    subsets = []

    # Removed list keeps track of the item lists that were already
    # removed
    removed_list = []
    checked_sets = []

    for item_list in cand_trans_list:
        temp_list = []
        subsets = []
        debuga("item_list: " + str(item_list))
        get_subsets_of(item_list,temp_list,subsets)



        debuga("subsets: " + str(subsets))
        for iter in subsets:
            if iter not in checked_sets:
                checked_sets.append(iter)
                inside = 0
                debuga("iter: " + str(iter))

                for item in f_item_list:
                    debuga("item.item_set: " + str(item.item_set))
                    if set(iter).issubset(item.item_set):
                        inside = 1
                        break


                if inside == 0:
                    if item_list not in removed_list:
                        cand_trans_list.remove(item_list)
                        removed_list.append(item_list)


    debuga("cand_trans_list: " + str(cand_trans_list))


    for item_list in cand_trans_list:
        trans = Transaction(set(item_list))
        ht.add_trans(trans)


    return cand_trans_list

############################################################################
#                              Get subsets of Function                     #
############################################################################

def get_subsets_of(item_list,temp_list,return_list):
    #    for item in get_subset_recursive(len(item_list),size):
    #    return_list.append(list(item_list[i] for i in item))
    #    yield list(item[i] for i in item)

    for i in range(len(item_list)):
        temp_list.extend(item_list[0:i])
        temp_list.extend(item_list[i+1:])
        return_list.append(temp_list)
        temp_list = []


############################################################################
#                               Check item last                            #
############################################################################

# This function checks if all the items in transaction 1 are the same as
# transaction 2 except for the last element of both


def check_item_last(trans1, trans2):
    if trans1 != trans2:
        for index in range(len(trans1.item_list)):
            if trans1.item_list[index] != trans2.item_list[index]\
                    and index != len(trans1.item_list)-1:
                return []

        temp_list = trans1.item_list[:]
        temp_list.append(trans2.item_list[len(trans2.item_list) -1])
        return temp_list
    else:
        return []


############################################################################
#                               Apriori                                    #
############################################################################


def apriori(minsup, w_size,file, d_window,node_threshold):

    # minsup is the minimum frequency support, w_size is the window
    # size, file is the file taken in as input, d_window specifies if
    # the dynamic windowing option should be used or not
    # Get the transaction_list T using the parser function (read from
    # file)
    transaction_list,hash_dict =  parser(w_size,file,d_window)

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
        cand_trans_list = generate(L_kminusone_set,minsup,ht)


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

        if ht.L_k_set != []:
            # add the set to the all_Lk_dict if its not an empty set
            all_Lk_dict[k] = ht.L_k_set

        # increment to the next iteration

        L_kminusone_set = ht.L_k_set
        k += 1




    # Send the data to an output file showing each set on a line. Sets
    # are shown from the most items to the least items
    outputfile = open ('outputfile.txt', 'w')
    for k in sorted(all_Lk_dict.keys(),reverse=True):
        for i in all_Lk_dict[k]:
            temp_list = []
            for item in sorted(i.item_set):
                temp_list.append(hash_dict[item])
            output_string = str(temp_list) + "\n occurs\
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

