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
	Transform("Encrypted" + input, "EncryptedEncrypted" + input, (-1 * K));
	byte[] in1 = Files.readAllBytes(new File(input).toPath());
	byte[] in2 = Files.readAllBytes(new File("EncryptedEncrypted" + input).toPath());

	for (int i = 0; i < in1.length; i++) {
	    if (in1[i] != in2[i])
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

    static void Transform(String inputFileName, String outputFileName, int inputK) throws IOException, UnsupportedEncodingException {
	File ip = new File(inputFileName);

	if (ip.isFile())
	    Transform(ip, new File(outputFileName), inputK);
	else {
	    for (File f: ip.listFiles())
		Transform(f, new File(f.getParent() + "/Encrypted" + f.getName()), inputK);
	}
    }
    
    public static void main(String[] args) throws IOException {
	if (args.length < 2) {
	    String filepath = "";

	    JFileChooser fileChooser = new JFileChooser();
	    fileChooser.setDialogTitle("Select a file");
	    int userSelection = fileChooser.showSaveDialog(null);

	    if (userSelection == JFileChooser.APPROVE_OPTION)
		filepath = fileChooser.getSelectedFile().getAbsolutePath();

	    String inputk = JOptionPane.showInputDialog("Give a number: ","");

	    args = new String[] { filepath, inputk };
	}

	long startTime = System.nanoTime();
	Transform(args[0], "Encrypted" + args[0], Integer.parseInt(args[1]));
	System.out.println("Encryption took: " + (System.nanoTime() - startTime) + "ns");

	if (new File(args[0]).isFile()) {
	    if (!test(args[0], Integer.parseInt(args[1])))
		System.out.println("The encryption was unsuccessful. You won't be able to revert the encrypted file :/");
	}
    }
}
