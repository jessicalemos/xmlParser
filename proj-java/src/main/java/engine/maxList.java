package engine;
import java.time.LocalDate;

public class maxList {
    private long id;
    private LocalDate creationDate;

/** Construtores */
   

    /**
     * Construtor vazio de uma maxList
     */
    public maxList() {
        this.id = 0;
        this.creationDate = LocalDate.now();
    }
    
    /**
     * Construtor por parâmetros de uma maxList
     * @param id              Id
     * @param creationDate    Data de criação do post
     */
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

    /**
     * Obter a data de criação
     * @return data de criação
     */
    public LocalDate getCreationDate() {
        return creationDate;
    }

    /**
     * Altera o id
     * @param id
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Altera a data de criação do post
     * @param creationDate      Data de criação
     */
    public void setCreationDate(LocalDate creationDate) {
        this.creationDate = creationDate;
    }

    /**
     * Compara duas maxList
     * @param a maxList a comparar
     * @return É uma maxList igual(true) ou não é (false)
     */
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        maxList p = (maxList) o;
        return p.getId() == this.id &&  p.getCreationDate().equals(this.creationDate);
    }

    /**
     * Imprime a informação de uma maxList
     * @return String com a informação
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("O id é");
        sb.append(this.id);
        sb.append("e foi criado em");
        sb.append(this.creationDate);
        sb.append(".\n");
        return sb.toString();
    }

    /**
     * Faz a cópia de uma maxList
     * @return a cópia da maxList
     */
    public maxList clone() {
        return new maxList(this);
    }
}