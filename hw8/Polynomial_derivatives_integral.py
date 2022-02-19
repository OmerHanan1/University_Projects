# Author: Omer Hanan
# Course: Introduction to computer science.
import copy


# Monom: this class is the most basic part of the code,
# each Monom instance carries (Power, coefficient).
class Monom:
    def __init__(self, power, coef=1):
        """
        Constructor Method
        """
        self.power = power
        self.coef = round(coef, 2)
        self.next = None

    def __repr__(self):
        """ Represent Method
        (1) Rounding the value for 2 digits after the point,
        Then checking if the value of the digits after the point is 0. if so-
        Casting the value to integer
        (2) Compute and represent the values of negative numbers
        (3) Zero number OR zero power
        (4) Number value = 1 OR power value = 1
        (5) Regular represent
        """
        if not (self.coef * 10) % 10: self.coef = int(self.coef)

        if self.coef < 0:  # (2)
            if self.power == 0: return str("(" + str(self.coef) + ")")
            if self.power == 1: return str("(" + "{}X".format(self.coef) + ")")
            if self.power != 0: return str("(" + "{}X^{}".format(self.coef, self.power) + ")")

        if self.coef == 0: return str(0)  # (3)
        if self.power == 0: return str(self.coef)

        if self.coef == 1 and self.power == 1: return str("X")  # (4)
        if self.coef == 1: return str("X^{}".format(self.power))
        if self.power == 1:
            return str("{}X".format(self.coef))

        else:  # (5)
            return str("{}X^{}".format(self.coef, self.power))

    def __add__(self, other):
        if self.power == other.power:
            temp = Monom(self.power, self.coef + other.coef)
            return temp

    def __mul__(self, other):
        """ Multiplication Method
        (1) Scaler multiply by a 'Monom'
        (2) 'Monom' multiply by a 'Monom'
        """
        if isinstance(other, int):  # (1)
            temp = Monom(self.power, self.coef)
            temp.coef *= other
            temp.coef = round(temp.coef, 2)
            return temp

        if isinstance(other, float):  # (1) --- also counting as 1
            temp = Monom(self.power, self.coef)
            temp.coef *= other
            temp.coef = round(temp.coef, 2)
            return temp

        if isinstance(other, Monom):  # (2)
            temp = Monom(self.power + other.power, self.coef * other.coef)
            temp.coef = round(temp.coef, 2)
            return temp

    def __rmul__(self, other):  # Right multiplication
        return self * other

    def monom_value_by_x(self, x):
        return (x ** self.power) * self.coef

    def derivative(self):
        """ Derivative Method"""
        if self.power == 0:
            temp = Monom(0, 0)
            return temp
        if self.coef == 1 and self.power == 1:
            temp = Monom(0, 1)
            return temp
        if self.coef == 1 and self.power != 1:
            temp = Monom(self.power - 1, self.power)
            return temp
        temp = Monom(self.power - 1, round(self.coef, 2) * self.power)
        return temp

    def integral(self):
        """
        (1) integration zero
        (2) integration for "only power" case
        :return: new object without changing the value of the original object.
        """
        if self.coef == 0 and self.power == 0:  # (1)
            temp = Monom(0, 0)
            return temp

        if self.coef == 1 and self.power != 0:  # (2)
            p = self.power
            p += 1
            temp = Monom(p, self.coef / p)
            return temp
        if self.coef != 0 and self.power == 0:
            temp = Monom(1, self.coef)
            return temp

        temp = Monom(self.power + 1, (round(self.coef, 2) / (self.power + 1)))
        return temp

# Polynomial: a chain of Monoms connecting together
# representing a mathematical polynomial.
class Polynomial:
    def __init__(self, l):
        """
        Constructor for polynomial class
        :param l: list type, contains tuples with two numbers (int or float)
        """
        self.head = None
        mem = {}
        solution = []
        # Checking the Input:
        if type(l) != list: raise ValueError("invalid polynomial initialization.")
        for x in l:
            if type(x) != tuple or len(x) != 2: raise ValueError("invalid polynomial initialization.")
            if not isinstance(x[0], int or float): raise ValueError("invalid polynomial initialization.")
            if not isinstance(x[0], int or float): raise ValueError("invalid polynomial initialization.")

        # Sorting the input by power order:
        l = sorted(l, key=lambda x: x[0], reverse=True)  # sorting the tuples from biggest power to lowest
        # putting the list l values in a dictionary: keys = power, value = coef
        for i in l:
            if i[1] == 0:
                continue
            if i[0] not in mem.keys():
                mem[i[0]] = i[1]
            else:
                mem[i[0]] += i[1]
        # Deleting the zero values from the dictionary:
        mem = {k: v for k, v in mem.items() if v != 0}

        """
        Making the sorted dictionary a list of 'Monoms':
        """
        for x in mem:
            temp = Monom(x, mem[x])
            solution.append(temp)

        """
        Making the sorted list, a LINKED LIST:
        """
        if len(solution) != 0:
            self.head = solution[0]
        if len(solution) != 0:
            for x in range(len(solution) - 1):
                solution[x].next = solution[x + 1]

    def __repr__(self):
        """
        representation of a single Polynomial
        :return: -> string
        """
        solution_str = "P(X)="

        a = self.head
        if not a:
            return "P(X)=0"
        while a:
            if a.coef == 0:
                a = a.next
                continue
            else:
                solution_str += str(a)
                solution_str += "+"
                a = a.next
        solution_str = solution_str[:-1]
        return solution_str

    def rank(self):
        """
        rank of a polynomial = the power of the highest power Monom in it
        :return: -> int
        """
        if not self.head:
            return 0
        else:
            return self.head.power

    def calculate_value(self, x):
        """
        calculating the value of a polynomial by a given value X
        :param x: a value to calculate
        :return: -> int/float
        """
        head = self.head
        if not head:
            return 0
        value = 0
        while head:
            value += head.monom_value_by_x(x)
            head = head.next
        return value

    def __neg__(self):
        """
        taking a polynomial and multiply all of is monos with minus
        :return: -> (new) Polynomial
        """
        solution = []
        head = self.head
        if not head:
            return copy.deepcopy(self)
        else:
            while head:
                temp = (head.power, -1 * head.coef)
                solution.append(temp)
                head = head.next
        return Polynomial(solution)

    def __sub__(self, other):
        """
        one polynomial subtract other polynomial
        :param other: polynomial
        :return: -> (new) polynomial
        """
        solution = []
        main_p = self.head
        other_p = other.head
        if not other_p:
            return copy.deepcopy(self)
        while main_p:
            flag = False
            if not other_p or main_p.power > other_p.power:
                temp = (main_p.power, main_p.coef)
                solution.append(temp)
            if other_p and main_p.power == other_p.power:
                temp = (main_p.power, main_p.coef - other_p.coef)
                solution.append(temp)
                other_p = other_p.next
            if other_p and other_p.power > main_p.power:
                temp = (other_p.power, -1 * other_p.coef)
                solution.append(temp)
                other_p = other_p.next
                flag = True
            if main_p == None and other_p != None:
                flag = True
            if not flag:
                main_p = main_p.next
                if main_p == None and other_p != None:
                    while other_p:
                        temp = (other_p.power, -1 * other_p.coef)
                        solution.append(temp)
                        other_p = other_p.next
        return Polynomial(solution)

    def __add__(self, other):
        """
        adding two polynomials together - USING THE "SUB" FUNCTION !!!
        :param other: some polynomial
        :return: -> (new) polynomial
        """
        main_p = copy.deepcopy(self)
        other_p = copy.deepcopy(other)
        return main_p.__sub__(other_p.__neg__())

    def __rmul__(self, other):  # Right Multiplication
        return self * other

    def __mul__(self, other):
        """
        multiplication number and poly
        :param other: int/float
        :return: -> (new) polynomial
        """
        solution = []
        head = self.head
        if isinstance(other, (int or float)):
            while head:
                temp = (head.power, head.coef * other)
                solution.append(temp)
                head = head.next
            return Polynomial(solution)
        if isinstance(other, Polynomial):
            other_head = other.head
            while head:
                while other_head:
                    temp = ((head * other_head).power, (head * other_head).coef)
                    solution.append(temp)
                    other_head = other_head.next
                other_head = other.head
                head = head.next
        return Polynomial(solution)

    def derivative(self):
        """
        derivative a given function
        :return: -> a derivative function (new)
        """
        solution = []
        poly = Polynomial([])
        head = self.head
        if self.rank() == 0:
            return Polynomial([])
        while head:
            solution.append(head.derivative())
            head = head.next
        poly.head = solution[0]
        p_h = poly.head
        for i in range(len(solution) - 1):
            p_h.next = solution[i + 1]
            p_h = p_h.next
        return poly

    def integral(self):
        """
        integrate a given function
        :return: -> integtal (new)
        """
        solution = []
        poly = Polynomial([])
        head = self.head
        if self.rank() == 0:
            return Polynomial([])
        while head:
            solution.append(head.integral())
            head = head.next
        poly.head = solution[0]
        p_h = poly.head
        for i in range(len(solution) - 1):
            p_h.next = solution[i + 1]
            p_h = p_h.next
        return poly

    def __eq__(self, other):
        """
        equal function
        :param other:
        :return: -> BOOL
        """
        s_head = self.head
        o_head = other.head
        s_counter, o_counter = 0, 0
        while s_head:
            s_counter += 1
            s_head = s_head.next
        while o_head:
            o_counter += 1
            o_head = o_head.next
        if o_counter != s_counter:
            return False
        s_head = self.head
        o_head = other.head
        while s_head:
            if s_head.power != o_head.power or s_head.coef != o_head.coef:
                return False
            s_head = s_head.next
            o_head = o_head.next
        return True

    def __le__(self, other):
        if self == other: return True
        if self.rank() < other.rank(): return True
        if self.rank() > other.rank(): return False
        if self.calculate_value(2) < other.calculate_value(2):
            return True
        else:
            return False

    def __ge__(self, other):
        if self == other: return True
        if self.rank() > other.rank(): return True
        if self.rank() < other.rank(): return False
        if self.calculate_value(2) > other.calculate_value(2):
            return True
        else:
            return False

    def __lt__(self, other):
        return self <= other and self != other

    def __gt__(self, other):
        return self >= other and self != other

    def __ne__(self, other):
        return not self == other

# Binary tree node: holed a polynomial.
# This is a sub-class to Polynomial BST.
class BinTreeNode:
    def __init__(self, val):
        """
        Constructor of a tree Node
        :param val: Poly
        """
        self.value = val
        self.left = self.right = None

    def __repr__(self):
        """
        BinTreeNode representation (for myself - not asked function)
        :return: -> string
        """
        return str(self.value)

# Polynomial Binary tree: a Binary search tree of polynomials,
# since all the polynomials have comparison functions,
# an insertion to this binary tree will keep it sorted.
class PolynomialBST:
    def __init__(self):
        """
        Constructor of a BST
        """
        self.head = None

    def insert(self, val):
        """
        insertion by given rules
        :param val: poly
        :return: -> the SAME tree (BST)
        """
        value = BinTreeNode(val)
        if self.head == None:
            self.head = value
            return self

        def insert_rec(tree, node):
            if tree.value >= node.value:
                if tree.left == None:
                    tree.left = node
                else:
                    insert_rec(tree.left, node)
            if node.value > tree.value:
                if tree.right == None:
                    tree.right = node
                else:
                    insert_rec(tree.right, node)

        insert_rec(self.head, value)

    def in_order(self):
        """
        representation of tree in list by given order
        :return: -> list
        """
        if not self.head:
            return []
        head = self.head
        lst = []
        end = []

        def rec_search(head, lst):
            if head:
                lst.append(head)
                rec_search(head.right, lst)
                rec_search(head.left, lst)
            return lst

        end = rec_search(head, lst)
        return sorted(end, key=lambda x: x.value)

    def __add__(self, other):
        """
        adding two trees together
        :param other: tree (BST)
        :return: -> (new) tree
        """
        solution = PolynomialBST()
        temp = copy.deepcopy(self.in_order()) + copy.deepcopy(other.in_order())
        for x in range(len(temp)):
            temp[x].right = None
            temp[x].left = None
        if temp:
            solution.head = temp[0]

        for i in range(len(temp) - 1):
            temp[i + 1].right = None
            temp[i + 1].left = None
            solution.insert(temp[i + 1])
        return solution


# p = Polynomial([(3,4),(3,3)])
# print(p)
# tests about repr function in MONOM
# m13 = Monom(2, 2.003)
# m17 = Monom(0, -2.013)
# m27 = m17 * m13
# print(m27)
# print(m27.__repr__() == '(-4.02X^2)')

# derivative repr in MONOM
#
# m9 = Monom(8, -1.6789)
# # m14 = Monom(2, -2.003)
# m36 = m9.derivative()
# print(m9.__repr__())
# print(m36.__repr__())
# m37 = m14.derivative()
# print(m36.__repr__() == '(-13.44X^7)')
# print(m37.__repr__() == '(-4X)')

# p1 = Polynomial([(1, 2), (2, 1), (5, 6), (6, 5), (1, 2), (2, 1)])
# print(p1)
# print(p1.derivative())
# p2 = p1.derivative()
# print(p2.integral())
# p2 = Polynomial([(3, 1)])
# p3 = Polynomial([])
# p4 = Polynomial([(8, 0), (3, -5), (3, 5), (0, 18)])
# p5 = Polynomial([(8, 0), (3, 7), (3, 2), (0, 0)])
# p6 = Polynomial([(3, -5), (3, 5)])
# p7 = Polynomial([(1, 2), (2, 1), (5, 6), (6, 5), (3, 2), (4, 1)])
# p8 = Polynomial([(3, -5), (3, -5)])
# print(p7)
# print(p8)
# print(p7-p8)
# print((p2 - p5).__repr__() == 'P(X)=(-8X^3)')
# print((p2 - p3).__repr__() == 'P(X)=X^3')
# print((p7 - p8).__repr__() =='P(X)=5X^6+6X^5+X^4+12X^3+X^2+2X')
# print((p2 - p8).__repr__() == 'P(X)=11X^3')
# print((p1 - p2).__repr__() == 'P(X)=5X^6+6X^5+(-1X^3)+2X^2+4X')
# print((p2 - p1).__repr__() == 'P(X)=(-5X^6)+(-6X^5)+X^3+(-2X^2)+(-4X)')

# polynomial adding - the same problem, NoneType - To Fix!
# p1 = Polynomial([(1, 2), (2, 1), (5, 6), (6, 5), (1, 2), (2, 1)])
# p2 = Polynomial([(3,1)])
# p3 = Polynomial([])
# p4 = Polynomial([(8, 0), (3, -5), (3, 5), (0, 18)])
# p5 = Polynomial([(8, 0), (3, 7), (3, 2), (0, 0)])
# p6 = Polynomial([(3, -5), (3, 5)])
# p7 = Polynomial([(1, 2), (2, 1), (5, 6), (6, 5), (3, 2), (4, 1)])
# p8 = Polynomial([(3, -5), (3, -5)])
# print((p2 + p3).__repr__() == 'P(X)=X^3')
# print((p7 + p8).__repr__() == 'P(X)=5X^6+6X^5+X^4+(-8X^3)+X^2+2X')
# print((p2 + p8).__repr__() == 'P(X)=(-9X^3)')

# binary search tree insertion and orders
# p1 = Polynomial([(3, 3), (2, 2), (1, 1)])
# p2 = Polynomial([(3, 6), (2, 5), (1, 4)])
# p3 = Polynomial([])
# p4 = Polynomial([(8, 0), (3, -5), (3, 5), (0, 18)])
# p5 = Polynomial([(8, 0), (3, 1), (3, 0), (0, 0)])
# p6 = Polynomial([(0, 1)])
# p7 = Polynomial([(0, 10)])
# p8 = Polynomial([(0, 8)])
# p9 = Polynomial([(0, 2)])
# p10 = Polynomial([(0, 3)])
# t1 = PolynomialBST()
# t2 = PolynomialBST()
# t3 = PolynomialBST()
# t4 = PolynomialBST()
# t3.insert(p1)
# t1.insert(p1)
# t1.insert(p2)
# t1.insert(p3)
# t1.insert(p4)
# t1.insert(p5)
# t4.insert(p6)
# t4.insert(p7)
# t4.insert(p8)
# t4.insert(p9)
# t4.insert(p10)
# print(t1.in_order())
# print(str(t1.in_order()) == "[P(X)=0, P(X)=18, P(X)=X^3, P(X)=3X^3+2X^2+X, P(X)=6X^3+5X^2+4X]")
# print(str(t2.in_order()) == '[]')
# print(str(t3.in_order()) == '[P(X)=3X^3+2X^2+X]')
# print(str(t4.in_order()) == '[P(X)=1, P(X)=2, P(X)=3, P(X)=8, P(X)=10]')
