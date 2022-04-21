import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class CircleArray <T extends ICircle> implements Cloneable, Iterable<T> {

    ArrayList<T> a = new ArrayList<>();

    public CircleArray() {}

    public CircleArray(Collection<T> collection) {
        a.addAll(collection);
    }

    ICircle avgCircle() {
        if (a.isEmpty())
            return null;
        ICircle avg = a.get(0).myClone();

        var it = iterator(); it.next();
        while (it.hasNext())
            avg.plusTo(it.next());

        avg.setX(avg.getX() / a.size());
        avg.setY(avg.getY() / a.size());
        avg.setR(avg.getR() / a.size());
        return avg;
    }

    ICircle maxCircle() {
        if (a.isEmpty())
            return null;
        ICircle max = a.get(0).myClone();

        for (var i : this) {
            if (max.compareTo(i) < 0)
                max = i.myClone();
        }

        return max;
    }

    public <V extends ICircle> int compareMaxCircle(CircleArray<V> o) {
        return maxCircle().compareTo(o.maxCircle());
    }

    public <V extends ICircle> void setAvgCircleFirst(CircleArray<V> o, Pair<ICircle> pair) {
        boolean less = avgCircle().compareTo(o.at(0)) < 0;
        pair.setFirst((less ? this : o).avgCircle());
        pair.setSecond((less ? this : o).at(0));
    }

    ICircle at(int index) {
        return a.get(index).myClone();
    }

    void add(T val) { a.add(val); }

    @Override
    public Iterator<T> iterator() { return a.iterator(); }

    @Override
    public CircleArray<T> clone() {
        return new CircleArray<T>((Collection<T>) a.clone());
    }
}
