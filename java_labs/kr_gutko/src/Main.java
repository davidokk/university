import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        CircleArray<Circle> circles = new CircleArray<>();
        ReadCircleArray(circles);

        CircleArray<FilledCircle> filledCircles = new CircleArray<>(Arrays.asList(
                new FilledCircle(10, -5, -1, "red"),
                new FilledCircle(),
                new FilledCircle("blue"),
                new FilledCircle(-1.5, 2, 5.5)
        ));

        System.out.println(circles.avgCircle().toString());
        System.out.println(filledCircles.maxCircle().toString());
        System.out.println(circles.compareMaxCircle(filledCircles));

        Pair<ICircle> pair = new Pair<>();
        circles.setAvgCircleFirst(filledCircles, pair);
        System.out.println(pair.toString());

        var clone = circles.clone();

        for (var i : clone)
            System.out.println(i.toString());
    }

    static void ReadCircleArray(CircleArray<Circle> a) {
        try (Scanner in = new Scanner(new FileReader(".idea/input.txt"))) {
            int n = Integer.parseInt(in.nextLine());
            for (int i = 0; i < n; ++i) {
                a.add(Circle.parseFrom(in.nextLine()));
            }
        } catch (IOException e) {
            System.err.println("File do not exist");
            System.exit(0);
        }
    }
}
