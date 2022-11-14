#include <iostream>
#include <vector>
using namespace std;

int MOD = 1e9 + 7;

long long countWays(
	int n, int m,
	int index,int mask,
	vector<vector<long long> >& dp,
	vector<int> v[]
	){

	if(mask==((1<<n) -1)){ 
		// All the people have worn unique hats
		return 1;
	}

	if(index>m){
		// we don't have any hat to be alloted
		return 0;
	}

	if(dp[mask][index]!=-1){
		return dp[mask][index];
	}
	/*
		we have 2 option
		1st option - not allowing this ith cap to anyone
    */
    dp[mask][index] = countWays(n,m,index+1,mask,dp,v);

    /*
        2nd option - allowing this ith cap to at least one person
    */
    for(auto person:v[index]){
        // first check if this person is not allocated any other hat
        if(((1<<person)&mask)==0){
            // allocate the ith cap to this person
            int temp_mask = mask | (1<<person);
            dp[mask][index] = (dp[mask][index] + countWays(n,m,index+1,temp_mask,dp,v))%MOD;
        }
    }
    return dp[mask][index];
}


int numberWays(vector<vector<int>>& hats) {
	int n = hats.size();
	int hat_nos = 50;

	vector<int> v[hat_nos+1];
    for(int person=0;person<n;person++){
        for(auto hat:hats[person]){
            v[hat].push_back(person);
        }
    }
    vector<vector<long long> > dp(1<<n, vector<long long>(hat_nos+1,-1));
    return countWays(n,hat_nos,0,0,dp,v);
}

int main() {


	vector<vector<int>> hats{
		{1,2,3,4},
		{1,2,3,4},
		{1,2,3,4},
		{1,2,3,4}
	};
	
	cout<<"Different ways to assign caps are: "<<numberWays(hats);
} 