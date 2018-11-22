using namespace std;

int agg_trv(int nnn, int mmm, int zzz, bitset<64> *query_inx, int *tree_node, int *bank_tree_node, int &index_tree_bank, int &len_r, int &len_tree_table, int *PQ, int *score_PQ, int *R, int *C, int &len_pq, int best_num, int &renew_flag, bitset<64> &differ, int *tree_score_list, int *tree_id_list, int &list_pointer, int &len_rec_pq, int *rec_PQ, int *hist_node, int &len_hist_node, int *rpt_R, int &time_points) {
	if (len_tree_table == 0) {
		return 0;
	}
	if (tree_node[1 + nnn * 9] == 1) {
		
		if (renew_flag == 0) {
			
			for (int y = tree_node[3 + nnn * 9]; y < tree_node[5 + nnn * 9]; y++) {
				int tmm = len_r;
				checkin(bank_tree_node[y], 0, len_r, R);
				if (len_r > tmm) {
					rpt_R[len_r - 1] = bank_tree_node[y];
				}
			}
			
			for (int y = tree_node[6 + nnn * 9]; y < tree_node[8 + nnn * 9]; y++) {
				int tum = len_r;
				checkin(bank_tree_node[y], 0, len_r, R);
				if (len_r > tum) {
					
					/////////////
					//cout << "leaf addtional -- ";
					//cout << bank_tree_node[y] << endl;
					/////////////
					rpt_R[len_r - 1] = bank_tree_node[y];
				}
			}
			
		}
		if (renew_flag != 0) {
			
			for (int y = tree_node[3 + nnn * 9]; y < tree_node[5 + nnn * 9]; y++) {
				checkin(bank_tree_node[y], 0, len_r, R);
			}
			
		}
	}
	if (tree_node[1 + nnn * 9] > 1) {
		int len_c = 0;
		if (renew_flag == 0) {
			
			for (int g = tree_node[3 + nnn * 9]; g < tree_node[5 + nnn * 9]; g++) {
				C[len_c] = bank_tree_node[g];
				len_c++;
				//\\//
				time_points++;
			}
			
			for (int g = tree_node[6 + nnn * 9]; g < tree_node[8 + nnn * 9]; g++) {
				
				C[len_c] = bank_tree_node[g];
				len_c++;
				//\\//
				time_points++;
			}
			
		}
		if (renew_flag != 0) {
			
			for (int e = tree_node[3 + nnn * 9]; e < tree_node[5 + nnn * 9]; e++) {
				C[len_c] = bank_tree_node[e];
				len_c++;
			}
			
			int ch_lay = tree_node[1 + C[0] * 9];
			
			int tmp_count = 0;
			
			for (int u = 0; u < len_tree_table; u++) {
				if (tree_node[1 + u * 9] == ch_lay && tree_node[u * 9] == 0) {
					
					C[len_c + tmp_count] = u;
					tmp_count++;
				}
			}
			len_c = len_c + tmp_count;
			
		}
		
		int *C_order = new int[len_c]();
		int *score = new int[len_c]();
		int *arr_for_sort = new int[len_c]();
		int gap = 0;
		for (int j = 0; j < len_c; j++) {
			differ = *(query_inx + tree_node[2 + C[j] * 9]) ^ *(query_inx + zzz);
			for (int v = 0; v < 64; v++) {
				if (differ[v]) {
					gap++;
				}
			}
			score[j] = gap;
			gap = 0;
		}
		for (int i = 0; i < len_c; i++) {
			arr_for_sort[i] = 10000000 * score[i] + C[i];
		}
		sort(arr_for_sort, arr_for_sort + len_c);
		for (int q = 0; q < len_c; q++) {
			C_order[q] = arr_for_sort[q] % 10000000;
		}
		if (renew_flag != 0) {
			int C_m[mmm];
			int C_ms[mmm];
			
			int counter_i = 0;
			int counter_k = 0;
			int rec_len_hist_node = 0;
			int max_i = mmm;
			while (counter_i < mmm) {
				if (counter_k == len_c) {
					max_i = counter_i;
					break;
				}
				rec_len_hist_node = len_hist_node;
				checkin(C_order[counter_k], 0, len_hist_node, hist_node);
				if (len_hist_node > rec_len_hist_node) {
					C_m[counter_i] = C_order[counter_k];
					
					C_ms[counter_i] = arr_for_sort[counter_k] / 10000000;
					counter_i++;
				}
				counter_k++;
			}
			
			int flag_0 = 0;
			gap = 0;
			for (int d = 0; d < max_i; d++) {
				
				for (int r = 0; r < list_pointer; r++) {
					if (C_m[d] == tree_id_list[r]) {
						flag_0 = 1;
						gap++;
						break;
					}
				}
				if (flag_0 == 0) {
					tree_id_list[list_pointer + d - gap] = C_m[d];
					
					tree_score_list[list_pointer + d - gap] = C_ms[d];
				}
				flag_0 = 0;
			}
			list_pointer = list_pointer + max_i - gap;
			
			for (int h = 0; h < max_i; h++) {
				PQ[len_pq] = C_m[max_i - h - 1];
				score_PQ[len_pq] = C_ms[max_i - h - 1];
				len_pq++;
			}
		}
		if (renew_flag == 0) {
			
			for (int h = 0; h < len_c; h++) {
				PQ[len_pq] = C_order[len_c - h - 1];
				score_PQ[len_pq] = arr_for_sort[len_c - h - 1] / 10000000;
				len_pq++;
			}
			
			if (false) {
				for (int h = 0; h < len_c - 1; h++) {
					PQ[len_pq] = C_order[len_c - h - 1];
					score_PQ[len_pq] = arr_for_sort[len_c - h - 1] / 10000000;
					
					len_pq++;
				}
			}
		}
		
		int C_order_st = 0;
		minpop(PQ, score_PQ, len_pq, C_order_st, tree_node);
		
		delete[] C_order;
		delete[] score;
		delete[] arr_for_sort;
		
		agg_trv(C_order_st, mmm, zzz, query_inx, tree_node, bank_tree_node, index_tree_bank, len_r, len_tree_table, PQ, score_PQ, R, C, len_pq, best_num, renew_flag, differ, tree_score_list, tree_id_list, list_pointer, len_rec_pq, rec_PQ, hist_node, len_hist_node, rpt_R, time_points);
	}
	return 0;
}