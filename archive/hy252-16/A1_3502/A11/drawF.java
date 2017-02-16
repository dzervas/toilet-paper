import java.util.Scanner;

public class drawF {
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
		Scanner in = new Scanner(System.in);

		lines = Integer.parseInt(args[0]);

		do {
			if (lines < 4 || lines > 30)
				break;

			limit = (lines / 2) + 1;
			for (int i = 0; i < lines; i++)
				System.out.println(algorithm(i, '*'));

			System.out.println("Feed me moar: ");
			lines = in.nextInt();
		} while (lines >= 4 && lines <= 30);
	}
}
