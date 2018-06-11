package src.main.java.engine;

import java.util.Comparator;

public class DataComparator implements Comparator<maxList> {
    public int compare(maxList c1, maxList c2) {
        if (c1.getCreationDate().isBefore(c2.getCreationDate())) return 1;
        if (c1.getCreationDate().isAfter(c2.getCreationDate())) return -1;
        return 0;
    }
}