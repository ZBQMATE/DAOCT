# include "setup.h"
void setup::init() {
	
	data_len = 100000;
	qur_num = 6000;
	best_num = 100;
	renewable = 5000;
	table_width = 2000;
	
	mx = 10000;
	m = 10;
	a = 5;
	a_l = 50;
	a_mxx = 40;
	rt_k = 0.8;
	k = 0.8;
	add_acc_dist = 1;
	
	// means to search data, 1 for brute force and 2 for hct
	search_method = 2;
	
	hct_table_width = 500;
	num_hct = 2;
}

void setup::create_data(bitset<64> *data) {
	ifstream in("100ksift_lda_64_binary.txt");
	string line;
	int i = 0;
	while (getline(in, line)) {
		bitset<64> bily(line);
		for (int zq = 0; zq < 64; zq++) {
			data[i][zq] = bily[zq];
		}
		i++;
	}
}

void setup::create_query(bitset<64> *query) {
	
	ifstream cons_in("100ksift_lda_64_binary_rand.txt");
	string line;
	for (int j = 0; j < 5000; j++) {
		getline(cons_in, line);
		bitset<64> stcy(line);
		for (int ju = 0; ju < 64; ju++) {
			query[j][ju] = stcy[ju];
		}
	}
	
	ifstream qur_in("100ksift_lda_64_binary_query.txt");
	string qur_line;
	for (int j = 5000; j < qur_num; j++) {
		getline(qur_in, qur_line);
		bitset<64> stcy(qur_line);
		for (int ju = 0; ju < 64; ju++) {
			query[j][ju] = stcy[ju];
		}
	}
}