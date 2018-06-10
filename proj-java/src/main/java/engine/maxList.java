public class maxList {
    private long id;
    private LocalDate creationDate;

    public maxList() {
        this.id = 0;
        this.creationDate = LocalDate.now();
    }

    public maxList(maxList c) {
        this.id = c.getId();
        this.creationDate = c.getCreationDate();
    }
	
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

    public maxList clone() {
        return new maxList(this);
    }
}