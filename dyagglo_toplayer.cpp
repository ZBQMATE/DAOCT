using namespace std;

void deal_top(int &layer_count, bitset<64> *data, bitset<64> *query, int z, int &len_tree_table, int *tree_node, int *bank_tree_node, int &index_tree_bank, int &root_layer, int m, int &root_id, int &tp_nd, bitset<64> &tp_dif, int &tp_scr, int &len_pq, int *PQ, int *score_PQ, int &len_rec_pq, int *rec_PQ) {
	
	if (layer_count == m) {
		tree_node[0 + len_tree_table * 9] = 0;
		tree_node[1 + len_tree_table * 9] = root_layer + 1;
		
		tree_node[3 + len_tree_table * 9] = index_tree_bank;
		
		int tmp_len = 0;
		for (int kl = 0; kl < len_tree_table; kl++) {
			if (tree_node[1 + kl * 9] == root_layer) {
				tree_node[0 + kl * 9] = len_tree_table;
				tree_node[2 + len_tree_table * 9] = tree_node[2 + kl * 9];
				bank_tree_node[index_tree_bank] = kl;
				index_tree_bank++;
				tmp_len++;
			}
		}
		
		tree_node[4 + len_tree_table * 9] = tmp_len;
		tree_node[5 + len_tree_table * 9] = index_tree_bank;
		
		root_layer++;
		root_id = len_tree_table;
		len_tree_table++;
	}
	
}