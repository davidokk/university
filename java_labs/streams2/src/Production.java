public record Production(String name, int actualCount, int plannedCount) {

    Production(String name) {
        this(name, 100, 100);
    }

    @Override
    public String toString() { return name; }

}
