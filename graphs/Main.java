import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int nVertex = sc.nextInt();
        int nEdges = sc.nextInt();

        Character[] vertices = new Character[nVertex];
        String[] edges = new String[nEdges];

        for (int i = 0; i < nVertex; i++) {
            vertices[i] = sc.next().charAt(0);
        }

        for (int i = 0; i < nEdges; i++) {
            edges[i] = sc.next();
        }

        GraphAdjacencyMatrix graphAdjacencyMatrix = new GraphAdjacencyMatrix(vertices, edges);
        GraphAdjacencyList graphAdjacencyList = new GraphAdjacencyList(vertices, edges);
        System.out.println("Graph Adjacency Matrix: ");
        System.out.println(graphAdjacencyMatrix);
        System.out.println("Graph Adjacency List: ");
        System.out.println(graphAdjacencyList);
    }
}