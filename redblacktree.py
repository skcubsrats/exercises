import sys
import math
from random import randint

class RedBlackTreeError(Exception):
  pass

class RedBlackTree(object):
  
  class Node(object):
    ROOTTOP = -1
    RED = 0
    BLACK = 1
    
    def __init__(self, key,  parent = None, type_ = RED):
      self.type = type_
      self.key = key
      self.parent = parent
      self.children = [None] * 2
      self.side = 0
    
    def __str__(self):
      return '(%s, %d, %d)' % (
        self.type == RedBlackTree.Node.RED and 'R' or 'B',
        self.key,
        self.side)
    
    def dumps(self):
      return '(%s, %d, %d, {%s, %s})' % (
        self.type == RedBlackTree.Node.RED and 'R' or 'B',
        self.key,
        self.side,
        self.children[0] and self.children[0].dumps() or None,
        self.children[1] and self.children[1].dumps() or None)
    
    def is_right_child(self, node):
      return self.side == 1
    
    def is_left_child(self, node):
      return self.side == 0
    
    def is_leaf(self):
      return self.children[0] is None and self.children[1] is None
    
    def is_root(self):
      return self.parent.type == RedBlackTree.Node.ROOTTOP
    
    def get_left_child(self):
      return self.children[0]
    
    def get_right_child(self):
      return self.children[1]
    
    def get_sibling(self):
      if self.is_root():
        return None
      return self.parent.children[1 - self.side]
    
    def set_child(self, node, side):
      self.children[side] = node
      if node is not None:
        node.parent = self
        node.side = side
    
    def rotate_left(self):
      child = self.get_right_child()
      if child is None:
        print self.dumps()
        raise RedBlackTreeError('cannot rotate left because node has no right edge')
      
      # there is always the ROOTTOP sentinel node
      self.parent.set_child(child, self.side)
      lgchild = child.get_left_child()
      child.set_child(self, 0)
      self.set_child(lgchild, 1)
    
    def rotate_right(self):
      child = self.get_left_child()
      if child is None:
        print self.dumps()
        raise RedBlackTreeError('cannot rotate right because node has no left edge')
      
      # there is always the ROOTTOP sentinel node
      self.parent.set_child(child, self.side)
      rgchild = child.get_right_child()
      child.set_child(self, 1)
      self.set_child(rgchild, 0)
    
    def insert_child(self, node):
      self.__binary_insert_child(node)
      node.__swap_to_red()
    
    def traverse_inorder(self):
      if self.children[0] is not None:
        for n in self.children[0].traverse_inorder():
          yield n
      yield self
      if self.children[1] is not None:
        for n in self.children[1].traverse_inorder():
          yield n
    
    def traverse_preorder(self):
      yield self
      if self.children[0] is not None:
        for n in self.children[0].traverse_preorder():
          yield n
      if self.children[1] is not None:
        for n in self.children[1].traverse_preorder():
          yield n
    
    def __binary_insert_child(self, node):
      if node.key < self.key:
        if self.children[0] is None:
          self.set_child(node, 0)
        else:
          self.children[0].__binary_insert_child(node)
      else:
        if self.children[1] is None:
          self.set_child(node, 1)
        else:
          self.children[1].__binary_insert_child(node)
     
    def __swap_to_red(self):
      if self.is_root():
        return
      
      self.type = RedBlackTree.Node.RED
      p = self
      while p.parent.type == RedBlackTree.Node.RED:
        p = p.parent
      
      if p is self:
        return
      
      # case 1:
      sib = p.get_sibling()
      if sib is not None and sib.type == RedBlackTree.Node.RED:
        p.type = RedBlackTree.Node.BLACK
        sib.type = RedBlackTree.Node.BLACK
        p.parent.__swap_to_red()
      else:
        gp = p.parent
        if p.side == 0:
          # case 2:
          if self.side == 1:
            p.rotate_left()
            self.type = RedBlackTree.Node.BLACK
          else:
            p.type = RedBlackTree.Node.BLACK
          # case 3:
          gp.rotate_right()
        else:
          # case 2:
          if self.side == 0:
            p.rotate_right()
            self.type = RedBlackTree.Node.BLACK
          else:
            p.type = RedBlackTree.Node.BLACK
          # case 3:
          gp.rotate_left()
        
        gp.type = RedBlackTree.Node.RED
      
  def __init__(self, keys):
    self.roottop = RedBlackTree.Node(-1, None, RedBlackTree.Node.ROOTTOP)
    self.size = 0
    self.build(keys)
  
  def dumps(self):
    root = self.__root()
    if root is not None:
      return root.dumps()
  
  def build(self, keys):
    for k in keys:
      self.insert(k)
  
  def insert(self, key):
    node = RedBlackTree.Node(key)
    root = self.__root()
    if root is None:
      node.type = RedBlackTree.Node.BLACK
      self.roottop.set_child(node, 0)
    else:
      root.insert_child(node)
    self.size += 1

  def remove(self, key):
    pass
  
  def inorder_iter(self):
    root = self.__root()
    if root is not None:
      for n in root.traverse_inorder():
        yield n.key
    
  def print_all_paths(self):
    root = self.__root()
    if root is not None:
      for n in root.traverse_preorder():
        if n.is_leaf():
          node = n
          path = [str(node)]
          nblks = n.type == RedBlackTree.Node.BLACK and 1 or 0
          while not node.is_root():
            node = node.parent
            path.append(str(node))
            if node.type == RedBlackTree.Node.BLACK:
              nblks += 1
            
          path.reverse()
          print '%d (Bs = %d): %s' % (len(path), nblks, '->'.join(path))
          
  def __root(self):
    return self.roottop.get_left_child()
  
input = []
for i in range(int(sys.argv[1])):
  input.append(randint(0, 1000))
#input = [19, 4, 7, 19, 18, 11, 12, 17, 5, 16]
print 'input: %s' % input

tree = RedBlackTree(input)
print tree.dumps()

for k in tree.inorder_iter():
  print k,
print '\nsize: %d, ideal height: %f' % (tree.size, math.log(tree.size, 2))
tree.print_all_paths()