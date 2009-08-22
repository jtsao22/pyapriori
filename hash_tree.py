import apriori_extragen,sys

class Node:
    def __init__(self,parent, state,depth):              # initialize
                  #node with parent and state (0 = leaf, 1 = interior)
        self.parent = parent
        self.children = {}
        self.state = state
        self.item_lists = []
        self.item_sets = []
        self.trans_list = []
        self.depth = depth

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
        self.children[item_list[depth]] = node

    def remove_child(self,node):
        del self.children[node]

    def add_transaction(self,transaction):
        self.item_lists.append(list(sorted(transaction.item_set)))
        self.item_sets.append(transaction.item_set)
        self.trans_list.append(transaction)


    def get_num_lists(self):
        return len(self.item_lists)

    # update all three lists to reflect the change of one item set
    def append_itemset(self,item_set,trans):
        self.item_sets.append(item_set)
        self.item_lists.append(sorted(list(item_set)))
        self.trans_list.append(trans)

    # make node into an interior node
    def _make_interior(self):
        debug("leaf-> into interior")
        self.state = 1
        self.item_lists = []
        self.item_sets = []
        self.trans_list = []


    def expand_node(self,threshold):
        if len(self.item_lists) <= threshold:
            return 0;

        else:
            debug("____new call to expand_node______")
            debug("self.item_lists: " + str(self.item_lists))
            for index,itemset in enumerate(self.item_lists):
                debug("self.depth: " + str(self.depth))
                debug("itemset: " + str(itemset))
                key = itemset[self.depth]
                child = self.children.setdefault(key,\
                        Node(self,0,self.depth +1))
                child.add_transaction(self.trans_list[index])
            self._make_interior()

            [child.expand_node(threshold) for child in self.children.values()]
            return 1;




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
        debug("trans to be added: " +  str(trans.item_set))
        if self.root == None:
            self.root = Node(None,0,0)
            self.root.add_transaction(trans)
            debug(str(trans.item_set) + " put at depth zero ")

        else:
            self.add_trans_recursive(self.root,\
                    sorted(list(trans.item_set)),trans,0)

    def add_trans_recursive(self, node, list1,trans,depth):
        if node.get_state() == 1:       # if its an interior node:
            # hash on depth, if found call funct again
            debug("looking at interior")
            if list1[depth] in node.children.keys():
                self.add_trans_recursive(node.children[list1[depth]]\
                        ,list1,trans,depth + 1)
            else:          # if not found, make a new Node
                temp = Node(node,0,depth+1)
                temp.add_transaction(trans)
                debug(str(trans.item_set) + " put at depth: " +\
                        str(depth))
                node.add_child(depth,temp)
        else:               # if its a leaf node:
            debug("looking at leaf at depth: " + str(depth))

            node.add_transaction(trans)   # add the list to the node, and
                                            #then check threshold
            assert(len(node.trans_list[0].item_set)==
                    len(trans.item_set),node.trans_list)
            node.expand_node(self.threshold)




    def check_threshold(self,node): # return true if greater than
                                    # threshold
        return node.get_num_lists() > self.threshold

    def print_all_tree(self,node):

        debug("_________________")
        if node.get_state() == 1:
            debug1("in an interior node")
            for i in node.children.values():
                self.print_all_tree(i)
            debug1("out of interior node")
        else:
            debug1("Here's a leaf node item list: "+
                    str(node.item_lists))
            debug1("Here's item set: "+ str(node.item_sets))

    def prints(self):
        if self.root != None:
            self.print_all_tree(self.root)

    def subset(self,t):
        debug1("dealing with this t: " + str(t))
        if self.root != None:
            t_list = sorted(list(t.item_set))
            self.subset_recursive(self.root,0,t_list,t)
            debug1("DONE WITH SUBSET FUNCTION")


    def subset_recursive(self,node,num_to_hash,t_list,t):
        if node.get_parent() == None:      # if root, hash on every item
                                            # in t
            if node.get_state() == 1:
                for item in t_list:
                    if item in node.children.keys():
                        child = node.children[item]
                        debug1("@ root: " + str(item))
                        self.subset_recursive(child,num_to_hash+1,t_list,t)
            else:
                debug1("t.item_set: " + str(t.item_set))
                for index,item_set in enumerate(node.item_sets):
                    debug1("item_set: " + str(item_set))

                    if item_set.issubset(t.item_set):
                        debug1(str(node.trans_list[index])+ " appended")
                        self.cand_list_final.append(node.trans_list[index])



        else:                   # if not root, check interior or leaf
            if node.get_state() == 0: # if leaf, find ones in T
                debug1("t.item_set: " + str(t.item_set))
                for index,item_set in enumerate(node.item_sets):
                    debug1("item_set: " + str(item_set))

                    if item_set.issubset(t.item_set):
                        debug1(str(node.trans_list[index])+ " appended")
                        self.cand_list_final.append(node.trans_list[index])
            else:
                #if interior node, hash on items after
                debug1("in interior node")
                for index,iter in enumerate(t_list[num_to_hash:\
                        len(t_list)]):
                    debug1("iter: " + str(iter))
                    if iter in node.children.keys():
                        debug1("iter: " + str(iter) + "; num_to_hash: "\
                                + str(num_to_hash))
                        self.subset_recursive(node.children[iter],\
                            index+num_to_hash+1, t_list, t)
                        debug1("out of interior node")

    def check_minsup(self,node,minsup):
        if node != None:
            if node.get_state() == 1:
                for i in node.children.values():
                    self.check_minsup(i,minsup)
            else:
                assert(len(node.trans_list) == \
                        len(node.item_lists))
                for trans in node.trans_list:
                    debug("c in cand_trans_list: " + str(trans))
                    if trans.count >= minsup:
                        self.L_k_set.append(trans)


def debug(data):
    if False:
        #sys.stderr.write(str(data))
       # sys.stderr.write('\n')

        print data

def debug1(data):
    if False:
        print data




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
    #ht.add_trans(apriori.Transaction(set([1,2,3])))
    #ht.add_trans(apriori.Transaction(set([2,1,4])))
    #ht.add_trans(apriori.Transaction(set([1,2,5])))
    #ht.add_trans(apriori.Transaction(set([1,2,6])))
    #ht.add_trans(apriori.Transaction(set([2,1,5])))
    #ht.add_trans(apriori.Transaction(set([1,3,6])))
    #ht.add_trans(apriori.Transaction(set([3,2,6])))
    #ht.add_trans(apriori.Transaction(set([1,6,5])))
    #ht.add_trans(apriori.Transaction(set([1,2,4])))
    #ht.add_trans(apriori.Transaction(set([1,2,5])))
    #ht.add_trans(apriori.Transaction(set([1,2,6])))
    #ht.add_trans(apriori.Transaction(set([3,1,7])))
    #ht.add_trans(apriori.Transaction(set([1,3,2,5,4])))
    #ht.add_trans(apriori.Transaction(set([3,2,5,4,3])))
    #ht.add_trans(apriori.Transaction(set([2,5,4,3,1])))
    #ht.add_trans(apriori.Transaction(set([5,4,3,1,2])))
    #ht.add_trans(apriori.Transaction(set([4,3,1,2])))
    #ht.add_trans(apriori.Transaction(set([3,1,2,1])))
    #ht.add_trans(apriori.Transaction(set([1,2,3])))
    #ht.add_trans(apriori.Transaction(set([2,3,1])))
    #ht.add_trans(apriori.Transaction(set([2,3,1])))
    #ht.add_trans(apriori.Transaction(set([3,1,2,4])))
    #ht.add_trans(apriori.Transaction(set([1,2,3,4,5])))
    #ht.add_trans(apriori.Transaction(set([2,3,4,5,6])))
    #ht.add_trans(apriori.Transaction(set([3,4,5,6,7])))
    #ht.add_trans(apriori.Transaction(set([4,5,6,7,8])))
    #ht.add_trans(apriori.Transaction(set([5,6,7,8,2])))
    #ht.add_trans(apriori.Transaction(set([6,7,8,2,1])))
    #ht.add_trans(apriori.Transaction(set([7,8,2,1])))
    #ht.add_trans(apriori.Transaction(set([8,2,1,4])))
    #ht.add_trans(apriori.Transaction(set([2,1,4])))
    #ht.add_trans(apriori.Transaction(set([1,4,2])))
    #ht.add_trans(apriori.Transaction(set([1,4,2])))
    #ht.add_trans(apriori.Transaction(set([4,2,3])))
    #ht.add_trans(apriori.Transaction(set([2,3,4])))
    #ht.add_trans(apriori.Transaction(set([2,3,4,5])))
    #ht.add_trans(apriori.Transaction(set([2,3,4,5,8])))
    #ht.add_trans(apriori.Transaction(set([3,4,5,8,7])))
    ht.add_trans(apriori.Transaction(set([2, 5, 6])))
    ht.add_trans(apriori.Transaction(set([2, 4, 7])))
    ht.add_trans(apriori.Transaction(set([9, 3, 2])))
    ht.add_trans(apriori.Transaction(set([9, 8, 7])))
    ht.add_trans(apriori.Transaction(set([1, 4, 7])))
    ht.add_trans(apriori.Transaction(set([9, 3, 6])))
    ht.add_trans(apriori.Transaction(set([1, 3, 5])))
    ht.add_trans(apriori.Transaction(set([9, 2, 4])))
    ht.add_trans(apriori.Transaction(set([1, 8, 4])))
    ht.add_trans(apriori.Transaction(set([9, 8, 2])))
    ht.add_trans(apriori.Transaction(set([2, 5, 4])))
    ht.add_trans(apriori.Transaction(set([8, 2, 5])))
    ht.add_trans(apriori.Transaction(set([2, 7, 6])))
    ht.add_trans(apriori.Transaction(set([8, 5, 6])))
    ht.add_trans(apriori.Transaction(set([1, 8, 3])))
    ht.add_trans(apriori.Transaction(set([3, 7, 6])))
    ht.add_trans(apriori.Transaction(set([1, 2, 5])))
    ht.add_trans(apriori.Transaction(set([9, 4, 6])))
    ht.add_trans(apriori.Transaction(set([1, 2, 4])))
    ht.add_trans(apriori.Transaction(set([3, 5, 4])))
    ht.add_trans(apriori.Transaction(set([3, 2, 6])))
    ht.add_trans(apriori.Transaction(set([2, 5, 7])))
    ht.add_trans(apriori.Transaction(set([8, 4, 6])))
    ht.add_trans(apriori.Transaction(set([1, 3, 7])))
    ht.add_trans(apriori.Transaction(set([1, 9, 7])))
    ht.add_trans(apriori.Transaction(set([8, 2, 6])))
    ht.add_trans(apriori.Transaction(set([1, 3, 2])))
    ht.add_trans(apriori.Transaction(set([3, 5, 7])))
    ht.add_trans(apriori.Transaction(set([8, 3, 4])))
    ht.add_trans(apriori.Transaction(set([9, 2, 7])))
    ht.add_trans(apriori.Transaction(set([1, 8, 2])))
    ht.add_trans(apriori.Transaction(set([1, 9, 3])))
    ht.add_trans(apriori.Transaction(set([1, 9, 8])))
    ht.add_trans(apriori.Transaction(set([8, 3, 7])))
    ht.add_trans(apriori.Transaction(set([9, 7, 6])))
    ht.add_trans(apriori.Transaction(set([8, 3, 6])))
    ht.add_trans(apriori.Transaction(set([1, 5, 4])))
    ht.add_trans(apriori.Transaction(set([1, 8, 6])))
    ht.add_trans(apriori.Transaction(set([5, 4, 6])))
    ht.add_trans(apriori.Transaction(set([1, 9, 6])))
    ht.add_trans(apriori.Transaction(set([8, 2, 7])))
    ht.add_trans(apriori.Transaction(set([3, 2, 7])))
    ht.add_trans(apriori.Transaction(set([8, 5, 4])))
    ht.add_trans(apriori.Transaction(set([9, 3, 4])))
    ht.add_trans(apriori.Transaction(set([1, 8, 5])))
    ht.add_trans(apriori.Transaction(set([3, 2, 4])))
    ht.add_trans(apriori.Transaction(set([9, 5, 4])))
    ht.add_trans(apriori.Transaction(set([2, 4, 6])))
    ht.add_trans(apriori.Transaction(set([5, 7, 6])))
    ht.add_trans(apriori.Transaction(set([9, 8, 3])))
    ht.add_trans(apriori.Transaction(set([9, 3, 5])))
    ht.add_trans(apriori.Transaction(set([1, 5, 6])))
    ht.add_trans(apriori.Transaction(set([3, 5, 6])))
    ht.add_trans(apriori.Transaction(set([1, 2, 6])))
    ht.add_trans(apriori.Transaction(set([8, 2, 4])))
    ht.add_trans(apriori.Transaction(set([1, 4, 6])))
    ht.add_trans(apriori.Transaction(set([4, 7, 6])))
    ht.add_trans(apriori.Transaction(set([9, 4, 7])))
    ht.add_trans(apriori.Transaction(set([8, 7, 6])))
    ht.add_trans(apriori.Transaction(set([1, 9, 2])))
    ht.add_trans(apriori.Transaction(set([1, 2, 7])))
    ht.add_trans(apriori.Transaction(set([9, 5, 6])))
    ht.add_trans(apriori.Transaction(set([9, 8, 6])))
    ht.add_trans(apriori.Transaction(set([3, 2, 5])))
    ht.add_trans(apriori.Transaction(set([8, 3, 5])))
    ht.add_trans(apriori.Transaction(set([3, 4, 6])))
    ht.add_trans(apriori.Transaction(set([9, 8, 4])))
    ht.add_trans(apriori.Transaction(set([9, 3, 7])))
    ht.add_trans(apriori.Transaction(set([9, 8, 5])))
    ht.add_trans(apriori.Transaction(set([8, 3, 2])))
    ht.add_trans(apriori.Transaction(set([5, 4, 7])))
    ht.add_trans(apriori.Transaction(set([1, 8, 7])))
    ht.add_trans(apriori.Transaction(set([3, 4, 7])))
    ht.add_trans(apriori.Transaction(set([1, 9, 4])))
    ht.add_trans(apriori.Transaction(set([1, 3, 4])))
    ht.add_trans(apriori.Transaction(set([8, 5, 7])))
    ht.add_trans(apriori.Transaction(set([1, 7, 6])))
    ht.add_trans(apriori.Transaction(set([9, 5, 7])))
    ht.add_trans(apriori.Transaction(set([9, 2, 6])))
    ht.add_trans(apriori.Transaction(set([9, 2, 5])))
    ht.add_trans(apriori.Transaction(set([1, 3, 6])))
    ht.add_trans(apriori.Transaction(set([1, 5, 7])))
    ht.add_trans(apriori.Transaction(set([8, 4, 7])))
    ht.add_trans(apriori.Transaction(set([1, 9, 5])))


    debug1("ht.prints(): ")
    ht.prints()
    f = apriori.Transaction(set([1,2,3,4,5]))
    ht.subset(f)


    print ht.cand_list_final
