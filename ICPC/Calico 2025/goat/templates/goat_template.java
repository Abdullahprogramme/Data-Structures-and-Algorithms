import java.io.*;

class Solution {
    /**
     * Given a rooted tree, with each vertex labeled A_1, A_2, .., A_N,
     * find the result of all Q GOAT queries.
     * 
     * N: the size of the tree
     * Q: the number of GOAT queries
     * P: the list of parent nodes for each vertex
     * A: the list of labels on the vertices of the tree
     * G: the list of each GOAT query
     */
    static void solve(int N, int Q, int[] P, int[] A, int[] G) {
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
            int Q = Integer.parseInt(info[1]);
            
            int[] P = new int[N];
            String[] parents = in.readLine().split(" ");
            for (int j = 0; j < N; j++) {
                P[j] = Integer.parseInt(parents[j]);
            }
            
            int[] A = new int[N];
            String[] labels = in.readLine().split(" ");
            for (int j = 0; j < N; j++) {
                A[j] = Integer.parseInt(labels[j]);
            }
            
            int[] G = new int[Q];
            String[] queries = in.readLine().split(" ");
            for (int j = 0; j < Q; j++) {
                G[j] = Integer.parseInt(queries[j]);
            }
            
            solve(N, Q, P, A, G);
        }
        out.flush();
    }
}
