import java.util.Objects;

public class IncandescentLamp extends Lamp {
    int operatingTime;
    final static double priceCoefficient = 0.0001;

    public IncandescentLamp(String manufacturer, double power, int operatingTime) {
        super(manufacturer, power);
        this.operatingTime = operatingTime;
    }

    @Override
    public double getPrice() {
        return Math.round(100 * priceCoefficient * power * operatingTime) / 100.0;
    }

    @Override
    public String toString() {
        return "IncandescentLamp{" + super.toString() +
                ", operatingTime=" + operatingTime + "}";
    }

    // я когда оле рассказал что в задачах по алгоритмам не надо делать привате поля и писать гэтэры и сэтэры (Art of Getters
    // and Setters Book "K::Idioms page 1") она ахуела
    // у нас там 1 страница всего )
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        IncandescentLamp that = (IncandescentLamp) o;
        return operatingTime == that.operatingTime;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), operatingTime);
    }

}
