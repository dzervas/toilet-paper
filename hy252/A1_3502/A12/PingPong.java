import javax.swing.JOptionPane;
import org.jfugue.Player;

public class PingPong {
	public static void main(String[] args) {
		Ping.ping(10);
	}
}

class Utilities {
	public static void sound(int i) {
		i = i*12;
		Player p = new Player();
		p.play("[" + i + "] [" + (i+2) + "] [" + (i+5) + "]");
		return;
	}
}

class Ping {
	public static void ping(int i) {
		Utilities.sound(i);
		JOptionPane.showMessageDialog(null, Integer.toString(i), "Ping", JOptionPane.INFORMATION_MESSAGE);
		if (i > 1)
			Pong.pong(i - 1);
	}
}

class Pong {
	public static void pong(int i) {
		Utilities.sound(i);
		JOptionPane.showMessageDialog(null, Integer.toString(i), "Pong", JOptionPane.INFORMATION_MESSAGE);
		if (i > 1)
			Ping.ping(i - 1);
	}
}
