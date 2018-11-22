# pragma once
using namespace std;

class setup {
	public:
		
		int data_len;
		int qur_num;
		int best_num;
		int renewable;
		int table_width;
		
		int mx;
		int m;
		int a;
		int a_l;
		int a_mxx;
		double rt_k;
		double k;
		int add_acc_dist;
		
		int search_method;
		int hct_table_width;
		int num_hct;
		
		void init();
		void create_data(std::bitset<64>*);
		void create_query(std::bitset<64>*);
};