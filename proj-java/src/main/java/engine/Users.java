package src.main.java.engine;

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

    public Users(Users u) {
        this.ownerUserId = u.getOwnerUserId();
        this.displayName = u.getDisplayName();
        this.reputation = u.getReputation();
        this.nPosts = u.getnPosts();
        this.aboutMe = u.getAboutMe();
        this.userList = u.getUserList();
    }

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

    public int getnPosts() {
        return nPosts;
    }

    public void setnPosts(int nPosts) { 
    	this.nPosts = nPosts; 
    }

    public String getAboutMe() {
        return aboutMe;
    }

    public void setAboutMe(String aboutMe) {
        this.aboutMe = aboutMe;
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
    
    public Users clone() {
        return new Users(this);
    }
}