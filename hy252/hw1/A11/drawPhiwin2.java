import java.util.Scanner;
import javax.swing.JOptionPane;

public class drawPhiwin2 {
    private static Integer lines; // Number of lines to draw (user input)
    private static Integer limit; // Which line(s) will be the largest
    // Line in case of odd and lines in case of even number of lines
    // Limit also serves as the vertical separator of the bitmap

    // HACK: Took the function from the previous hw and multiplied spaces left & right
    //           by 2.
    private static StringBuilder algorithm(int line, char character) {
	StringBuilder out = new StringBuilder("");
	int i;

	// Allocate the string columns with spaces
	for (i = 0; i < (limit * 4 + 1); i++)
	    out.append(' ');
	out.append('\n');

	if (line > limit)
	    line = lines - line - 1;

	out.setCharAt(2 * (limit - line), character); // Paint the left bit
	out.setCharAt(2 * limit, character); // Paint the middle bit
	out.setCharAt(2 * (limit + line), character); // Paint the right bit

	return out;
    }

    public static void main(String[] args) {
	do {
	    StringBuilder tmp = new StringBuilder("");
	    lines = Integer.parseInt(JOptionPane.showInputDialog("Give me a number ", 4));

	    if (lines < 4 || lines > 9)
		System.exit(0);

	    limit = (lines / 2) + (lines % 2) - 1;
	    for (int i = 0; i < lines; i++)
		// HACK: Turn int into char through ASCII table
		tmp.append(algorithm(i, (char) (i + 1 + 48)));

	    JOptionPane.showMessageDialog(null, tmp.toString(), "Output window", JOptionPane.INFORMATION_MESSAGE);
	} while (lines >= 4 && lines <= 30);
    }
}
