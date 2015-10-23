import java.util.Scanner;

public class A1EA {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		Integer[] A = new Integer[4];
		Integer[] B = new Integer[4];
		int i = 0;
		char passes = 0;

		do {
			System.out.println("Feed me nums: ");
			A[passes] = in.nextInt();
			passes++;
		} while (passes < 4);

		System.out.println("You gave me:");
		for (i = 0; i < 4; i++)
			System.out.println(A[i]);

		for (i = 0; i < 4; i++) {
			if (A[i] % 2 == 0 && A[i] != 0)
				A[i]++;
		}

		System.out.println("But now A contains...");
		for (i = 0; i < 4; i++) {
			System.out.println(A[i]);
		}

		for (i = 0; i < 4; i++)
			B[i] = A[3-i];

		System.out.println("STARSSSS:");
		for (i = 0; i < 4; i++) {
			System.out.print(B[i]);

			if (B[i] > 0) {
				for (int j = 0; j < B[i]; j++)
					System.out.print("*");
			}

			System.out.println();
		}
	}
}
