
class Node:
    def __init__(self,parent, state,subset):              # initialize
                  #node with parent and state (0 = leaf, 1 = interior)
        self.parent = parent
        self.children = {}
        self.state = state
        self.item_sets = []
        self.depth = 1
        self.item_sets.append(subset)
        if state == 1:
            self.add_child(self.depth,subset)
        self.depth += 1
    def get_parent(self):
        return self.parent

    def get_state(self):
        return self.state

    def get_children(self):
        return self.children

    def get_num_children(self):
        print len(self.children)
        return len(self.children)

    def get_first_token(self):
        if len(self.item_sets) > 0:
            temp = self.item_sets[0]
            for x in sorted(temp):
                return x
        return 0

    def add_child(self,depth,set):
        self.children[depth] = set

    def add_set(self,set):
        self.item_sets.append(set)

    def get_num_sets(self):
        return len(self.item_sets)

    def get_sets(self):
        return self.item_sets


class Hash_tree:
    def __init__(self,threshold):
        self.threshold = threshold
        self.node_counter = 0
        self.root = None
        print "tree initialized"
    def add_set(self, set):
        if self.root == None:
            self.root = Node(None,1,set)
            print "added as root"
            print self.root.get_first_token()
        else:
            if self.root.get_state() == 1:
                print self.root.get_first_token()
                print "________________________"

                if self.matching_first_token(self.root,set):
                    self.root.add_set(set)
                    print self.root.get_num_sets()

                    if self.check_threshold(self.root):
                        print "greater than threshold"
                else:
                    self.root.add_child(self.root.depth,set)
            print "added as leaf"

    def check_threshold(self,node): # return true if greater than
                                    # threshold
        return node.get_num_sets() > self.threshold

    def matching_first_token(self,node, set):
        for x in sorted(set):
            return x == node.get_first_token()

    def get_root_children(self):
        return self.root.children

    def print_all_tree(self,node):

        print "_________________"
        if node.get_num_children() != 0:
            for i in node.children:
                self.print_all_tree(i)
        print node.item_sets

    def prints(self):
        self.print_all_tree(self.root)

#a = Node(None,0,set([1,2]))
#b = Node(None,0,set([1,3]))
#c = Node(None,0,set([1,4]))
#d = Node(None,0,set([1,5]))
#print a.get_sets()
a=set([1,2])
b=set([1,3])
c=set([1,4])
d=set([2,5])
e=set([3,5])
f=set([1,6])
ht = Hash_tree(3)

ht.add_set(a)
ht.add_set(b)
ht.add_set(c)
ht.add_set(d)
ht.add_set(e)
ht.add_set(f)

ht.prints()
