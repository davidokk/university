import java.util.*;
import java.util.stream.Collectors;

public class Main {

    public static void main(String[] args) {

        Factory detailFactory = new Factory(
                "Цех деталей",
                List.of(
                        new Production("камера"),
                        new Production("зарядка"),
                        new Production("клавиатура")
                ),
                List.of()
        );

        Company detailCompany = new Company( "Details",  List.of(detailFactory));

        Company appleCompany = new Company(
                "Apple",
                List.of(
                        new Factory(
                                "Цех IPhone",
                                List.of(new Production("телефон")),
                                List.of(detailFactory)
                        ),
                        new Factory(
                                "Цех макбуков",
                                List.of(new Production("ноутбук"), new Production("зарядка")),
                                List.of(detailFactory)
                        )
                )
        );

        Company xiaomiCompany = new Company(
                "Xiaomi",
                List.of(
                        new Factory(
                                "Цех телефонов Xiaomi",
                                List.of(new Production("телефон"), new Production("зарядка")),
                                List.of(detailFactory)
                        ),
                        new Factory(
                                "Цех компьютеров",
                                List.of(new Production("ноутбук"), new Production("зарядка")),
                                List.of(detailFactory)
                        )
                )
        );

        List<Company> companies = List.of(appleCompany, detailCompany, xiaomiCompany);

        buildMap(companies).entrySet().forEach(System.out::println);
    }

    public static Map<Production, List<Factory>> buildMap(List<Company> companies) {

        var productionStream = companies.stream()
                .flatMap(company -> company.factories().stream()
                        .flatMap(factory -> factory.productions().stream())
        ).distinct();

        return productionStream.collect(Collectors.toMap(
                production -> production,
                production -> {
                    List<Factory> factories = new ArrayList<>();
                    companies.forEach(company -> company.factories().forEach(factory -> {
                        if (factory.produce(production.name()))
                            factories.add(factory);
                    }));
                    return factories;
                }
        ));

    }
}
