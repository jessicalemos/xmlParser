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

    public maxMap(long id, int count, int flag) {
        this.id = id;
        this.count = count;
        this.flag = flag;
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

    public void setId(long id) {
        this.id = id;
    }

    public void setCount(int count) {
        this.count = count;
    }

    /**
     * Altera a flag
     * @param flag
     */
    public void setFlag(int flag){ 
        this.flag = flag;
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        maxMap p = (maxMap) o;
        return p.getId() == this.id &&  p.getCount() == this.count && p.getFlag() == this.getFlag();
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("O seu id é: ");
        sb.append(this.id);
        sb.append("com contador ");
        sb.append(this.count);
        sb.append("e flag");
        sb.append(this.flag);
        sb.append("\n")
        return sb.toString();
    }

    public maxMap clone() {
        return new maxMap(this);
    }
}
