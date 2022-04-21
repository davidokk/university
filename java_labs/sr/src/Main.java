import java.util.*;

public class Main {
    public static void main(String[] args) {
        testSet();
        testMap();
    }

    static void testSet() {
        TreeSet<String> strs = new TreeSet<>();
        SortedSet set = strs;
        // добавление элемента другого типа игнорируется
        set.add(new Date());
        // исключение вызвано при обращении к элементу
        // String a = strs.iterator().next();
        // java.lang.ClassCastException: class java.util.Date cannot be cast to class java.lang.String

        SortedSet<String> safeStrs = Collections.checkedSortedSet(strs, String.class);
        SortedSet set1 = safeStrs;
        // исключение вызвано при добавлении
        // set1.add(1);
        // java.lang.ClassCastException: Attempt to insert class java.lang.Integer element into collection with element type class java.lang.String
    }

    static void testMap() {
        TreeMap<Integer, String> tmap = new TreeMap<>();
        NavigableMap map = tmap;
        // неправильное добавление игнорируется
        map.put(1, 1);
        // исключение при обращении
        // String a = tmap.get(1);
        // java.lang.ClassCastException: class java.lang.Integer cannot be cast to class java.lang.String

        NavigableMap safeMap = Collections.checkedNavigableMap(tmap, Integer.class, String.class);
        NavigableMap map1 = safeMap;
        // исключение при добавлении
        // map1.put(1, new Date());
        // java.lang.ClassCastException: Attempt to insert class java.util.Date value into map with value type class java.lang.String
    }
}
