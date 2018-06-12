package engine;

import java.util.ArrayList;
import java.util.List;

public class Users {
    private long ownerUserId;
    private String displayName;
    private int reputation;
    private int nPosts;
    private String aboutMe;
    private List<maxList> userList;

    /** Construtores */

    /**
     * Constrói um User sem parâmetros
     */
    public Users() {
        this.ownerUserId = 0;
        this.displayName = "";
        this.reputation = 0;
        this.nPosts = 0;
        this.aboutMe = "";
        this.userList = new ArrayList<maxList>();
    }

    /**
     * Construtor por parâmetros de um User
     * @param ownerUserId  Id do utilizador
     * @param displayName  Nome do utilizador
     * @param reputation   Reputação do utilizador
     * @param aboutMe      Short bio do utilizador
     * @param userList     Lista dos pots do utilizador     
     */
    public Users(long ownerUserId, String displayName, int reputation, String aboutMe, ArrayList<maxList> userList) {
        this.ownerUserId = ownerUserId;
        this.displayName = displayName;
        this.reputation = reputation;
        this.nPosts = 0;
        this.aboutMe = aboutMe;
        this.userList = new ArrayList<maxList>();
        if(userList!=null) setUserList(userList);
    }

    /**
     * Constroi um user a partir de um objeto definido
     * @param u User
     */
    public Users(Users u) {
        this.ownerUserId = u.getOwnerUserId();
        this.displayName = u.getDisplayName();
        this.reputation = u.getReputation();
        this.nPosts = u.getnPosts();
        this.aboutMe = u.getAboutMe();
        this.userList = u.getUserList();
    }
	/* Métodos de Instância */

    /**
     * Obter o id do utilizador
     * @return id do utilizador
     */
    public long getOwnerUserId() {
        return ownerUserId;
    }

    /**
     * Altera o id do utilizador
     * @param ownerUserId   Id do utilizador
     */
    public void setOwnerUserId(long ownerUserId) {
        this.ownerUserId = ownerUserId;
    }

    /**
     * Obter o nome do utilizador
     * @return nome do utilizador
     */
    public String getDisplayName() {
        return displayName;
    }

    /**
     * Altera o nome do utilizador
     * @param displayName   Nome do utilizador
     */
    public void setDisplayName(String displayName) {
        this.displayName = displayName;
    }

    /**
     * Obter a reputação do utilizador
     * @return reputação
     */
    public int getReputation() {
        return reputation;
    }

    /**
     * Altera a reputação do utilizador
     * @param reputation   Nova reputação
     */
    public void setReputation(int reputation) {
        this.reputation = reputation;
    }

    /**
     * Obter o número de posts
     * @return número de posts
     */
    public int getnPosts() {
        return nPosts;
    }

    /**
     * Altera o número de posts
     * @param número de posts
     */
    public void setnPosts(int nPosts) { 
    	this.nPosts = nPosts; 
    }

    /**
     * Obter uma pequena informação sobre o user
     * @return pequena informação sobre o user
     */
    public String getAboutMe() {
        return aboutMe;
    }

    /**
     * Altera a pequena informação sobre o user
     * @param aboutMe
     */
    public void setAboutMe(String aboutMe) {
        this.aboutMe = aboutMe;
    }

    /**
     * Adiciona uma maxList à lista de posts do utilizador
     * @param p    maxList
     */
    public void addUserList(maxList p){
        this.userList.add(p.clone());
    }
    
    /**
     * Altera a lista com os posts do utilizador
     * @param utilizador   Nova lista 
     */
    private void setUserList(ArrayList<maxList> utilizadores) {
        this.userList = new ArrayList<maxList>();
        for(maxList i : utilizadores)
            this.userList.add(i.clone());
    }

    /**
     * Obter a lista com os posts do utilizador
     * @return estrutura 
     */
    public ArrayList<maxList> getUserList(){
        ArrayList<maxList> aux = new ArrayList<maxList>();
        for(maxList i : this.userList){
            aux.add(i.clone());
        }
        return aux;
    }

    /**
     * Compara dois users
     * @param o user a comparar
     * @return é um user igual(true) ou não (false)
     */
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        Users u = (Users) o;
        return u.getOwnerUserId() == (this.ownerUserId) && u.getDisplayName().equals(this.displayName) &&
                u.getReputation() == (this.reputation) && u.getnPosts() == (this.nPosts) &&
                u.getAboutMe().equals(this.aboutMe) && u.getUserList().equals(this.userList);
    }

    /**
     * Imprime a informação de um User
     * @return String com a informação
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("O id do utilizador é ");
        sb.append(this.ownerUserId);
        sb.append(", cujo nome é ");
        sb.append(this.displayName);
        sb.append(".\n Tem");
        sb.append(this.reputation);
        sb.append(" pontos de reputação e tem");
        sb.append(this.nPosts);
        sb.append("posts.\n");
        sb.append("Lista dos posts do utilizador:\n");
        for(maxList m: this.userList)
            sb.append(m.toString());
        sb.append(".\n");
        return sb.toString();
    }
    
    /**
     * Faz a cópia de um user
     * @return cópia do user
     */
    public Users clone() {
        return new Users(this);
    }
}
