#pragma once

#include <string>
#include <list>


class Ship {
private:
	int _stock_amount;
	int _stock_id;

	int _demand_amount;
	int _demand_id;

	std::list<std::string> _log;
public:
	Ship();

	int get_stock_id()  const;
	int get_demand_id() const;

	int get_stock_amount() const;
	int get_demand_amount()const;

	std::list<std::string> get_log() const;

	void clear_log();
	
	void read();
};
