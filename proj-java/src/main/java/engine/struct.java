package src.main.java.engine;
import src.main.java.common.Pair;

import java.util.*;
import java.lang.Long;
import java.time.LocalDate;

public class Struct {
    private Map<Long, Tag> tags;
    private Map<LocalDate, TreeHash> treeHashTable;
    private Map<Long, Users> userHashTable;
    private List<maxPosts> topN;

    public Struct() {
        this.tags = new HashMap<Long, Tag>();
        this.treeHashTable = new HashMap<LocalDate, TreeHash>();
        this.userHashTable = new HashMap<Long, Users>();
        this.topN = new ArrayList<maxPosts>();
    }

    public Map<Long, Tag> getTags() {
        return this.tags;
    }

    public Map<LocalDate, TreeHash> getTreeHashTable() {
        return this.treeHashTable;
    }

    public List<maxPosts> getTopN() {
        return this.topN;
    }

    public Map<Long, Users> getUserHashTable() {
        return this.userHashTable;
    }

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

    public void addUsers(Users u){
        this.userHashTable.put(u.getOwnerUserId(), u.clone());
    }

    public void addTags(Tag t){
        this.tags.put(t.getId(), t.clone());
    }


    public void addTopN(){
        for(Users i : this.userHashTable.values()) {
            maxPosts m = new maxPosts(i.getOwnerUserId(), i.getnPosts());
            this.topN.add(m.clone());
        }
        Collections.sort(this.topN, new nPostsComparator());
    }
}