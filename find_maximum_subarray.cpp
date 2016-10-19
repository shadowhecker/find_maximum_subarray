#include<iostream>
#include<vector>
#include<string>
using namespace std;
class result
{
	private:
		    int low_max;
			int high_max;
			int sum;
	public:
			result(){};
			result(int item1,int item2,int item3):low_max(item1),high_max(item2),sum(item3){}
			result(const result& item):low_max(item.low_max),high_max(item.high_max),sum(item.sum){}
			result& operator=(const result& item);
			int get_low_max();
			int get_high_max();
			int get_sum();
};
int result::get_low_max()
{
	return low_max;
}
int result::get_high_max()
{
	return high_max;
}
int result::get_sum()
{
	return sum;
}
result& result::operator=(const result& item)
{
	low_max=item.low_max;
	high_max=item.high_max;
	sum=item.sum;
	return *this;
}
result find_cross_subbarray(const vector<int>& item,int low,int mid,int high)
{
	int left_sum=-100;
	int sum_L=0;
	int max_left;
	for(auto i=mid;i>=low;--i)
	{
		sum_L+=item[i];
		if(sum_L>left_sum)
		{
			left_sum=sum_L;
            max_left=i;
		}
	}
	int right_sum=-100;
	int sum_R=0;
	int max_right;
	for(auto i=mid+1;i<=high;++i)
	{
		sum_R+=item[i];
		if(sum_R>right_sum)
		{
            right_sum=sum_R;
			max_right=i;
		}
	}
	result A(max_left,max_right,left_sum+right_sum);
	return A;
}
result find_maximum_subarray(const vector<int>& item,int low,int high)
{
    if(low==high)
	{
       result A(low,high,item[low]);
	   return A;
	}
	else
	{
		int mid=(low+high)/2;
        result left_max=find_maximum_subarray(item,low,mid);
		result right_max=find_maximum_subarray(item,mid+1,high);
        result cross_max=find_cross_subbarray(item,low,mid,high);
	    if(left_max.get_sum()>=right_max.get_sum()&&left_max.get_sum()>=cross_max.get_sum())
	      return left_max;
		else if(right_max.get_sum()>=left_max.get_sum()&&right_max.get_sum()>=cross_max.get_sum())
		  return right_max;
        else
		  return cross_max;
	}
}
int main()
{
	vector<int> fuck={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
	result A;
	A=find_maximum_subarray(fuck,0,fuck.size()-1);
    cout<<A.get_low_max()<<"  "<<A.get_high_max()<<"  "<<A.get_sum();
}
