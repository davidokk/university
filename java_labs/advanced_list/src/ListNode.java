public class ListNode {
    public ListNode(int value) {
        this.value = value;
        next = prev = null;
    }
    public ListNode(int value, ListNode next, ListNode prev) {
        this.value = value;
        this.next = next;
        this.prev = prev;
    }

    public ListNode next;
    public ListNode prev;
    public int value;
}
