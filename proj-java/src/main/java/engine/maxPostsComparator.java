package engine;

import java.util.Comparator;

public class maxPostsComparator implements Comparator<maxPosts> {

	/**
     * Compara duas maxPosts consoante o contador
     * @param c1 maxPosts 1
     * @param c2 maxPosts 2
     * @return O contador da maxPosts 1 é maior (-1); O contador da maxPosts 2 é maior (1); São iguais (0);
     */
    public int compare(maxPosts c1, maxPosts c2) {
        if (c1.getNPosts() < c2.getNPosts()) return 1;
        if (c1.getNPosts() > c2.getNPosts()) return -1;
        return 0;
    }
}
