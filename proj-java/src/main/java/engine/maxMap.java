package engine;

public class maxMap {
    private long id;
    private int count;
    private int flag;

	/** Construtores */
   
    /**
     * Construtor vazio de uma maxMap
     */
    public maxMap() {
        this.id = 0;
        this.count = 0;
        this.flag = 0;
    }

     /**
     * Construtor por parâmetros de uma maxMap
     * @param id      Id do post
     * @param count   Contador
     * @param flag    Indica se a condição é verdadeira
     */
    public maxMap(long id, int count, int flag) {
        this.id = id;
        this.count = count;
        this.flag = flag;
    }

    public maxMap(maxMap c) {
        this.id = c.getId();
        this.count = c.getCount();
        this.flag = c.getFlag();
    }
	
	/** Métodos de instância */

    /**
     * Obter o id do post
     * @return id do post
     */
    public long getId() {
        return id;
    }

    public int getCount(){ 
        return count;
    }

    public int getFlag(){ 
        return flag;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setCount(int count) {
        this.count = count;
    }

    /**
     * Altera a flag
     * @param flag
     */
    public void setFlag(int flag){ 
        this.flag = flag;
    }

    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        maxMap p = (maxMap) o;
        return p.getId() == this.id &&  p.getCount() == this.count && p.getFlag() == this.getFlag();
    }

    /**
     * Imprime a informação de uma maxMap
     * @return String com a informação
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("O seu id é: ");
        sb.append(this.id);
        sb.append("com contador ");
        sb.append(this.count);
        sb.append("e flag");
        sb.append(this.flag);
        sb.append("\n");
        return sb.toString();
    }

    /**
     * Faz a cópia de uma maxMap
     * @return cópia da maxMap
     */
    public maxMap clone() {
        return new maxMap(this);
    }
}
