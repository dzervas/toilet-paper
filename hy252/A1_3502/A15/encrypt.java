import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.lang.System;
import java.nio.file.Files;
import java.util.Scanner;
import java.util.Arrays;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

public class encrypt {
	private static String q, a;

	static boolean test(String input, int K) throws IOException {
		File f = new File(input);
		Transform(f.getParent() + "/Encrypted" + f.getName(), f.getParent() + "/EncryptedEncrypted" + f.getName(), (-1 * K), "Decrypt");

		byte[] in1 = Files.readAllBytes(f.toPath());
		byte[] in2 = Files.readAllBytes(new File(f.getParent() + "/EncryptedEncrypted" + f.getName()).toPath());

		for (int i = 0; i < in1.length; i++) {
			if (in1[i] != in2[i])
				return false;
		}

		return true;
	}

	static void Transform(File inputFile, File outputFile, int inputK, String operation) throws IOException, UnsupportedEncodingException {
		byte K = (byte) inputK;
		byte[] in = Files.readAllBytes(inputFile.toPath());
		FileOutputStream out = new FileOutputStream(outputFile);

		Scanner stdin = new Scanner(System.in);

		System.out.println("How do you pronounce Java? (max 10 characters)");
		String a = stdin.nextLine();
		if (a.length() > 10) {
			System.out.println("As said, the answer can be up to 10 characters...");
			System.exit(1);
		}
		a = a + ("##########".substring(a.length()));


		if (operation.equals("Encrypt") && a.length() > 0) {
			a = "How do you pronounce Java?=" + a;

			for (byte buff: a.getBytes())
				out.write(buff + K);
		} else if (operation.equals("Decrypt")) {
			int i;
			byte[] q = Arrays.copyOfRange(in, 0, 27);

			for (i = 0; i < 27; i++)
				q[i] += K;

			if (Arrays.equals("How do you pronounce Java?=".getBytes(), q)) {
				byte[] qa = Arrays.copyOfRange(in, 27, 37);
				for (i = 0; i < 10; i++)
					qa[i] += K;

				if (!Arrays.equals(a.getBytes(), qa)) {
					System.out.println("Wrong answer!");
					System.exit(1);
				}
				in = Arrays.copyOfRange(in, 37, in.length);
			}
		}

		for (byte buff: in)
			out.write(buff + K);

		out.close();
	}

	static void Transform(String inputFileName, String outputFileName, int inputK, String operation) throws IOException, UnsupportedEncodingException {
		File ip = new File(inputFileName);

		if (ip.isFile())
			Transform(ip, new File(outputFileName), inputK, operation);
		else {
			for (File f: ip.listFiles())
				Transform(f, new File(f.getParent() + "/Encrypted" + f.getName()), inputK, operation);
		}
	}

	public static void main(String[] args) throws IOException {
		long startTime = System.nanoTime();
		File f = new File(args[0]);
		Transform(f.getAbsolutePath(), f.getParent() + "/Encrypted" + f.getName(), Integer.parseInt(args[2]), args[1]);
		System.out.println(args[1] + "ion took: " + (System.nanoTime() - startTime) + "ns");

		if (args[1].equals("Encrypt")) {
			if (!f.isFile() || !test(args[0], Integer.parseInt(args[2])))
				System.out.println("The encryption was unsuccessful. Bummer :/");
			else
				System.out.println("Tests passed!");
		}
	}
}
