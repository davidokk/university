class Pair<T> {
    public Pair() {}

    public Pair(T first, T second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() { return first; }

    public T getSecond() { return second; }

    public void setFirst(T newValue) { first = newValue; }

    public void setSecond(T newValue) { second = newValue; }

    @Override
    public String toString() {
        return "(" + first.toString() + "," + second.toString() + ")";
    }

    private T first;
    private T second;
}
