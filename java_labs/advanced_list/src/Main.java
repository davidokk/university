import java.lang.reflect.Array;
import java.lang.reflect.Member;
import java.util.Arrays;
import java.util.ListIterator;

public class Main {
    public static void main(String[] args) {
       //testList();
       //testConstList();
    }

    static void testConstList() {
        MyList l = new MyList(Arrays.asList(1, 2, 3));
        Integer[] a = l.toArray(new Integer[0]);

        for (Integer i : a)
            System.out.print(i + " ");
        System.out.println();

        for (Integer integer : l) System.out.print(integer + " ");
        System.out.println();

        System.out.println(l.contains(2));
        System.out.println(l.contains(4));
        System.out.println(l.containsAll(Arrays.asList(1, 2)));

        l.print();
    }

    static void testList() {
        MyList l = new MyList();

        l.add(1); // добавление в пустой список
        l.add(1, 2); // добавление в конец списка
        l.add(1, 100); // добавление в середину
        l.add(0, 9); // в начало

        ListIterator<Integer> it = l.listIterator();
        //it.next();
        it.add(99);
        it.add(10000);
        it.add(333333);
        l.print();

        l.retainAll(Arrays.asList(1, 2, 4));
        l.print();
    }
}
