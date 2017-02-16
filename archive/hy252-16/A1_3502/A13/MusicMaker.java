import org.jfugue.Player;

public class MusicMaker {
	static int[] concat(int[] a, int[] b) {
		int result[];

		result = new int[a.length + b.length];

		for (int i = 0; i < a.length; i++) {
			result[i] = a[i];
		}

		for (int i = 0; i < b.length; i++) {
			result[a.length + i] = b[i];
		}

		return result;
	}

	// I assume that "by" will ALWAYS be of 3 elemts long
	static int[] expand(int[] input, int[] by) {
		int result[];

		result = new int[input.length * 3];

		for (int i = 0; i < input.length; i++) {
			for (int j = 0; j < by.length; j++) {
				result[(i * by.length) + j] = input[i] + by[j];
			}
		}
		System.out.println();

		return result;
	}

	static int[] expandHappy(int[] input) {
		return expand(input, new int[]{0, 4, 7});
	}

	static int[] expandSad(int[] input) {
		return expand(input, new int[]{0, 3, 7});
	}

	static void playArray(int a[]) {
		StringBuilder result = new StringBuilder("");

		for (int i = 0; i < a.length; i++) {
			result.append("[" + a[i] + "] ");
		}

		System.out.println(result);
		Player p = new Player();
		p.play(result.toString());
	}

	public static void main(String[] args) {
		int seed1[] = {80, 80};
		int seed2[] = {80, 92, 104};
		int seed3[] = {70,70,74,77,77};

		playArray(seed1);
		playArray(expandHappy(seed1));
		playArray(expandSad(seed1));
		playArray(expandHappy(seed2));
		playArray(concat(seed1,
					concat(expandHappy(seed3),expandSad(seed2))));

	}
}
