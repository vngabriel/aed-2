package kruskal;

import java.util.Arrays;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int nVertices = sc.nextInt();
        int nEdges = sc.nextInt();

        Character[] vertices = new Character[nVertices];
        String[] edges = new String[nEdges];

        for (int i = 0; i < nVertices; i++) {
            vertices[i] = sc.next().charAt(0);
        }

        for (int i = 0; i < nEdges; i++) {
            String edge = sc.next();
            String weight = sc.next();

            edges[i] = edge + " " + weight;
        }


        GraphAdjacencyMatrix graphAdjacencyMatrix = new GraphAdjacencyMatrix(vertices, edges);
        System.out.println("Graph Adjacency Matrix: ");
        System.out.println(graphAdjacencyMatrix);
        graphAdjacencyMatrix.kruskal();
    }
}