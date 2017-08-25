Sqrt Decomp with lazy updates
-----------------------------------------------------------------------------------------

Int n, sqrt_n;
Vi numbers, delta, needs_update;
vector<unordered_map> buckets;


//in main
sqrt _n = sqrt(n);
if(sqrt_n * sqrt_n != n) sqrt_n++;

for(int i =0; i < sqrt_n; i++)
{
	for(int j = i*sqrt_n; j < (i+1)*sqrt_n and j < n; j++)
	{
		//update bucket i
	}
}


//query

Type query(int left, int right)
{
	Int left_bucket = left/sqrt_n, right_bucket = right/sqrt_n;
	if(left%sqrt_n != 0)
	{
		if(needs_update[left_bucket])
		{
			//clear_bucket and remake it
		}
		for(int i = left; i < (left_bucket+1)*sqrt_n and i <= right)
		{
			//Check every element taking into account the delta
		}
		left_bucket++;
	}
	if((right+1)%sqrt_n != 0 and right >= left)
	{
		if(needs_update[right_bucket])
		{
			//clear bucket and remake it
		}
		for(int i = right_bucket*sqrt_n; i >= left and i <= right; i++)
		{
			//check every element taking into account the delta
		}

		right_bucket--;
}
	
	for(int i = left_bucket; i<= right_bucket; i++)
	{
		//check if every bucket needs an update first
		//check every bucket taking into account the delta
	}
	Return ans;
}


//update

Void update_range(int left, int right, int val)
{	
	Int left_bucket = left/sqrt_n, right_bucket = right/sqrt_n;

	if(left % sqrt_n != 0)
	{
		needs_update[left_bucket] = true;
		for(int i = left; i < (left_bucket+1)*sqrt_n and i <= right; i++)
		{
			Numbers[i] += val;
		}
left_bucket++;
	}
	if((right+1)%sqrt_n != 0 and right >= left)
	{
		Needs_update[left_bucket] = true;
		for(int i = right_bucket * sqrt_n; i <= right and i>=left; i++)
		{
			Numbers[i] += val;
		}
right_bucket--;	
	}

	for(int i = left_bucket; i <= right_bucket; i++)
{
		Delta[i] += val;
	}

}


