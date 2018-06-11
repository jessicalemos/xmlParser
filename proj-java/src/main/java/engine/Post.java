package src.main.java.engine;

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

    /** Construtores */
   
    /**
     * Construtor vazio de um Post
     */
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

    public Post(Post p) {
        this.postTypeId = p.getPostTypeId();
        this.parentID = p.getParentID();
        this.id = p.getId();
        this.tag = p.getTag();
        this.title = p.getTitle();
        this.ownerUserID = p.getOwnerUserID();
        this.answerCount = p.getAnswerCount();
        this.commentCount = p.getCommentCount();
        this.score = p.getScore();
    }
    
    /** Métodos de instância */

    /**
     * Obter o tipo do Post, ou seja, se corresponde a um post tipo pergunta ou resposta
     * @return tipo do post
     */
    public int getPostTypeId() {
        return postTypeId;
    }

    /**
     * Obter o id do post da pergunta correspondente
     * @return id do post
     */
    public long getParentID() {
        return parentID;
    }

    /**
     * Obter o id do Post
     * @return id do post
     */
    public long getId() {
        return id;
    }

    /**
     * Obter as tags presentes no Post
     * @return tags
     */
    public String getTag() {
        return tag;
    }

    /**
     * Obter o título do Post
     * @return o título
     */
       public String getTitle() {
        return title;
    }

    /**
     * Obter o id do utilizador
     * @return o id do utilizador
     */
    public long getOwnerUserID() {
        return ownerUserID;
    }

    /**
     * Obter o número de respostas ao post
     * @return número de respostas
     */
    public int getAnswerCount() {
        return answerCount;
    }

    /**
     * Obter o número de comentários ao post
     * @return número de comentários
     */
    public int getCommentCount() {
        return commentCount;
    }

    /**
     * Obter o score de um post
     * @return o score
     */
    public int getScore() {
        return score;
    }

    /**
     * Altera o tipo do post
     * @param postTypeId  Novo tipo do post  
     */
    public void setPostTypeId(int postTypeId) {
        this.postTypeId = postTypeId;
    }

    /**
     * Altera o id do post da pergunta correspondente
     * @param parentID   Novo id da pergunta correspondente
     */
    public void setParentID(long parentID) {
        this.parentID = parentID;
    }

    /**
     * Altera o id do Post
     * @param id   Novo id
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Altera a Tag do post
     * @param tag   Nova Tag
     */
    public void setTag(String tag) {
        this.tag = tag;
    }

    /**
     * Altera o título do post
     * @param title   Novo título
     */
    public void setTitle(String title) {
        this.title = title;
    }

    /**
     * Altera o id do utilizador que criou o post
     * @param ownerUserID   Novo id
     */
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

    /**
     * Compara dois Posts
     * @param o post a comparar
     * @return È um post igual(true) ou não é (false)
     */
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

    /**
     * Faz a cópia de um post
     * @return cópia do post
     */
    public Post clone() {
        return new Post(this);
    }
}