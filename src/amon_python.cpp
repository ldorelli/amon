#include <graph/graph.hpp>


BOOST_PYTHON_MODULE(amon)
{

	void (amon::Graph::*add_dedge_1) (int, int, double) = &amon::Graph::addDirectedEdge;
	void (amon::Graph::*add_dedge_2) (int, int) = &amon::Graph::addDirectedEdge;
	void (amon::Graph::*add_edge_1) (int, int, double) = &amon::Graph::addUndirectedEdge;
	void (amon::Graph::*add_edge_2) (int, int) = &amon::Graph::addUndirectedEdge;

    class_<amon::Graph>("Graph", init<>())
    	.def(init<int>())
        .def("load_undirected", &amon::Graph::loadFromEdgeFileUndirected)
        .def("nodes_qty", &amon::Graph::nodesQty)
        .def("add_node", &amon::Graph::addNode)
        .def("remove_node", &amon::Graph::removeNode)
        .def("add_dedge", add_dedge_1)
        .def("add_dedge", add_dedge_2)
        .def("add_edge", add_edge_1)
        .def("add_edge", add_edge_2)
        .def("neighboors_begin", &amon::Graph::neighboorsBegin)
    ;
}