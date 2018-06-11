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

    public List<Long> topMostActive(int N){
        List<Long> aux = new ArrayList<Long>();
        if(N<=0) return aux;
        List<maxPosts> top = this.com.getTopN();
        for(int i=0; i<N && i<top.size(); i++)
            aux.add(top.get(i).getId());
        return aux;
    }

    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin)) return aux;
        this.com.getList(aux,begin,end,tag);
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
