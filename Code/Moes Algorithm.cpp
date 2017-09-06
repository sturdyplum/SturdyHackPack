/*
  Not Tested!
  
  Used when you have offline querys.
  Complexity explination : 
    So since we are sorting the querys by thier left bucket, for each bucket of querys, the left 
    pointer will need to move at most sqrt(n) positions. The right pointer will need to move at most
    N positions over all the buket. So the complexity ends up being Q * sqrt(N) + sqrt(Q) * N
    note that this does not take into acount any additional data structure. 
*/ 

#define NUMQUERYS 100000
int blockSize;
int ans[NUMQUERYS];

struct query
{
    int l, r, i;
};

bool comp(query &a, query&b)
{
    if(a.l/blockSize == b.l/blockSize) return a.r < b.r;
    return a.l/blockSize < b.l/blockSize;
}

void put(int x)
{
    // add value x to your range
}

void rem(int x)
{
    // remove value x from your range
}

int main()
{
  //get querys then sort them
  return 0;
}
