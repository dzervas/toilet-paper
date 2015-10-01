import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.Reader;
import java.net.MalformedURLException;
import java.net.URL;

public class convHtml {
    public static void main(String[] args) throws MalformedURLException, IOException {
	String[][] map = new String[][]{
	    // HTML Escaping
	    {"\n", "<br />"},
	    {"&",  "&amp"},
	    {" ",  "&nbsp"},
	    {"\t", "&nbsp"},
	    {">",  "&gt"},
	    {"<",  "&lt"},

	    // Small greek
	    {"α", "a"},
	    {"β", "b"},
	    {"γ", "g"},
	    {"δ", "d"},
	    {"ε", "e"},
	    {"ζ", "z"},
	    {"η", "h"},
	    {"θ", "8"},
	    {"ι", "i"},
	    {"κ", "k"},
	    {"λ", "l"},
	    {"μ", "m"},
	    {"ν", "n"},
	    {"ξ", "x"},
	    {"ο", "o"},
	    {"π", "p"},
	    {"ρ", "r"},
	    {"σ", "s"},
	    {"τ", "t"},
	    {"υ", "u"},
	    {"φ", "f"},
	    {"χ", "x"},
	    {"ψ", "y"},
	    {"ω", "w"},

	    // Capital greek
	    {"Α", "A"},
	    {"Β", "B"},
	    {"Γ", "G"},
	    {"Δ", "D"},
	    {"Ε", "E"},
	    {"Ζ", "Z"},
	    {"Η", "H"},
	    {"Θ", "8"},
	    {"Ι", "I"},
	    {"Κ", "K"},
	    {"Λ", "L"},
	    {"Μ", "M"},
	    {"Ν", "N"},
	    {"Ξ", "X"},
	    {"Ο", "O"},
	    {"Π", "P"},
	    {"Ρ", "R"},
	    {"Σ", "S"},
	    {"Τ", "T"},
	    {"Υ", "U"},
	    {"Φ", "F"},
	    {"Χ", "X"},
	    {"Ψ", "Y"},
	    {"Ω", "W"},

	    // Small with diacritics
	    {"ά", "a"},
	    {"έ", "e"},
	    {"ή", "h"},
	    {"ί", "i"},
	    {"ΐ", "i"},
	    {"ό", "o"},
	    {"ς", "s"},
	    {"ύ", "u"},
	    {"ώ", "w"},

	    // Capital with diacritics
	    {"Ά", "A"},
	    {"Έ", "E"},
	    {"Ή", "H"},
	    {"Ί", "I"},
	    {"Ό", "O"},
	    {"Ύ", "U"},
	    {"Ώ", "W"},
	};

	int i;
	long startTime, finalTime;
	Reader fp;
	String buff;

	try {
	    fp = new FileReader(args[0]);
	    PrintWriter out = new PrintWriter(args[0] + ".html", "UTF-8");
	} catch (FileNotFoundException e) {
	    fp = new InputStreamReader(new URL(args[0]).openStream(), "UTF-8");
	    PrintStream out = System.out;
	}

	out.println("<!DOCTYPE html>\n<html>\n<head>\n" +
			   "<meta http-equiv=\"content-type\" " +
			   "content=\"text/html;charset=utf-8\" />\n" +
			   "<title>" + args[0] + "</title>\n</head>\n<body>");

	BufferedReader in = new BufferedReader(fp);

	startTime = System.nanoTime();
	while (in.ready()) {
	    buff = in.readLine();

	    for (i = 0; i < map.length; i++)
		buff = buff.replace(map[i][0], map[i][1]);

	    out.println(buff + "<br />");
	}
	finalTime = System.nanoTime() - startTime;

	out.println("</body>\n</html>");
	System.out.println("Took just " + finalTime + "ns!");

	out.close();
    }
}
