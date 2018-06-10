package src.main.java.engine;

public class Tag {
    private long id;
    private String tagName;

    public Tag(){
        this.id = 0;
        this.tagName = "";
    }

    public Tag(Tag t) {
        this.id = t.getId();
        this.tagName = t.getTagName();
    }

	public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        Tag t = (Tag) o;
        return t.getId() == (this.id) && t.getTagName().equals(this.tagName);
    }
