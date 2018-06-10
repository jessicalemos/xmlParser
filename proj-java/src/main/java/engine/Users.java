public class Users {
    private long ownerUserId;
    private String displayName;
    private int reputation;
    private int nPosts;
    private String aboutMe;
    private List<maxList> userList;

    public Users() {
        this.ownerUserId = 0;
        this.displayName = "";
        this.reputation = 0;
        this.nPosts = 0;
        this.aboutMe = "";
        this.userList = new ArrayList<maxList>();
    }

    public Users(long ownerUserId, String displayName, int reputation, String aboutMe, ArrayList<maxList> userList) {
        this.ownerUserId = ownerUserId;
        this.displayName = displayName;
        this.reputation = reputation;
        this.nPosts = 0;
        this.aboutMe = aboutMe;
        this.userList = new ArrayList<maxList>();
        if(userList!=null) setUserList(userList);
    }

    public long getOwnerUserId() {
        return ownerUserId;
    }

    public void setOwnerUserId(long ownerUserId) {
        this.ownerUserId = ownerUserId;
    }

    public String getDisplayName() {
        return displayName;
    }

    public void setDisplayName(String displayName) {
        this.displayName = displayName;
    }

    public int getReputation() {
        return reputation;
    }

    public void setReputation(int reputation) {
        this.reputation = reputation;
    }

    public int getnPosts() {
        return nPosts;
    }

    public void setnPosts(int nPosts) { 
    	this.nPosts = nPosts; 
    }

    public String getAboutMe() {
        return aboutMe;
    }

    public void setAboutMe(String aboutMe) {
        this.aboutMe = aboutMe;
    }

    public ArrayList<maxList> getUserList(){
        ArrayList<maxList> aux = new ArrayList<maxList>();
        for(maxList i : this.userList){
            aux.add(i.clone());
        }
        return aux;
    }

    public Users clone() {
        return new Users(this);
    }
}