#include <graph/graph.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(amon)
{	
	void (amon::Graph::*add_dedge_1) (int, int, double) = &amon::Graph::addDirectedEdge;
	void (amon::Graph::*add_dedge_2) (int, int) = &amon::Graph::addDirectedEdge;
	void (amon::Graph::*add_edge_1) (int, int, double) = &amon::Graph::addUndirectedEdge;
	void (amon::Graph::*add_edge_2) (int, int) = &amon::Graph::addUndirectedEdge;
	double (amon::Graph::*mean_deg_1) () = &amon::Graph::meanDegree;
	double (amon::Graph::*mean_deg_2) (double) = &amon::Graph::meanDegree;
	int (amon::Graph::*bridges) () = &amon::Graph::bridges;
	std::string (amon::Graph::*to_dot1) (bool) = &amon::Graph::toDot;
	std::string (amon::Graph::*to_dot2) (bool, boost::python::list) = &amon::Graph::toDot_py;

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
        .def("adjacency", &amon::Graph::adjacency_py)
        .def("out_degree", &amon::Graph::outDegree)
        .def("global_cc", &amon::Graph::globalClusteringCoefficient)
        .def("mean_degree", mean_deg_1)
        .def("mean_degree", mean_deg_2)
        .def("bridges", bridges)
        .def("bfs", &amon::Graph::bfs_py)
        .def("betweenness_unw", &amon::Graph::unweightedBetweennssCentrality_py)
        .def("mix_assortativity", &amon::Graph::mixingAssortativy)
        .def("as_dot", to_dot1)
        .def("as_dot_selected", to_dot2)
        .def("is_deleted", &amon::Graph::isDeleted)
    ;
}