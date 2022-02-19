import org.w3c.dom.ranges.Range;

import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Random;


public class StudentSolution implements MyInterface {
    public AVL<ObjectWithCoordinates> AVLX;
    public AVL<ObjectWithCoordinates> AVLY;


    // Constructor
    public StudentSolution() {
        this.AVLX = new AVL<ObjectWithCoordinates>();
        this.AVLY = new AVL<ObjectWithCoordinates>();
    }

    /**
     * @param: as we asked for: object name, int x, int y.
     * @return: void, inserting data from DB file into AVL trees.
     */
    @Override
    public void insertDataFromDBFile(String objectName, int objectX, int objectY) {
        // TODO Auto-generated method stub
        ObjectWithCoordinates objectWithCoordinates = new ObjectWithCoordinatesImpl(objectX, objectY, objectName);
        this.AVLX.insert(objectX, objectWithCoordinates);
        this.AVLY.insert(objectY, objectWithCoordinates);
    }


    /**
     * @param: two points for generating a rectangle.
     * @return: this function takes two AVL trees, one for X coordinate and one for Y coordinate.
     * this function relate every tree (by x or y) as "1D".
     * we search for all X's in the given range and put them into LinkedList,
     * than search for all the Y's in the given range and put them into LinkedList.
     * after that - put the X's into HashTable.
     * after all of the X's are in the hash, the function iterates the Y's LinkedList and checking
     * if the Node found in the hash. if so - put him into "Solution LL"' else - throw it out.
     * last, we convert the Solution LL into Strings array and return it.
     */
    @Override
    public String[] firstSolution(int leftTopX, int leftTopY, int rightBottomX,
                                  int rightBottomY) {

        LinkedList<ObjectWithCoordinates> solution = new LinkedList<>();
        int count = 0;

        LinkedList<ObjectWithCoordinates> linkedListX = RangeX(this.AVLX.getRoot(), leftTopX, rightBottomX);
        LinkedList<ObjectWithCoordinates> linkedListY = RangeX(this.AVLY.getRoot(), rightBottomY, leftTopY);
        int max = Math.max(linkedListX.size(), linkedListY.size());
        HashTable hashTable = new HashTable(max);

        ListIterator<ObjectWithCoordinates> listIteratorX = linkedListX.listIterator();
        while (listIteratorX.hasNext()) {
            hashTable.insert(listIteratorX.next());
        }

        ListIterator<ObjectWithCoordinates> listIteratorY = linkedListY.listIterator();
        while (listIteratorY.hasNext()) {
            ObjectWithCoordinates temp = listIteratorY.next();
            if (hashTable.search(temp) != null) {
                solution.add(temp);
            }
        }
        int size = solution.size();
        String[] strings = new String[size];


        ListIterator<ObjectWithCoordinates> res = solution.listIterator();
        while (res.hasNext()) {
            ObjectWithCoordinates t = res.next();
            String s = ""+t.getData()+" X="+t.getX() +" Y="+t.getY();
            strings[count] = s;
            count++;
        }
        return strings;
    }


    /**
     * @param: same as first solution.
     * @return: we make 2 linked list of the related X and Y's as explained in first solution documentation.
     * than we put the max size between them into an array.
     * last we iterate the minimum LinkedList in order to find those values in the array.
     * for make in logarithmic time search we use an array binary search.
     * if we found that values - put them into "Solution LinkedList", else - throw them out.
     * last we convert the Solution LinkedList into Strings array and return it.
     */
    @Override
    public String[] secondSolution(int leftTopX, int leftTopY,
                                   int rightBottomX, int rightBottomY) {
        // TODO Auto-generated method stub
        LinkedList<ObjectWithCoordinates> solutions = new LinkedList<>();
        int count1 = 0;
        int count2 = 0;

        LinkedList<ObjectWithCoordinates> linkedListX = RangeX(this.AVLX.getRoot(), leftTopX, rightBottomX);
        LinkedList<ObjectWithCoordinates> linkedListY = RangeY(this.AVLY.getRoot(), rightBottomY, leftTopY);
        int max = Math.max(linkedListX.size(), linkedListY.size());
        ObjectWithCoordinates[] objectWithCoordinates = new ObjectWithCoordinates[max];

        if (linkedListX.size() >= linkedListY.size()) {
            ListIterator<ObjectWithCoordinates> maximum = linkedListX.listIterator();
            ListIterator<ObjectWithCoordinates> minimum = linkedListY.listIterator();
            while (maximum.hasNext()) {
                objectWithCoordinates[count1] = maximum.next();
                count1++;
            }
            while (minimum.hasNext()) {
                ObjectWithCoordinates temp = minimum.next();
                if (arrayBinarySearchX(objectWithCoordinates, temp.getX()) != null) {
                    solutions.add(temp);
                }
            }
        } else {
            ListIterator<ObjectWithCoordinates> maximum = linkedListY.listIterator();
            ListIterator<ObjectWithCoordinates> minimum = linkedListX.listIterator();
            while (maximum.hasNext()) {
                objectWithCoordinates[count2] = maximum.next();
                count2++;
            }
            while (minimum.hasNext()) {
                ObjectWithCoordinates temp = minimum.next();
                if (arrayBinarySearchY(objectWithCoordinates, temp.getY()) != null) {
                    solutions.add(temp);
                }
            }
        }
        int size = solutions.size();
        int c = 0;

        String[] strings = new String[size];
        ListIterator<ObjectWithCoordinates> res = solutions.listIterator();

        while (res.hasNext()) {
            ObjectWithCoordinates t = res.next();
            String s = ""+t.getData()+" X="+t.getX() +" Y="+t.getY();
            strings[c] = s;
            c++;
        }
        return strings;
    }

    //Binary search by X
    public ObjectWithCoordinates arrayBinarySearchX(ObjectWithCoordinates[] objectWithCoordinates, int key) {
        int right = objectWithCoordinates.length - 1;
        int left = 0;

        while (left <= right) {
            int mid = (right + left) / 2;
            if (objectWithCoordinates[mid].getX() == key) {
                return objectWithCoordinates[mid];
            }

            if (objectWithCoordinates[mid].getX() > key) {
                right = mid;
            } else {
                left = (mid + 1);
            }
        }
        return null;
    }


    //Binary search by Y.
    public ObjectWithCoordinates arrayBinarySearchY(ObjectWithCoordinates[] objectWithCoordinates, int key) {
        int right = objectWithCoordinates.length - 1;
        int left = 0;

        while (left <= right) {
            int mid = (right + left) / 2;
            if (objectWithCoordinates[mid].getY() == key) {
                return objectWithCoordinates[mid];
            }

            if (objectWithCoordinates[mid].getY() > key) {
                right = mid;
            } else {
                left = (mid + 1);
            }
        }
        return null;
    }


    /**
     * @param: GCA, int a (left range value), int b (right range value).
     * @return: all nodes in that range (by X).
     */
    public LinkedList<ObjectWithCoordinates> RangeX(AVLNode<ObjectWithCoordinates> avlNode, int a, int b) {
        // Finding the common ancestor:
        LinkedList<ObjectWithCoordinates> linkedList = new LinkedList<>();
        if (avlNode != null) {
            while (avlNode.getRightChild() != null && avlNode.getKey() < a) {
                avlNode = avlNode.getRightChild();
            }
            while (avlNode.getLeftChild() != null && avlNode.getKey() > b) {
                avlNode = avlNode.getLeftChild();
            }
            if (avlNode.getKey() >= a && avlNode.getKey() <= b) {
                inOrder1(avlNode, a, b, linkedList);
            }
        }
        return linkedList;
    }


    //INORDER func:
    public LinkedList<ObjectWithCoordinates> inOrder1(AVLNode<ObjectWithCoordinates> objectWithCoordinatesAVLNode, int a, int b, LinkedList<ObjectWithCoordinates> linkedList) {
        if (objectWithCoordinatesAVLNode.getLeftChild() != null) {
            inOrder1(objectWithCoordinatesAVLNode.getLeftChild(), a, b, linkedList);
        }

        if (objectWithCoordinatesAVLNode.getKey() >= a && objectWithCoordinatesAVLNode.getKey() <= b) {
            linkedList.add(objectWithCoordinatesAVLNode.getData());
        }

        if (objectWithCoordinatesAVLNode.getRightChild() != null) {
            inOrder1(objectWithCoordinatesAVLNode.getRightChild(), a, b, linkedList);
        }
        return linkedList;
    }


    /**
     * @param: GCA, int a (left range value), int b (right range value).
     * @return: all nodes in that range (by Y).
     */
    public LinkedList<ObjectWithCoordinates> RangeY(AVLNode<ObjectWithCoordinates> avlNode, int a, int b) {
        LinkedList<ObjectWithCoordinates> linkedList = new LinkedList<>();

        if (avlNode != null) {
            while (avlNode.getRightChild() != null && avlNode.getKey() < a) {
                avlNode = avlNode.getRightChild();
            }
            while (avlNode.getLeftChild() != null && avlNode.getKey() > b) {
                avlNode = avlNode.getLeftChild();
            }
            if (avlNode.getKey() >= a && avlNode.getKey() <= b) {
                inOrder2(avlNode, a, b, linkedList);
            }
        }
        return linkedList;
    }


    //INORDER FUNC:
    public LinkedList<ObjectWithCoordinates> inOrder2(AVLNode<ObjectWithCoordinates> objectWithCoordinatesAVLNode, int a, int b, LinkedList<ObjectWithCoordinates> linkedList) {
        if (objectWithCoordinatesAVLNode.getLeftChild() != null) {
            inOrder2(objectWithCoordinatesAVLNode.getLeftChild(), a, b, linkedList);
        }

        if (objectWithCoordinatesAVLNode.getKey() >= a && objectWithCoordinatesAVLNode.getKey() <= b) {
            linkedList.add(objectWithCoordinatesAVLNode.getData());
        }

        if (objectWithCoordinatesAVLNode.getRightChild() != null) {
            inOrder2(objectWithCoordinatesAVLNode.getRightChild(), a, b, linkedList);
        }
        return linkedList;
    }
}
