#include "linear.h"
using namespace std;

int* linear::lin_sch(bitset<64> *dt, bitset<64> qy, int data_len, int best_num) {
	
	int dist = 0;
	int *ret = new int[best_num]();
	int *score = new int[data_len];
	int cur_best;
	int cur_best_id;
	bitset<64> cur_dt;
	bitset<64> differ;
	for (int i = 0; i < data_len; i++) {
		cur_dt = dt[i];
		differ = cur_dt ^ qy;
		for (int r = 0; r < 64; r++) {
			if (differ[r]) {
				dist++;
			}
		}
		score[i] = dist;
		dist = 0;
	}
	for (int f = 0; f < best_num; f++) {
		cur_best = 64;
		cur_best_id = 0;
		for (int j = 0; j < data_len; j++) {
			if (score[j] < cur_best) {
				cur_best = score[j];
				cur_best_id = j;
			}
		}
		score[cur_best_id] = 64;
		ret[f] = cur_best_id;
	}
	delete[] score;
	return ret;
}

void linear::brute_force_map(bitset<64> *data, bitset<64> *query, int data_len, int best_num, int *linear_result_map, int qur_num, int renewable) {
	int *lin_ths;
	for (int s = 0; s < qur_num; s++) {
		if (s >= renewable) {
			cout << s << endl;
			lin_ths = lin_sch(data, query[s], data_len, best_num);
			linear_result_map[s] = *lin_ths;
		}
	
	}
}

void linear::brute_force(bitset<64> *data, bitset<64> *query, int data_len, int best_num, int *linear_result, int qur_num, int renewable) {
	int *lin_ths;
	for (int l = 0; l < qur_num; l++) {
		if (l >= renewable) {
			cout << l << endl;
			lin_ths = lin_sch(data, query[l], data_len, best_num);
			for (int w = 0; w < best_num; w++) {
				linear_result[w + l * best_num] = *(lin_ths + w);
			}
		}
	}
}