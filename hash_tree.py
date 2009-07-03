
class Node:
    def __init__(self,parent=None):
        self.parent = parent
        self.children = []

class Hash_tree:
    node_counter = 0
    depth = 1
    root = Node
    node_list = []
    def __init__(self):
        print "tree initialized"
    def add_Node(self, Node):
        if node_list == []:
            self.node_list.append(Node)
            root = Node
        else:




a = Node()
b = Hash_tree()
b.add_Node([1,2])
b.add_Node([3,4])
print b.node_list



