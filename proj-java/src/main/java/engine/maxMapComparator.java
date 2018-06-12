package engine;

import java.util.Comparator;

public class maxMapComparator implements Comparator<maxMap> {

    /**
     * Compara duas maxMaps consoante o contador
     * @param c1 maxMap 1
     * @param c2 maxMap 2
     * @return O contador da maxMap 1 é maior (-1); O contador da maxMap 2 é maior (1); São iguais (0);
     */
    public int compare(maxMap c1, maxMap c2) {
        if (c1.getCount() < c2.getCount()) return 1;
        if (c1.getCount() > c2.getCount()) return -1;
        return 0;
    }
}