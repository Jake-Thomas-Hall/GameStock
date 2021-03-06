#pragma once
#include <string>
#include "Game.h"

/// <summary>
/// Class used to represent a purchase item and stores purchase item details
/// </summary>
class PurchaseItem
{
	int _i_id;
	int _i_purchase_id;
	int _i_game_id;
	Game _obj_game;
	int _i_count;
	double _d_price;
	double _d_total;
public:
	PurchaseItem(int i_game_id, int i_count, double d_price);
	PurchaseItem(int i_game_id, Game obj_game, int i_count, double d_price);
	PurchaseItem(int i_id, int i_purchase_id, int i_game_id, Game obj_game, int i_count, double d_price);
	PurchaseItem(int i_id, std::string str_game_name, double d_game_price, std::string str_game_genre, std::string str_game_rating, int i_count, double d_total);

	// Note no sets, PurchaseItems are only created via constructor
	int get_id() { return _i_id; }
	int get_purchase_id() { return _i_purchase_id; }
	int get_game_id() { return _i_game_id; }
	Game& get_game() { return _obj_game; }
	double get_price() { return _d_price; }
	double get_total() { return _d_total; }
	double get_total_before_vat() { return _d_total * 0.8; }

	int get_count() { return _i_count; }

	/// <summary>
	/// Sets count, and re-calculates total
	/// </summary>
	/// <param name="i_count"></param>
	void set_count(int i_count);
};

