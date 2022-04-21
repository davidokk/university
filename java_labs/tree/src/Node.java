public class Node {

    public Node(int value) {
        this.value = value;
        left = right = null;
    }

    public Node(int value, Node left, Node right) {
        this.value = value;
        this.left = left;
        this.right = right;
    }

    public boolean isLeaf() { return left == null && right == null; }

    public int value;
    public Node left;
    public Node right;
}
