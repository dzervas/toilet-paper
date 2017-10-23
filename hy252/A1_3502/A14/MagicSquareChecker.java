import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.net.URL;
import java.util.Scanner;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class MagicSquareChecker {
	static int msiz, mnum;
	static boolean isDup = false;

	private static int sumOfRow(int[][] s, int k) {
		int sum = 0;

		for (int i = 0; i < msiz; i++)
			sum += s[k][i];

		return sum;
	}

	private static int sumOfColumn(int[][] s, int k) {
		int sum = 0;

		for (int i = 0; i < msiz; i++)
			sum += s[k][i];

		return sum;
	}

	private static int sumOfDiagonal1(int[][] s) {
		int sum = 0;

		for (int i = 0; i < msiz; i++)
			sum += s[i][i];

		return sum;
	}

	private static int sumOfDiagonal2(int[][] s) {
		int sum = 0;

		for (int i = (msiz - 1); i >= 0; i--)
			sum += s[i][i];

		return sum;
	}

	public static boolean checkIsMagic(int[][] s) {
		if (isDup)
			return false;

		for (int i = 0; i < msiz; i++) {
			if (sumOfRow(s, i) != mnum || sumOfColumn(s, i) != mnum) {
				return false;
			}
		}

		if (sumOfDiagonal1(s) != mnum)
			return false;

		if (sumOfDiagonal2(s) != mnum)
			return false;

		return true;
	}

	public static void main(String[] args) throws java.io.IOException, java.net.MalformedURLException {
		boolean[] dupCheck = new boolean[8 * Integer.BYTES];
		int[][] table;
		int i, j;
		JFileChooser fc = new JFileChooser();
		Scanner line, in;

		fc.setDialogTitle("Select a file");
		if (fc.showOpenDialog(null) != JFileChooser.APPROVE_OPTION) {
			return;
		}

		File file = fc.getSelectedFile();
		try {
			in = new Scanner(new FileReader(file.getAbsolutePath()));
		} catch (java.io.FileNotFoundException e) {
			in = new Scanner(new URL(JOptionPane.showInputDialog("Give me a URL. File not found... ")).openStream());
		}

		table = new int[10][10];

		for (i = 0; in.hasNextLine() && i < 10; i++) {
			line = new Scanner(in.nextLine());

			for (j = 0; line.hasNextInt() && j < 10; j++) {
				table[i][j] = line.nextInt();

				if (dupCheck[table[i][j]])
					isDup = true;

				dupCheck[table[i][j]] = true;
			}

			if (i == 0)
				msiz = j;
			else if (j != msiz) {
				System.out.println("Table is not square...");
				return;
			}

			line.close();
		}

		if (i != msiz) {
			System.out.println("Table is not square...");
			return;
		}

		mnum = sumOfRow(table, 0);

		if (!checkIsMagic(table)) {
			System.out.println("Muggle table. It's not magic... :/");
			return;
		}

		fc = new JFileChooser();
		fc.setDialogTitle("Select a directory");
		fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		fc.setAcceptAllFileFilterUsed(false);

		if (fc.showSaveDialog(null) != JFileChooser.APPROVE_OPTION) {
			return;
		}

		file = fc.getSelectedFile();
		PrintWriter out = new PrintWriter(file.getAbsolutePath() + "/MagicSquareSavedFile.txt");

		for (i = 0; i < msiz; i++) {
			for (j = 0; j < msiz; j++) {
				out.print(Integer.toString(table[i][j]) + " ");
			}
			out.println();
		}
		out.println("Magic table with magic number " + Integer.toString(msiz));
		out.close();
	}
}
