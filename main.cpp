#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

#include <bitset>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "minpop.cpp"
#include "setup.h"
#include "setup.cpp"
#include "linear.h"
#include "linear.cpp"
#include "dyagglo.h"
#include "dyagglo.cpp"

using namespace std;

int main() {
	
	setup modd;
	modd.init();
	
	bitset<64> *data = new bitset<64>[modd.data_len]();
	modd.create_data(data);
	
	bitset<64> *query = new bitset<64>[modd.qur_num]();
	modd.create_query(query);
	
	/**
	int *linear_result = new int[modd.qur_num * modd.best_num]();
	
	linear linda;
	// linda.brute_force(data, query, modd.best_num, linear_result, modd.qur_num, modd.renewable);
	linda.brute_force(data, query, modd.data_len, modd.best_num, linear_result, modd.qur_num, 0);
	cout << "linear_report" << endl;
	ofstream linear_report("linear_report.txt");
	for (int i = 0; i < modd.qur_num * modd.best_num; i++) {
		linear_report << linear_result[i] << endl;
	}
	delete[] linear_result;
	*/
	int *this_result = new int[modd.qur_num * modd.best_num]();
	
	
	/////////////////////// using this method //////////////////////
	int *flag_lin = new int[modd.data_len]();
	
	int *hct_tree_node = new int[5 * modd.data_len](); // [bottom, cat, start, length, end]
	int *hct_bank_tree_node = new int[200000000]();
	int *hct_PQ = new int[modd.num_hct * modd.data_len]();
	int *hct_PQ_score = new int[modd.num_hct * modd.data_len]();
	int *hct_R = new int[modd.data_len]();
	
	int *tree_node = new int[9 * modd.data_len](); // [parent, layer, cat, start1, length1, end1, start2, length2, end2]
	int *bank_tree_node = new int[200000000]();
	int *hist_node = new int[3 * modd.data_len]();
	int *PQ = new int[modd.data_len]();
	int *score_PQ = new int[modd.data_len]();
	int *rec_PQ = new int[3 * modd.data_len]();
	int *R = new int[3 * modd.data_len]();// r, bigger, smaller
	int *rpt_R = new int[modd.data_len]();
	int *rpt_R_score = new int[modd.data_len]();
	int *tree_score_list = new int[modd.data_len]();
	int *tree_id_list = new int[modd.data_len]();
	int *ot_score = new int[modd.data_len]();
	int *C = new int[modd.data_len]();
	int *new_node = new int[modd.m]();
	
	dyagglo agg_tree;
	agg_tree.dynamic_agglo(data, query, this_result, modd, flag_lin, tree_node, bank_tree_node, hct_tree_node, hct_bank_tree_node, PQ, score_PQ, rec_PQ, hct_PQ, hct_PQ_score, R, hct_R, tree_score_list, tree_id_list, ot_score, C, new_node, hist_node, rpt_R, rpt_R_score);
	///////////////////////////////////////////////////////////////
	
	cout << "this_report" << endl;
	ofstream this_report("this_report_64sift_1000_10_5_50.txt");
	for (int i = 0; i < modd.qur_num * modd.best_num; i++) {
		this_report << this_result[i] << endl;
	}
	
	return 0;
}