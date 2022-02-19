public class ObjectWithCoordinatesImpl implements ObjectWithCoordinates{

    public int x;
    public int y;
    public Object data;


    /**
     * @param: constructor full args parameters: x,y,data.
     * @return: Constructor.
     */
    public ObjectWithCoordinatesImpl(int x, int y, Object data){
        this.x = x;
        this.y = y;
        this.data = data;
    }

    /**
     * @param: empty Constructor.
     * @return: Constructor.
     */
    public ObjectWithCoordinatesImpl(){
        this.x = 0;
        this.y = 0;
        this.data = null;
    }


    // GETTERS & SETTERS:
    @Override
    public int getX() {
        return this.x;
    }

    @Override
    public int getY() {
        return this.y;
    }

    @Override
    public Object getData() {
        return this.data;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void setData(Object data) {
        this.data = data;
    }


    @Override
    public String toString() {
        return ""+ data + "";
    }
}
