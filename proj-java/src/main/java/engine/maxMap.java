package engine;

public class maxMap {
    private long id;
    private int count;
    private int flag;

    public maxMap() {
        this.id = 0;
        this.count = 0;
        this.flag = 0;
    }

    public maxMap(maxMap c) {
        this.id = c.getId();
        this.count = c.getCount();
        this.flag = c.getFlag();
    }

    public long getId() {
        return id;
    }

    public int getCount(){ 
        return count;
    }

    public int getFlag(){ 
        return flag;
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))


    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("O seu id é: ");
        sb.append(this.id);
        sb.append("com contador ");
        sb.append(this.count);
        sb.append("e flag");

    public maxMap clone() {
        return new maxMap(this);
    }
}
