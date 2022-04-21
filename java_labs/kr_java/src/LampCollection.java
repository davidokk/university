import java.util.*;
import java.util.stream.Collectors;

public class LampCollection <T extends Lamp> implements Iterable<T> {

    ArrayList<T> lamps = new ArrayList<>();

    public LampCollection() {}
    public LampCollection(Collection<T> collection) {
        lamps.addAll(collection);
    }

    public void add(T value) {
        lamps.add(value);
    }

    public List<T> getSortedByPrice() {
        return lamps.stream().sorted(Comparator.comparingDouble(Lamp::getPrice).reversed()).toList();
    }

    public List<T> getSortedByPricePowerRatio() {
        return lamps.stream().sorted(
            (e1, e2) -> Double.compare(e2.getPrice() / e2.power, e1.getPrice() / e1.power)
        ).toList();
    }

    public List<String> getManufacturers() {
        return lamps.stream().map(e -> e.manufacturer).distinct().toList();
    }

    public double getAveragePriceOfManufacturer(String manufacturer) {
        var result = lamps.stream().filter(e -> e.manufacturer.equals(manufacturer)).mapToDouble(Lamp::getPrice).average();
        if (result.isEmpty())
            throw new NoSuchElementException("collection doesn't contain such a manufacturer");
        return Math.round(100 * result.getAsDouble()) / 100.0;
    }

    @Override
    public Iterator<T> iterator() {
        return lamps.iterator();
    }
}
