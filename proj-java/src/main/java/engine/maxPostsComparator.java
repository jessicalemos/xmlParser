package src.main.java.engine;

import java.util.Comparator;

public class maxPostsComparator implements Comparator<maxPosts> {
    public int compare(maxPosts c1, maxPosts c2) {
        if (c1.getNPosts() < c2.getNPosts()) return 1;
        if (c1.getNPosts() > c2.getNPosts()) return -1;
        return 0;
    }
}
