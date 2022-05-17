package kruskal;

import java.util.*;

public class GraphAdjacencyMatrix {

    private class Edge {
        public char vertex1;
        public char vertex2;
        public int weight;

        Edge(char u, char v, int weight) {
            this.vertex1 = u;
            this.vertex2 = v;
            this.weight = weight;
        }

        @Override
        public String toString() {
            return String.format("%c%c", vertex1, vertex2);
        }
    }

    private final LinkedList<Character> mappingVertices;
    private final int nVertices;
    private final LinkedList<Edge> edges;
    private final int[][] adjacencyMatrix;

    public GraphAdjacencyMatrix(Character[] vertices, String[] edges) {
        mappingVertices = new LinkedList<>(List.of(vertices));
        nVertices = mappingVertices.size();
        this.edges = new LinkedList<>();

        for (String e : edges) {
            char u = e.charAt(0);
            char v = e.charAt(1);
            int weight = Integer.parseInt(e.split(" ")[1]);

            this.edges.add(new Edge(u, v, weight));
        }

        adjacencyMatrix = new int[nVertices][nVertices];
        for (int i = 0; i < nVertices; i++) {
            for (int j = 0; j < nVertices; j++) {
                if (i == j) {
                    adjacencyMatrix[i][j] = 1; // TODO: para grafos ponderados, inicia a diagonal principal tudo 1?
                } else {
                    adjacencyMatrix[i][j] = 0;
                }
            }
        }

        createConnections();
    }

    // Kruskal's algorithm to minimum spanning tree
    public void kruskal() {
        LinkedList<String> mst = new LinkedList<>();
        Set<Set<Character>> verticesSets = new HashSet<>();

        for (Character vertex : mappingVertices) {
            Set<Character> vertexSet = new HashSet<>();
            vertexSet.add(vertex);

            verticesSets.add(vertexSet);
        }
        edges.sort(Comparator.comparingInt(edge -> edge.weight));

        for (Edge edge : edges) {
            if (verticesSets.size() == 1) {
                break;
            }
            if (findSet(edge.vertex1, verticesSets) != findSet(edge.vertex2, verticesSets)) {
                mst.add(edge.toString());
                union(edge.vertex1, edge.vertex2, verticesSets);
            }
        }

        System.out.println(mst);
    }

    private void union(char vertex1, char vertex2, Set<Set<Character>> verticesSets) {
        Set<Character> vertex1Set = findSet(vertex1, verticesSets);
        Set<Character> vertex2Set = findSet(vertex2, verticesSets);
        if (vertex1Set != null && vertex2Set != null) {
            verticesSets.remove(vertex1Set);
            verticesSets.remove(vertex2Set);
            vertex1Set.addAll(vertex2Set);
            verticesSets.add(vertex1Set);
        }
    }

    private Set<Character> findSet(Character vertex, Set<Set<Character>> verticesSets) {
        for (Set<Character> set : verticesSets) {
            if (set.contains(vertex)) {
                return set;
            }
        }

        return null;
    }

    public void add(char u, char v, int weight) {
        adjacencyMatrix[mappingVertices.indexOf(u)][mappingVertices.indexOf(v)] = weight;
        adjacencyMatrix[mappingVertices.indexOf(v)][mappingVertices.indexOf(u)] = weight;
    }

    private void createConnections() {
        for (Edge edge : edges) {
            add(edge.vertex1, edge.vertex2, edge.weight);
        }
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
