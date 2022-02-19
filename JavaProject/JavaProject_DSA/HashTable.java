import java.util.Arrays;
import java.util.LinkedList;
import java.util.ListIterator;


public class HashTable {
    public LinkedList<ObjectWithCoordinates>[] Hash;
    public int m;

    // Constructors:
    public HashTable(int m) {
        this.m = m;
        this.Hash = new LinkedList[m];
    }
    public HashTable(){
        this.m = 11;
        this.Hash = new LinkedList[this.m];
    }


    //Hash function:
    /**
     * @param: ObjectWithCoordinates point,
     * @return: hash function as asked for.
     */
    public int h(ObjectWithCoordinates point) {
        int y = point.getY();
        int x = point.getX();
        return (x + y) % this.m;
    }


    /**
     * @param: object with coordinates.
     * insert this object into the hash table using
     * the hash function "h".
     * insertion as "Open Hashing" option - chaining.
     * @return: void. insertion.
     */
    public void insert(ObjectWithCoordinates object) {
        int i = h(object);
        LinkedList<ObjectWithCoordinates> ll = new LinkedList<ObjectWithCoordinates>();
        if (this.Hash[i] == null) {
            this.Hash[i] = ll;
            ll.add(0, object);
        } else {
            this.Hash[i].add(0, object);
        }
    }

    /**
     * @param: object with coordinates.
     * @return: if exist - the object, else- null.
     */
    public ObjectWithCoordinates search(ObjectWithCoordinates objectWithCoordinates) {
        int index = h(objectWithCoordinates);

        // Not in hash table !!!
        if (this.Hash[index] == null) return null;
        else {
            if (this.Hash[index].contains(objectWithCoordinates)) {
                return objectWithCoordinates;
            } else {
                return null;
            }
        }
    }

    /**
     * @param: int x, int y (coordinates of an object.
     * @return: if exist - the object, else- null.
     */
    public ObjectWithCoordinates search(int x, int y){
        ObjectWithCoordinates temp = new ObjectWithCoordinatesImpl(x,y, null);
        int index = h(temp);

        if (this.Hash[index] == null) return null;
        else{
            ListIterator<ObjectWithCoordinates> listIterator = this.Hash[index].listIterator();
            while(listIterator.hasNext()){
                ObjectWithCoordinates next = listIterator.next();
                if (next.getX() == x && next.getY() == y){
                    return next;
                }
            }
        }
        return null;
    }


    /**
     * AUTO GENERATE TO STRING METHOD-
     */
    @Override
    public String toString() {
        return "HashTable{" +
                "Hash=" + Arrays.toString(Hash) +
                ", m=" + m +
                '}';
    }
}

