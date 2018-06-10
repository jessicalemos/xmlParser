public class Struct {
    private Map<Long, Tag> tags;
    private Map<LocalDate, TreeHash> treeHashTable;
    private Map<Long, Users> userHashTable;
    private List<maxPosts> topN;

    public void addPosts(Post p, LocalDate data){
        if (this.treeHashTable.containsKey(data)) {
            this.treeHashTable.get(data).addTreeMap(p.clone());
        } else {
            this.treeHashTable.put(data, new TreeHash());
            this.treeHashTable.get(data).setCreationDate(data);
            this.treeHashTable.get(data).addTreeMap(p.clone());
        }
        TreeHash t = this.treeHashTable.get(data);
        if (p.getPostTypeId() == 1)  t.setContadorP(t.getContadorP()+1);
        if (p.getPostTypeId() == 2) t.setContadorR(t.getContadorR()+1);
        maxList list = new maxList(p.getId(), data);
        if (this.userHashTable.containsKey(p.getOwnerUserID())) {
            this.userHashTable.get(p.getOwnerUserID()).addUserList(list);
            Users u = this.userHashTable.get(p.getOwnerUserID());
            u.setnPosts(u.getnPosts()+1);
        }
    }
}