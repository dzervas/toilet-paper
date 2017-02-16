import java.io.*;

public class drawFHtml {
    public static void main(String[] args) throws IOException {
	Integer tmp = Integer.parseInt(args[0]) * 10;
	PrintWriter out = new PrintWriter("PhiF.html", "UTF-8");
	out.print("<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />\n</head>\n<body>\n<p style=\"font-size:"
		  + Integer.toString(tmp*10) + "%\" align=\"center\">F</p>\n</body>\n</html>");
	out.close();
    }
}
