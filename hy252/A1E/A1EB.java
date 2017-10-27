import java.util.Scanner;

public class A1EB {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String dash = "";
		int num, min, max, i;
		int[] A, B;

		A = new int[7];

		for (i = 0; i < 7; i++) {
			System.out.println("Give me num num:");
			A[i] = in.nextInt();
		}

		for (i = 0; i < 7; i++)
			A[i] *= A[i];

		min = A[0];
		max = A[0];

		for (i = 1; i < 7; i++) {
			if (A[i] < min)
				min = A[i];
			if (A[i] > max)
				max = A[i];
		}

		B = new int[2];
		B[0] = min;
		B[1] = max;

		System.out.println("B[0] = " + B[0]);
		System.out.println("B[1] = " + B[1]);

		for (i = 0; i < (B[1] - B[0]); i++) {
			dash += "-";
			if (i % 10 == 9)
				dash += "\n";
		}

		System.out.println(dash);
		dash = "";
	}
}
