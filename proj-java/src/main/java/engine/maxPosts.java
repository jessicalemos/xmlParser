public class maxPosts {
    private long id;
    private int nPosts;

    public maxPosts(long id, int nPosts) {
        this.id = id;
        this.nPosts = nPosts;
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
	
	public maxPosts clone() {
        return new maxPosts(this);
    }
}