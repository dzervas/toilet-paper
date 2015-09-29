import java.util.Scanner;
import javax.swing.JOptionPane;

public class drawPhiwin {
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
	StringBuilder tmp = new StringBuilder("");
	lines = Integer.parseInt(JOptionPane.showInputDialog("Give me a number ", 4));

	//do {
	    if (lines < 4 || lines > 30)
		System.exit(0);

	    limit = (lines / 2) + (lines % 2) - 1;
	    for (int i = 0; i < lines; i++)
		tmp.append(algorithm(i, '*'));

	    JOptionPane.showMessageDialog(null, tmp.toString(), "Output window", JOptionPane.INFORMATION_MESSAGE);
	//} while (lines >= 4 && lines <= 30);
    }
}
