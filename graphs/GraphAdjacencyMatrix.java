import java.util.LinkedList;
import java.util.List;

public class GraphAdjacencyMatrix {

    private LinkedList<Character> mappingVertices;
    private int[][] adjacencyMatrix;
    private int numberOfVertex;

    public GraphAdjacencyMatrix(Character[] vertices, String[] edges) {
        mappingVertices = new LinkedList<>(List.of(vertices));
        numberOfVertex = mappingVertices.size();

        adjacencyMatrix = new int[numberOfVertex][numberOfVertex];
        for (int i = 0; i < numberOfVertex; i++) {
            for (int j = 0; j < numberOfVertex; j++) {
                if (i == j) {
                    adjacencyMatrix[i][j] = 1;
                } else {
                    adjacencyMatrix[i][j] = 0;
                }
            }
        }

        createConnections(edges);
    }

    private void createConnections(String[] edges) {
        for (String edge : edges) {
            char vertex1 = edge.charAt(0);
            char vertex2 = edge.charAt(1);

            int index_vertex1 = mappingVertices.indexOf(vertex1);
            int index_vertex2 = mappingVertices.indexOf(vertex2);

            adjacencyMatrix[index_vertex1][index_vertex2] = 1;
            adjacencyMatrix[index_vertex2][index_vertex1] = 1;
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

        for (int i = 0; i < numberOfVertex; i++) {
            graph.append(mappingVertices.get(i))
                    .append("\t");
            for (int j = 0; j < numberOfVertex; j++) {
                graph.append(adjacencyMatrix[i][j])
                        .append("\t");
            }
            graph.append("\n");
        }
        return graph.toString();
    }
}
