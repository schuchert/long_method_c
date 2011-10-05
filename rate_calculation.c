#include "rate_calculation.h"

// -----------------------------------------------
// -----------------------------------------------
// stubbed to simplify exercise
BOOL isWinter() {
	return FALSE;
}

int calculateSlidingScale(int kwh) {
	return kwh;
}

int calculateTerritory(const char *address) {
	return 0;
}
// -----------------------------------------------
// -----------------------------------------------

double calculateRate(Customer *c) {
	double rate = 0;
	switch (c->type) {
	case Consumer:
		switch (c->rate) {
		case lifeline:
			if (c->kwh <= 100) {
				rate = c->kwh * .03;
				break;
			} else if (c->kwh <= 200) {
				rate = 3 + (c->kwh - 100) * .05;
				break;
			}
			// Customer does not qualify for lifeline,
			// fall through to territorial case.
		case territorial:
			switch (calculateTerritory(c->address)) {
			case 1:
				// spec says territory 1 and 2 use same rate.
			case 2:
				rate = c->kwh * (isWinter() ? .07 : .06);
				break;
			case 3:
				rate = c->kwh * .065;
				break;
			}
			break;
		}
		break; // consumer
	case Business:
	case Industrial: {
		list_iterator *iter = linked_list_begin(c->sites);
		while (linked_list_has_next(iter)) {
			Site *s = linked_list_next(iter);
			rate += calculateSlidingScale(s->kwh);
		}
		linked_list_end(iter);
		if (c->type == Industrial)
			switch (c->industrialRate) {
			case interruptable:
				rate *= .8;
				break;
			case oneHourNotice:
				rate *= .9;
				break;
			default:
				rate *= .95;
				break;
			} // industrial rate
		break; // business + industrial
	}
	} // customer.type
	return rate;
}
