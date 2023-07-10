#pragma once

class Computer {
private:
	char* _model;
	char* _color;
	char* _CPU; // Intel Core i7-8550U
	static size_t _staticId;
	size_t _id;
	size_t _year;
	short _RAM;
	size_t _space; // (Hard disc or SSD)

public:
	Computer();
	Computer(const char* model, const char* color, const char* CPU, size_t year, short RAM, size_t space);

	// Get Methods
	inline const char* GetModel() const;
	inline const char* GetColor() const;
	inline const char* GetCPU() const;
	inline size_t GetYear() const;
	inline short GetRAM() const;
	inline size_t GetSpace() const;
	inline size_t GetId() const;
	inline static size_t GetStaticId();

	// Set Methods
	void SetModel(const char* model);
	void SetColor(const char* color);
	void SetCPU(const char* CPU);
	void SetYear(size_t year);
	void SetRAM(short RAM);
	void SetSpace(size_t space);

	Computer(const Computer& other);
	Computer& operator=(const Computer& other);

	void print();
	~Computer();
};

size_t Computer::_staticId = 0;

Computer::Computer() {
	_id = ++_staticId;
	_model = nullptr;
	_color = nullptr;
	_CPU = nullptr;
	_year = 0;
	_RAM = 0;
	_space = 0;
}

void Computer::SetModel(const char* model) {
	if (this->_model != nullptr) {
		delete[]this->_model;
	}
	size_t len = strlen(model);
	this->_model = new char[len + 1];
	strcpy_s(this->_model, len + 1, model);
}

void Computer::SetColor(const char* color) {
	if (this->_color != nullptr) {
		delete[]this->_color;
	}
	size_t len = strlen(color);
	this->_color = new char[len + 1];
	strcpy_s(this->_color, len + 1, color);
}

void Computer::SetCPU(const char* CPU) {
	if (this->_CPU != nullptr) {
		delete[]this->_CPU;
	}
	size_t len = strlen(CPU);
	this->_CPU = new char[len + 1];
	strcpy_s(this->_CPU, len + 1, CPU);
}

void Computer::SetYear(size_t year) {
	if (year > 2010) {
		this->_year = year;
		return;
	}
	assert(!"Invalid year!!");
}

void Computer::SetRAM(short RAM) {
	if (RAM >= 4) {
		this->_RAM = RAM;
		return;
	}
	assert(!"Invalid RAM!!");
}

void Computer::SetSpace(size_t space) {
	if (space >= 128) {
		this->_space = space;
		return;
	}
	assert(!"Invalid Space!!");
}

Computer::Computer(const char* model, const char* color, const char* CPU, size_t year, short RAM, size_t space) {
	_id = ++_staticId;
	SetModel(model);
	SetColor(color);
	SetCPU(CPU);
	SetYear(year);
	SetRAM(RAM);
	SetSpace(space);
}

inline const char* Computer::GetModel() const { return this->_model; }
inline const char* Computer::GetColor() const { return this->_color; }
inline const char* Computer::GetCPU() const { return this->_CPU; }
inline size_t Computer::GetYear() const { return this->_year; }
inline short Computer::GetRAM() const { return this->_RAM; }
inline size_t Computer::GetSpace() const { return this->_space; }
inline size_t Computer::GetId() const { return this->_id; }
inline size_t Computer:: GetStaticId() { return _staticId; }

Computer::Computer(const Computer& other):_id(++_staticId) {
	SetModel(other._model);
	SetColor(other._color);
	SetCPU(other._CPU);
	SetYear(other._year);
	SetRAM(other._RAM);
	SetSpace(other._space);
}

Computer& Computer::operator=(const Computer& other) {
	this->SetModel(other._model);
	this->SetColor(other._color);
	this->SetCPU(other._CPU);
	this->SetYear(other._year);
	this->SetRAM(other._RAM);
	this->SetSpace(other._space);

	return *this;
}

void Computer::print() {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\tID: " << this->_id << endl;
	cout << "Model: " << (this->_model != nullptr ? this->_model : "NULL") << endl;
	cout << "Color: " << (this->_color != nullptr ? this->_color : "NULL") << endl;
	cout << "CPU: " << (this->_CPU != nullptr ? this->_CPU : "NULL") << endl;
	cout << "Year: " << this->GetYear() << endl;
	cout << "RAM: " << this->GetRAM() << endl;
	cout << "Space: " << this->GetSpace() << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

Computer::~Computer() {
	delete[]_model;
	delete[]_color;
	delete[]_CPU;
}

//-----------------------------------------------------------------------------------

class CompStore {
private:
	char* _name;
	Computer** _computers;
	size_t _count;

public:
	CompStore() = delete;
	CompStore(const char* name, Computer**& computers, size_t count);

	// GetMethods
	inline const char* GetName();
	inline Computer** GetComputers();
	inline size_t GetCount();

	//SetMethods
	void SetName(const char* name);
	void SetComputers(Computer**& computers, size_t count);

	CompStore(const CompStore& other);
	CompStore& operator=(const CompStore& other);

	void print();
	void printComputersRAMGreaterThan(short min);
	void printComputersYearBetween(size_t minYear, size_t maxYear);

	Computer* getComputerById(size_t id);
	Computer** getComputersByColor(const char* color);

	~CompStore();
};

void CompStore::SetName(const char* name) {
	if (this->_name != nullptr) {
		delete[]this->_name;
	}
	size_t len = strlen(name);
	this->_name = new char[len + 1];
	strcpy_s(this->_name, len + 1, name);
}

void CompStore::SetComputers(Computer**& computers, size_t count) {
	for (size_t i = 0; i < this->_count; i++) {
		delete this->_computers[i];
	}
	delete[] this->_computers;

	this->_computers = new Computer * [count];
	for (size_t i = 0; i < count; i++) {
		this->_computers[i] = new Computer(computers[i]->GetModel(), computers[i]->GetColor(),
			computers[i]->GetCPU(), computers[i]->GetYear(), computers[i]->GetRAM(), computers[i]->GetSpace());
	}
	this->_count = count;
}

CompStore::CompStore(const char* name, Computer**& computers, size_t count) {
	SetName(name);
	SetComputers(computers, count);
}

inline const char* CompStore::GetName() { return this->_name; }
inline Computer** CompStore::GetComputers() { return this->_computers; }
inline size_t CompStore::GetCount() { return this->_count; }

CompStore::CompStore(const CompStore& other) {
	if (this != &other) {
		SetName(other._name);

		this->_count = other._count;
		this->_computers = new Computer * [_count];

		for (size_t i = 0; i < this->_count; i++) {
			this->_computers[i] = new Computer(*other._computers[i]);
		}
	}
}

CompStore& CompStore::operator=(const CompStore& other) {
	if (this != &other) {
		SetName(other._name);

		for (size_t i = 0; i < this->_count; i++) {
			delete this->_computers[i];
		}
		delete[] this->_computers;

		this->_count = other._count;
		this->_computers = new Computer * [this->_count];

		for (size_t i = 0; i < this->_count; i++) {
			this->_computers[i] = new Computer(*other._computers[i]);
		}
	}
	return *this;
}

void CompStore::print() {
	cout << "\t_Computer Store Info_" << endl;
	cout << "=======================================" << endl;
	cout << "\tName: " << this->_name << endl;
	cout << "=======================================" << endl;
	cout << "\t~All Computers~" << endl;
	for (size_t i = 0; i < this->_count; i++) {
		this->_computers[i]->print();
	}
}

void CompStore::printComputersRAMGreaterThan(short min) {
	cout << "\tComputers' RAM greater than " << min << ":" << endl;
	for (size_t i = 0; i < this->_count; i++) {
		if (this->_computers[i]->GetRAM() > min)
			this->_computers[i]->print();
	}
}

void CompStore::printComputersYearBetween(size_t minYear, size_t maxYear) {
	cout << "\tComputers' year between " << minYear << " and " << maxYear << ":" << endl;
	for (size_t i = 0; i < this->_count; i++) {
		if (this->_computers[i]->GetYear() >= minYear && this->_computers[i]->GetYear() <= maxYear)
			this->_computers[i]->print();
	}
}

Computer* CompStore::getComputerById(size_t id) {
	for (size_t i = 0; i < this->_count; i++) {
		if (id == this->_computers[i]->GetId()) {
			return this->_computers[i];
		}
	}
	return nullptr;
}

Computer** CompStore::getComputersByColor(const char* color) {
	int len = 0;
	for (int i = 0; i < this->_count; i++) {
		if (strcmp(_computers[i]->GetColor(), color) == 0)
			len++;
	}

	if (len == 0)
		return nullptr;

	Computer** result = new Computer * [len + 1];
	size_t a = 0;
	for (size_t i = 0; i < this->_count; i++) {
		if (strcmp(this->_computers[i]->GetColor(), color) == 0)
			result[a++] = this->_computers[i];
	}
	result[a] = nullptr;

	return result;
}

CompStore::~CompStore() {
	delete[] _name;
	for (size_t i = 0; i < _count; i++)
		delete _computers[i];
	delete[] _computers;
	_computers = NULL;
	_count = 0;
}