import java.io.IOException;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        System.out.println("Тест LadLamp");
        test(readLedLamps());
        System.out.println("\nТест IncandescentLamps");
        test(readIncandescentLamps());
    }

    public static <T extends Lamp> void test(LampCollection<T> collection) {
        System.out.println("Сортировка по убыванию цены: ");
        collection.getSortedByPrice().forEach(System.out::println);
        System.out.println("Сортировка по убыванию Цена / Мощность: ");
        collection.getSortedByPricePowerRatio().forEach(System.out::println);
        System.out.println("Список производителей: ");
        collection.getManufacturers().forEach(System.out::println);
        System.out.println("Средняя цена производителя cd: ");
        System.out.println(collection.getAveragePriceOfManufacturer("cd"));
    }

    public static LampCollection<LedLamp> readLedLamps() {
        LampCollection<LedLamp> list = new LampCollection<>();
        try {
            var lines = Reader.readLines("input1.txt");
            lines.forEach(e -> list.add(LampParser.parseLedLamp(e)));
        } catch (IOException exception) {
            System.out.println(exception.toString());
        }
        return list;
    }

    public static LampCollection<IncandescentLamp> readIncandescentLamps() {
        LampCollection<IncandescentLamp> list = new LampCollection<>();
        try {
            var lines = Reader.readLines("input2.txt");
            lines.forEach(e -> list.add(LampParser.parseIncandescentLamp(e)));
        } catch (IOException exception) {
            System.out.println(exception.toString());
        }
        return list;
    }

}
