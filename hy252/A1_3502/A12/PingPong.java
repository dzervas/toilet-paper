import org.jfugue.Player;

class Utilities {
	public static void sound(int i) {
		Player p = new Player();
		p.play("[" + i + "] [" + (i+2) + "] [" + (i+5) + "]");
		return;
	}
}

class Ping {
	public static void ping(int i) {
		System.out.println("Ping " + i + " " + (i+3) + " " + (i+7));
		Utilities.sound(i);
		if (i < 100)
			Pong.pong(i - 1);
	}

	public static void main(String[] args) {
		Ping.ping(40);
	}
}

class Pong {
	public static void pong(int i) {
		System.out.println("Ping " + i + " " + (i+4) + " " + (i+7));
		Utilities.sound(i);
		if (i > 1)
			Ping.ping(i + 2);
	}

	public static void main(String[] args) {
		Pong.pong(40);
	}
}
