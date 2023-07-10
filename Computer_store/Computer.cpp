#include <iostream>
#include <cassert>

using namespace std;

#include"Comp_store.h"

int main() {
	Computer* comp1 = new Computer("Model_1", "Black", "Intel Core i5-7500", 2019, 8, 512);
	Computer* comp2 = new Computer("Model_2", "Silver", "Intel Core i7-10700", 2022, 32, 2048);
	Computer* comp3 = new Computer("Model_3", "Blue", "Intel Core i7-4790", 2015, 8, 512);
	Computer* comp4 = new Computer("Model_4", "Silver", "Intel Core i7-13700K", 2023, 32, 2048);
	Computer* comp5 = new Computer("Model_5", "Black", "Intel Core i9-9900K", 2020, 16, 1024);
	Computer* comp6(comp3);

	Computer* comp7;
	comp7 = comp2;

	Computer** computers = new Computer * [7] {comp1, comp2, comp3, comp4, comp5, comp6, comp7};

	CompStore store("Technology Store", computers, 7);
	store.print();

	store.printComputersRAMGreaterThan(16); 
	store.printComputersYearBetween(2019, 2022);

	Computer* compById = store.getComputerById(6);
	if (compById != nullptr) {
		cout << "\tGet_Computer_By_Id" << endl;
		compById->print();
	}
	else 
		cout << "No computers found with the given ID!" << endl;

	Computer** compsByColor = store.getComputersByColor("Silver");
	if (compsByColor != nullptr) {
		cout << "\tGet_Computers_By_Color" << endl;
		for (size_t i = 0; compsByColor[i] != nullptr; i++) {
			compsByColor[i]->print();
		}
	}
	else 
		cout << "No computers found with the given COLOR!" << endl;



	return 0;
}