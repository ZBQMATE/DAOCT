using namespace std;

void add_btm(int z, int &num_node_in_tree, int *tree_node, int *bank_tree_node, int &index_tree_bank, int &len_tree_table, int best_num, int *this_result, int *flag_lin, int a_l) {
	int idtc = 0;
	if (z == 0) {
		num_node_in_tree++;
		tree_node[len_tree_table * 9] = 0;
		tree_node[1 + len_tree_table * 9] = 1;
		tree_node[2 + len_tree_table * 9] = z;
		
		tree_node[3 + len_tree_table * 9] = index_tree_bank;
		
		int tmp_cnt_a = 0;
		for (int i = 0; i < best_num; i++) {
			bank_tree_node[index_tree_bank] = this_result[i];
			flag_lin[this_result[i]] = 1;
			index_tree_bank++;
			tmp_cnt_a++;
		}
		tree_node[5 + len_tree_table * 9] = index_tree_bank;
		tree_node[4 + len_tree_table * 9] = tmp_cnt_a;
		
		len_tree_table++;
		
	}
	if (z > 0) {
		idtc = 0;
		for (int i = 0; i < best_num; i++) {
			if (flag_lin[this_result[i + z * best_num]] == 0) {
				idtc++;
			}
		}
		
		if (idtc > a_l) {
			
			num_node_in_tree++;
			tree_node[len_tree_table * 9] = 0;
			tree_node[1 + len_tree_table * 9] = 1;
			tree_node[2 + len_tree_table * 9] = z;
			
			tree_node[3 + len_tree_table * 9] = index_tree_bank;
			int tmp_cnt_b = 0;
			for (int j = 0; j < best_num; j++) {
				bank_tree_node[index_tree_bank] = this_result[j + z * best_num];
				flag_lin[this_result[j + z * best_num]] = 1;
				index_tree_bank++;
				tmp_cnt_b++;
			}
			tree_node[4 + len_tree_table * 9] = tmp_cnt_b;
			tree_node[5 + len_tree_table * 9] = index_tree_bank;
			
			len_tree_table++;
			idtc = 0;
		}
	}
}

void add_rest(int root_layer, int &len_tree_table, int *tree_node, int *bank_tree_node, int &index_tree_bank, bitset<64> &differ, bitset<64> *query, int add_acc_dist, int m, int *flag_lin, bitset<64> *data, int best_num, int data_len) {
	
	for (int y = 1; y < root_layer; y++) {
		
		cout << "add rest at layer ---- ";
		cout << y << endl;
		
		int count_number = 0;
		for (int r = 0; r < len_tree_table; r++) {
			if (tree_node[r * 9] == 0 && tree_node[1 + r * 9] == y) {
				count_number++;
			}
		}
		int num_pnt = 0;
		for (int f = 0; f < len_tree_table; f++) {
			if (tree_node[1 + f * 9] == y + 1) {
				num_pnt++;
			}
		}
		
		int *rest_this_layer = new int[count_number]();
		int *centroids_to_rest = new int[5 * count_number](); // max 5 overlap
		
		int c_number = 0;
		for (int r = 0; r < len_tree_table; r++) {
			if (tree_node[r * 9] == 0 && tree_node[1 + r * 9] == y) {
				
				rest_this_layer[c_number] = r;
				
				int idx_to_pnt = 0;
				int temp_score = 0;
				int *pnt_id = new int[num_pnt]();
				int *pnt_scr = new int[num_pnt]();
				int *pnt_arr_for_sort = new int[num_pnt]();
				for (int h = 0; h < len_tree_table; h++) {
					if (tree_node[1 + h * 9] == y + 1) {
						pnt_id[idx_to_pnt] = h;
						differ = query[tree_node[2 + h * 9]] ^ query[tree_node[2 + r * 9]];
						for (int c = 0; c < 64; c++) {
							if (differ[c]) {
								temp_score++;
							}
						}
						pnt_scr[idx_to_pnt] = temp_score;
						idx_to_pnt++;
						temp_score = 0;
					}
				}
				for (int e = 0; e < num_pnt; e++) {
					pnt_arr_for_sort[e] = pnt_scr[e] * 10000000 + pnt_id[e];
				}
				sort(pnt_arr_for_sort, pnt_arr_for_sort + num_pnt);
				
				for (int t = 0; t < num_pnt; t++) {
					if ((pnt_arr_for_sort[t] / 10000000) - (pnt_arr_for_sort[0] / 10000000) > add_acc_dist) {
						break;
					}
					if (t == 5) {
						break;
					}
					centroids_to_rest[c_number * 5 + t] = pnt_arr_for_sort[t] % 10000000;
					
				}
				
				delete[] pnt_id;
				delete[] pnt_scr;
				delete[] pnt_arr_for_sort;
				
				c_number++;
			}
		}
		
		for (int q = 0; q < len_tree_table; q++) {
			if (tree_node[1 + q * 9] == y + 1) {
				
				tree_node[6 + q * 9] = index_tree_bank;
				
				int tmp_len = 0;
				for (int s = 0; s < count_number; s++) {
					for (int w = 0; w < 5; w++) {
						if (centroids_to_rest[s * 5 + w] == q) {
							bank_tree_node[index_tree_bank] = rest_this_layer[s];
							index_tree_bank++;
							tmp_len++;
						}
					}
				}
				
				tree_node[7 + q * 9] = tmp_len;
				tree_node[8 + q * 9] = index_tree_bank;
				
			}
		}
		delete[] rest_this_layer;
		delete[] centroids_to_rest;
	}
	
	// solve the bottom layer
	int count_out = 0;
	for (int s = 0; s < data_len; s++) {
		if (flag_lin[s] == 0) {
			count_out++;
		}
	}
	
	int num_rest = 0;
	for (int s = 0; s < len_tree_table; s++) {
		if (tree_node[1 + s * 9] == 1) {
			num_rest++;
		}
	}
	
	int *rest_btm = new int[count_out]();
	int *centroids_btm = new int[5 * count_out]();
	
	int counter_tmp = 0;
	for (int s = 0; s < data_len; s++) {
		if (flag_lin[s] == 0) {
			
			if (s % 10 == 0) {
				cout << "add rest data point ====>  ";
				cout << s << endl;
			}
			
			rest_btm[counter_tmp] = s;
			
			int idx_to_rest = 0;
			int tmp_score = 0;
			int *rest_id = new int[num_rest]();
			int *rest_scr = new int[num_rest]();
			int *rest_arr_for_sort = new int[num_rest]();
			for (int j = 0; j < len_tree_table; j++) {
				if (tree_node[1 + j * 9] == 1) {
					
					rest_id[idx_to_rest] = j;
					
					differ = query[tree_node[2 + j * 9]] ^ data[s];
					for (int c = 0; c < 64; c++) {
						if (differ[c]) {
							tmp_score++;
						}
					}
					
					rest_scr[idx_to_rest] = tmp_score;
					tmp_score = 0;
					idx_to_rest++;
				}
			}
			for (int j = 0; j < num_rest; j++) {
				rest_arr_for_sort[j] = rest_scr[j] * 10000000 + rest_id[j];
			}
			sort(rest_arr_for_sort, rest_arr_for_sort + num_rest);
			//int tmp_counter_b = 0;
			for (int t = 0; t < num_rest; t++) {
				
				if (t == 5) {
					break;
				}
				centroids_btm[counter_tmp * 5 + t] = rest_arr_for_sort[t] % 10000000;
				if ((rest_arr_for_sort[t] / 10000000) - (rest_arr_for_sort[0] / 10000000) > add_acc_dist) {
					centroids_btm[counter_tmp * 5 + t] = len_tree_table + 555;
				}
				
				/**
				// for clustering to zero
				if ((rest_arr_for_sort[t] / 10000000) - (rest_arr_for_sort[0] / 10000000) > add_acc_dist) {
					break;
				}
				if (t == 5) {
					break;
				}
				centroids_btm[counter_tmp * 5 + t] = rest_arr_for_sort[t] % 10000000;
				*/
			}
			
			delete[] rest_id;
			delete[] rest_scr;
			delete[] rest_arr_for_sort;
			
			counter_tmp++;
		}
	}
	
	for (int s = 0; s < len_tree_table; s++) {
		if (tree_node[1 + s * 9] == 1) {
			
			tree_node[6 + s * 9] = index_tree_bank;
			
			int tmp_len_b = 0;
			for (int d = 0; d < count_out; d++) {
				for (int x = 0; x < 5; x++) {
					if (centroids_btm[d * 5 + x] == s) {
						bank_tree_node[index_tree_bank] = rest_btm[d];
						index_tree_bank++;
						tmp_len_b++;
					}
				}
			}
			
			tree_node[7 + s * 9] = tmp_len_b;
			tree_node[8 + s * 9] = index_tree_bank;
		}
	}
	
	delete[] rest_btm;
	delete[] centroids_btm;
	
}