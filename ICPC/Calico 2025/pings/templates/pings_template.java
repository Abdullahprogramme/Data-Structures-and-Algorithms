import java.io.*;

class Solution {
    /**
     * Output the number of times each user is pinged in the server after
     * all actions.
     *
     * Q: the total number of actions
     * N: the number of roles in the server
     * M: the number of users in the server
     * X: the list of actions performed at each timestep
     * R: the list of roles involved at each timestep
     * U: the list of users involved at each timestep, or -1 if the action is a ping
     */
    static void solve(int Q, int N, int M, char[] X, int[] R, int[] U) {
        // YOUR CODE HERE
        System.out.println(0);
        System.out.println(1);
    }

    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            String[] temp = in.readLine().strip().split(" ");
            int Q = Integer.parseInt(temp[0]);
            int N = Integer.parseInt(temp[1]);
            int M = Integer.parseInt(temp[2]);

            char[] X = new char[Q];
            int[] R = new int[Q];
            int[] U = new int[Q];

            for (int k = 0; k < Q ; k++) {
                String[] tok = in.readLine().strip().split(" ");
                X[k] = tok[0].charAt(0);
                R[k] = Integer.parseInt(tok[1]);
                if (tok.length > 2) {
                    U[k] = Integer.parseInt(tok[2]);
                } else {
                    U[k] = -1;
                }
            }

            solve(Q, N, M, X, R, U);
        }
        out.flush();
    }
}
