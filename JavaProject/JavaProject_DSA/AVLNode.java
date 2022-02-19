import java.util.IllegalFormatCodePointException;

public class AVLNode<T> implements Comparable<AVLNode<T>> {

    // AVL node general fields constructors:
    public T data;
    public AVLNode<T> left;
    public AVLNode<T> right;
    public AVLNode<T> father;
    public int key;

    // Data-only constructor:
    public AVLNode(T data) {
        super();
        this.data = data;
        this.left = null;
        this.right = null;
        this.father = null;
        this.key = 0;
    }

    // All args constructor:
    public AVLNode(T data, AVLNode<T> left, AVLNode<T> right, AVLNode<T> father, int key) {
        super();
        this.data = data;
        this.left = left;
        this.right = right;
        this.father = father;
        this.key = key;
    }

    // Duplicator constructor:
    public AVLNode(AVLNode<T> temp) {

        if (temp.data != null) {
            this.data = temp.data;
        } else {
            this.data = null;
        }
        this.key = temp.key;
        this.father = temp.father;
        this.left = temp.left;
        this.right = temp.right;

    }



    /**
     * @param: AVL node.
     * @return: comparison result.
     */
    public int compareTo(AVLNode<T> avlNode) {
        if (this.getKey() <= avlNode.getKey()) {
            return -1;
        }
        if (this.getKey() == avlNode.getKey()) {
            return 0;
        }
        return 1;
    }

    /**
      @param: AVL node to check.
      @return: AVL node's height.
     */
    public int getHeight(AVLNode<T> avlNode) {
        if (avlNode == null) {
            return -1;
        }
        int lefth = getHeight(avlNode.left);
        int righth = getHeight(avlNode.right);
        if (lefth > righth) {
            return lefth + 1;
        } else {
            return righth + 1;
        }
    }

    /**
     * @param: AVL node for balance checking.
     * @return: int represents BF.
     */
    public int getBalanceF(AVLNode<T> avlNode) {
        int a = avlNode.getHeight(avlNode.getLeftChild());
        int b = avlNode.getHeight(avlNode.getRightChild());
        return (a - b);
    }

    /**
     * @param: AVL node
     * @return: void, the function sends the param node to the correct rotation for balancing the tree.
     */
    public void Rotations(AVLNode<T> avlNode) {
        // Checking:
        if (avlNode.getBalanceF(avlNode) < 0) {
            if (avlNode.getRightChild() != null && avlNode.getRightChild().getBalanceF(avlNode.getRightChild()) < 0) {
                avlNode.RR(avlNode);
            }
            if (avlNode.getRightChild() != null && avlNode.getRightChild().getBalanceF(avlNode.getRightChild()) > 0) {
                avlNode.RL(avlNode);
            }
        }

        if (avlNode.getBalanceF(avlNode) > 0) {
            if (avlNode.getLeftChild() != null && avlNode.getLeftChild().getBalanceF(avlNode.getLeftChild()) < 0) {
                avlNode.LR(avlNode);
            }
            if (avlNode.getLeftChild() != null && avlNode.getLeftChild().getBalanceF(avlNode.getLeftChild()) > 0) {
                avlNode.LL(avlNode);
            }
        }

    }

    /**
     * @param: avlNode to rotate
     * @return: void. rotating as we learn in class (double right rotation).
     */
    public void RR(AVLNode<T> avlNode) {
        // final father is the final node to be the father
        AVLNode<T> final_father = null;
        if (avlNode.getFather() != null) {
            final_father = avlNode.getFather();
        }
        //*
        // pivot:           node to rotate.
        // pivot_father:    the pivot father.
        // pivot_left:      the pivot left child.
        //
        // *//

        AVLNode<T> pivot = avlNode.getRightChild();
        AVLNode<T> pivot_father = pivot.father;
        AVLNode<T> pivot_left = null;
        if (pivot.getLeftChild() != null) {
            pivot_left = pivot.left;
        }

        // set pivot left child to be "pivot_father".
        pivot.left = pivot_father;
        pivot.left.father = pivot;

        // set pivot left child's right child to be "pivot_left".
        pivot.left.right = pivot_left;
        if (pivot.left.right != null) {
            pivot.left.right.father = pivot.left;
        }

        pivot.father = final_father;
        if (final_father != null) {
            final_father.right = pivot;
        }
    }

    /**
     * @param: avlNode to rotate
     * @return: void. rotating as we learn in class (double left rotation).
     */
    public void LL(AVLNode<T> avlNode) {
        AVLNode<T> final_father = null;
        if (avlNode.getFather() != null) {
            final_father = avlNode.getFather();
        }
        AVLNode<T> pivot = avlNode.getLeftChild();
        AVLNode<T> pivot_father = pivot.father;
        AVLNode<T> pivot_right = null;
        if (pivot.getLeftChild() != null) {
            pivot_right = pivot.right;
        }
        pivot.right = pivot_father;
        pivot.right.father = pivot;

        pivot.right.left = pivot_right;
        if (pivot.right.left != null) {
            pivot.right.left.father = pivot.right;
        }

        pivot.father = final_father;
        if (final_father != null) {
            final_father.left = pivot;
        }
    }


    /**
     * @param: avlNode to rotate
     * @return: void. rotating as we learn in class,
     * first making a fixing move of single right rotate- and than sending to
     * the double right rotation function (RR)
     */
    public void RL(AVLNode<T> avlNode) {
        AVLNode<T> final_father = avlNode;
        AVLNode<T> root = avlNode.getRightChild();
        AVLNode<T> pivot = avlNode.getRightChild().getLeftChild();
        AVLNode<T> pivot_right_child = null;
        if (pivot.getRightChild() != null){
            pivot_right_child = pivot.getRightChild();
        }

        final_father.right = pivot;
        pivot.father = final_father;

        pivot.right = root;
        root.father = pivot;

        root.left = pivot_right_child;
        if (pivot_right_child != null){
            pivot_right_child.father = root;
        }
        RR(avlNode);
    }

    /**
     * @param: avlNode to rotate
     * @return: void. rotating as we learn in class,
     * first making a fixing move of single left rotate- and than sending to
     * the double left rotation function (LL)
     */
    public void LR(AVLNode<T> avlNode) {
        AVLNode<T> final_father = avlNode;
        AVLNode<T> root = avlNode.getLeftChild();
        AVLNode<T> pivot = avlNode.getLeftChild().getRightChild();
        AVLNode<T> pivot_left_child = null;
        if (pivot.getLeftChild() != null){
            pivot_left_child = pivot.getLeftChild();
        }

        final_father.left = pivot;
        pivot.father = final_father;

        pivot.left = root;
        root.father = pivot;

        root.right = pivot_left_child;
        if (pivot_left_child != null){
            pivot_left_child.father = root;
        }
        LL(avlNode);
    }

    // TO ALL UNDER:
    // GETTERS & SETTERS FUNCTIONS.
    // (nothing special for documentation). //

    public AVLNode<T> getLeftChild() {
        if (this.left != null) {
            return this.left;
        } else {
            return null;
        }
    }

    public AVLNode<T> getRightChild() {
        if (this.right != null) {
            return this.right;
        } else {
            return null;
        }
    }

    public void setLeftChild(AVLNode<T> left) {
        this.left = left;
    }

    public void setRightChild(AVLNode<T> right) {
        this.right = right;
    }

    public AVLNode<T> getFather() {
        return this.father;
    }

    public void setKey(int k) {
        this.key = k;
    }

    public int getKey() {
        return this.key;
    }

    public T getData() {
        return this.data;
    }

    public void setFather(AVLNode<T> father) {
        this.father = father;
    }

    @Override
    public String toString() {

        String s = "";

        if (getLeftChild() != null) {
            s += "(";
            s += getLeftChild().toString();
            s += ")";
        }
        s += getKey();
        if (getRightChild() != null) {
            s += "(";
            s += getRightChild().toString();
            s += ")";
        }
        return s;
    }
}


