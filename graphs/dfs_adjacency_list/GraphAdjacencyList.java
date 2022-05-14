package dfs_adjacency_list;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class GraphAdjacencyList {

    public enum Color {
        WHITE,
        BLACK,
        GRAY
    }

    // attributes to represent the graph
    private final LinkedList<Character> mappingVertices;
    private final int nVertices;
    private final LinkedList<String> edges;
    private final LinkedList<Integer>[] adjacencyList;

    // attributes to deep-first-search
    private Color[] colors;
    private Character[] predecessors;
    private int[] discoveryTime;
    private int[] finishTime;
    private int time;

    public GraphAdjacencyList(Character[] vertices, String[] edges) {
        mappingVertices = new LinkedList<>(List.of(vertices));
        this.edges = new LinkedList<>(List.of(edges));
        nVertices = mappingVertices.size();

        adjacencyList = new LinkedList[nVertices];
        for (int i = 0; i < nVertices; i++) {
            adjacencyList[i] = new LinkedList<Integer>();
        }

        createConnections();
    }

    // deep-first-search
    public void dfs() {
        colors = new Color[nVertices];
        predecessors = new Character[nVertices];
        discoveryTime = new int[nVertices];
        finishTime = new int[nVertices];

        for (int i = 0; i < nVertices; i++) {
            colors[i] = Color.WHITE;
            predecessors[i] = null;
            discoveryTime[i] = 0;
            finishTime[i] = 0;
        }
        time = 0;
        for (int i = 0; i < nVertices; i++) {
            if (colors[i] == Color.WHITE) {
                dfsVisit(i);
            }
        }

        showDfsResult();
    }

    private void dfsVisit(int intVertex) {
        discoveryTime[intVertex] = ++time;
        colors[intVertex] = Color.GRAY;

        for (Integer intAdjacencyVertex : adjacencyList[intVertex]) {
            if (colors[intAdjacencyVertex] == Color.WHITE) {
                predecessors[intAdjacencyVertex] = mappingVertices.get(intVertex);
                dfsVisit(intAdjacencyVertex);
            }
        }
        colors[intVertex] = Color.BLACK;
        finishTime[intVertex] = ++time;
    }

    private void showDfsResult() {
        System.out.println("Deep-First-Search result:");
        System.out.println("Colors: " + Arrays.toString(colors));
        System.out.println("Predecessors: " + Arrays.toString(predecessors));
        System.out.println("Discovery time: " + Arrays.toString(discoveryTime));
        System.out.println("Finish time: " + Arrays.toString(finishTime));
    }

    public void add(char u, char v) {
        adjacencyList[mappingVertices.indexOf(u)].add(mappingVertices.indexOf(v));
//        adjacencyList[mappingVertices.indexOf(v)].add(mappingVertices.indexOf(u));
    }

    private void createConnections() {
        for (String edge : edges) {
            char vertex1 = edge.charAt(0);
            char vertex2 = edge.charAt(1);

            add(vertex1, vertex2);
        }
    }

    @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        for (int i = 0; i < nVertices; i++) {
            graph.append(mappingVertices.get(i))
                    .append(": ");
            LinkedList<Integer> linkedList = adjacencyList[i];
            for (Integer index : linkedList) {
                graph.append(mappingVertices.get(index))
                        .append(" ");
            }
            graph.append("\n");
        }

        return graph.toString();
    }
}
