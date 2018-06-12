package engine;

public class maxMap {
    private long id;
    private int count;
    private int flag;

    public maxMap(maxMap c) {
        this.id = c.getId();
        this.count = c.getCount();
        this.flag = c.getFlag();
    }

    public long getId() {
        return id;
    }

    public maxMap clone() {
        return new maxMap(this);
    }
}
