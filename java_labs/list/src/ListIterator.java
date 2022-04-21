import java.util.Iterator;

public class ListIterator implements Iterator<Integer> {
    ListNode node;
    List list;

    public ListIterator(List list, ListNode node) {
        this.node = node;
        this.list = list;
    }

    public ListIterator clone() {
        return new ListIterator(list, node != null ? new ListNode(node.value, node.next, node.prev) : null);
    }

    @Override
    public boolean hasNext() { return node != null; }

    @Override
    public Integer next() {
        Integer ret = node.value;
        node = node.next;
        return ret;
    }

    @Override
    public void remove() {
        if (node == list.head)
            throw new IllegalStateException("Операция удаления недопустима");
        if (node == null) {
            list.popBack();
        } else if (node.prev == list.head) {
            node.prev = null;
            list.head = node;
        } else {
            node.prev.prev.next = node;
            node.prev = node.prev.prev;
        }
    }
}
