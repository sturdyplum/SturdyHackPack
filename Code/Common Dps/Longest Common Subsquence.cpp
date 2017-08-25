Int table[n+1][m+1];
Int seq1[n], seq2[m];
memset(table, 0, sizeof table);

forall(i, n+)
{
	if(!i) continue;
	forall(j,m+1)
	{
		if(!j) continue;
		if(seq1[i]==seq2[j])
{
	table[i][j] = table[i-1][j-1]+1;
} 
Else
{
	table[i][j] = max(table[i-1][j], table[i][j-1]);
}
	}
}

Cout << table[n][m];
