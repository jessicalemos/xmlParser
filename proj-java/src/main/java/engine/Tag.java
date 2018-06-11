package src.main.java.engine;

public class Tag {
    private long id;
    private String tagName;
    
    /** Construtores */

    /**
     * Constrói uma Tag sem parâmetros
     */
    public Tag(){
        this.id = 0;
        this.tagName = "";
    }

    public Tag(long id, String tagName) {
        this.id = id;
        this.tagName = tagName;
    }
    
    public Tag(Tag t) {
        this.id = t.getId();
        this.tagName = t.getTagName();
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getTagName() {
        return tagName;
    }

    /**
     * Altera o nome da Tag
     * @param tagName   Nome da Tag
     */
    public void setTagName(String tagName) {
        this.tagName = tagName;
    }

    /**
     * Compara duas Tags
     * @param a Tag a comparar
     * @return é uma Tag igual (true) ou não (false)
     */
	public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        Tag t = (Tag) o;
        return t.getId() == (this.id) && t.getTagName().equals(this.tagName);
    }

    /**
     * Faz uma cópia da Tag
     * @return cópia da Tag
     */
    public Tag clone() {
        return new Tag(this);
    }
}
