import java.util.Random;

public class CyclicCalls {
    private static Random rand;

    private static void m1(int arg) {
	if (arg == 9) {
	    System.out.println("Bingo!");
	    System.exit(0);
	}

	System.out.println("m1 called with argument " + arg);
	m2((int) (arg * rand.nextDouble()));
    }

    private static void m2(int arg) {
	if (arg == 9) {
	    System.out.println("Bingo!");
	    System.exit(0);
	}

	System.out.println("m2 called with argument " + arg);
	m1((int) (arg * rand.nextDouble()));
    }

    public static void main(String[] args) {
	rand = new Random();
	m1(10);
    }
}
