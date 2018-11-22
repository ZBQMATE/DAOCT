#include "checkin.cpp"
#include "dyagglo.h"
#include "adamx.h"
#include "adamx.cpp"
#include "dyagglo_toplayer.cpp"
#include "agglo_traverse.cpp"
#include "search_method.cpp"
#include "add_btm.cpp"

using namespace std;

void dyagglo::dynamic_agglo(bitset<64> *data, bitset<64> *query, int *this_result, setup modd, int *flag_lin, int *tree_node, int *bank_tree_node, int *hct_tree_node, int *hct_bank_tree_node, int *PQ, int *score_PQ, int *rec_PQ, int *hct_PQ, int *hct_PQ_score, int *R, int *hct_R, int *tree_score_list, int *tree_id_list, int *ot_score, int *C, int *new_node, int *hist_node, int *rpt_R, int *rpt_R_score) {
	
	int hct_len_tree_table = 0;
	int hct_index_tree_bank = 0;
	int *hct_len_pq = new int[modd.num_hct]();
	int hct_len_r = 0;
	int *hct_root_id = new int[modd.num_hct]();
	
	
	int list_pointer = 0;
	int len_tree_table = 0;
	int index_tree_bank = 0;
	int root_layer = 1;
	int len_hist_node = 0;
	int root_id = 0;
	int len_pq = 0;
	int len_rec_pq = 0;
	int len_r = 0;
	int num_node_in_tree = 0;
	int renew_flag = 1;
	int this_mx = 60000;
	
	int report_width = 50000;
	int iat = 0;
	bitset<64> differ;
	
	ofstream r_report("r_report_64sift_10_5_50.txt");
	ofstream r_score_report("r_score_64sift_10_5_50.txt");
	
	ofstream w0("node_layer_1_64sift_10_5_50.txt");
	ofstream w1("node_layer_2_64sift_10_5_50.txt");
	ofstream w2("node_layer_3_64sift_10_5_50.txt");
	
	ofstream hhh("report_tree_node_64sift_10_5_50.txt");
	
	int time_points = 0;
	ofstream timer("count_operations.txt");
	
	for (int z = 0; z < modd.qur_num; z++) {
		
		///////////
		cout << "index_tree_bank -- ";
		cout << index_tree_bank << endl;
		///////////
		
		cout << z << endl;
		if (z == modd.renewable) {
			int intree = 0;
			for (int h = 0; h < modd.data_len; h++) {
				if (flag_lin[h] == 1) {
					intree++;
				}
			}
			cout << intree << endl;
			
			add_rest(root_layer, len_tree_table, tree_node, bank_tree_node, index_tree_bank, differ, query, modd.add_acc_dist, modd.m, flag_lin, data, modd.best_num, modd.data_len);
			
			for (int c = 0; c < len_tree_table; c++) {
				hhh << "layer- ";
				hhh << tree_node[1 + c * 9];
				hhh << " 3- ";
				hhh << tree_node[3 + c * 9];
				hhh << " 5- ";
				hhh << tree_node[5 + c * 9];
				hhh << " 6- ";
				hhh << tree_node[6 + c * 9];
				hhh << " 8- ";
				hhh << tree_node[8 + c * 9] << endl;
			}
			
		}
		
		if (z >= modd.renewable) {
			renew_flag = 0;
			
		}
		adamx setmx;
		this_mx = setmx.adapt_mx(z, modd.mx);
		
		for (int wu = 0; wu < len_pq; wu++) {
			PQ[wu] = 0;
			score_PQ[wu] = 0;
		}
		for (int wh = 0; wh < len_r; wh++) {
			rpt_R[wh] = 0;
		}
		for (int ww = 0; ww < 3 * len_r; ww++) {
			R[ww] = 0;
		}
		for (int wy = 0; wy < 3 * len_rec_pq; wy++) {
			rec_PQ[wy] = 0;
		}
		for (int wz = 0; wz < 3 * len_hist_node; wz++) {
			hist_node[wz] = 0;
		}
		for (int ru = 0; ru < list_pointer; ru++) {
			tree_id_list[ru] = 0;
			tree_score_list[ru] = 0;
		}
		list_pointer = 0;
		len_pq = 0;
		len_r = 0;
		len_rec_pq = 0;
		len_hist_node = 0;
		
		time_points = 0;
		
		int tp_nd = 0;
		int tp_scr = 0;
		bitset<64> tp_dif;
		
		int layer_count = 0;
		for (int t = 0; t < len_tree_table; t++) {
			if (tree_node[1 + t * 9] == root_layer) {
				layer_count++;
				agg_trv(t, modd.m, z, query, tree_node, bank_tree_node, index_tree_bank, len_r, len_tree_table, PQ, score_PQ, R, C, len_pq, modd.best_num, renew_flag, differ, tree_score_list, tree_id_list, list_pointer, len_rec_pq, rec_PQ, hist_node, len_hist_node, rpt_R, time_points);
			}
		}
		
		deal_top(layer_count, data, query, z, len_tree_table, tree_node, bank_tree_node, index_tree_bank, root_layer, modd.m, root_id, tp_nd, tp_dif, tp_scr, len_pq, PQ, score_PQ, len_rec_pq, rec_PQ);
		
		if (num_node_in_tree * modd.best_num > this_mx) {
			if (len_pq == 0) {
				cout << "MESSAGE: PQ is null." << endl;
			}
			if (len_pq != 0) {
				
				while (len_r < this_mx) {
					
					if (len_pq == 0) {
						cout << len_r;
						cout << " dusk ";
						int intree = 0;
						for (int h = 0; h < modd.data_len; h++) {
							if (flag_lin[h] == 1) {
								intree++;
							}
						}
						cout << intree << endl;
						// beacause only the first m nodes were added to PQ queue in travese step
						break;
					}
					
					minpop(PQ, score_PQ, len_pq, iat, tree_node);
					
					int tmp_rec = len_rec_pq;
					checkin(iat, 0, len_rec_pq, rec_PQ);
					if (len_rec_pq > tmp_rec) {
						
						agg_trv(iat, modd.m, z, query, tree_node, bank_tree_node, index_tree_bank, len_r, len_tree_table, PQ, score_PQ, R, C, len_pq, modd.best_num, renew_flag, differ, tree_score_list, tree_id_list, list_pointer, len_rec_pq, rec_PQ, hist_node, len_hist_node, rpt_R, time_points);
					}
					
				}
			}
			
			int cndt = 0;
			for (int layer_i = root_layer - 1; layer_i > 0; layer_i--) {
				
				cndt = 0;
				for (int a = 0; a < list_pointer; a++) {
					if (tree_node[1 + tree_id_list[a] * 9] == layer_i) {
						cndt++;
					}
				}
				if (cndt > 0) {
					if (cndt < modd.m) {
						cout << "WARNING: number of nodes in tree_id_list at layer  ";
						cout << layer_i << endl;
						cout << "  is less than the branch factor." << endl;
					}
					int *dug_sort = new int[cndt]();
					
					int counter_a = 0;
					for (int v = 0; v < list_pointer; v++) {
						if (tree_node[1 + tree_id_list[v] * 9] == layer_i) {
							dug_sort[counter_a] = tree_score_list[v] * 10000000 + tree_id_list[v];
							counter_a++;
						}
					}
					
					sort(dug_sort, dug_sort + cndt);
					for (int t = 0; t < modd.m; t++) {
						new_node[t] = dug_sort[t] % 10000000;
					}
					delete[] dug_sort;
					int num_ovlp = 0;
					for (int i = 0; i < modd.m; i++) {
						if (tree_node[new_node[i] * 9] == 0) {
							num_ovlp++;
						}
					}
					
					if (num_ovlp > modd.a) {
						
						tree_node[len_tree_table * 9] = 0;
						tree_node[1 + len_tree_table * 9] = layer_i + 1;
						tree_node[2 + len_tree_table * 9] = z;
						
						tree_node[3 + len_tree_table * 9] = index_tree_bank;
						int tmp_counter_c = 0;
						for (int s = 0; s < modd.m; s++) {
							bank_tree_node[index_tree_bank] = new_node[s];
							index_tree_bank++;
							tmp_counter_c++;
						}
						tree_node[4 + len_tree_table * 9] = tmp_counter_c;
						tree_node[5 + len_tree_table * 9] = index_tree_bank;
						
						int log_len = len_tree_table;
						len_tree_table++;
						
						for (int s = 0; s < modd.m; s++) {
							
							tree_node[new_node[s] * 9] = tree_node[new_node[s] * 9] + log_len;
							
						}
						int rd_100 = rand() % 100;
						double rd_pct = (double) rd_100 / 100;
						if (modd.k > rd_pct) {
							for (int hz = 0; hz < len_tree_table; hz++) {
								
								if (tree_node[1 + hz * 9] == layer_i + 1) {
									if (tree_node[hz * 9] == 0) {
										cout << "deleting..." << endl;
										tree_node[1 + hz * 9] = 0;
										
										for (int dl = tree_node[3 + hz * 9]; dl < tree_node[5 + hz * 9]; dl++) {
											tree_node[bank_tree_node[dl] * 9] = tree_node[bank_tree_node[dl] * 9] - hz;
											cout << "check now --- ";
											cout << tree_node[bank_tree_node[dl] * 9] << endl;
										}
										
										if (hz == root_id) {
											for (int nr = 0; nr < len_tree_table; nr++) {
												if (tree_node[1 + nr * 9] == layer_i + 1 && tree_node[nr * 9] == 0) {
													root_id = nr;
													break;
												}
											}
										}
									}
									break;
								}
							}
						}
					}
				}
			}
			
		}
		else {
			for (int f = 0; f < len_tree_table; f++) {
				if (tree_node[1 + f * 9] == 1) {
					
					for (int e = tree_node[3 + f * 9]; e < tree_node[5 + f * 9]; e++) {
						checkin(bank_tree_node[e], 0, len_r, R);
					}
					
				}
			}
		}
		if (modd.search_method == 1) {
			brute_force(data, query, modd.data_len, z, renew_flag, ot_score, flag_lin, modd.best_num, R, len_r);
		}
		if (modd.search_method == 2 && renew_flag == 1) {
			hct(data, query, modd.data_len, z, modd.num_hct, hct_tree_node, hct_bank_tree_node, flag_lin, hct_PQ, hct_PQ_score, hct_R, hct_len_pq, hct_len_r, hct_root_id, hct_len_tree_table, hct_index_tree_bank, R, len_r);
		}
		int *fn_score = new int[len_r]();
		int tmp_dist = 0;
		int tmp_flag = 0;
		int tmp_counter = 0;
		int tmp_best_id = 0;
		int tmp_cur_best = 64;
		bitset<64> tmp_differ;
		for (int i = 0; i < len_r; i++) {
			fn_score[i] = 64;
		}
		for (int j = 0; j < len_r; j++) {
			tmp_differ = query[z] ^ data[R[j * 3]];
			for (int i = 0; i < 64; i++) {
				if (tmp_differ[i]) {
					tmp_dist++;
				}
			}
			fn_score[j] = tmp_dist;
			tmp_dist = 0;
		}
		
		for (int w = 0; w < len_r; w++) {
			tmp_best_id = 0;
			tmp_cur_best = 64;
			for (int g = 0; g < len_r; g++) {
				if (fn_score[g] < tmp_cur_best) {
					tmp_cur_best = fn_score[g];
					tmp_best_id = g;
				}
			}
			
			this_result[tmp_counter + z * modd.best_num] = R[tmp_best_id * 3];
			tmp_counter++;
			if (tmp_counter == modd.best_num) {
				break;
			}
			
			fn_score[tmp_best_id] = 64;
			tmp_flag = 0;
		}
		delete[] fn_score;
		if (renew_flag != 0) {
			add_btm(z, num_node_in_tree, tree_node, bank_tree_node, index_tree_bank, len_tree_table, modd.best_num, this_result, flag_lin, modd.a_l);
		}
		
		if (renew_flag == 0) {
			for (int w = 0; w < report_width; w++) {
				r_report << rpt_R[w] << endl;
				differ = query[z] ^ data[rpt_R[w]];
				int tmm_scr = 0;
				for (int j = 0; j < 64; j++) {
					if (differ[j]) {
						tmm_scr++;
					}
				}
				r_score_report << tmm_scr << endl;
			}
		}
		
		int sn = 0;
		int yw = 0;
		int zy = 0;
		for (int qwe = 0; qwe < len_tree_table; qwe++) {
			if (tree_node[1 + 9 * qwe] == 1) {
				sn++;
			}
			if (tree_node[1 + 9 * qwe] == 2) {
				yw++;
			}
			if (tree_node[1 + 9 * qwe] == 3) {
				zy++;
			}
			
		}
		w0 << sn << endl;
		w1 << yw << endl;
		w2 << zy << endl;
		
		timer << time_points << endl;
	}
	
}