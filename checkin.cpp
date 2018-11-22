using namespace std;

int checkin(int element_to_add, int cur_node, int &len_store, int *store) {
	// cur_node is index to store
	if (len_store == 0) {
		store[0] = element_to_add;
		len_store++;
		return 1;
	}
	if (element_to_add > store[3 * cur_node]) {
		if (store[3 * cur_node + 1] == 0) {
			store[3 * len_store] = element_to_add;
			store[3 * cur_node + 1] = len_store;
			len_store++;
			return 1;
		}
		else {
			checkin(element_to_add, store[3 * cur_node + 1], len_store, store);
		}
	}
	if (element_to_add < store[3 * cur_node]) {
		if (store[3 * cur_node + 2] == 0) {
			store[3 * len_store] = element_to_add;
			store[3 * cur_node + 2] = len_store;
			len_store++;
			return 1;
		}
		else {
			checkin(element_to_add, store[3 * cur_node + 2], len_store, store);
		}
	}
	if (element_to_add == store[3 * cur_node]) {
		return 0;
	}
	return 3;
}

int Xcheckin(int element_to_add, int cur_node, int &len_store, int *store) {
	store[3 * len_store] = element_to_add;
	len_store++;
	return 0;
}