public class Circle implements ICircle, Comparable<Circle> {

    double x = 0, y = 0, r = 0;

    public Circle() {}

    public Circle(double centerX, double centerY, double radius) {
        x = centerX;
        y = centerY;
        r = radius;
    }

    @Override
    public double getX() { return x; }

    @Override
    public double getY() { return y; }

    @Override
    public double getR() { return r; }

    @Override
    public void setX(double x) { this.x = x; }

    @Override
    public void setY(double y) { this.y = y; }

    @Override
    public void setR(double r) { this.r = r; }

    @Override
    public void plusTo(ICircle o) {
        x += o.getX();
        y += o.getY();
        r += o.getR();
    }

    @Override
    public ICircle myClone() { return new Circle(x, y, r); }

    @Override
    public Circle clone() { return new Circle(x, y, r); }

    @Override
    public int compareTo(ICircle o) { return Double.compare(r, o.getR()); }

    @Override
    public int compareTo(Circle o) { return Double.compare(r, o.r); }

    @Override
    public String toString() {
        return "[x = " + Double.toString(x) +
               ", y = " + Double.toString(y) +
               ", r = " + Double.toString(r) + "]";
    }

    static public Circle parseFrom(String input) {
        var str = input.split(" ");
        double x = Double.parseDouble(str[0]);
        double y = Double.parseDouble(str[1]);
        double r = Double.parseDouble(str[2]);
        return new Circle(x, y, r);
    }

}
