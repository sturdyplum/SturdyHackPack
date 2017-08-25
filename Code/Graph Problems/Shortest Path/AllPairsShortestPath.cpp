/*
    Comlplexity O(v^3)

    Set the initial values to be large.  
*/

for (int k = 0; k < V; k++) // remember that loop order is k->i->j
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			AdjMat[i][j] = min(AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j]);

/*
The above algorithm can be modified to not have the shortest path but instead return weather or not there exist a path betwen two nodes. This is much faster as it uses bit operations. 
*/

for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++)
            AdjMat[i][j] |= (AdjMat[i][k] & AdjMat[k][j]);


