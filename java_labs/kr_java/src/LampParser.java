import java.util.List;

public class LampParser {

    public static IncandescentLamp parseIncandescentLamp(String input) {
        String[] params = input.split(" ");
        return new IncandescentLamp(params[0], Double.parseDouble(params[1]), Integer.parseInt(params[2]));
    }

    public static LedLamp parseLedLamp(String input) {
        String[] params = input.split(" ");
        return new LedLamp(params[0], Double.parseDouble(params[1]), Integer.parseInt(params[2]));
    }

}
