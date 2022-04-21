import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Tree t = new Tree();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter n: ");
        int n = scanner.nextInt();
        if (n != 0)
            System.out.print("Enter tree: ");
        for (int i = 0; i < n; ++i)
            t.add(scanner.nextInt());
        System.out.println("q(v0) = " + t.q());
    }
}
