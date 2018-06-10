public class Post {
    private int postTypeId; 
    private long parentID; 
    private long id;
    private String tag;

    public Post() {
        this.postTypeId = 0;
        this.parentID = 0;
        this.id = 0;
        this.tag = "";
        this.title = "";
        this.ownerUserID = 0;
        this.answerCount = 0;
        this.commentCount = 0;
        this.score = 0;
    }

    public int getPostTypeId() {
        return postTypeId;
    }

    public long getParentID() {
        return parentID;
    }

    public long getId() {
        return id;
    }

    public String getTag() {
        return tag;
    }
}