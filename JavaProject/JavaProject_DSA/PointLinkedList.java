public class PointLinkedList {
    PointLinkedList next;
    ObjectWithCoordinates data;

    public PointLinkedList(){
        this.data = null;
        this.next = null;
    }
    public PointLinkedList(ObjectWithCoordinates data, PointLinkedList next){
        this.data = data;
        this.next = next;

    }
    public PointLinkedList(ObjectWithCoordinates data){
        this.data = data;
        this.next = null;
    }
    public PointLinkedList(PointLinkedList pointLinkedList){
        this.data = pointLinkedList.data;
        this.next = pointLinkedList.next;
    }


    public PointLinkedList getNext() {
        return this.next;
    }

    public ObjectWithCoordinates getData() {
        return data;
    }

    public void setNext(PointLinkedList next) {
        this.next = next;
    }

    public void setData(ObjectWithCoordinates data) {
        this.data = data;
    }


    @Override
    public String toString() {
        return "PointLinkedList{" +
                "next=" + next +
                ", data=" + data +
                '}';
    }
}
