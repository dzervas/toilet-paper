import java.util.Scanner;

public class drawZ {
	private static Integer lines; // Number of lines to draw (user input)

	// Reusable for the next homework
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
		Scanner in = new Scanner(System.in);
		lines = Integer.parseInt(args[0]);

		while (lines >= 4 && lines <= 30) {
			for (int i = 0; i < lines; i++)
				System.out.println(algorithm(i, '*'));

			System.out.println("Feed me moar: ");
			lines = in.nextInt();
		}
	}
}
