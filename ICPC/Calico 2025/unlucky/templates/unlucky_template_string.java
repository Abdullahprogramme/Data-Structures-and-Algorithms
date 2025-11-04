import java.io.*;

class Solution {
    /**
      * Find the largest D digit number that does not contain any unlucky number
      * from L.
      *
      * N: the number of unlucky numbers
      * D: the number of digits in the number to find
      * L: the list of unlucky numbers
      */
    static String solve(int N, int D, String[] L) {
        // YOUR CODE HERE
        return "-1";
    }
    
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().split(" ");
            int N = Integer.parseInt(temp[0]);
            int D = Integer.parseInt(temp[1]);
            String[] L = in.readLine().split(" ");
            out.println(solve(N, D, L));
        }
        out.flush();
    }
}
