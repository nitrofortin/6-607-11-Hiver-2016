import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

f= open("partition.txt",'rb')
labels = eval(f.read())
f.close()
# print 'labels: ', labels
# labels = {0:23,1:7,2:7,3:7,4:7,5:7,6:7,7:7,8:7,9:7,10:7,11:7,12:7,13:7,14:7,15:23,16:23,17:7,18:7,19:23,20:7,21:23,22:7,23:23,24:23,25:23,26:23,27:23,28:23,29:23,30:23,31:7,32:23,33:23}

fh=open("./graph_examples/karate2.txt", 'rb')
sup = fh.readline()
G=nx.read_weighted_edgelist(fh,delimiter='\t')

fh.close()
pos=nx.spring_layout(G)
pos2 = {}
ids = {}
for i in pos:
    pos2[int(i)] = pos[i]
    ids[int(i)] = i


real_colors = ['r','b','g','c','m','y','k','w','#03ED3A','#8EBA42','#F0E442','#cbcbcb','#bc82bd']
# real_colors = [str(i) for i in np.arange(0.,1.,100)]
# print real_colors
labels_only = [labels[n] for n in labels]
dumm = []
dumm2 = []
colors = range(len(labels_only))

for i in range(len(labels_only)):
	if labels_only[i] in dumm:
		pass
	else:
		dumm.append(labels_only[i])

# print labels_only
# print dumm
for i in range(len(dumm)):
	yolo = []
	for j in range(len(labels_only)):
		if labels_only[j] == dumm[i]:
			# print j
			yolo.append(str(j+1))
	# print yolo
	nx.draw_networkx_nodes(G,pos,nodelist=yolo,node_color=real_colors[i],cmap='inferno')

# print pos2
# nx.draw_networkx_nodes(G,pos)
nx.draw_networkx_edges(G,pos,width=1.0,alpha=0.5)
nx.draw_networkx_labels(G,pos)
plt.axis('off')
plt.show()
# nx.draw_networkx_nodes(G,pos,node_color=color)



