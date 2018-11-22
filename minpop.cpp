using namespace std;

void minpop(int *PQ, int *score_PQ, int &len_pq, int &iat, int *tree_node) {
	
	int tmp_best = 5555;
	int tmp_best_id = 0;
	for (int i = 0; i < len_pq; i++) {
		
		if (score_PQ[i] + (60 / tree_node[1 + PQ[i] * 9]) < tmp_best) {
			tmp_best = score_PQ[i] + (60 / tree_node[1 + PQ[i] * 9]);
			tmp_best_id = i;
		}
	}
	
	iat = PQ[tmp_best_id];
	PQ[tmp_best_id] = PQ[len_pq - 1];
	score_PQ[tmp_best_id] = score_PQ[len_pq - 1];
	PQ[len_pq - 1] = 0;
	score_PQ[len_pq - 1] = 0;
	len_pq = len_pq - 1;
	
	
	return;
}