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


    public void addTop(){
        for(Users i : this.userHashTable.values()) {
            maxPosts m = new maxPosts(i.getOwnerUserId(), i.getnPosts());
            maxPosts mr = new maxPosts(i.getOwnerUserId(), i.getReputation());
            this.topN.add(m.clone());
            this.topR.add(mr.clone());
        }
        Collections.sort(this.topN, new maxPostsComparator());
        Collections.sort(this.topR, new maxPostsComparator());
    }

    public void getPair(Pair p, LocalDate begin, LocalDate end){
        long respostas = 0, perguntas = 0;
        for(TreeHash t : this.treeHashTable.values())
            if(t.getCreationDate().equals(begin) || t.getCreationDate().equals(end) ||
                    (t.getCreationDate().isAfter(begin) && t.getCreationDate().isBefore(end))){
                respostas += t.getContadorR();
                perguntas += t.getContadorP();
            }
        p.setFst(perguntas);
        p.setSecond(respostas);
    }

    public void getList(List<Long> l, LocalDate begin, LocalDate end, String tag){
        List<maxList> aux = new ArrayList<maxList>();
        for(TreeHash t : this.treeHashTable.values())
            if(t.getCreationDate().equals(begin) || t.getCreationDate().equals(end) ||
                    (t.getCreationDate().isAfter(begin) && t.getCreationDate().isBefore(end))) {
                for (Post p : t.getPostTree().values()) {
                    if (p.getPostTypeId() == 1 && p.getTag() != null) {
                        String[] splitted = p.getTag().split(">");
                        for (int i = 0; i< splitted.length; i++)
                            if (splitted[i].contains(tag)) {
                                String[] splitted2 = splitted[i].split("<");
                                if(splitted2[1].equals(tag)) {
                                    maxList m = new maxList(p.getId(), t.getCreationDate());
                                    aux.add(m.clone());
                                }
                            }
                    }
                }
            }
        Collections.sort(aux, new DataComparator());
        for(maxList i : aux)
            l.add(i.getId());
    }

    public Post procuraPost(long id){
        for(TreeHash i : this.treeHashTable.values())
            if (i.getPostTree().containsKey(id)) return i.getPostTree().get(id);
        return null;
    }

    public void getInfo(List<Long> ids, long id){
        if(this.userHashTable.containsKey(id)){
            List<maxList> user = this.userHashTable.get(id).getUserList();
            Collections.sort(user,new DataComparator());
            for(int i=0; i<10 && i<user.size(); i++)
                ids.add(user.get(i).getId());
        }
    }

    public void mostVoted(List<Long> aux, LocalDate begin, LocalDate end, int N) {
        List<maxPosts> l = new ArrayList<maxPosts>();
        for (TreeHash t : this.treeHashTable.values())
            if (t.getCreationDate().equals(begin) || t.getCreationDate().equals(end) ||
                    (t.getCreationDate().isAfter(begin) && t.getCreationDate().isBefore(end))) {
                for (Post p : t.getPostTree().values()) {
                    if (p.getPostTypeId() == 2) {
                        maxPosts m = new maxPosts(p.getId(), p.getScore());
                        l.add(m.clone());
                    }
                }
            }
            Collections.sort(l, new maxPostsComparator());
            for(int i=0; i<N && i<l.size(); i++)
                aux.add(l.get(i).getId());
    }
    
    public void mostAnswered(List<Long> aux, LocalDate begin, LocalDate end, int N) {
        Map<Long,maxMap> m = new HashMap<Long,maxMap>();
        for (TreeHash t : this.treeHashTable.values())
            if (t.getCreationDate().equals(begin) || t.getCreationDate().equals(end) ||
                    (t.getCreationDate().isAfter(begin) && t.getCreationDate().isBefore(end))) {
                for(Post p : t.getPostTree().values()){
                    if(p.getPostTypeId() == 1) {
                        if (!m.containsKey(p.getId())) {
                            maxMap mm = new maxMap(p.getId(), 0, 1);
                            m.put(p.getId(), mm);
                        } else m.get(p.getId()).setFlag(1);
                    }
                    else if(!m.containsKey(p.getParentID())){
                        maxMap mm = new maxMap(p.getParentID(),1,0);
                        m.put(p.getParentID(),mm);
                    }
                    else{
                        m.get(p.getParentID()).setCount(m.get(p.getParentID()).getCount()+1);
                    }
                }
            }
        List<maxMap> max = new ArrayList<maxMap>();
        for(maxMap j : m.values()) {
            if (j.getFlag() == 1)
                max.add(j.clone());
        }
        Collections.sort(max,new maxMapComparator());
        for(int i=0; i<N && i<max.size(); i++) {
            aux.add(max.get(i).getId());
        }
    }

    public void containsW(List<Long> aux, String word, int N){
        List<maxList> l = new ArrayList<maxList>();
        for (TreeHash t : this.treeHashTable.values())
            for (Post p : t.getPostTree().values()) {
                if(p.getTitle().contains(word)){
                    maxList m = new maxList(p.getId(),t.getCreationDate());
                    l.add(m.clone());
                }
            }
        Collections.sort(l,new DataComparator());
        for(int i=0; i<N && i<l.size(); i++)
            aux.add(l.get(i).getId());
    }

    public void both(List<Long> aux, int N, long id1, long id2){
        if(this.userHashTable.containsKey(id1) && this.userHashTable.containsKey(id2)) {
            List<maxList> l1 = this.userHashTable.get(id1).getUserList();
            List<maxList> l2 = this.userHashTable.get(id2).getUserList();
            List<Long> parents = new ArrayList<Long>();
            List<maxList> l = new ArrayList<maxList>();
            List<Long> v = new ArrayList<Long>();
            List<maxList> lmaior = l2, lmenor = l1;
            if(l1.size() > l2.size()) {
                lmaior = l1;
                lmenor = l2;
            }
            for(maxList m : lmenor){
                Post p = this.treeHashTable.get(m.getCreationDate()).getPostTree().get(m.getId());
                if(p.getPostTypeId() == 2){
                    long parent = p.getParentID();
                    parents.add(parent);
                }
                else parents.add(p.getId());
            }
            for(maxList i : lmaior) {
                Post p = this.treeHashTable.get(i.getCreationDate()).getPostTree().get(i.getId());
                if (p.getPostTypeId() == 2) {
                    if(!v.contains(p.getParentID())) {
                            long parent = p.getParentID();
                            if (parents.contains(parent)) {
                                maxList mx = new maxList(parent, i.getCreationDate());
                                l.add(mx.clone());
                                v.add(parent);
                            }
                        }
                } else if(!v.contains(p.getId())) {
                        if (parents.contains(p.getId())) {
                            maxList mx = new maxList(p.getId(), i.getCreationDate());
                            l.add(mx.clone());
                            v.add(p.getId());
                        }
                    }
            }
            Collections.sort(l,new DataComparator());
            for(int i=0; i<N && i<l.size(); i++)
                aux.add(l.get(i).getId());
        }
    }

    public long answer(long id) {
        int nRespostas = 0;
        double c = 0, max = 0;
        long idMax = -1;
        Post p = procuraPost(id);
        if (p != null) nRespostas = p.getAnswerCount();
        for (TreeHash i : this.treeHashTable.values()) {
            for (Post j : i.getPostTree().values())
                if (j.getPostTypeId() == 2 && j.getParentID() == id) {
                    c = 0.25 * this.userHashTable.get(j.getOwnerUserID()).getReputation() + j.getScore() * 0.65 +
                            j.getCommentCount() * 0.1;
                    if (c > max) {
                        max = c;
                        idMax = j.getId();
                    }
                    nRespostas--;
                }
            if (nRespostas == 0) break;
        }
        return idMax;
    }

    public void bestRep(List<Long> aux, int N, LocalDate begin, LocalDate end ){
        List<maxPosts> m = new ArrayList<maxPosts>();
        List<Long> users = new ArrayList<Long>();
        Map<Long,maxPosts> tag = new HashMap<Long,maxPosts>();
        for(int i=0; i<N && i<this.topR.size(); i++) {
            users.add(this.topR.get(i).getId());
        }
        for (TreeHash t : this.treeHashTable.values())
            if (t.getCreationDate().equals(begin) || t.getCreationDate().equals(end) ||
                    (t.getCreationDate().isAfter(begin) && t.getCreationDate().isBefore(end))) {
                for (Post p : t.getPostTree().values()) {
                       if(users.contains(p.getOwnerUserID()) && p.getTag()!=null){
                           String[] splitted = p.getTag().split(">");
                            for (int i = 0; i< splitted.length; i++){
                                String[] splitted2 = splitted[i].split("<");
                                if(splitted2.length>1) {
                                    long tagId = this.tags.get(splitted2[1]).getId();
                                    if(!tag.containsKey(tagId)) {
                                        maxPosts mx = new maxPosts(tagId, 1);
                                        tag.put(tagId, mx);
                                    }
                                    else tag.get(tagId).setnPosts(tag.get(tagId).getNPosts()+1);
                                }
                        }
                    }
                }
         }
         List<maxPosts> max = new ArrayList<maxPosts>();
         for(maxPosts j : tag.values())
             max.add(j.clone());
         Collections.sort(max,new maxPostsComparator());
         for(int i=0; i<N && i<max.size(); i++)
             aux.add(max.get(i).getId());
    }
}