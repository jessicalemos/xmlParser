package src.main.java.engine;

import java.util.Comparator;

public class maxMapComparator implements Comparator<maxMap> {
    public int compare(maxMap c1, maxMap c2) {
        if (c1.getCount() < c2.getCount()) return 1;
        if (c1.getCount() > c2.getCount()) return -1;
        return 0;
    }
}