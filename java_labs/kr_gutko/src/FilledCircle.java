public class FilledCircle extends Circle {

    String color = "none";

    public FilledCircle() {}

    public FilledCircle(String color) {
        this.color = color;
    }

    public FilledCircle(double centerX, double centerY, double radius) {
        super(centerX, centerY, radius);
    }

    public FilledCircle(double centerX, double centerY, double radius, String color) {
        super(centerX, centerY, radius);
        this.color = color;
    }

    public String getColor() { return color; }

    @Override
    public String toString() {
        return "[x = " + Double.toString(x) +
                ", y = " + Double.toString(y) +
                ", r = " + Double.toString(r) +
                ", color = " + color + "]";
    }

    @Override
    public ICircle myClone() { return new FilledCircle(x, y, r, color); }

    @Override
    public FilledCircle clone() { return new FilledCircle(x, y, r, color); }

    static public FilledCircle parseFrom(String input) {
        var str = input.split(" ");
        double x = Double.parseDouble(str[0]);
        double y = Double.parseDouble(str[1]);
        double r = Double.parseDouble(str[2]);
        String color = str[3];
        return new FilledCircle(x, y, r, color);
    }

}
