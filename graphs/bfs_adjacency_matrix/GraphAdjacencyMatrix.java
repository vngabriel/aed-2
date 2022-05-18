package bfs_adjacency_matrix;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class GraphAdjacencyMatrix {

    private enum Color {
        WHITE,
        BLACK,
        GRAY
    }

    public static class VertexNotFind extends Exception {
        @Override
        public String getMessage() {
            return "Vertex not find!";
        }
    }

    private final LinkedList<Character> mappingVertices;
    private final int nVertices;
    private final int[][] adjacencyMatrix;

    public GraphAdjacencyMatrix(int nVertices) {
        this.nVertices = nVertices;
        this.mappingVertices = new LinkedList<>();
        this.adjacencyMatrix = new int[nVertices][nVertices];

        for (int i = 0; i < nVertices; i++) {
            for (int j = 0; j < nVertices; j++) {
                if (i == j) {
                    adjacencyMatrix[i][j] = 1;
                } else {
                    adjacencyMatrix[i][j] = 0;
                }
            }
        }
    }

    // breadth-first-search
    public void bfs(char originVertex) throws VertexNotFind {
        if (!mappingVertices.contains(originVertex)) {
            throw new VertexNotFind();
        }

        Color[] colors = new Color[nVertices];
        int[] distances = new int[nVertices];
        Character[] predecessors = new Character[nVertices];

        for (int i = 0; i < nVertices; i++) {
            colors[i] = Color.WHITE;
            distances[i] = Integer.MAX_VALUE;
            predecessors[i] = null;
        }
        colors[mappingVertices.indexOf(originVertex)] = Color.GRAY;
        distances[mappingVertices.indexOf(originVertex)] = 0;
        Queue<Character> queue = new LinkedList<>();
        queue.add(originVertex);

        while (!queue.isEmpty()) {
            Character vertex = queue.poll();
            int[] adjacent = adjacencyMatrix[mappingVertices.indexOf(vertex)];
            for (int intVertices = 0; intVertices < nVertices; intVertices++) {
                if (adjacent[intVertices] == 1) { // getting the adjacency vertices
                    if (colors[intVertices] == Color.WHITE) {
                        colors[intVertices] = Color.GRAY;
                        distances[intVertices] = distances[mappingVertices.indexOf(vertex)] + 1;
                        predecessors[intVertices] = vertex;
                        queue.add(mappingVertices.get(intVertices));
                    }
                }
            }
            colors[mappingVertices.indexOf(vertex)] = Color.BLACK;
        }

        System.out.println("\nBreadth-First-Search result:");
        System.out.println("Colors: " + Arrays.toString(colors));
        System.out.println("Distances: " + Arrays.toString(distances));
        System.out.println("Predecessors: " + Arrays.toString(predecessors));
    }

    public void addEdge(char u, char v) {
        adjacencyMatrix[mappingVertices.indexOf(u)][mappingVertices.indexOf(v)] = 1;
        adjacencyMatrix[mappingVertices.indexOf(v)][mappingVertices.indexOf(u)] = 1;
    }

    public void addVertex(char vertex) {
        mappingVertices.add(vertex);
    }

    @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        graph.append("\t");
        for (Character vertex : mappingVertices) {
            graph.append(vertex)
                    .append("\t");
        }
        graph.append("\n");

        for (int i = 0; i < nVertices; i++) {
            graph.append(mappingVertices.get(i))
                    .append("\t");
            for (int j = 0; j < nVertices; j++) {
                graph.append(adjacencyMatrix[i][j])
                        .append("\t");
            }
            graph.append("\n");
        }
        return graph.toString();
    }
}
