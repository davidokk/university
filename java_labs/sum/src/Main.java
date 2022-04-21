import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter n: ");
        int n = scanner.nextInt();
        //System.out.println("Real time: " + realTime(n));
        System.out.println("Linear time: " + linearTime(n));
    }

    public static double linearTime(int n) {
        double a = 1, b = 1, s = 0;
        for (int i = 1; i <= (n >> 1); i++)
            s += (a *= 1.0 * (n - (i << 1) + 2) * (n - (i << 1) + 1) / i / i / i);
        if ((n & 1) == 1)
            a /= n + 1;
        for (int i = (n >> 1) + 1; i <= n; i++)
            s += (a *= 1.0 * (n - i + 1) / i / i);
        return s;
    }

    public static double realTime(int n) {
        double sum = 0;
        for (int i = 1; i <= n; i++)
            sum += 1.0 * c(n - i, Math.min(i, n - i)) * c(n, n - i) / fact(i);
        return sum;
    }

    public static int fact(int n) {
        if (n == 0)
            return 1;
        return fact(n - 1) * n;
    }

    public static int c(int n, int m) {
        return fact(n) / fact(n - m) / fact(m);
    }
}
