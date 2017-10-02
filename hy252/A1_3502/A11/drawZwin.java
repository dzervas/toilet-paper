import java.util.Scanner;
import javax.swing.JOptionPane;

public class drawZwin {
	private static Integer lines; // Number of lines to draw (user input)

	private static StringBuilder algorithm(int line, char character) {
		StringBuilder out = new StringBuilder("");
		int i;

		if (line == 0 || line == (lines - 1)) {
			for (i = 0; i < lines; i++)
				out.append(character);
			return out;
		}

		// Allocate the string columns with spaces
		for (i = 0; i < (lines - line - 1); i++)
			out.append(' ');

		out.append(character);

		return out;
	}

	public static void main(String[] args) {
		do {
			StringBuilder tmp = new StringBuilder("");
			lines = Integer.parseInt(JOptionPane.showInputDialog("Give me a number ", 4));

			if (lines < 4 || lines > 30)
				System.exit(0);

			for (int i = 0; i < lines; i++) {
				tmp.append(algorithm(i, '*'));
				tmp.append("\n");
			}

			JOptionPane.showMessageDialog(null, tmp.toString(), "Output window", JOptionPane.INFORMATION_MESSAGE);
		} while (lines >= 4 && lines <= 30);
	}
}
