package prim;

import java.util.*;

public class GraphAdjacencyList {

    private static class Node {
        public char vertex;
        public int weight;

        Node(char vertex, int weight) {
            this.vertex = vertex;
            this.weight = weight;
        }

        @Override
        public String toString() {
            return String.format("%c[%d]", vertex, weight);
        }
    }

    private static class PrimVertex implements Comparable<PrimVertex> {
        public char representation;
        public int key;
        public Character predecessor;

        PrimVertex(char representation, int key, Character predecessor) {
            this.representation = representation;
            this.key = key;
            this.predecessor = predecessor;
        }

        @Override
        public String toString() {
            return String.format("%c[%d]", representation, key);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            PrimVertex vertex = (PrimVertex) o;
            return representation == vertex.representation;
        }

        @Override
        public int compareTo(PrimVertex o) {
            return Integer.compare(this.key, o.key);
        }
    }

    public static class VertexNotFind extends Exception {
        @Override
        public String getMessage() {
            return "Vertex not find!";
        }
    }

    private final LinkedList<Character> mappingVertices;
    private final int nVertices;
    private final Map<Character, List<Node>> adjacencyList;

    public GraphAdjacencyList(int nVertices) {
        this.nVertices = nVertices;
        this.mappingVertices = new LinkedList<>();
        this.adjacencyList = new HashMap<>();
    }

    public void prim(Character originVertexRepresentation) throws VertexNotFind {
        if (!mappingVertices.contains(originVertexRepresentation)) {
            throw new VertexNotFind();
        }

        LinkedList<PrimVertex> primVertices = new LinkedList<>();
        PriorityQueue<PrimVertex> queue = new PriorityQueue<>(nVertices);
        for (Character vertexRepresentation : mappingVertices) {
            PrimVertex vertex;
            if (originVertexRepresentation == vertexRepresentation) {
                vertex = new PrimVertex(vertexRepresentation, 0, null);
            } else {
                vertex = new PrimVertex(vertexRepresentation, Integer.MAX_VALUE, null);
            }
            primVertices.add(vertex);
            queue.add(vertex);
        }

        while (!queue.isEmpty()) {
            PrimVertex vertex = queue.remove();
            for (Node node : adjacencyList.get(vertex.representation)) {
                PrimVertex adjacentVertex = primVertices.get(mappingVertices.indexOf(node.vertex));
                if (queue.contains(adjacentVertex) && node.weight < adjacentVertex.key) {
                    queue.remove(adjacentVertex);
                    adjacentVertex.predecessor = vertex.representation;
                    adjacentVertex.key = node.weight;
                    queue.add(adjacentVertex);
                    // it's necessary to remove and add the element to trigger de priority queue reorder
                }
            }
        }

        showPrimResults(primVertices);
    }

    private void showPrimResults(LinkedList<PrimVertex> primVertices) {
        int sum = 0;

        System.out.println("Vertices: " + mappingVertices);
        System.out.print("Predecessors: [");
        for (int i = 0; i < primVertices.size(); i ++) {
            if (i == primVertices.size() - 1) {
                System.out.println(primVertices.get(i).predecessor + "]");
            } else {
                System.out.print(primVertices.get(i).predecessor + ", ");
            }
        }
        System.out.print("Keys: [");
        for (int i = 0; i < primVertices.size(); i ++) {
            sum += primVertices.get(i).key;
            if (i == primVertices.size() - 1) {
                System.out.println(primVertices.get(i).key + "]");
            } else {
                System.out.print(primVertices.get(i).key + ", ");
            }
        }
        System.out.println("Sum of minimum spanning tree weights: " + sum);
    }

    public void addVertex(char vertex) {
        adjacencyList.put(vertex, new LinkedList<>());
        mappingVertices.add(vertex);
    }

    public void addEdge(char u, char v, int weight) {
        adjacencyList.get(u).add(new Node(v, weight));
        adjacencyList.get(v).add(new Node(u, weight));
    }

    @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        for (Map.Entry<Character, List<Node>> entry : adjacencyList.entrySet()) {
            graph.append(entry.getKey())
                    .append(": ");
            List<Node> list = entry.getValue();
            for (Node node : list) {
                graph.append(node)
                        .append(" ");
            }
            graph.append("\n");
        }

        return graph.toString();
    }
}
