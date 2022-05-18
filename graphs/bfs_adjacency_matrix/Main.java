package bfs_adjacency_matrix;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

    private static final String DIR = "bfs_adjacency_matrix";

    public static void main(String[] args) {
        Scanner scannerUser = new Scanner(System.in);
        Scanner scannerFile = null;
        String filePath = new File("").getAbsolutePath();

        System.out.print("Enter the file name (the file must be in the same directory as the Main class): ");
        filePath = filePath.concat(File.separator + DIR + File.separator + scannerUser.nextLine());
        File file = new File(filePath);

        try {
            scannerFile = new Scanner(file);

            if (scannerFile.hasNext()) {
                int nVertices = scannerFile.nextInt();
                int nEdges = scannerFile.nextInt();

                GraphAdjacencyMatrix graphAdjacencyMatrix = new GraphAdjacencyMatrix(nVertices);

                for (int i = 0; i < nVertices; i++) {
                    graphAdjacencyMatrix.addVertex(scannerFile.next().charAt(0));
                }

                for (int i = 0; i < nEdges; i++) {
                    String edge = scannerFile.next();
                    graphAdjacencyMatrix.addEdge(edge.charAt(0), edge.charAt(1));
                }

                System.out.println("Graph Adjacency Matrix: ");
                System.out.println(graphAdjacencyMatrix);
                System.out.print("Enter the origin vertex to breadth-first-search algorithm: ");
                char originVertex = scannerUser.next().charAt(0);
                graphAdjacencyMatrix.bfs(originVertex);
            }

        } catch (FileNotFoundException | GraphAdjacencyMatrix.VertexNotFind e) {
            System.out.println(e.getMessage());
        }
    }
}