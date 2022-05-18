package dfs_adjacency_list;

import java.util.*;

public class GraphAdjacencyList {

    private enum Color {
        WHITE,
        BLACK,
        GRAY
    }

    // attributes to represent the graph
    private final LinkedList<Character> mappingVertices;
    private final int nVertices;
    private final Map<Character, List<Character>> adjacencyList;

    // attributes to deep-first-search
    private Color[] colors;
    private Character[] predecessors;
    private int[] discoveryTime;
    private int[] finishTime;
    private int time;

    public GraphAdjacencyList(int nVertices) {
        this.nVertices = nVertices;
        this.mappingVertices = new LinkedList<>();
        this.adjacencyList = new HashMap<>();
    }

    // deep-first-search
    public void dfs() {
        colors = new Color[nVertices];
        predecessors = new Character[nVertices];
        discoveryTime = new int[nVertices];
        finishTime = new int[nVertices];

        for (Character vertex : mappingVertices) {
            int indexVertex = mappingVertices.indexOf(vertex);

            colors[indexVertex] = Color.WHITE;
            predecessors[indexVertex] = null;
            discoveryTime[indexVertex] = 0;
            finishTime[indexVertex] = 0;
        }

        time = 0;
        for (Character vertex : mappingVertices) {
            int indexVertex = mappingVertices.indexOf(vertex);

            if (colors[indexVertex] == Color.WHITE) {
                dfsVisit(indexVertex);
            }
        }

        System.out.println("Deep-First-Search result:");
        System.out.println("Colors: " + Arrays.toString(colors));
        System.out.println("Predecessors: " + Arrays.toString(predecessors));
        System.out.println("Discovery time: " + Arrays.toString(discoveryTime));
        System.out.println("Finish time: " + Arrays.toString(finishTime));
    }

    private void dfsVisit(int indexVertex) {
        discoveryTime[indexVertex] = ++time;
        colors[indexVertex] = Color.GRAY;

        for (Character adjacentVertex : adjacencyList.get(mappingVertices.get(indexVertex))) {
            int indexAdjacentVertex = mappingVertices.indexOf(adjacentVertex);
            if (colors[indexAdjacentVertex] == Color.WHITE) {
                predecessors[indexAdjacentVertex] = mappingVertices.get(indexVertex);
                dfsVisit(indexAdjacentVertex);
            }
        }
        colors[indexVertex] = Color.BLACK;
        finishTime[indexVertex] = ++time;
    }

    public void addVertex(char vertex) {
        adjacencyList.put(vertex, new LinkedList<>());
        mappingVertices.add(vertex);
    }

    public void addEdge(char u, char v) {
        adjacencyList.get(u).add(v);
        adjacencyList.get(v).add(u);
    }

    @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        for (Map.Entry<Character, List<Character>> entry : adjacencyList.entrySet()) {
            graph.append(entry.getKey())
                    .append(": ");
            List<Character> list = entry.getValue();
            for (Character vertex : list) {
                graph.append(vertex)
                        .append(" ");
            }
            graph.append("\n");
        }

        return graph.toString();
    }
}
