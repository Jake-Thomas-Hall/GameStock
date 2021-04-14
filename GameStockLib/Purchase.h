#pragma once
#include <string>
#include <vector>
#include "PurchaseItem.h"

class Purchase
{
	int _i_id;
	int _i_user_id;
	std::vector<PurchaseItem> _vec_purchase_items;
	std::string _str_date;
public:
	Purchase();
	Purchase(int i_user_id, std::vector<PurchaseItem> vec_purchase_items);
	Purchase(int i_id, int i_user_id, std::vector<PurchaseItem> vec_purchase_items, std::string str_date);

	int get_id() { return _i_id; }
	void set_id(int i_id) { _i_id = i_id; }

	int get_user_id() { return _i_user_id; }
	void set_user_id(int i_user_id) { _i_user_id = i_user_id; }

	std::vector<PurchaseItem>& get_vec_purchase_items() { return _vec_purchase_items; }

	std::string get_date() { return _str_date; }
	void set_date(std::string str_date) { _str_date = str_date; }
};
