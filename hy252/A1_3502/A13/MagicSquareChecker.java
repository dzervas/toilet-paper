import java.util.Scanner;

public class MagicSquareChecker {
	static int msiz, mnum;
	static boolean isDup = false;

	private static int sumOfRow(int[][] s, int k) {
		int sum = 0;

		for (int i = 0; i < msiz; i++)
			sum += s[k][i];

		System.out.println("sumOfRow: row " + k + " = " + sum);

		return sum;
	}

	private static int sumOfColumn(int[][] s, int k) {
		int sum = 0;

		for (int i = 0; i < msiz; i++)
			sum += s[k][i];

		System.out.println("sumOfColumn: row " + k + " = " + sum);

		return sum;
	}

	private static int sumOfDiagonal1(int[][] s) {
		int sum = 0;

		for (int i = 0; i < msiz; i++)
			sum += s[i][i];

		System.out.println("sumOfDiagonal1  = " + sum);

		return sum;
	}

	private static int sumOfDiagonal2(int[][] s) {
		int sum = 0;

		for (int i = (msiz - 1); i >= 0; i--)
			sum += s[i][i];

		System.out.println("sumOfDiagonal2  = " + sum);

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

	public static void main(String[] args) {
		boolean[] dupCheck = new boolean[8 * Integer.BYTES];
		int[][] table;
		Scanner in = new Scanner(System.in);

		System.out.print("Please give size of table (2<=size<=10): ");

		msiz = in.nextInt();
		table = new int[msiz][msiz];

		if (msiz < 2 || msiz > 10) {
			System.out.println("Number is out of range");
			return;
		}

		System.out.println("Give contents of table:");

		for (int i = 0; i < msiz; i++) {
			for (int j = 0; j < msiz; j++) {
				table[i][j] = in.nextInt();

				if (dupCheck[table[i][j]])
					isDup = true;

				dupCheck[table[i][j]] = true;
			}
		}

		//for (int i = 0; i < msiz; i++) {
			//for (int j = 0; j < msiz; j++)
				//System.out.print(table[i][j]);
			//System.out.print("\n");
		//}

		mnum = sumOfRow(table, 0);

		if (checkIsMagic(table))
			System.out.println("Yey! Magic table! *.*");
		else
			System.out.println("Muggle table. It's not magic... :/");
	}
}
