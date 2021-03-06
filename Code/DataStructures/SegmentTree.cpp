/*
 Not Tested!
 Taken from the stanfordacm hackpack with very minot modifications (adding comments and changing the names of some variables)
*/

class SegmentTreeRangeUpdate {
	public:
	vector<long long> leaf, update;
	int origSize;
	SegmentTreeRangeUpdate(vector<int> &l)	{
		origSize = l.size();
		leaf.resize(4 * l.size());
		update.resize(4 * l.size());
		build(1,0,l.size()-1,l);
	}
	void build(int curr, int b, int e, vector<int> &l)	{
		if(b == e)
			leaf[curr] = l[b];
		else	{
			int mid = (b+e)/2;
			build(2 * curr, b, mid, l);
			build(2 * curr + 1, mid+1, e, l);
			leaf[curr] = leaf[2*curr] + leaf[2*curr+1];
		}
	}
	// Here the update function is adding val to all the values in the range
	void UPDATE(int BEGIN, int END, int val)	{
		UPDATE(1,0,origSize-1,BEGIN,END,val);
	}
	void UPDATE(int curr,  int tBegin, int tEnd, int b, int e, int val)	{
		if(tBegin >= b && tEnd <= e)
			update[curr] += val;
		else	{
			leaf[curr] += (min(e,tEnd)-max(b,tBegin)+1) * val;
			int mid = (tBegin+tEnd)/2;
			if(mid >= b && tBegin <= e)
				UPDATE(2*curr, tBegin, mid, b, e, val);
			if(tEnd >= b && mid+1 <= e)
				UPDATE(2*curr+1, mid+1, tEnd, b, e, val);
		}
	}
	// Here you are querying the sum of all values in the range
    long query(int BEGIN, int END)	{
		return query(1,0,origSize-1,BEGIN,END);
	}
	long query(int curr, int tBegin, int tEnd, int b, int e)	{
		if(tBegin >= b && tEnd <= e)	{
			if(update[curr] != 0)	{
				leaf[curr] += (tEnd-tBegin+1) * update[curr];
				if(2*curr < (int)update.size()){
					update[2*curr] += update[curr];
					update[2*curr+1] += update[curr];
				}
				update[curr] = 0;
			}
			return leaf[curr];
		}
		else	{
			leaf[curr] += (tEnd-tBegin+1) * update[curr];
			if(2*curr < (int)update.size()){
				update[2*curr] += update[curr];
				update[2*curr+1] += update[curr];
			}
			update[curr] = 0;
			int mid = (tBegin+tEnd)/2;
			long ret = 0;
			if(mid >= b && tBegin <= e)
				ret += query(2*curr, tBegin, mid, b, e);
			if(tEnd >= b && mid+1 <= e)
				ret += query(2*curr+1, mid+1, tEnd, b, e);
			return ret;
		}
	}
};

