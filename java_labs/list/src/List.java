public class List implements Iterable<Integer> {

    @Override
    public ListIterator iterator() { return new ListIterator(this, head); }

    public void pushBack(int value) {
        if (isEmpty()) {
            addFirst(value);
        } else {
            tail.next = new ListNode(value, null, tail);
            tail = tail.next;
        }
    }

    public void popBack() {
        if (head == tail) {
            removeLast();
        } else {
            tail = tail.prev;
            tail.next = null;
        }
    }

    public void pushFront(int value) {
        if (isEmpty()) {
            addFirst(value);
        } else {
            head.prev = new ListNode(value, head, null);
            head = head.prev;
        }
    }

    public void popFront() {
        if (head == tail) {
            removeLast();
        } else {
            head = head.next;
            head.prev = null;
        }
    }

    public void print() {
        System.out.print("(");
        boolean first = true;
        for (Integer integer : this) {
            if (!first)
                System.out.print(", ");
            first = false;
            System.out.print(integer);
        }
        System.out.print(")");
    }

    public boolean isEmpty() { return head == null; }

    private void addFirst(int value) { head = tail = new ListNode(value); }
    private void removeLast() { head = tail = null; }

    ListNode head = null;
    ListNode tail = null;
}
