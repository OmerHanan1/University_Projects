import java.util.Base64;

public class AVL<T> {
    public AVLNode<T> root;


    /**
     * Constructor function:
     * @param: AVL root to generate.
     */
    public AVL(AVLNode<T> root) {
        this.root = root;
    }

    /**
     * default empty constructor;
     */
    public AVL() {
        this.root = null;
    }


    /**
     * @param: int key
     * @param: T data
     * @return: the function takes the args and inserting them into an AVL node
     * than insert this AVL node into the AVL tree into the right place using a
     * helper function called "rec_insert".
     */
    public void insert(int key, T data) {
        if (this.root == null) {
            this.root = new AVLNode<T>(data, null, null, null, key);
        } else {

            AVLNode<T> current = rec_insert(this.root, key, data);


            while (current != null) {
                if (Math.abs(current.getBalanceF(current)) > 1) {
                    if (current == this.root) {

                        if (current.getBalanceF(current) < 0) {
                            if (current.getRightChild() != null && current.getRightChild().getBalanceF(current.getRightChild()) < 0) {
                                this.root = current.getRightChild();
                            }
                            if (current.getRightChild() != null && current.getRightChild().getBalanceF(current.getRightChild()) > 0) {
                                this.root = current.getRightChild().getLeftChild();
                            }
                        }
                        if (current.getBalanceF(current) > 0) {
                            if (current.getLeftChild() != null && current.getLeftChild().getBalanceF(current.getLeftChild()) > 0) {
                                this.root = current.getLeftChild();
                            }
                            if (current.getLeftChild() != null && current.getLeftChild().getBalanceF(current.getLeftChild()) < 0) {
                                this.root = current.getLeftChild().getRightChild();
                            }
                        }
                    }
                    current.Rotations(current);
                    break;
                }
                current = current.getFather();
            }
        }
    }

    /**
     * @param: avl node as a "root" (moving as we move with the recursion frames).
     * @param: int k for future inserting node.
     * @param: T data for future inserting node.
     * @return: AVL node after inserting.
     */
    public AVLNode<T> rec_insert(AVLNode<T> avlNode, int k, T data) {
//
        AVLNode<T> temp = avlNode;
        while (temp != null) {
            if (temp.getRightChild() == null && temp.getKey() < k) {
                AVLNode<T> eden = new AVLNode<T>(data, null, null, temp, k);
                temp.setRightChild(eden);
                eden.setFather(temp);
                return eden;
            }
            if (temp.getLeftChild() == null && temp.getKey() >= k) {
                AVLNode<T> eden = new AVLNode<T>(data, null, null, temp, k);
                temp.setLeftChild(eden);
                eden.setFather(temp);
                return eden;
            }
            if (temp.getLeftChild() != null && k <= temp.getKey()) {
                temp = temp.getLeftChild();

            }
            if (temp.getRightChild() != null && k > temp.getKey()) {
                temp = temp.getRightChild();
            }
        }
        return null;
    }

    /**
     * @param: int key
     * @return: T data
     * this function is the wrapper function for rec_search func.
     */
    public T search(int key) {
        if (this.root == null) {
            return null;
        }
        AVLNode<T> solution = rec_search(this.root, key);
        if (solution != null) {
            return solution.getData();
        }
        return null;
    }

    /**
     * @param: avl node.
     * @param: int key.
     * this function
     */
    public AVLNode<T> rec_search(AVLNode<T> current, int key) {
        if (current != null && current.getKey() == key) {
            return current;
        } else {
            if (current.getKey() > key && current.getLeftChild() != null) {
                return rec_search(current.getLeftChild(), key);
            }
            if (current.getKey() <= key && current.getRightChild() != null) {
                return rec_search(current.getRightChild(), key);
            } else {
                return null;
            }
        }
    }


    public AVLNode<T> getRoot() {
        return this.root;
    }

    /**
     * @param: avl node
     * @return: void (printing in order method).
     * function for self use.
     */
    public void inOrder(AVLNode<T> curr){
        if (curr == null){
            return;
        }

        if (curr.getLeftChild() != null){
            inOrder(curr.getLeftChild());
        }

        System.out.println(curr.getKey());

        if (curr.getRightChild() != null){
            inOrder(curr.getRightChild());
        }
    }

}


