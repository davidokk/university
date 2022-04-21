import java.util.Random;

public class DetailGenerator {

    DetailGenerator() {}
    DetailGenerator(int maxSize) { this.maxSize = maxSize; }

    Detail newDetail() {
        ++id;
        return new Detail(
            id, "detail" + id,
            new Size(getRandomSize(), getRandomSize(), getRandomSize()),
            Math.random() * 100,
            Math.random() * 100
        );
    }

    private int getRandomSize() {
        return gen.nextInt((int)(k * maxSize));
    }

    static Random gen = new Random();
    static int id = 0;
    int maxSize = 10;
    static final double k = 1.2;
}
