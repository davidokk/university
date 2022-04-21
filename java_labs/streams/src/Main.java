import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        DetailGenerator gen = new DetailGenerator();

        ArrayList<Detail> arrayList = new ArrayList<>();
        for (int i = 0; i < 10; ++i)
            arrayList.add(gen.newDetail());

        arrayList.forEach(System.out::println);

        System.out.println("\n\nКрупногабаритные:");

        int maxLength = 10;
        int maxWidth = 8;
        int maxHeight = 7;
        Size maxSize = new Size(maxLength, maxWidth, maxHeight);

        arrayList.stream().filter(detail -> !detail.size().less(maxSize)).forEach(System.out::println);
//        var list = arrayList.stream().filter(detail -> !detail.size().less(maxSize)).toList();
    }
}
