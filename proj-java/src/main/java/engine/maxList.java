package src.main.java.engine;
import java.time.LocalDate;

public class maxList {
    private long id;
    private LocalDate creationDate;

    public maxList() {
        this.id = 0;
        this.creationDate = LocalDate.now();
    }

    public maxList(long id, LocalDate creationDate) {
        this.id = id;
        this.creationDate = creationDate;
    }

    /**
     * Constrói uma maxList a partir de uma definida
     * @param c maxList
     */
    public maxList(maxList c) {
        this.id = c.getId();
        this.creationDate = c.getCreationDate();
    }
	
    /** Métodos de instância */

    /**
     * Obter o id
     * @return id
     */
	public long getId() {
        return id;
    }

    public LocalDate getCreationDate() {
        return creationDate;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setCreationDate(LocalDate creationDate) {
        this.creationDate = creationDate;
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        maxList p = (maxList) o;
        return p.getId() == this.id &&  p.getCreationDate().equals(this.creationDate);
    }

    /**
     * Faz a cópia de uma maxList
     * @return a cópia da maxList
     */
    public maxList clone() {
        return new maxList(this);
    }
}