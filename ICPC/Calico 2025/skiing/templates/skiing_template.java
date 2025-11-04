import java.io.*;

class Solution {
    /**
     * Output the true difficulty of each trail given
     * a mountain range with N checkpoints and M trails
     * between them.
     * 
     * N: the number of checkpoints on the mountain
     * M: the number of available trails between checkpoints
     * X: the list of X_i, the checkpoints at the start of each trail
     * Y: the list of Y_i, the checkpoints at the end of each trail
     * Z: the list of Z_i, the skill levels needed to traverse each trail
     */
    static void solve(int N, int M, int[] X, int[] Y, int[] Z) {
        // YOUR CODE HERE
        return;
    }
    
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) throws IOException {
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            String[] info = in.readLine().split(" ");
            int N = Integer.parseInt(info[0]);
            int M = Integer.parseInt(info[1]);
            int[] X = new int[M];
            int[] Y = new int[M];
            int[] Z = new int[M];
            for (int j = 0; j < M; j++) {
                String[] trail = in.readLine().split(" ");
                X[j] = Integer.parseInt(trail[0]);
                Y[j] = Integer.parseInt(trail[1]);
                Z[j] = Integer.parseInt(trail[2]);
            }
            solve(N, M, X, Y, Z);
        }
        out.flush();
    }
}
