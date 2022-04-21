import java.io.IOException;
import java.nio.file.*;
import java.util.List;
import java.util.stream.*;

public class Reader {

    public static List<String> readLines(String path) throws IOException {
        Path dataFile = Paths.get(path);
        Stream<String> dataStream = Files.lines(dataFile);
        return dataStream.collect(Collectors.toList());
    }

}
