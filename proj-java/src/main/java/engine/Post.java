public class Post {
    private int postTypeId; 
    private long parentID; 
    private long id;
    private String tag;
    private String title; 
    private long ownerUserID; 
    private int answerCount; 
    private int commentCount;
    private int score;

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

    public Post(int postTypeId, long parentID, long id, String tag, String title, long ownerUserID, int answerCount, int commentCount, int score) {
        this.postTypeId = postTypeId;
        this.parentID = parentID;
        this.id = id;
        this.tag = tag;
        this.title = title;
        this.ownerUserID = ownerUserID;
        this.answerCount = answerCount;
        this.commentCount = commentCount;
        this.score = score;
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

       public String getTitle() {
        return title;
    }

    public long getOwnerUserID() {
        return ownerUserID;
    }

    public int getAnswerCount() {
        return answerCount;
    }

    public int getCommentCount() {
        return commentCount;
    }

    public int getScore() {
        return score;
    }

    public void setPostTypeId(int postTypeId) {
        this.postTypeId = postTypeId;
    }

    public void setParentID(long parentID) {
        this.parentID = parentID;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setTag(String tag) {
        this.tag = tag;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setOwnerUserID(long ownerUserID) {
        this.ownerUserID = ownerUserID;
    }

    public void setAnswerCount(int answerCount) {
        this.answerCount = answerCount;
    }

    public void setCommentCount(int commentCount) {
        this.commentCount = commentCount;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        Post p = (Post) o;
        return this.postTypeId == p.getPostTypeId() && p.getParentID() == this.parentID &&
                p.getId() == (this.id) && p.getTag().equals(this.tag) && p.getTitle().equals(this.title) &&
                p.getOwnerUserID() == (this.getOwnerUserID()) &&
                p.getAnswerCount() == (this.answerCount) && p.getCommentCount() == (this.commentCount) &&
                p.getScore() == (this.score);
    }

    public Post clone() {
        return new Post(this);
    }
}