package engine;

import src.main.java.common.Pair;
import src.main.java.engine.Parse;
import src.main.java.engine.Post;
import src.main.java.engine.Struct;
import src.main.java.engine.maxPosts;
import src.main.java.li3.TADCommunity;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Queries implements TADCommunity {
    private Struct com;
    private Parse parse;

    public void init(){
        this.com = new Struct();
        this.parse = new Parse();
    }

    public void load(String dumpPath){
        init();
        ArrayList<String> aux = new ArrayList<>();
        StringBuilder su = new StringBuilder();
        su.append(dumpPath);
        su.append("/Users.xml");
        aux.add(su.toString());
        StringBuilder sp = new StringBuilder();
        sp.append(dumpPath);
        sp.append("/Posts.xml");
        aux.add(sp.toString());
        StringBuilder st = new StringBuilder();
        st.append(dumpPath);
        st.append("/Tags.xml");
        aux.add(st.toString());
        for(int i=0; i<3; i++){
            if (i==0) parse.parseUsers(aux.get(i),this.com);
            else if (i==1) parse.parsePosts(aux.get(i),this.com);
            else parse.parseTags(aux.get(i),this.com);
        }
        this.com.addTop();
    }

    public Pair<String,String> infoFromPost(long id){
        String nome = null, title = null;
        Post p = this.com.procuraPost(id);
        if (p != null){
            if (p.getPostTypeId() == 1){
                title = p.getTitle();
                if(this.com.getUserHashTable().containsKey(p.getOwnerUserID()))
                    nome = this.com.getUserHashTable().get(p.getOwnerUserID()).getDisplayName();
            }
            else{
                Post parent = this.com.procuraPost(p.getParentID());
                title = parent.getTitle();
                if(this.com.getUserHashTable().containsKey(parent.getOwnerUserID()))
                    nome = this.com.getUserHashTable().get(parent.getOwnerUserID()).getDisplayName();
            }
        }
        Pair pair;
        pair = new Pair(title,nome);
        return pair;
    }

    public List<Long> topMostActive(int N){
        List<Long> aux = new ArrayList<Long>();
        if(N<=0) return aux;
        List<maxPosts> top = this.com.getTopN();
        for(int i=0; i<N && i<top.size(); i++)
            aux.add(top.get(i).getId());
        return aux;
    }

    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        long respostas = 0, perguntas = 0;
        Pair pair;
        pair = new Pair(perguntas,respostas);
        if(end.isBefore(begin)) return pair;
        this.com.getPair(pair,begin,end);
        return pair;
    }

    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin)) return aux;
        this.com.getList(aux,begin,end,tag);
        return aux;
    }

    public Pair<String, List<Long>> getUserInfo(long id){
        String aboutMe = null;
        List<Long> ids = new ArrayList<Long>();
        if(this.com.getUserHashTable().containsKey(id)){
            aboutMe = this.com.getUserHashTable().get(id).getAboutMe();}
        this.com.getInfo(ids,id);
        Pair pair;
        pair = new Pair(aboutMe,ids);
        return pair;
    }

    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.mostVoted(aux,begin,end,N);
        return aux;
    }

    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.mostAnswered(aux,begin,end,N);
        return aux;
    }

    public List<Long> containsWord(int N, String word){
        List<Long> aux = new ArrayList<Long>();
        if(N<=0) return aux;
        this.com.containsW(aux,word,N);
        return aux;
    }

    public List<Long> bothParticipated(int N, long id1, long id2){
        List<Long> aux = new ArrayList<Long>();
        if(N<=0) return aux;
        this.com.both(aux,N,id1,id2);
        return aux;
    }
    
    public long betterAnswer(long id){
        return this.com.answer(id);
    }

    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.bestRep(aux,N,begin,end);
        return aux;
    }

    public void clear(){
        this.com.getUserHashTable().clear();
        this.com.getTreeHashTable().clear();
        this.com.getTopN().clear();
        this.com.getTopR().clear();
        this.com.getTags().clear();
        this.com = null;
    }
}
