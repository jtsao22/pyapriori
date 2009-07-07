
class Node:
    def __init__(self,parent, state,list):              # initialize
                  #node with parent and state (0 = leaf, 1 = interior)
        self.parent = parent
        self.children = {}
        self.state = state
        self.item_lists = []
        self.item_sets = []
        self.depth = 1
        if state == 0:
            self.item_lists.append(sorted(list))    # lists are sorted
            self.item_sets.append(set(list))        # sets are not


    def get_parent(self):
        return self.parent

    def get_state(self):
        return self.state

    def get_children(self):
        return self.children

    def get_num_children(self):
        print len(self.children)
        return len(self.children)

    def add_child(self,depth,node):
        assert(self.state == 1)
        item_list = node.item_lists[0]
        self.children[item_list[depth-1]] = node


    def add_list(self,list):
        self.item_lists.append(sorted(list))
        self.item_sets.append(set(list))

    def get_num_lists(self):
        return len(self.item_lists)


class Hash_tree:
    def __init__(self,threshold):
        self.threshold = threshold
        self.node_counter = 0
        self.root = None
        print "tree initialized"
    def add_list(self, list):
        if self.root == None:
            self.root = Node(None,1,list)
            temp = Node(self.root,0,list)
            self.root.add_child(list[0],temp)
        else:
            self.add_list_recursive(self.root,list,1)

    def add_list_recursive(self, node, list,depth):
        if node.get_state() == 1:       # if its an interior node:
            list.sort()    # hash on depth, if found call funct again
            if list[depth-1] in node.children.keys():
                self.add_list_recursive(node.children[list[depth-1]]\
                        ,list,depth + 1)
            else:          # if not found, make a new Node
                temp = Node(node,0,list)
                node.add_child(depth,temp)
        else:               # if its a leaf node:
            node.add_list(list)         # add the list to the node, and
                                        #then check threshold
            if self.check_threshold(node):
                # if past threshold, change node into interior node
                node.state = 1
                for list in node.item_lists:
                    temp = Node(node,0,list)
                    node.add_child(depth,temp)
                node.item_lists = []


    def check_threshold(self,node): # return true if greater than
                                    # threshold
        return node.get_num_lists() > self.threshold

    def print_all_tree(self,node):

        print "_________________"
        if node.get_state() == 1:
            print "in an interior node"
            for i in node.children.values():
                self.print_all_tree(i)
            print "out of interior node"
        else:
            print "Here's a leaf node item list: ",node.item_lists
            print "Here's item set: ", node.item_sets

    def prints(self):
        self.print_all_tree(self.root)

    def subset(self,t):
        self.subset_recursive(self.root,0,t)

    def subset_recursive(self,node,num_to_hash,t):
        if node.get_parent() == None:      # if root, hash on every item in t
            for child in node.children.values():
                self.subset_recursive(child,num_to_hash+1,t)
        else:                   # if not root, check interior or leaf
            if node.get_state() == 0: # if leaf, find ones in T
                for item_set in node.item_sets:
                    if item_set.issubset(t):
                        print item_set
            else:
                # if interior node, hash on items after
                for iter in t[num_to_hash:(len(t)-(num_to_hash-1))]:
                    if iter in node.children:
                        self.subset_recursive(node.children[iter],\
                            num_to_hash +1, t)

#a = Node(None,0,set([1,2]))
#b = Node(None,0,set([1,3]))
#c = Node(None,0,set([1,4]))
#d = Node(None,0,set([1,5]))
#print a.get_sets()
#a=[1,2,3,4]
#b=[1,3,4,5]
#c=[1,4,5,6]
#d=[5,2,1,7]
#e=[3,4,2,7]
#f=[1,6,3,5]
#g=[2,5,1,8]
#l=[2,1,3,8]
#k=[1,2,4,8]
#
#
#
#ht = Hash_tree(3)
#
#ht.add_list(a)
#ht.add_list(b)
#ht.add_list(c)
#ht.add_list(d)
#ht.add_list(e)
#ht.add_list(f)
#ht.add_list(g)
#ht.add_list(l)
#ht.add_list(k)
#
#ht.prints()
#
#ht.subset(([1,3,4,6,7]))
