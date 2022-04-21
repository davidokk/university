public class Tree {
    private Node root;

    public void add(int value) {
        Node node = new Node(value);
        Node v = root;
        Node pv = null;
        while (v != null) {
            pv = v;
            if (value < v.value) {
                v = v.left;
            } else {
                v = v.right;
            }
        }
        v = new Node(value);
        if (pv == null)
            root = v;
        else if (value < pv.value)
            pv.left = v;
        else
            pv.right = v;
    }

    public void remove(int value) {
        Node v = root, pv = null;
        boolean isLeft = false;
        while (v != null && v.value != value) {
            pv = v;
            isLeft = value < v.value;
            if (value < v.value)
                v = v.left;
            else
                v = v.right;
        }
        if (v != null) {
            if (v.left != null && v.right != null) {
                Node d = v.left, pd = v;
                while (d.right != null) {
                    pd = d;
                    d = d.right;
                }
                v.value = d.value;
                pd.right = d.left;
            } else if (v == root) {
                root = v.left == null? v.right : v.left;
            } else {
                Node k = v.left == null? v.right : v.left;
                if (isLeft)
                    pv.left = k;
                else
                    pv.right = k;
            }
        }
    }

    public void print() { print(root); System.out.println(); }

    private void print(Node v) {
        if (v != null) {
            print(v.left);
            System.out.print(v.value + " ");
            print(v.right);
        }
    }

    public int q() { return root == null? -1 : q(root, 0); }

    private int q(Node v, int level) {
        if (v.isLeaf())
            return v.value;
        if (v.left != null && v.right != null) {
            int l = q(v.left, level + 1);
            int r = q(v.right, level + 1);
            return level % 2 == 1 ? Math.max(l, r) : Math.min(l, r);
        }
        if (v.left != null)
            return q(v.left, level + 1);
        return q(v.right, level + 1);
    }

}
