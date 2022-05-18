package kruskal;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

    private static final String DIR = "kruskal";

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
                    int weight = scannerFile.nextInt();
                    graphAdjacencyMatrix.addEdge(edge.charAt(0), edge.charAt(1), weight);
                }

                System.out.println("Graph Adjacency Matrix: ");
                System.out.println(graphAdjacencyMatrix);
                graphAdjacencyMatrix.kruskal();
            }

        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }
}