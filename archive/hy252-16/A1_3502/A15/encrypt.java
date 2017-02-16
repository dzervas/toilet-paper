import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.nio.file.Files;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class encrypt {
	static boolean test(String input, int K) throws IOException {
		File ip = new File(input);
		File ip1 = new File(ip.getParent() + "/Encrypted" + ip.getName());
		File ip2 = new File(ip.getParent() + "/EncryptedEncrypted" + ip.getName());
		byte[] in;
		byte[] in2;

		Transform(ip1, ip2, -1 * K);
		in = Files.readAllBytes(ip.toPath());
		in2 = Files.readAllBytes(ip2.toPath());

		for (int i = 0; i < in.length; i++) {
			if (in[i] != in2[i])
				return false;
		}

		return true;
	}

	static void Transform(File inputFile, File outputFile, int inputK) throws IOException, UnsupportedEncodingException {
		byte K = (byte) inputK;
		byte[] in = Files.readAllBytes(inputFile.toPath());
		FileOutputStream out = new FileOutputStream(outputFile);

		for (byte buff: in)
			out.write(buff + K);

		out.close();
	}

	// The second parameter "outputFileName" just complicates things.
	// Though it works if it's commented out.
	//static void Transform(String inputFileName, String outputFileName, int inputK) throws IOException, UnsupportedEncodingException {
	static void Transform(String inputFileName, int inputK) throws IOException, UnsupportedEncodingException {
		File ip = new File(inputFileName);

		if (ip.isFile())
			Transform(ip, new File(ip.getParent() + "/Encrypted" + ip.getName()), inputK);
		else {
			for (File f: ip.listFiles()) {
				Transform(f, new File(f.getParent() + "/Encrypted" + f.getName()), inputK);
				test(new File(f.getParent() + "/Encrypted" + f.getName()).toString(), inputK);
			}
		}
	}

	public static void main(String[] args) throws IOException {
		String inputk;

		if (args.length < 2) {
			String filepath = "";

			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setDialogTitle("Select a file");
			int userSelection = fileChooser.showOpenDialog(null);

			if (userSelection == JFileChooser.APPROVE_OPTION) {
				filepath = fileChooser.getSelectedFile().getAbsolutePath();
				inputk = JOptionPane.showInputDialog("Give a number: ","");
				args = new String[] { filepath, inputk };
			}
		}

		long startTime = System.nanoTime();
		Transform(args[0], Integer.parseInt(args[1]));
		System.out.println("Encryption took: " + (System.nanoTime() - startTime) + "ns");

		if (new File(args[0]).isFile()) {
			if (!test(args[0], Integer.parseInt(args[1])))
				System.out.println("The encryption was unsuccessful. You won't be able to revert the encrypted file :/");
		}
	}
}
