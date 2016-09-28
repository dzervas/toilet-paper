import java.util.Scanner;
import javax.swing.JOptionPane;

public class drawFwin2 {
	private static Integer lines; // Number of lines to draw (user input)
	private static Integer limit; // Which line & column will be the middle

	private static StringBuilder algorithm(int line, char character) {
		StringBuilder out = new StringBuilder("");
		int i;

		if (line == 0) {
			for (i = 0; i < lines; i++)
				out.append(character);
		} else if (line == limit - 1) {
			for (i = 0; i < limit; i++)
				out.append(character);
		} else {
			out.append(character);
		}

		return out;
	}

	public static void main(String[] args) {
		do {
			StringBuilder tmp = new StringBuilder("");
			lines = Integer.parseInt(JOptionPane.showInputDialog("Give me a number ", 4));

			if (lines < 4 || lines > 9) {
				JOptionPane.showMessageDialog(null, "Allowed range is 4-9", "DrawFwin", JOptionPane.ERROR_MESSAGE);
				System.exit(0);
			}

			limit = (lines / 2) + 1;
			for (int i = 0; i < lines; i++) {
				// Add 49 to convert character to ASCII
				// 49 is 0 in ASCII, so 49 + i == ascii_char(i + 1)
				tmp.append(algorithm(i, (char) (i+49)));
				tmp.append("\n");
			}

			JOptionPane.showMessageDialog(null, tmp.toString(), "Output window", JOptionPane.INFORMATION_MESSAGE);
		} while (true);
	}
}
