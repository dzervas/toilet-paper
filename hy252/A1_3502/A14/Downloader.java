import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;

public class Downloader {
	static int download(String address, String output) {
		StringBuilder tmp = new StringBuilder("");
		long startTime;
		long endTime;
		int c;

		try {

			URL url = new URL(address);
			BufferedReader in = new BufferedReader(
					new InputStreamReader(url.openStream(), "UTF-8"));

			startTime = System.nanoTime();
			do {
				c = in.read();
				tmp.append((char) c);
			} while (c != -1);
			endTime = System.nanoTime();

			in.close();
		} catch (Exception e) {
			System.out.println(e);
			return -1;
		}

		//System.out.print(tmp.toString());
		System.out.print("Download time: " + (endTime - startTime) + "ns");

		return 0;
	}

	public static void main(String[] a) {
		JFileChooser chooser;
		int returnVal;

		String toDownload = JOptionPane.showInputDialog("Δώστε την διεύθυνση ","");

		chooser = new JFileChooser();
		if(chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			System.out.println("You chose to open this file: " + chooser.getSelectedFile());
			download(toDownload, chooser.getSelectedFile());
		}
	}
}
