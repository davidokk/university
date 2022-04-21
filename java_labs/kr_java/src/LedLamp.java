import java.util.Objects;

public class LedLamp extends Lamp {
    int diodeCount;
    final static double priceCoefficient = 1.0;

    public LedLamp(String manufacturer, double power, int diodeCount) {
        super(manufacturer, power);
        this.diodeCount = diodeCount;
    }

    @Override
    public double getPrice() {
        return Math.round(100 * power * diodeCount / priceCoefficient) / 100.0;
    }

    @Override
    public String toString() {
        return "LedLamp{" + super.toString() +
                ", diodeCount=" + diodeCount + "}";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        LedLamp ledLamp = (LedLamp) o;
        return diodeCount == ledLamp.diodeCount;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), diodeCount);
    }

}
