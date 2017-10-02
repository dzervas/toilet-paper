import java.io.*;

public class drawZHtml {
    public static void main(String[] args) throws IOException {
	Integer tmp = Integer.parseInt(args[0]);
	PrintWriter out = new PrintWriter("Z.html", "UTF-8");
	out.print("<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />\n</head>\n<body>\n<font size=\""
		  + Integer.toString(tmp) + "\">Z</font>\n</body>\n</html>");
	out.close();
    }
}
