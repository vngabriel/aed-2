package dfs_adjacency_list;

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
            edges[i] = sc.next();
        }

        GraphAdjacencyList graphAdjacencyList = new GraphAdjacencyList(vertices, edges);
        System.out.println("Graph Adjacency List: ");
        System.out.println(graphAdjacencyList);
        graphAdjacencyList.dfs();
    }
}
