import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.URL;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;

public class Downloader {
	static int download(String address, File output) {
		BufferedReader in;
		PrintWriter out;
		URL url;

		long startTime;
		long endTime;
		int c;

		try {
			out = new PrintWriter(output);
			url = new URL(address);
			in = new BufferedReader(new InputStreamReader(url.openStream(), "UTF-8"));

			startTime = System.nanoTime();

			do {
				c = in.read();
				out.print((char) c);
			} while (c != -1);

			endTime = System.nanoTime();

			in.close();
		} catch (Exception e) {
			System.out.println(e);
			return -1;
		}

		System.out.print("Download time: " + (endTime - startTime) + "ns");

		return 0;
	}

	public static void main(String[] a) {
		JFileChooser chooser;
		String toDownload;
		int returnVal;

		toDownload = JOptionPane.showInputDialog("Δώστε την διεύθυνση ","");
		chooser = new JFileChooser();

		if(chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			download(toDownload, chooser.getSelectedFile());
		}
	}
}
