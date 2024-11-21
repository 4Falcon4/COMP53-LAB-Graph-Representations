#ifndef ADJACENCYLISTGRAPH_H
#define ADJACENCYLISTGRAPH_H

#include "DirectedGraph.h"
#include "AdjacencyListVertex.h"

class AdjacencyListGraph : public DirectedGraph {
protected:
   std::vector<AdjacencyListVertex*> vertices;
   
public:    
   virtual ~AdjacencyListGraph() {
      for (AdjacencyListVertex* vertex : vertices) {
         delete vertex;
      }
   }

   // Creates and adds a new vertex to the graph, provided a vertex with the
   // same label doesn't already exist in the graph. Returns the new vertex on
   // success, nullptr on failure.
   virtual Vertex* AddVertex(std::string newVertexLabel) override {
      
	   for (int i = 0; i < vertices.size(); i++) {
		   if (vertices[i]->GetLabel() == newVertexLabel) {
			   return nullptr;
		   }
	   }

       vertices.push_back(new AdjacencyListVertex(newVertexLabel));
       Vertex* newVertex = new AdjacencyListVertex(newVertexLabel);

      return newVertex;
   }
    
   // Adds a directed edge from the first to the second vertex. If the edge
   // already exists in the graph, no change is made and false is returned.
   // Otherwise the new edge is added and true is returned.
   virtual bool AddDirectedEdge(Vertex* fromVertex, Vertex* toVertex) override {
       for (int i = 0; i < vertices.size(); i++)
       {
           if (vertices[i] == fromVertex) 
           {
               if (HasEdge(fromVertex, toVertex)) 
               {
                   return false;
               }
               else 
               {
                   vertices[i]->adjacent.push_back(toVertex);
                   return true;
               }
           }
       }
      return false;
   }
    
   // Returns a vector of edges with the specified fromVertex.
   virtual std::vector<Edge> GetEdgesFrom(Vertex* fromVertex) override {
       std::vector<Edge> edges;
       for (int i = 0; i < vertices.size(); i++)
       {
           if (HasEdge(fromVertex, vertices[i]))
           {
               edges.push_back(Edge(fromVertex, vertices[i]));
           }
       }
      return std::vector<Edge>();
   }
    
   // Returns a vector of edges with the specified toVertex.
   virtual std::vector<Edge> GetEdgesTo(Vertex* toVertex) override {
       std::vector<Edge> edges;
       for (int i = 0; i < vertices.size(); i++)
       {
           if (HasEdge(vertices[i], toVertex))
           {
			   edges.push_back(Edge(vertices[i], toVertex));
           }
       }
      return edges;
   }
    
   // Returns a vertex with a matching label, or nullptr if no such vertex
   // exists
   virtual Vertex* GetVertex(std::string vertexLabel) override {

       for (int i = 0; i < vertices.size(); i++) {
           if (vertices[i]->GetLabel() == vertexLabel) {
               return vertices[i];
           }
       }
       return nullptr;
   }
    
   // Returns true if this graph has an edge from fromVertex to toVertex
   virtual bool HasEdge(Vertex* fromVertex, Vertex* toVertex) override {
       for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == fromVertex) {
                for (int j = 0; j < vertices[i]->adjacent.size(); j++) {
                    if (vertices[i]->adjacent[j] == toVertex) {
                        return true;
                    }
                }
           }
       }
      return false;
   }
};

#endif