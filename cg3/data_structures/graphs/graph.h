/*
 * This file is part of cg3lib: https://github.com/cg3hci/cg3lib
 * This Source Code Form is subject to the terms of the GNU GPL 3.0
 *
 * @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
 */
#ifndef CG3_GRAPH_H
#define CG3_GRAPH_H

#include <vector>
#include <set>
#include <map>
#include <unordered_map>

#include <limits>

#define NUMBER_DELETE_FOR_RECOMPACT 10000

namespace cg3 {

enum GraphType { DIRECTED, UNDIRECTED };

/**
 * @brief Class representing a weighted graph (directed or undirected)
 *
 * It can be specified if it is directed or undirected: directed is
 * the default one.
 *
 * Weights are optional: if not specified, we assume that every edge has
 * cost 0. We also assume that if there is not an edge between two nodes,
 * then the cost is MAX_WEIGHT (std::numeric_limits<double>::max()/2).
 *
 * Note that operations with iterators are usually faster, since the operations
 * that use values have to perform finding the id of the node (a map is used).
 *
 * The graph is implemented in order to have the best time complexity but it
 * is not optimal in memory if we perform delete operations. Indeed the removal
 * of the node in the graph is implemented with a lazy approach. Every time
 * we delete a node, we do not remove an entry from the node vector and from the
 * node adjacency list: we just set a flag.
 * Use recompact() method to clear the deleted node references.
 *
 * Recompact operation is automatically done after a defined number of deleted nodes
 * (to avoid memory exhaustion and optimize its usage). This number is set to 10000.
 *
 */
template <class T>
class Graph
{

private:

    /* Node class */

    class Node;


public:

    /* Public const */

    static constexpr double MAX_WEIGHT = std::numeric_limits<double>::max()/2;


    /* Iterator classes */

    class GenericNodeIterator;

    class NodeIterator;
    friend class NodeIterator;
    class RangeBasedNodeIterator;

    class EdgeIterator;
    friend class EdgeIterator;
    class RangeBasedEdgeIterator;

    class AdjacentNodeIterator;
    friend class AdjacentNodeIterator;
    class RangeBasedAdjacentNodeIterator;


    /* Constructors / destructor */

    explicit Graph(const GraphType& type = GraphType::DIRECTED);



    /* Public methods with values */

    NodeIterator addNode(const T& o);
    bool deleteNode(const T& o);
    NodeIterator findNode(const T& o);

    bool addEdge(const T& o1, const T& o2, const double weight = 0);
    bool deleteEdge(const T& o1, const T& o2);
    bool isAdjacent(const T& o1, const T& o2) const;

    double getWeight(const T& o1, const T& o2);
    void setWeight(const T& o1, const T& o2, const double weight);



    /* Public methods with iterators */

    bool deleteNode(GenericNodeIterator it);

    void addEdge(GenericNodeIterator it1, GenericNodeIterator it2, const double weight = 0);
    void deleteEdge(GenericNodeIterator it1, const GenericNodeIterator it2);
    bool isAdjacent(const GenericNodeIterator it1, const GenericNodeIterator it2) const;

    double getWeight(const GenericNodeIterator it1, const GenericNodeIterator it2);
    void setWeight(GenericNodeIterator it1, GenericNodeIterator it2, const double weight);



    /* Utility methods */

    size_t numNodes();
    size_t numEdges();
    void clear();
    void recompact();



    /* Iterators */

    NodeIterator nodeIteratorBegin();
    NodeIterator nodeIteratorEnd();
    RangeBasedNodeIterator nodeIterator();

    EdgeIterator edgeIteratorBegin();
    EdgeIterator edgeIteratorEnd();
    RangeBasedEdgeIterator edgeIterator();

    AdjacentNodeIterator adjacentNodeIteratorBegin(NodeIterator nodeIt);
    AdjacentNodeIterator adjacentNodeIteratorEnd(NodeIterator nodeIt);
    RangeBasedAdjacentNodeIterator adjacentNodeIterator(NodeIterator nodeIt);

    AdjacentNodeIterator adjacentNodeIteratorBegin(const T& o);
    AdjacentNodeIterator adjacentNodeIteratorEnd(const T& o);
    RangeBasedAdjacentNodeIterator adjacentNodeIterator(const T& o);

private:

    /* Private functions for iterators */

    inline typename std::vector<Node>::iterator getFirstValidIteratorNode(
            typename std::vector<Node>::iterator it);

    inline std::unordered_map<size_t, double>::iterator getFirstValidIteratorAdjacent(
            NodeIterator nodeIt,
            std::unordered_map<size_t, double>::iterator it);

    void getFirstValidIteratorEdge(
            NodeIterator nodeIt,
            AdjacentNodeIterator adjIt,
            NodeIterator& newNodeIt,
            AdjacentNodeIterator& newAdjIt);



    /* Helpers */

    inline long long int findNodeHelper(const T& o) const;
    inline void addEdgeHelper(const size_t& id1, const size_t& id2, const double weight);
    inline void deleteEdgeHelper(const size_t& id1, const size_t& id2);
    inline bool isAdjacentHelper(const size_t& id1, const size_t& id2) const;

    inline double getWeightHelper(const size_t& id1, const size_t& id2) const;
    inline void setWeightHelper(const size_t& id1, const size_t& id2, const double weight);


    /* Private fields */

    GraphType type;

    std::vector<Node> nodes; //Vector of nodes
    std::map<T, size_t> map; //Map to find a node with a value

    std::vector<bool> isDeleted; //Delete flag
    int nDeletedNodes;

};


}

#include "includes/nodes/graph_node.h"

#include "includes/iterators/graph_genericnodeiterator.h"
#include "includes/iterators/graph_nodeiterator.h"
#include "includes/iterators/graph_edgeiterator.h"
#include "includes/iterators/graph_adjacentnodeiterator.h"

#include "graph.tpp"

#endif // CG3_GRAPH_H
