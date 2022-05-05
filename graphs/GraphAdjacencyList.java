import java.util.LinkedList;
import java.util.List;

public class GraphAdjacencyList {

    private LinkedList<Character> mappingVertices;
    private LinkedList<Integer>[] adjacencyList;
    private int numberOfVertex;

    public GraphAdjacencyList(Character[] vertices, String[] edges) {
        mappingVertices = new LinkedList<>(List.of(vertices));
        numberOfVertex = mappingVertices.size();

        adjacencyList = new LinkedList[numberOfVertex];
        for (int i = 0; i < numberOfVertex; i++) {
            adjacencyList[i] = new LinkedList<Integer>();
        }

        createConnections(edges);
    }

    private void createConnections(String[] edges) {
        for (String edge : edges) {
            char vertex1 = edge.charAt(0);
            char vertex2 = edge.charAt(1);

            int index_vertex1 = mappingVertices.indexOf(vertex1);
            int index_vertex2 = mappingVertices.indexOf(vertex2);

            adjacencyList[index_vertex1].add(index_vertex2);
            adjacencyList[index_vertex2].add(index_vertex1);
        }
    }

    @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        for (int i = 0; i < numberOfVertex; i++) {
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
