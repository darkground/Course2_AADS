#include <iostream>
#include "test.h"
#include <cassert>

using namespace std;

int rng(int min = 0, int max = 0) {
	return min + (rand() % (max - min + 1));
}

void random(LinkedList* lptr, int n) {
	for (int i = 0; i < n; i++)
		lptr->append(rng(-1000, 1000));
}

unsigned randomIndex(LinkedList* lptr) {
	return rng(0, lptr->size() - 1);
}

void random(Vector* lptr, int n) {
	for (int i = 0; i < n; i++)
		lptr->append(rng(-1000, 1000));
}

unsigned randomIndex(Vector* lptr) {
	return rng(0, lptr->size() - 1);
}

void random(Stack* lptr, int n) {
	for (int i = 0; i < n; i++)
		lptr->push(to_string(rng(-1000, 1000)));
}

void testLinked(unsigned amount) {
	for (unsigned idx = 0; idx < amount; idx++) {
		LinkedList ll;
		random(&ll, rng(5, 15));
		cout << "LinkedList " << idx + 1 << ": ";
		unsigned appSize = ll.length();
		ll.append(rng(-1000, 1000));
		if (ll.length() != appSize + 1) {
			cout << "fail (size is " << ll.length() << " is but should be " << appSize + 1 << ")\n";
			cout << ll << endl;
			return;
		}
		unsigned insIdx = randomIndex(&ll);
		int insVal = rng(-1000, 1000);
		ll.insert(insIdx, insVal);
		if (ll.at(insIdx) != insVal) {
			cout << "fail (at " << insIdx << " is " << ll.at(insIdx) << " not " << insVal << ")\n";
			cout << ll << endl;
			return;
		}
		unsigned delSize = ll.length();
		ll.remove(randomIndex(&ll));
		ll.remove(ll.at(randomIndex(&ll)));
		if (ll.length() != delSize - 2) {
			cout << "fail (size is " << ll.length() << " is but should be " << delSize - 2 << ")\n";
			cout << ll << endl;
			return;
		}
		if (ll.length() != ll.size()) {
			cout << "fail (size " << ll.size() << " != length " << ll.length() << ")\n";
			cout << ll << endl;
			return;
		}

		ll.search(ll.at(randomIndex(&ll)));
		unsigned swpIdx1 = randomIndex(&ll), swpIdx2 = randomIndex(&ll);
		int swpVal1 = ll.at(swpIdx1), swpVal2 = ll.at(swpIdx2);
		ll.swap(swpIdx1, swpIdx2);

		if (ll.at(swpIdx1) != swpVal2 || ll.at(swpIdx2) != swpVal1) {
			cout << "fail (swap mismatch " 
				<<" at " << swpIdx1 << "(" << swpVal2 << ", real " << ll.at(swpIdx1)
				<< "and at " << swpIdx2 << "(" << swpVal1 << ", real " << ll.at(swpIdx2) << ")\n";
			cout << ll << endl;
			return;
		}

		ll.swap(ll.at(randomIndex(&ll)), ll.at(randomIndex(&ll)));
		cout << "ok" << endl;
	}
}

void testDynamic(unsigned amount) {
	for (unsigned idx = 0; idx < amount; idx++) {
		Vector da;
		random(&da, rng(5, 15));
		cout << "Dynamic " << idx + 1 << ": ";
		unsigned appSize = da.size();
		da.append(rng(-1000, 1000));
		if (da.size() != appSize + 1) {
			cout << "fail (size is " << da.size() << " is but should be " << appSize + 1 << ")\n";
			cout << da << endl;
			return;
		}
		unsigned insIdx = randomIndex(&da);
		int insVal = rng(-1000, 1000);
		da.insert(insIdx, insVal);
		if (da.at(insIdx) != insVal) {
			cout << "fail (at " << insIdx << " is " << da.at(insIdx) << " not " << insVal << ")\n";
			cout << da << endl;
			return;
		}
		unsigned delSize = da.size();
		da.remove(randomIndex(&da));
		da.remove(da.at(randomIndex(&da)));
		if (da.size() != delSize - 2) {
			cout << "fail (size is " << da.size() << " is but should be " << delSize - 2 << ")\n";
			cout << da << endl;
			return;
		}

		da.search(da.at(randomIndex(&da)));
		unsigned swpIdx1 = randomIndex(&da), swpIdx2 = randomIndex(&da);
		int swpVal1 = da.at(swpIdx1), swpVal2 = da.at(swpIdx2);
		da.swap(swpIdx1, swpIdx2);

		if (da.at(swpIdx1) != swpVal2 || da.at(swpIdx2) != swpVal1) {
			cout << "fail (swap mismatch "
				<< " at " << swpIdx1 << "(" << swpVal2 << ", real " << da.at(swpIdx1)
				<< "and at " << swpIdx2 << "(" << swpVal1 << ", real " << da.at(swpIdx2) << ")\n";
			cout << da << endl;
			return;
		}

		da.swap(da.at(randomIndex(&da)), da.at(randomIndex(&da)));
		cout << "ok" << endl;
	}
}

void testStack(unsigned amount) {
	for (unsigned idx = 0; idx < amount; idx++) {
		Stack st;
		random(&st, rng(5, 15));
		cout << "Stack " << idx + 1 << ": ";
		
		string pushFront = to_string(rng(5, 15));
		st.push(pushFront);
		if (st.front() != pushFront) {
			cout << "fail (front is " << st.front() << " but should be " << pushFront << ")\n";
			cout << st << endl;
			return;
		}
		st.pop();

		string pushBack = to_string(rng(5, 15));
		st.pushBack(pushBack);
		if (st.back() != pushBack) {
			cout << "fail (back is " << st.back() << " but should be " << pushBack << ")\n";
			cout << st << endl;
			return;
		}
		st.popBack();

		string front = st.front();
		string frontPop = st.pop();
		if (front != frontPop) {
			cout << "fail (front popped is " << frontPop << " but should be " << front << ")\n";
			cout << st << endl;
			return;
		}
		string back = st.back();
		string backPop = st.popBack();
		if (back != backPop) {
			cout << "fail (back popped is " << backPop << " but should be " << back << ")\n";
			cout << st << endl;
			return;
		}

		if (st.size() != st.length()) {
			cout << "fail (size " << st.size() << " != length " << st.length() << ")\n";
			cout << st << endl;
			return;
		}
		cout << "ok" << endl;
	}
}

void test() {
	testLinked(10000);
	testDynamic(10000);
	testStack(10000);
	system("pause");
}