public class TreeHash {
    private Map<Long, Post> postTree;
    private long contadorR;
    private long contadorP;
    private LocalDate creationDate;

    public Map<Long, Post> getPostTree(){
        Map<Long, Post> neo = new TreeMap<Long, Post>();
        for(Map.Entry<Long, Post> entry : this.postTree.entrySet()){
            neo.put(entry.getKey(), entry.getValue());
        }
        return neo;
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        TreeHash p = (TreeHash) o;
        return this.contadorP == p.getContadorP() && p.getContadorR() == this.contadorR &&
                 p.getPostTree().equals(this.postTree) && p.getCreationDate().equals(this.creationDate);
    }

}