import java.sql.Array;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        List l = enterList(0);
        l.print();
        int lastEl = 0;
        System.out.println("Enter the penultimate element: ");
        int i = scanner.nextInt();
        if (l.isEmpty()) {
            l.pushBack(i);
            l.print();
        } else {
            ListIterator it = l.iterator();
            ListIterator copy_it = it.clone();
            while (copy_it.hasNext()) {
                it.next();
                lastEl = copy_it.next();
            }
            it.remove();
            l.pushBack(i);
            l.pushBack(lastEl);
            l.print();
        }
    }

    static ArrayList<List> ans;

    public static void solveTask() {
        List l = enterList(0);

        ArrayList<List> lists = new ArrayList<List>();
        lists.add(enterList(1));
        lists.add(enterList(2));
        lists.add(enterList(3));

        ans = new ArrayList<List>();
        ans.add(new List());
        ans.add(new List());
        ans.add(new List());
        ans.add(new List());

        int i = 0;
        ListIterator it = l.iterator();
        while (it.hasNext() && i < lists.size()) {
            ListIterator copy_it = it.clone();
            if (contains(it, lists.get(i))) {
                ++i;
            } else {
                it = copy_it;
                ans.get(i).pushBack(it.next());
            }
        }

        while (it.hasNext())
            ans.get(ans.size() - 1).pushBack(it.next());

        if (i < lists.size())
            System.out.println("Solution doesn't exist");
        else
            printAnswer();
    }

    private static void printAnswer() {
        System.out.print("L = ");
        ans.get(0).print();
        System.out.print(" + Ls1 + ");
        ans.get(1).print();
        System.out.print(" + Ls2 + ");
        ans.get(2).print();
        System.out.print(" + Ls3 + ");
        ans.get(3).print();
    }

    private static boolean contains(ListIterator it, List l) {
        ListIterator it1 = l.iterator();
        while (it.hasNext() && it1.hasNext()) {
            if (!it.next().equals(it1.next()))
                return false;
        }
        return !it1.hasNext();
    }

    private static List enterList(int num) {
        List l = new List();
        System.out.println("Enter L" + (num > 0 ? "s" + num : ""));
        int n = scanner.nextInt();
        while (n-- != 0)
            l.pushBack(scanner.nextInt());
        return l;
    }

    static Scanner scanner = new Scanner(System.in);

    public static void listTest() {
        List empty = new List();
        empty.pushFront(1);
        empty.popBack();
        empty.print();

        List list = new List();
        list.pushBack(1);
        list.pushBack(2);
        list.pushBack(3);
        list.pushBack(4);
        list.pushBack(5);
        list.popBack();
        list.popFront();
        list.pushFront(9);
        list.pushFront(10);

        // 10 9 2 3 4
        list.print();

        ListIterator it = list.iterator();
        it.next();
        it.remove(); // должно удалить 10 (удаление первого)
        it.next();
        it.next();
        it.remove(); // должно удалить 2 (удаление из середины)
        it.next();
        it.next();
        it.remove(); // должно удалить 4 (удаление последнего)

        // 9 3
        list.print();
    }

}
