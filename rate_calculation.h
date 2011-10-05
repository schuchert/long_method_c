#pragma once
#ifndef RATE_CALCULATION_H_
#define RATE_CALCULATION_H_

#define FALSE 0
#define TRUE 1
#define BOOL int

enum CustomerType {
	Consumer, Business, Industrial
};
enum CustomerRate {
	lifeline, territorial
};
enum IndustrialType {
	interruptable, oneHourNotice
};

#include "linked_list.h"

typedef struct {
	enum CustomerType type;
	enum CustomerRate rate;
	enum IndustrialType industrialRate;
	int kwh;
	const char* address;
	linked_list *sites;
} Customer;

typedef struct {
	int kwh;
} Site;

#endif
