package engine;

import common.Pair;
import li3.TADCommunity;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Queries implements TADCommunity {
    private struct com;
    private Parse parse;

    /**
     * Função responsável por iniciar as estruturas
     */
    public void init(){
        this.com = new struct();
        this.parse = new Parse();
    }

    /**
     * Carrega a informação dos diferentes ficheiros para a estrutura
     * @param dumpPath
     */
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

    /**
     * Query 1 - Devolve o tı́tulo do post e o nome do autor
     * @param id  Id de um post
     * @return    Par com o título do post e o nome do autor
     */
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

    /**
     * Query 2 - Devolve o top N utilizadores com maior número de posts de sempre
     * @param N  N pedido no top N
     * @return   Lista com os ids dos utilizadores com maior número de posts 
     */
    public List<Long> topMostActive(int N){
        List<Long> aux = new ArrayList<Long>();
        if(N<=0) return aux;
        List<maxPosts> top = this.com.getTopN();
        for(int i=0; i<N && i<top.size(); i++)
            aux.add(top.get(i).getId());
        return aux;
    }

    /**
     * Query 3 - Devolve o número total de posts, perguntas e respostas separadamente, num dado intervalo de tempo
     * @param begin  Data inicial
     * @param end    Data final
     * @return       Par com o número de perguntas e número de respostas
     */
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        long respostas = 0, perguntas = 0;
        Pair pair;
        pair = new Pair(perguntas,respostas);
        if(end.isBefore(begin)) return pair;
        this.com.getPair(pair,begin,end);
        return pair;
    }

    /**
     * Query 4 - Devolve todas as perguntas que contenham uma determinada tag num dado intervalo de tempo
     * @param  tag     Tag a comparar
     * @param  begin   Data inicial
     * @param  end     Data final
     * @return         Lista com os ids das perguntas
     */
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin)) return aux;
        this.com.getList(aux,begin,end,tag);
        return aux;
    }

    /**
     * Query 5 - Devolve a informação do seu perfil e os ids dos seus 10 últimos posts
     * @param  id     Id de um utilizador
     * @return        Par que contém a short bio e os ids dos posts relativos ao user
     */
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

    /**
     * Query 6 - Devolve os ids das N respostas com mais votos num dado intervalo de tempo
     * @param N      N pedido no Top N
     * @param begin  Data inicial
     * @param end    Data final
     * @return       Lista com os ids das N respostas com mais votos
     */
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.mostVoted(aux,begin,end,N);
        return aux;
    }

    /**
     * Query 7 - Devolve os ids das N perguntas com mais respostas num dado intervalo de tempo
     * @param N      N pedido na Top N
     * @param begin  Data inicial
     * @param end    Data final
     * @return       Lista com os ids das N perguntas com mais respostas
     */
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.mostAnswered(aux,begin,end,N);
        return aux;
    }

    /**
     * Query 8 - Devolve uma lista com os ids de N perguntas cujos tı́tulos contenham uma dada palavra 
     * @param  word        Palavra a comparar
     * @param  N           N pedido no top N
     * @return             Lista com os ids de N perguntas cujos tı́tulos contenham a palavra
     */
    public List<Long> containsWord(int N, String word){
        List<Long> aux = new ArrayList<Long>();
        if(N<=0) return aux;
        this.com.containsW(aux,word,N);
        return aux;
    }

    /**
     * Query 9 - Devolve as últimas N perguntas em que participaram dois utilizadores especı́ficos
     * @param N     N pedido no top N
     * @param id1   Id de um utilizador
     * @param id2   Id de um utilizador 
     * @return      Lista com os ids das N perguntas em que participaram os dois utilizadores 
     */
    public List<Long> bothParticipated(int N, long id1, long id2){
        List<Long> aux = new ArrayList<Long>();
        if(N<=0) return aux;
        this.com.both(aux,N,id1,id2);
        return aux;
    }
    
    /**
     * Query 10 - obter a melhor resposta, ou seja, com melhor média ponderada
     * @param id    Id de uma pergunta
     * @return      Id da pergunta com melhor média ponderada
     */
    public long betterAnswer(long id){
        return this.com.answer(id);
    }

    /**
     * Query 11 - Devolve os identificadores das N tags mais usadas pelos N utilizadores com melhor reputação num dado intervalo de tempo
     * @param N      N pedido no Top N
     * @param begin  Data inicial
     * @param end    Data final
     * @return       Lista com os ids das N tags mais usadas pelos N utilizadores com melhor reputação
     */
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        List<Long> aux = new ArrayList<Long>();
        if(end.isBefore(begin) || N<=0) return aux;
        this.com.bestRep(aux,N,begin,end);
        return aux;
    }

    /**
     * Liberta todas as estruturas
     */
    public void clear(){
        this.com.getUserHashTable().clear();
        this.com.getTreeHashTable().clear();
        this.com.getTopN().clear();
        this.com.getTopR().clear();
        this.com.getTags().clear();
        this.com = null;
    }
}
