public interface ICircle extends Cloneable {

    double getX();
    double getY();

    double getR();

    void setX(double x);
    void setY(double y);

    void setR(double r);

    void plusTo(ICircle o);

    ICircle myClone();
    int compareTo(ICircle o);
}
