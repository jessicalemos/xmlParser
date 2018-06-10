package src.main.java.engine;

public class Tag {
    private long id;
    private String tagName;

    public Tag(Tag t) {
        this.id = t.getId();
        this.tagName = t.getTagName();
    }

