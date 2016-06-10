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
    boost::python::dict (amon::Graph::*bfs_py1) (boost::python::list) = &amon::Graph::bfs_py;
    boost::python::dict (amon::Graph::*bfs_py2) (int) = &amon::Graph::bfs_py;

	class_<amon::NetworkFlow> ("NetworkFlow", init<int>())
		.def("add_edge", &amon::NetworkFlow::addEdge)
		.def("max_flow", &amon::NetworkFlow::maxFlow)
		.def("clear", &amon::NetworkFlow::clear)
	;


    class_<amon::Graph>("Graph", init<>())
    	.def(init<int>())
        .def("random_walk", &amon::Graph::averageRandomWalkSteps_py)
        .def("load_undirected", &amon::Graph::loadFromEdgeFileUndirected)
        .def("load_directed", &amon::Graph::loadFromEdgeFileDirected)
        .def("nodes_qty", &amon::Graph::nodesQty)
        .def("edges_qty", &amon::Graph::edgesQty)
        .def("add_node", &amon::Graph::addNode)
        // .def("remove_node", &amon::Graph::removeNode)
        .def("add_dedge", add_dedge_1)
        .def("add_dedge", add_dedge_2)
        .def("add_edge", add_edge_1)
        .def("add_edge", add_edge_2)
        .def("adjacency", &amon::Graph::adjacency_py)
        .def("out_degree", &amon::Graph::outDegree)
        .def("in_degree", &amon::Graph::inDegree)
        .def("global_cc", &amon::Graph::globalClusteringCoefficient)
        .def("average_degree", mean_deg_1)
        .def("average_degree_p", mean_deg_2)
        .def("bridges", bridges)
        .def("bfs", bfs_py1)
        .def("bfs", bfs_py2)
        .def("betweenness_unw", &amon::Graph::unweightedBetweennssCentrality_py)
        .def("mix_assortativity", &amon::Graph::mixingAssortativy)
        .def("as_dot", to_dot1)
        .def("as_dot_selected", to_dot2)
        .def("connected_components", &amon::Graph::connectedComponents_py)
        .def("filter_nodes", &amon::Graph::filter_py)
        .def("local_clustering", &amon::Graph::localClustering)
        .def("transpose", &amon::Graph::transpose)
        .def("node_keys", &amon::Graph::nodeKeys_py)
        .def("eigenvector_centrality", &amon::Graph::eigenvectorCentrality_py)
        .def("node_key", &amon::Graph::getNodeKey)
        .def("node_index", &amon::Graph::getNodeIndex)
        .def("depth", &amon::Graph::getDepth)
        .def("cascade_centrality", &amon::Graph::cascadeInfluence_py)
        .def("dag_paths", &amon::Graph::DAGPaths_py)
		.def("communities", &amon::Graph::findCommunities_py)
		.def("jaccard_index", &amon::Graph::jaccardIndex)
		.def("random_graphs_jaccard", &amon::Graph::randomGraphFrom_py)
    ;

    class_<amon::NetworkGenerator> ("NetworkGen", init<>())
    	.def(init<int>())
    	.def("randomnet", &amon::NetworkGenerator::undirectedRandomNetwork)
    	.def("drandomnet", &amon::NetworkGenerator::directedRandomNetwork)
    ;

    class_<amon::TweetLoader> ("TweetLoader", init<>())
    	.def("load", &amon::TweetLoader::load)
    	.def("get_social_network", &amon::TweetLoader::getSocialNetwork)
        .def("get_hashtags", &amon::TweetLoader::getHashtags_py)
        .def("get_hashtag_activations", &amon::TweetLoader::getHashtagActivations_py)
        .def("get_activations_size", &amon::TweetLoader::getActvationsSize)
	;

    enum_<amon::TweetLoader::NetworkType>("TweetNetType")
        .value("retweet", amon::TweetLoader::Retweet)
        .value("mention", amon::TweetLoader::Mention)
    ;

    class_<amon::InformationNetwork>("InformationNetwork", init<amon::Graph>())
    	.def("attention_loss", &amon::InformationNetwork::lossOfAttention_py)
    	.def("information_depth", &amon::InformationNetwork::informationDepth_py)
    ;

	class_<amon::ETCascadeModel> ("ETCascadeModel", init<amon::Graph, double, int, double, double>())
		.def("run_from_record_paths", &amon::CascadeModel::runFromRecordWIthPaths_py)
		.def("step", &amon::CascadeModel::step)
		.def("set_starter", &amon::CascadeModel::setStarter)
		.def("cascades", &amon::CascadeModel::getCascades)
		.def("adoption_times", &amon::CascadeModel::getAdoptionTimes)
	;

	class_<amon::NETCascadeModel> ("NETCascadeModel", init<amon::Graph, double, int, double, double>())
		.def("run_from_record_paths", &amon::CascadeModel::runFromRecordWIthPaths_py)
		.def("step", &amon::CascadeModel::step)
		.def("set_starter", &amon::CascadeModel::setStarter)
		.def("cascades", &amon::CascadeModel::getCascades)
		.def("adoption_times", &amon::CascadeModel::getAdoptionTimes)
	;

    class_<amon::CascadeModel> ("CascadeModel", init<amon::Graph, double, int, double>())
        .def(init<amon::Graph>())
        .def("run_from_record_paths", &amon::CascadeModel::runFromRecordWIthPaths_py)
        .def("step", &amon::CascadeModel::step)
		.def("set_starter", &amon::CascadeModel::setStarter)
        .def("cascades", &amon::CascadeModel::getCascades)
		.def("adoption_times", &amon::CascadeModel::getAdoptionTimes)
    ;
}
