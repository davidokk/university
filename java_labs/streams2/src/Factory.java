import java.util.List;

public record Factory(String name, List<Production> productions, List<Factory> providers) {

    boolean produce(String production) {
        for (Production el : productions)
            if (el.name().equals(production))
                return true;
        return false;
    }

    @Override
    public String toString() { return name; }
}
