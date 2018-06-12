package engine;


import java.util.Comparator;

public class DataComparator implements Comparator<maxList> {

	/**
     * Compara duas maxLists consoante a data de criação
     * @param c1 maxList 1
     * @param c2 maxList 2
     * @return A data da maxList 1 é maior (-1); A data da maxList 2 é maior (1); São iguais (0);
     */
    public int compare(maxList c1, maxList c2) {
        if (c1.getCreationDate().isBefore(c2.getCreationDate())) return 1;
        if (c1.getCreationDate().isAfter(c2.getCreationDate())) return -1;
        return 0;
    }
}