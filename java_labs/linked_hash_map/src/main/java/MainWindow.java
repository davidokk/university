import javax.swing.*;
import java.awt.*;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.Map;

public class MainWindow {
    public MainWindow() {
        createWindow();
        createLabels();
        createButtons();
        window.setVisible(true);
    }

    private void createWindow() {
        window = new JFrame();
        window.setTitle("LinkedHashMap");
        window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        window.setSize(width, height);
        window.setLocation(200, 100);
        window.setLayout(null);
    }

    private void createLabels() {
        Font font = new Font("Consolas", Font.BOLD, 20);
        JLabel titleLabel = new JLabel("LinkedHashMap");
        titleLabel.setFont(font);
        titleLabel.setHorizontalAlignment(SwingConstants.CENTER);
        titleLabel.setBounds(0, 30, width, 30);
        titleLabel.setHorizontalAlignment(SwingConstants.CENTER);
        window.add(titleLabel);

        mapLabel = new JLabel(map.toString());
        mapLabel.setHorizontalAlignment(SwingConstants.CENTER);
        mapLabel.setBounds(0, 60, width, 30);
        mapLabel.setFont(font);
        window.add(mapLabel);
    }

    private void createButtons() {
        JLabel label1 = new JLabel("Константные");
        label1.setHorizontalAlignment(SwingConstants.CENTER);
        label1.setBounds(10, 10, 120, 40);
        window.add(label1);

        JButton sizeButton = new JButton("size");
        sizeButton.setBounds(10, 60, 120, 40);
        sizeButton.addActionListener(e -> showMessage("Размер " + map.size()));
        window.add(sizeButton);

        JButton isEmptyButton = new JButton("isEmpty");
        isEmptyButton.setBounds(10, 110, 120, 40);
        isEmptyButton.addActionListener(e -> showMessage(map.isEmpty()? "Словарь пустой" : "Словарь не пустой"));
        window.add(isEmptyButton);

        JButton containsKeyButton = new JButton("containsKey");
        containsKeyButton.setBounds(10, 160, 120, 40);
        containsKeyButton.addActionListener(e -> {
            try {
                Integer key = parseValue(JOptionPane.showInputDialog(window, "Введите ключ"));
                showMessage("Ключ " + key + (map.containsKey(key) ? "" : " не") + " содержится в словаре");
            } catch (Exception exception) {
                showMessage(exception.toString());
            }
        });
        window.add(containsKeyButton);

        JButton containsValueButton = new JButton("containsValue");
        containsValueButton.setBounds(10, 210, 120, 40);
        containsValueButton.addActionListener(e -> {
            try {
                Integer value = parseValue(JOptionPane.showInputDialog(window, "Введите значение"));
                showMessage("Значение " + value + (map.containsValue(value) ? "" : " не") + " содержится в словаре");
            } catch (Exception exception) {
                showMessage(exception.toString());
            }
        });
        window.add(containsValueButton);

        JButton getButton = new JButton("get");
        getButton.setBounds(10, 260, 120, 40);
        getButton.addActionListener(e -> {
            try {
                Integer key = parseValue(JOptionPane.showInputDialog(window, "Введите ключ"));
                Integer value = map.get(key);
                if (value == null)
                    showMessage("Словарь не содержит такого ключа");
                else
                    showMessage("Ключ " + key + " значение " + value);
                updateInfo();
            } catch (Exception exception) {
                showMessage(exception.toString());
            }
        });
        window.add(getButton);

        JLabel label2 = new JLabel("Модицифирующие");
        label2.setHorizontalAlignment(SwingConstants.CENTER);
        label2.setBounds(10, 310, 120, 40);
        window.add(label2);

        JButton addButton = new JButton("put");
        addButton.setBounds(10, 360, 120, 40);
        addButton.addActionListener(e -> {
            try {
                Integer[] pair = parseKeyValue(JOptionPane.showInputDialog(window, "Введите ключ и значение"));
                Integer prev = map.put(pair[0], pair[1]);
                updateInfo();
                if (prev != null)
                    showMessage("Значение " + prev + " было заменено на " + pair[1]);
            } catch (Exception exception) {
                showMessage(exception.toString());
            }
        });
        window.add(addButton);

        JButton clearButton = new JButton("clear");
        clearButton.setBounds(10, 410, 120, 40);
        clearButton.addActionListener(e -> {
            try {
                map.clear();
                updateInfo();
                showMessage("Словарь очищен");
            } catch (Exception exception) {
                showMessage(exception.toString());
            }
        });
        window.add(clearButton);

        JButton replaceButton = new JButton("replace");
        replaceButton.setBounds(10, 460, 120, 40);
        replaceButton.addActionListener(e -> {
            try {
                Integer[] pair = parseKeyValue(JOptionPane.showInputDialog(window, "Введите ключ и новое значение"));
                Integer prev = map.replace(pair[0], pair[1]);
                updateInfo();
                if (prev == null)
                    showMessage("Словарь не содержит ключа " + pair[0]);
                else
                    showMessage(prev + " заменено на " + pair[1]);
            } catch (Exception exception) {
                showMessage(exception.toString());
            }
        });
        window.add(replaceButton);

        JButton removeButton = new JButton("remove");
        removeButton.setBounds(10, 510, 120, 40);
        removeButton.addActionListener(e -> {
            try {
                Integer key = parseValue(JOptionPane.showInputDialog("Введите ключ"));
                Integer prev = map.remove(key);
                updateInfo();
                if (prev == null)
                    showMessage("Словарь не содержит ключа " + key);
                else
                    showMessage("Ключ " + key + " со значением " + prev + " удален");
            } catch (Exception exception) {
                showMessage(exception.toString());
            }
        });
        window.add(removeButton);

        JCheckBox unmodifiableCheckBox = new JCheckBox("unmodifiable");
        unmodifiableCheckBox.addItemListener(e -> switchModifiable());
        unmodifiableCheckBox.setBounds(650, 40, 100, 20);
        window.add(unmodifiableCheckBox);

        JCheckBox accessOrderCheckBox = new JCheckBox("accessOrder");
        accessOrderCheckBox.addItemListener(e -> switchAccessOrder());
        accessOrderCheckBox.setBounds(650, 70, 100, 20);
        window.add(accessOrderCheckBox);
    }

    private Integer[] parseKeyValue(String keyValue) {
        String[] params = keyValue.split(" ");
        if (params.length != 2)
            throw new NumberFormatException("invalid input");
        return new Integer[] {Integer.parseInt(params[0]), Integer.parseInt(params[1])};
    }

    private Integer parseValue(String value) {
        try {
            return Integer.parseInt(value);
        } catch(Exception exception) {
            throw new NumberFormatException("invalid input");
        }
    }

    void switchModifiable() {
        map = !unmodifiable ? Collections.unmodifiableMap(map) : new LinkedHashMap<>(map);
        unmodifiable = !unmodifiable;
    }

    void switchAccessOrder() {
        var map = !accessOrder ?
                new LinkedHashMap<Integer, Integer>(16, 0.75f, true)
                : new LinkedHashMap<Integer, Integer>();
        map.putAll(this.map);
        this.map = unmodifiable ? Collections.unmodifiableMap(map) : map;
        accessOrder = !accessOrder;
    }

    void showMessage(String message) {
        JOptionPane.showMessageDialog(window, message);
    }

    private void updateInfo() {
        mapLabel.setText(map.toString());
    }

    boolean unmodifiable = false;
    boolean accessOrder = false;
    Map<Integer, Integer> map = new LinkedHashMap<>();

    JFrame window;
    static final int width = 800;
    static final int height = 600;

    JLabel mapLabel;
}
