import javax.swing.JOptionPane;

public class PingPong {
	public static void main(String[] args) {
		Ping.ping(10);
	}
}

class Ping {
	public static void ping(int i) {
		JOptionPane.showMessageDialog(null, Integer.toString(i), "Ping", JOptionPane.INFORMATION_MESSAGE);
		if (i > 1)
			Pong.pong(i - 1);
	}
}

class Pong {
	public static void pong(int i) {
		JOptionPane.showMessageDialog(null, Integer.toString(i), "Pong", JOptionPane.INFORMATION_MESSAGE);
		if (i > 1)
			Ping.ping(i - 1);
	}
}
