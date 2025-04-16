#pragma once
#include "Service.h"
#include <map>
class RetetaDTO {
private:
	std::map<std::string, int> raport;
public:
	void fa_raport(const std::vector<const Medicament*>& reteta) {
		for (const auto& med : reteta) {
			raport[med->getDenumire()]++;
		}
	}
	const std::map<std::string, int>&  get_map() const {
		return raport;
	}
};