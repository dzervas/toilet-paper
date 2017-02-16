import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.net.URL;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;

public class Manipulator {
	static int manipulate(File input, File output, File regex) {
		BufferedReader in, reg;
		PrintWriter out;
		String line, result;
		String[] parts;
		StringBuilder tmp;

		long startTime;
		long endTime;
		int c;

		try {
			in = new BufferedReader(new FileReader(input));
			out = new PrintWriter(output);
			reg = new BufferedReader(new FileReader(regex));
			tmp = new StringBuilder("");

			c = in.read();
			while (c != -1) {
				tmp.append((char) c);
				c = in.read();
			}
			result = tmp.toString();

			line = reg.readLine();
			while (line != null) {
				parts = line.split("\\s+");
				result = result.replaceAll(parts[0], parts[1]);
				line = reg.readLine();
			}
			out.print(result);

			in.close();
			out.close();
			reg.close();
		} catch (Exception e) {
			System.out.println(e);
			return -1;
		}

		return 0;
	}

	public static void main(String[] a) {
		JFileChooser input;
		JFileChooser output;
		JFileChooser regex;

		input = new JFileChooser();
		input.setDialogTitle("Select 1st input file");
		output = new JFileChooser();
		output.setDialogTitle("Select output file");
		regex = new JFileChooser();
		regex.setDialogTitle("Select 2nd input file");

		if(input.showOpenDialog(null) == JFileChooser.APPROVE_OPTION &&
				regex.showOpenDialog(null) == JFileChooser.APPROVE_OPTION &&
				output.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
			manipulate(input.getSelectedFile(), output.getSelectedFile(), regex.getSelectedFile());
		}
	}
}
