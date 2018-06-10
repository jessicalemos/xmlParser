package src.main.java.engine;

public class maxPosts {
    private long id;
    private int nPosts;

	public maxPosts() {
        this.id = 0;
        this.nPosts = 0;
    }
    
    public maxPosts(long id, int nPosts) {
        this.id = id;
        this.nPosts = nPosts;
    }

    public maxPosts(maxPosts c) {
        this.id = c.getId();
        this.nPosts = c.getNPosts();
    }
    
	public long getId() {
        return id;
    }

    public int getNPosts(){ 
    	return nPosts;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setnPosts(int nPosts) {
        this.nPosts = nPosts;
    }
	
	 public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        maxPosts p = (maxPosts) o;
        return p.getId() == this.id &&  p.getNPosts() == this.nPosts;
    }

	public maxPosts clone() {
        return new maxPosts(this);
    }
}