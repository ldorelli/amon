#include <graph/graph.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <csys/network_models.hpp>
#include <social/twitter.hpp>
#include <csys/information_spread.hpp>
#include <csys/cascades.hpp>
#include <string>

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
        // .def("remove_node", &amon::Graph::removeNode)
        .def("add_dedge", add_dedge_1)
        .def("add_dedge", add_dedge_2)
        .def("add_edge", add_edge_1)
        .def("add_edge", add_edge_2)
        .def("adjacency", &amon::Graph::adjacency_py)
        .def("out_degree", &amon::Graph::outDegree)
        .def("global_cc", &amon::Graph::globalClusteringCoefficient)
        .def("average_degree", mean_deg_1)
        .def("average_degree_p", mean_deg_2)
        .def("bridges", bridges)
        .def("bfs", &amon::Graph::bfs_py)
        .def("betweenness_unw", &amon::Graph::unweightedBetweennssCentrality_py)
        .def("mix_assortativity", &amon::Graph::mixingAssortativy)
        .def("as_dot", to_dot1)
        .def("as_dot_selected", to_dot2)
        .def("connected_components", &amon::Graph::connectedComponents_py)
        .def("filter_nodes", &amon::Graph::filter_py)
        .def("local_clustering", &amon::Graph::localClustering)
        .def("transpose", &amon::Graph::transpose)
        .def("node_keys", &amon::Graph::nodeKeys_py)
    ;

    class_<amon::NetworkGenerator> ("NetworkGen", init<>())
    	.def(init<int>())
    	.def("randomnet", &amon::NetworkGenerator::undirectedRandomNetwork)
    	.def("drandomnet", &amon::NetworkGenerator::directedRandomNetwork)
    ;

    class_<amon::TweetLoader> ("TweetLoader", init<>())
    	.def("load_retweet_network", &amon::TweetLoader::genRetweetNetwork)
    	.def("get_social_network", &amon::TweetLoader::getSocialNetwork)
    ;

    class_<amon::InformationNetwork>("InformationNetwork", init<amon::Graph>())
    	.def("attention_loss", &amon::InformationNetwork::lossOfAttention_py)
    	.def("information_depth", &amon::InformationNetwork::informationDepth_py)
    ;

    class_<amon::CascadeModel> ("CascadeModel", init<amon::Graph, double, double, std::string>())
        .def("step", &amon::CascadeModel::step)
        .def("early_adopters", &amon::CascadeModel::getEarlyAdopters_py)
        .def("innovators", &amon::CascadeModel::getInnovators_py)
        .def("cascades", &amon::CascadeModel::getCascades)
        .def("max_reach", &amon::CascadeModel::reachFromInnovators)
    ;
}
