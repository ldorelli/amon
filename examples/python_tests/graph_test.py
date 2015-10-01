import amon

g = amon.Graph(5)

# Adds an extra node
g.add_node() 
g.add_edge(0, 1)
g.add_edge(0, 3)
g.add_edge(0, 5)
g.add_edge(2, 3, 1.34)
g.add_edge(2, 4)
print '======================'
x = g.adjacency(2)
print '2 adj list : ', x
for y in x:
	# y[0] is the node, y[1] the weight
	print y[0]
print '======================'
print 'Mean deg : ',  g.mean_degree() 
print '======================'
print 'Global cc: ', g.global_cc()
print '======================'
x = g.bfs(0)
print x
for e in x:
	print e, x[e]
print '======================'
btw = g.betweenness_unw()
print '\n======================'
for i in range(0, len(btw)):
	print i, ':' , btw[i]
print '======================'
print 'G as .dot:'
# print g.as_dot(True)
# -> This could be...different (maybe a dictionary)
print g.as_dot_selected(True, [True, True, False, True, False])


print "Done all tests"