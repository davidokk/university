import java.util.Objects;

public abstract class Lamp {
    String manufacturer;
    double power;

    public Lamp(String manufacturer, double power) {
        this.manufacturer = manufacturer;
        this.power = power;
    }

    @Override
    public String toString() {
        return "manufacturer='" + manufacturer + '\'' +
                ", power=" + power +
                ", price=" + getPrice();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Lamp lamp = (Lamp) o;
        return Double.compare(lamp.power, power) == 0 && Objects.equals(manufacturer, lamp.manufacturer);
    }

    @Override
    public int hashCode() {
        return Objects.hash(manufacturer, power);
    }

    public abstract double getPrice();
}
