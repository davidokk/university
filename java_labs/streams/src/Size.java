public record Size(int length, int width, int height) {

    boolean less(Size other) {
        return length < other.length && width < other.width && height < other.height;
    }

}
