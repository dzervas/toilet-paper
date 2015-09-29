import java.util.Scanner;

public class DrawPhi {
    private static Integer lines; // Number of lines to draw (user input)
    private static Integer limit; // Which line(s) will be the largest
    // Line in case of odd and lines in case of even number of lines
    // Limit also serves as the vertical separator of the bitmap

    // Reusable for the next homework
    private static StringBuilder algorithm(int line, char character) {
	StringBuilder out = new StringBuilder("");
	int i;

	// Allocate the string columns with spaces
	for (i = 0; i < (limit * 2 + 1); i++)
	    out.append(' ');

	if (line > limit)
	    line = lines - line - 1;

	out.setCharAt(limit - line, character); // Paint the left bit
	out.setCharAt(limit, character); // Paint the middle bit
	out.setCharAt(limit + line, character); // Paint the right bit

	return out;
    }

    public static void main(String[] args) {
	Scanner in = new Scanner(System.in);

	lines = Integer.parseInt(args[0]);

	do {
	    if (lines < 4 || lines > 30)
		break;

	    limit = (lines / 2) + (lines % 2) - 1;
	    for (int i = 0; i < lines; i++)
		System.out.println(algorithm(i, '*'));

	    System.out.println("Feed me moar: ");
	    lines = in.nextInt();
	} while (lines >= 4 && lines <= 30);
    }
}
