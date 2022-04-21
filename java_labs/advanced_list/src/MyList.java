import java.util.AbstractSequentialList;
import java.util.Collection;
import java.util.ListIterator;

public class MyList extends AbstractSequentialList<Integer> {

    MyList() {}
    MyList(Collection<Integer> collection) {
        for (Integer i : collection) {
            if (head == null) {
                head = tail = new ListNode(i);
            } else {
                tail.next = new ListNode(i, null, tail);
                tail = tail.next;
            }
            ++count;
        }
    }

    @Override
    public ListIterator<Integer> listIterator(int index) {
        MyListIterator it = new MyListIterator(this);
        while (index != 0 && it.hasNext()) {
            --index;
            it.next();
        }
        if (!it.hasNext() && index != 0)
            throw new IndexOutOfBoundsException();
        return it;
    }

    @Override
    public int size() { return count; }

    public void print() {
        boolean first = true;
        System.out.print("(");
        for (Integer el : this) {
            if (!first)
                System.out.print(", ");
            first = false;
            System.out.print(el);
        }
        System.out.println(")");
    }

    ListNode head = null;
    ListNode tail = null;
    int count = 0;
}
