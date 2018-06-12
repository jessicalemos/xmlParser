package engine;

public class maxPosts {
    private long id;
    private int nPosts;

	/** Construtores */

    /**
     * Construtor vazio de uma maxPosts
     */
	public maxPosts() {
        this.id = 0;
        this.nPosts = 0;
    }
    
    /**
     * Construtor por parâmetros de uma maxPosts
     * @param id       Id 
     * @param nPosts   Contador
     */
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

    /**
     * Altera o id
     * @param id  Novo id
     */
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

    /**
     * Imprime a informação de uma maxPost
     * @return String com a informação
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("O id do utilizador é ");
        sb.append(this.id); 
        sb.append(", sendo que publicou ");
        sb.append(this.nPosts);
        sb.append("posts.\n");
        return sb.toString();
    }

	public maxPosts clone() {
        return new maxPosts(this);
    }
}