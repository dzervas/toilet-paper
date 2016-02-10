import java.util.Random;
import org.jfugue.Player;

public class ArrayManager {
    private static Random rand;

    public static void fillRandom(int min, int max, int[] ar) {
	// NOTE: nextInt is exclusive, that's why the +1
	for (int i = 0; i < ar.length; i++)
	    ar[i] = rand.nextInt(max - min + 1) + min;
    }

    public static void fillFrom(int[] ar, int[] fromArr) {
	if (ar.length != fromArr.length) {
	    System.out.println("Oops... Arrays are not of the same size!");
	    return;
	}

	for (int i = 0; i < ar.length; i++)
	    ar[i] = fromArr[i];
    }

    public static void playMusic(int[] ar) {
	Player p = new Player();

	for (int i = 0; i < ar.length; i++)
	    p.play("[" + ar[i] + "]");
    }

    public static void main(String[] args) {
	int[] p1 = new int[20], p2 = new int[20];
	rand = new Random();

	fillRandom(50, 120, p1);
	fillFrom(p2, p1);
	playMusic(p2);
    }
}
