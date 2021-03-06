#include "PurchaseManager.h"

void PurchaseManager::fetch_purchases(User& obj_user) {
	// Clear any previous purchases first
	_vec_purchases.clear();
	sqlite3_stmt* stmt_fetch_purchases;

	// Fetch all purchases of user and order by datetime of purchase
	std::string str_fetch_purchases = "SELECT id, total, date FROM purchases WHERE user_id = ? ORDER BY datetime(date) DESC";

	if (sqlite3_prepare_v2(_db, str_fetch_purchases.c_str(), -1, &stmt_fetch_purchases, NULL) != SQLITE_OK) {
		std::string str_error_msg = "Failed to prepare fetch statement: ";
		str_error_msg = str_error_msg + (char*)sqlite3_errmsg(_db);
		throw std::runtime_error(str_error_msg);
	}

	sqlite3_bind_int(stmt_fetch_purchases, 1, obj_user.get_id());

	while (sqlite3_step(stmt_fetch_purchases) == SQLITE_ROW) {
		_vec_purchases.push_back(Purchase(
			sqlite3_column_int(stmt_fetch_purchases, 0),
			sqlite3_column_double(stmt_fetch_purchases, 1),
			(char*)sqlite3_column_text(stmt_fetch_purchases, 2)));
	}

	sqlite3_finalize(stmt_fetch_purchases);
}

void PurchaseManager::populate_purchase_details(Purchase& obj_purchase) {
	// Clear any previously populatd purchase details first
	obj_purchase.get_vec_purchase_items().clear();
	sqlite3_stmt* stmt_fetch_purchase_items;

	// Select all purchases that are related to the provided purchase id
	std::string str_fetch_purchase_items = "SELECT id, game_name, game_price, game_genre, game_rating, count, total FROM purchase_items WHERE purchase_id = ?";

	if (sqlite3_prepare_v2(_db, str_fetch_purchase_items.c_str(), -1, &stmt_fetch_purchase_items, NULL) != SQLITE_OK) {
		std::string str_error_msg = "Failed to prepare fetch statement: ";
		str_error_msg = str_error_msg + (char*)sqlite3_errmsg(_db);
		throw std::runtime_error(str_error_msg);
	}

	sqlite3_bind_int(stmt_fetch_purchase_items, 1, obj_purchase.get_id());

	while (sqlite3_step(stmt_fetch_purchase_items) == SQLITE_ROW) {
		obj_purchase.get_vec_purchase_items().push_back(
			PurchaseItem(
				sqlite3_column_int(stmt_fetch_purchase_items, 0),
				(char*)sqlite3_column_text(stmt_fetch_purchase_items, 1),
				sqlite3_column_double(stmt_fetch_purchase_items, 2),
				(char*)sqlite3_column_text(stmt_fetch_purchase_items, 3),
				(char*)sqlite3_column_text(stmt_fetch_purchase_items, 4),
				sqlite3_column_int(stmt_fetch_purchase_items, 5),
				sqlite3_column_double(stmt_fetch_purchase_items, 6)));
	}

	sqlite3_finalize(stmt_fetch_purchase_items);
}

double PurchaseManager::get_purchase_grand_total() {
	// Sum the totals of all purchases and return
	return std::accumulate(_vec_purchases.begin(),	_vec_purchases.end(), 0.0, [&](double total, Purchase& purchase) {
		return total + purchase.get_total();
	});
}

double PurchaseManager::get_purchase_average() {
	// Calculate average by getting total and then dividing by the number of purchases
	return get_purchase_grand_total() / (double)_vec_purchases.size();
}

int PurchaseManager::get_total_game_copies() {
	// Sum the total game copies of all purchases (only works properly when all purchases have thier purchase details/items popualted)
	return std::accumulate(_vec_purchases.begin(), _vec_purchases.end(), 0, [&](int total, Purchase& purchase) {
		return total + purchase.get_total_game_copies();
	});
}

void PurchaseManager::ensure_save_directory_exists() {
	// Create save directory if it does not already exist
	if (!std::filesystem::exists(_saves_path)) {
		std::filesystem::create_directory(_saves_path);
	}
}