import java.util.ListIterator;
import java.util.NoSuchElementException;

public class MyListIterator implements ListIterator<Integer> {
    /**
     * node указывает на элемент,
     * который вернет следующий вызов метода next();
     *     node.prev    node
     *    previous()   next()
     */
    int index = 0;
    ListNode node;
    MyList list;

    public MyListIterator(MyList list) {
        this.list = list;
        this.node = list.head;
    }

    @Override public boolean hasNext() { return node != null; }
    @Override public boolean hasPrevious() { return node != list.head; }

    @Override public int nextIndex() { return index; }
    @Override public int previousIndex() { return index - 1; }

    @Override
    public Integer next() {
        if (!hasNext())
            throw new NoSuchElementException();
        ++index;
        Integer ret = node.value;
        node = node.next;
        return ret;
    }

    @Override
    public Integer previous() {
        if (!hasPrevious())
            throw new NoSuchElementException();
        --index;
        Integer ret = node.prev.value;
        node = node.prev;
        return ret;
    }

    @Override
    public void set(Integer val) {
//        throw new UnsupportedOperationException("Недопустимая операция");
        if (node == null) {
            list.tail.value = val;
        } else {
            node.prev.value = val;
        }
    }

    @Override
    public void add(Integer val) {
//        throw new UnsupportedOperationException("Недопустимая операция");
        ++list.count;
        // добавляем в пустой список
        if (list.head == null) {
            ListNode new_node = new ListNode(val);
            list.head = list.tail = new_node;
            node = new_node;
        } // добавляем в конец списка
        else if (node == null) {
            ListNode new_node = new ListNode(val, null, list.tail);
            node = new_node;
            list.tail.next = new_node;
            list.tail = new_node;
        } // добавляем в начало списка
        else if (node == list.head) {
            ListNode new_node = new ListNode(val, list.head, null);
            node = new_node;
            list.head.prev = new_node;
            list.head = new_node;
        } // добавляем в середину списка
        else {
            ListNode new_node = new ListNode(val, node, node.prev);
            node.prev.next = new_node;
            node.prev = new_node;
            node = new_node;
        }
    }

    @Override
    public void remove() {
//        throw new UnsupportedOperationException("Недопустимая операция");
        --list.count;
        if (node == list.head)
            throw new IllegalStateException("Операция удаления недопустима");
        if (node == null) {
            list.tail = list.tail.prev;
            list.tail.next = null;
        } else if (node.prev == list.head) {
            node.prev = null;
            list.head = node;
        } else {
            node.prev.prev.next = node;
            node.prev = node.prev.prev;
        }
    }
}
