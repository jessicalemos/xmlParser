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

    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.mostAnswered(aux,begin,end,N);
        return aux;
    }

    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.bestRep(aux,N,begin,end);
        return aux;
    }
}
