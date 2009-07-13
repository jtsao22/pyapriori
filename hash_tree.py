import apriori,sys

class Node:
    def __init__(self,parent, state,trans):              # initialize
                  #node with parent and state (0 = leaf, 1 = interior)
        self.parent = parent
        self.children = {}
        self.state = state
        self.item_lists = []
        self.item_sets = []
        self.trans_list = []
        self.depth = 1
        self.trans = trans
        if state == 0:
            self.item_lists.append(sorted(list(trans.item_set)))
            self.item_sets.append(trans.item_set)
            self.trans_list.append(trans)

    def get_parent(self):
        return self.parent

    def get_state(self):
        return self.state

    def get_children(self):
        return self.children

    def get_num_children(self):
        return len(self.children)

    def add_child(self,depth,node):
        assert(self.state == 1)
        item_list = node.item_lists[0]

        # print "item_list: ", item_list[depth-1]
        self.children[item_list[depth-1]] = node


    def add_transaction(self,transaction):
        self.item_lists.append(list(sorted(transaction.item_set)))
        self.item_sets.append(transaction.item_set)
        self.trans_list.append(transaction)

    def get_num_lists(self):
        return len(self.item_lists)


class Hash_tree:
    def __init__(self,threshold):
        self.threshold = threshold
        self.root = None
        self.cand_list_final = []
        self.L_k_set = []

    def reinitialize(self):
        self.root = None
        self.cand_list_final = []

    def add_trans(self, trans):
        if self.root == None:
            self.root = Node(None,1,trans)
            temp = Node(self.root,0,trans)
            self.root.add_child(1,temp)
        else:
            self.add_trans_recursive(self.root,\
                    sorted(list(trans.item_set)),trans,1)


    def add_trans_recursive(self, node, list1,trans,depth):
        if node.get_state() == 1:       # if its an interior node:
            # hash on depth, if found call funct again
            if list1[depth-1] in node.children.keys():
                self.add_trans_recursive(node.children[list1[depth-1]]\
                        ,list1,trans,depth + 1)
            else:          # if not found, make a new Node
                temp = Node(node,0,trans)
                node.add_child(depth,temp)
        else:               # if its a leaf node:
            node.add_transaction(trans)   # add the list to the node, and
                                        #then check threshold
            assert(len(node.trans_list[0].item_set)==
                    len(trans.item_set),node.trans_list)
            if self.check_threshold(node):
                # if past threshold, change node into interior node
              #  print "changing leaf into interior"
                node.state = 1
                assert(len(node.item_lists) ==
                        len(node.trans_list))
                for transaction in node.trans_list:
                    temp = Node(node,0,transaction)
                    self.add_trans_recursive(node,sorted(\
                            list(transaction.item_set)),\
                            transaction,depth)
                node.item_lists = []
                node.item_sets = []
                node.trans_list = []

    def check_threshold(self,node): # return true if greater than
                                    # threshold
        return node.get_num_lists() > self.threshold

    def print_all_tree(self,node):

        debug("_________________")
        if node.get_state() == 1:
            debug("in an interior node")
            for i in node.children.values():
                self.print_all_tree(i)
            debug("out of interior node")
        else:
            debug("Here's a leaf node item list: "+
                    str(node.item_lists))
            debug("Here's item set: "+ str(node.item_sets))

    def prints(self):
        if self.root != None:
            self.print_all_tree(self.root)

    def subset(self,t):
        if self.root != None:
            t_list = sorted(list(t.item_set))
            self.subset_recursive(self.root,0,t_list,t)


    def subset_recursive(self,node,num_to_hash,t_list,t):
        if node.get_parent() == None:      # if root, hash on every ite
                                            # in t
            for index,item in enumerate(t_list):
                try:
                    child = node.children[item]
                    self.subset_recursive(child,index,t_list,t)
                except KeyError:
                    continue
        else:                   # if not root, check interior or leaf
            if node.get_state() == 0: # if leaf, find ones in T
                for index,item_set in enumerate(node.item_sets):
                    if item_set.issubset(t.item_set):
                        if item_set == set(['1','3','5']):
                            debug("transaction when set is 135: ", t)

                        self.cand_list_final.append(node.trans_list[index])
            else:
                #if interior node, hash on items after
                for index,iter in enumerate(t_list[num_to_hash:\
                        (len(t_list)-(num_to_hash-1))]):
                    if iter in node.children.keys():
                        self.subset_recursive(node.children[iter],\
                            num_to_hash +1, t_list, t)

    def check_minsup(self,node,minsup):
        if node != None:
            if node.get_state() == 1:
                for i in node.children.values():
                    self.check_minsup(i,minsup)
            else:
                assert(len(node.trans_list) == \
                        len(node.item_lists))
                for trans in node.trans_list:
                    debug("c in cand_trans_list: ", trans)
                    if trans.count >= minsup:
                        self.L_k_set.append(trans)


def debug(data):
    if True:
        sys.stderr.write(str(data))
        sys.stderr.write('\n')







if __name__ == '__main__':
    #a=apriori.Transaction(set([1,3,2]))
    #b=apriori.Transaction(set([1,3,5]))
    #c=apriori.Transaction(set([1,3,4]))
    #d=apriori.Transaction(set([1,2,5]))
    #e=apriori.Transaction(set([1,2,4]))
    #f=apriori.Transaction(set([1,5,4]))
    #g=apriori.Transaction(set([3,2,5]))
    #h=apriori.Transaction(set([3,5,4]))
    #i=apriori.Transaction(set([3,2,4]))
    #j=apriori.Transaction(set([2,5,4]))
    ht = Hash_tree(3)
    #ht.add_trans(a)
    #ht.add_trans(b)
    #ht.add_trans(c)
    #ht.add_trans(d)
    #ht.add_trans(e)
    #ht.add_trans(f)
    #ht.add_trans(g)
    #ht.add_trans(h)
    #ht.add_trans(i)
    #ht.add_trans(j)
    ht.add_trans(apriori.Transaction(set([1234])))
    ht.add_trans(apriori.Transaction(set([2345])))
    ht.add_trans(apriori.Transaction(set([345])))
    ht.add_trans(apriori.Transaction(set([453])))
    ht.add_trans(apriori.Transaction(set([5342])))
    ht.add_trans(apriori.Transaction(set([53421])))
    ht.add_trans(apriori.Transaction(set([3421])))
    ht.add_trans(apriori.Transaction(set([4213])))
    ht.add_trans(apriori.Transaction(set([2135])))
    ht.add_trans(apriori.Transaction(set([1354])))
    ht.add_trans(apriori.Transaction(set([1354])))
    ht.add_trans(apriori.Transaction(set([3543])))
    ht.add_trans(apriori.Transaction(set([5431])))
    ht.add_trans(apriori.Transaction(set([45312])))
    ht.add_trans(apriori.Transaction(set([5312])))
    ht.add_trans(apriori.Transaction(set([312])))
    ht.add_trans(apriori.Transaction(set([123])))
    ht.add_trans(apriori.Transaction(set([2135])))
    ht.add_trans(apriori.Transaction(set([21354])))
    ht.add_trans(apriori.Transaction(set([1354])))
    ht.add_trans(apriori.Transaction(set([3541])))
    ht.add_trans(apriori.Transaction(set([54313])))
    ht.add_trans(apriori.Transaction(set([4312])))
    ht.add_trans(apriori.Transaction(set([3125])))
    ht.add_trans(apriori.Transaction(set([13254])))
    ht.add_trans(apriori.Transaction(set([32543])))
    ht.add_trans(apriori.Transaction(set([25431])))
    ht.add_trans(apriori.Transaction(set([54312])))
    ht.add_trans(apriori.Transaction(set([4312])))
    ht.add_trans(apriori.Transaction(set([3121])))
    ht.add_trans(apriori.Transaction(set([123])))
    ht.add_trans(apriori.Transaction(set([231])))
    ht.add_trans(apriori.Transaction(set([231])))
    ht.add_trans(apriori.Transaction(set([3124])))
    ht.add_trans(apriori.Transaction(set([12345])))
    ht.add_trans(apriori.Transaction(set([23456])))
    ht.add_trans(apriori.Transaction(set([34567])))
    ht.add_trans(apriori.Transaction(set([45678])))
    ht.add_trans(apriori.Transaction(set([56782])))
    ht.add_trans(apriori.Transaction(set([67821])))
    ht.add_trans(apriori.Transaction(set([7821])))
    ht.add_trans(apriori.Transaction(set([8214])))
    ht.add_trans(apriori.Transaction(set([214])))
    ht.add_trans(apriori.Transaction(set([142])))
    ht.add_trans(apriori.Transaction(set([142])))
    ht.add_trans(apriori.Transaction(set([423])))
    ht.add_trans(apriori.Transaction(set([234])))
    ht.add_trans(apriori.Transaction(set([2345])))
    ht.add_trans(apriori.Transaction(set([23458])))
    ht.add_trans(apriori.Transaction(set([34587])))



    ht.prints()
    f = apriori.Transaction(set([1,3,4,6,7]))
    ht.subset(f)


    print ht.cand_list_final
