import amon
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

loader = amon.TweetLoader()
loader.load_retweet_network('tweets', 100.0)

g = loader.get_social_network()
degs = []
for i in range(0, g.nodes_qty()):
	degs.append( g.out_degree(i) )

fnet = amon.InformationNetwork(g)
v = fnet.information_depth()

plt.hist(v[0], bins=20, log=True)
plt.show()