package engine;
import java.util.Map;
import java.util.TreeMap;
import java.time.LocalDate;

public class TreeHash {
    private Map<Long, Post> postTree;
    private long contadorR;
    private long contadorP;
    private LocalDate creationDate;

    /** Construtores */
   
    /**
     * Construtor vazio de uma TreeHash
     */
    public TreeHash() {
        this.postTree = new TreeMap <Long, Post>();
        this.contadorR = 0;
        this.contadorP = 0;
    }

    /**
     * Contrutor por parâmetros de uma TreeHash
     * @param postTree        Árvore de posts
     * @param contadorR       Número de posts do tipo resposta
     * @param contadorP       Número de posts do tipo pergunta
     * @param creationDate    Data de criação
     */
    public TreeHash(TreeMap<Long, Post> postTree, long contadorR, long contadorP, LocalDate creationDate) {
        this.postTree = new TreeMap <Long, Post>();
        if(postTree!=null) setPostTree(postTree);
        this.contadorR = contadorR;
        this.contadorP = contadorP;
        this.creationDate = creationDate;
    }

    /**
     * Constrói uma TreeHash a partir de um definido
     * @param TreeHash
     */
    public TreeHash(TreeHash a) {
        this.postTree = a.getPostTree();
        this.contadorR = a.getContadorR();
        this.contadorP = a.getContadorP();
        this.creationDate = a.getCreationDate();
    }

    /** Métodos de instância */

    /**
     * Obter a árvore dos posts de uma dada data
     * @return postTree
     */
    public Map<Long, Post> getPostTree(){
        Map<Long, Post> neo = new TreeMap<Long, Post>();
        for(Map.Entry<Long, Post> entry : this.postTree.entrySet()){
            neo.put(entry.getKey(), entry.getValue());
        }
        return neo;
    }

    /**
     * Alterar a árvore com os posts de uma dada data
     * @param utilizadores  Árvore com os posts
     */
    private void setPostTree(Map<Long, Post> utilizadores) {
        this.postTree = new TreeMap<Long, Post>();
        for(Map.Entry<Long, Post> entry: utilizadores.entrySet())
            this.postTree.put(entry.getKey(), entry.getValue().clone());
    }

    /**
     * Obter o contador com os posts do tipo resposta
     * @return número de posts respostas
     */
    public long getContadorR() {
        return contadorR;
    }

    /**
     * Altera o contador com os posts do tipo resposta
     * @param contadorR    Número de posts respostas
     */
    public void setContadorR(long contadorR) {
        this.contadorR = contadorR;
    }
    
    /**
     * Obter o número de posts do tipo pergunta
     * @return número de posts 
     */
    public long getContadorP() {
        return contadorP;
    }

    /**
     * Altera o número de posts do tipo pergunta
     * @param contadorP    Número de posts
     */
    public void setContadorP(long contadorP) {
        this.contadorP = contadorP;
    }

    /**
     * Obter a data de criação
     * @return data 
     */
    public LocalDate getCreationDate() {
        return creationDate;
    }

    /**
     * Altera a data de criação
     * @param creationDate    Nova data 
     */
    public void setCreationDate(LocalDate creationDate) {
        this. creationDate = creationDate;
    }

    /**
     * Adiciona um post à árvore dos posts de uma dada data
     * @param p Post a adicionar
     */
    public void addTreeMap(Post p){
        this.postTree.put(p.getId(),p);
    }

    /**
     * Compara duas TreeHash
     * @param a TreeHash a comparar
     * @return É uma TreeHash igual (true) ou não é (false)
     */
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        TreeHash p = (TreeHash) o;
        return this.contadorP == p.getContadorP() && p.getContadorR() == this.contadorR &&
                 p.getPostTree().equals(this.postTree) && p.getCreationDate().equals(this.creationDate);
    }

    /**
     * Imprime a informação de uma TreeHash
     * @return String com a informação
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Número de posts do tipo resposta: ");
        sb.append(this.contadorR);
        sb.append(".\n Número de posts do tipo pergunta: ");
        sb.append(this.contadorP);
        sb.append(".\n Data de criação: ");
        sb.append(this.creationDate);
        sb.append(".\n Árvore dos posts: \n");
        for(Post i : this.postTree.values())
            sb.append(i.toString());
        sb.append(".\n");
        return sb.toString();
    }
    
    /**
     * Faz a cópia de uma TreeHash
     * @return cópida da TreeHash
     */
    public TreeHash clone() {
        return new TreeHash(this);
    }
}