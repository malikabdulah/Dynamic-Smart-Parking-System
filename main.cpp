#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

bool isValidVehicleNumber(string vehicleNumber)
{
	//length check
	if (vehicleNumber.length() != 7)
		return false;

	if ((vehicleNumber[0] < 'A' || vehicleNumber[1] < 'A' || vehicleNumber[2] < 'A') || (vehicleNumber[0] > 'Z' || vehicleNumber[1] > 'Z' || vehicleNumber[2] > 'Z'))
		return false;
	else if (vehicleNumber[3] != '-')
		return false;
	else if ((vehicleNumber[4] < '0' || vehicleNumber[5] < '0' || vehicleNumber[6] < '0') || (vehicleNumber[4] > '9' || vehicleNumber[5] > '9' || vehicleNumber[6] > '9'))
		return false;

	return true;
}

class ParkingBlock
{
	string** slots;
	int* slotsPerRow;
	int totalRows;
	float x_coordinate, y_coordinate;
public:
	ParkingBlock()//Default Constructor
	{
		totalRows = 0;
		slotsPerRow = nullptr;
		slots = nullptr;
		x_coordinate = 0;
		y_coordinate = 0;
	}
	ParkingBlock(int numRows)//Parameterized Constructor
	{
		totalRows = numRows;
		slotsPerRow = new int[totalRows];
		slots = new string * [totalRows];
		for (int i = 0; i < totalRows; i++)
		{
			slots[i] = nullptr;
			slotsPerRow[i] = 0;
		}
		x_coordinate = 0;
		y_coordinate = 0;
	}
	/*bool operator!=(const ParkingBlock& s)//Not Equal to operator to deeply check
	{
		bool unequal = false;
		if (totalRows != s.totalRows) return true;
		if (x_coordinate != s.x_coordinate) return true;
		if (y_coordinate != s.y_coordinate) return true;

		for (int i = 0; i < totalRows; i++)
		{
			if (slotsPerRow[i] != s.slotsPerRow[i]) return true;
			else
			{
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					if (slots[i][j] != s.slots[i][j]) return true;
				}
			}
		}
		return unequal;
	}*/
	ParkingBlock(const ParkingBlock& source)//Copy Constructor
	{
		totalRows = source.totalRows;
		x_coordinate = source.x_coordinate;
		y_coordinate = source.y_coordinate;
		slots = new string * [totalRows];
		slotsPerRow = new int[totalRows];
		for (int i = 0; i < totalRows; i++)
		{
			slotsPerRow[i] = source.slotsPerRow[i];
			slots[i] = new string[slotsPerRow[i]];
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				slots[i][j] = source.slots[i][j];
			}
		}
	}
	ParkingBlock(ParkingBlock&& source)//Move Constructor
	{
		totalRows = source.totalRows;
		x_coordinate = source.x_coordinate;
		y_coordinate = source.y_coordinate;
		slotsPerRow = source.slotsPerRow;
		source.slotsPerRow = nullptr;
		slots = source.slots;
		source.slots = nullptr;
		source.totalRows = 0;
	}
	ParkingBlock& operator=(const ParkingBlock& source)//Copy Assignment
	{
		if (this != &source)
		{
			if (slots != nullptr)
			{
				for (int i = 0; i < totalRows; i++)
					delete[]slots[i];
				delete[]slots;
			}
			if (slotsPerRow != nullptr)
				delete[]slotsPerRow;
			totalRows = source.totalRows;
			x_coordinate = source.x_coordinate;
			y_coordinate = source.y_coordinate;
			slots = new string * [totalRows];
			slotsPerRow = new int[totalRows];
			for (int i = 0; i < totalRows; i++)
			{
				slotsPerRow[i] = source.slotsPerRow[i];
				slots[i] = new string[slotsPerRow[i]];
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					slots[i][j] = source.slots[i][j];
				}
			}
		}
		return *this;
	}
	ParkingBlock& operator=(ParkingBlock&& source)//Move Assignment
	{
		if (this != &source)
		{
			if (slots != nullptr)
			{
				for (int i = 0; i < totalRows; i++)
					delete[]slots[i];
				delete[]slots;
			}
			if (slotsPerRow != nullptr)
				delete[]slotsPerRow;
			totalRows = source.totalRows;
			x_coordinate = source.x_coordinate;
			y_coordinate = source.y_coordinate;
			slotsPerRow = source.slotsPerRow;
			source.slotsPerRow = nullptr;
			slots = source.slots;
			source.slots = nullptr;
			source.totalRows = 0;
		}
		return *this;
	}
	void addRows(int n)//Adding Rows (mostly for just initializing)
	{
		if (n + totalRows < 1)
		{
			cout << "Error! Number of rows cannot be zero or negative" << endl;
		}
		else
		{
			ParkingBlock p1 = *this;
			totalRows = p1.totalRows + n;
			if (slotsPerRow != nullptr)
				delete[]slotsPerRow;
			if (slots != nullptr)
			{
				for (int i = 0;i < totalRows;i++)
					delete[]slots[i];
				delete[]slots;
			}
			slotsPerRow = new int[totalRows];
			slots = new string * [totalRows];
			int i = 0;
			for (i = 0; i < p1.totalRows && i < totalRows; i++)
			{
				slotsPerRow[i] = p1.slotsPerRow[i];
				slots[i] = new string[slotsPerRow[i]];
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					slots[i][j] = p1.slots[i][j];
				}
			}
			for (; i < totalRows; i++)
			{
				slots[i] = nullptr;
				slotsPerRow[i] = 0;
			}
		}
	}
	void addSlots(int row, int n)//Adding Slots (mostly for intialising)
	{
		if (n < 1)
			cout << "Error Slots cannot be zero or negative" << endl;
		else
		{
			if (slots != nullptr)
			{
				string* temp = new string[n];
				int i = 0;
				for (i = 0; i < slotsPerRow[row]; i++)
				{
					temp[i] = slots[row][i];
				}
				for (; i < n; i++)
				{
					temp[i] = "EMPTY";
				}
				slotsPerRow[row] = n; //new no. of slots
				delete[]slots[row];
				slots[row] = temp;
				temp = nullptr;
			}
		}
	}
	void parkCar(int row, int slot, string vehicleNumber)
	{
		if (row >= totalRows || row < 0)
			cout << "Error!!! Invalid Number of Rows" << endl;
		else if (slot >= slotsPerRow[row] || slot < 0)
			cout << "Error!!! Invalid Number of Slots" << endl;
		else if (slots[row][slot] != "EMPTY")
			cout << "Error!!! The requested slot is not EMPTY at the moment" << endl;
		else
		{
			cout << "Parking your Car..." << endl;
			slots[row][slot] = vehicleNumber;
			cout << "Car Parked Successfully" << endl;
		}
	}
	void removeCar(int row, int slot)
	{
		if (row >= totalRows || row < 0)
			cout << "Error!!! Invalid Number of Rows" << endl;
		else if (slot >= slotsPerRow[row] || slot < 0)
			cout << "Error!!! Invalid Number of Slots" << endl;
		else if (slots[row][slot] == "EMPTY")
			cout << "Error!!! The requested slot is already EMPTY" << endl;
		else
		{
			cout << "Is your Vehicle Number: " << slots[row][slot] << "? (Y/N): ";
			string choice;
			cin >> choice;
			if (choice == "Y" || choice == "y")
			{
				cout << "Removing your Car" << endl;
				slots[row][slot] = "EMPTY";
				cout << "Car Removed Successfully" << endl;
			}
			else
			{
				cout << "Car not Removed" << endl;
				return;
			}
		}
	}
	void resizeSlots(int row, int newSize)
	{
		if (row >= totalRows || row < 0)
			cout << "Error!!! Invalid Row entered" << endl;
		else if (newSize < 1)
			cout << "Error!!! The size cannot be Zero or Negative" << endl;
		else
		{
			if (newSize > slotsPerRow[row])//first copies the whole old row then fills remaining with EMPTY
			{
				string* temp = new string[newSize];
				int i = 0;
				for (i = 0; i < slotsPerRow[row]; i++)
					temp[i] = slots[row][i];
				for (; i < newSize; i++)
					temp[i] = "EMPTY";
				slotsPerRow[row] = newSize;
				if (slots[row] != nullptr)
					delete[]slots[row];
				slots[row] = temp;
				temp = nullptr;
				cout << "Slots resized (size increased)" << endl;
			}
			else if (newSize < slotsPerRow[row])//first checks if the excess is EMPTY, if not then returns, else copies
			{
				for (int i = newSize; i < slotsPerRow[row]; i++)
				{
					if (slots[row][i] != "EMPTY")
					{
						cout << "Error!!! There is a parked car present in Slot " << i << " of the row " << row << endl;
						return;
					}
				}
				string* temp = new string[newSize];
				int i = 0;
				for (i = 0; i < newSize; i++)
					temp[i] = slots[row][i];
				if (slots[row] != nullptr)
					delete[]slots[row];
				slotsPerRow[row] = newSize;
				slots[row] = temp;
				temp = nullptr;
				cout << "Slots resized (size decreased)" << endl;
			}
			else//No changes required if the slot is same as prev
			{
				cout << "The previous slot size is same" << endl;
				return;
			}
		}
	}
	void emptyRow(int row)
	{
		//No implicit constructor cuz only modifying the existing strings
		//No objects are being instantiated or passed by value
		if (row >= totalRows || row < 0)
			cout << "Error!!! Invalid Row entered" << endl;
		else
		{
			if (slotsPerRow == nullptr)
				cout << "Error!!! Slots do not exist yet" << endl;
			else
			{
				for (int i = 0; i < slotsPerRow[row]; i++)
				{
					slots[row][i] = "EMPTY";
				}
				cout << "The ROW " << row << " has been EMPTIED successfully" << endl;
			}
		}
	}
	void emptyBlock()
	{
		//No Constructor cuz modifying existing
		if (slots == nullptr || slotsPerRow == nullptr)
			cout << "Error!!! The Parking has not been created for this Block" << endl;
		else
		{
			cout << "Starting to EMPTY the whole block" << endl;
			for (int i = 0; i < totalRows; i++)
			{
				cout << "Emptying row " << i << "... " << endl;
				this->emptyRow(i);
			}
			cout << "The whole block is now EMPTY" << endl;
		}
	}
	void transferVehicles(const ParkingBlock& source)
	{
		//passing by reference to avoid Copy Constructor
		//deep copy kinda
		cout << "Emptying destination block..." << endl;
		this->emptyBlock();
		cout << "Resizing rows of destination block..." << endl;
		if (slots != nullptr) {
			for (int i = 0; i < totalRows; i++)
			{
				delete[]slots[i];
			}
			delete[]slots;
		}
		if (slotsPerRow != nullptr)
			delete[]slotsPerRow;

		totalRows = source.totalRows;
		slots = new string * [source.totalRows];
		slotsPerRow = new int[totalRows];
		for (int i = 0; i < totalRows; i++)
		{
			slotsPerRow[i] = 0;
			slots[i] = nullptr;
			this->resizeSlots(i, source.slotsPerRow[i]);
		}
		cout << "Slots resized" << endl;
		cout << "Transferring Vehicles..." << endl;
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				slots[i][j] = source.slots[i][j];
			}
		}
		cout << "Vehicles Transferred Successfully" << endl;
	}
	void mergeVehicles(const ParkingBlock& source)
	{
		int a = 0, b = 0;
		if (source.countOcccuppied() > countEmptySlots())
		{
			int reqSlots = source.countOcccuppied() - countEmptySlots();
			addRows(1);
			addSlots(totalRows - 1, reqSlots);
		}
		for (int i = 0; i < totalRows; i++)
		{
			for (int j = 0; j < slotsPerRow[i]; j++)
			{
				if (slots[i][j] == "EMPTY")
				{
					while (a < source.totalRows && source.slots[a][b] == "EMPTY")
					{
						b++;
						if (b >= source.slotsPerRow[a])
						{
							a++;
							b = 0;
						}
					}
					if (a < source.totalRows)
					{
						slots[i][j] = source.slots[a][b];
						b++;
						if (b >= source.slotsPerRow[a])
						{
							a++;
							b = 0;
						}
					}
				}
			}
		}
	}	
	int* searchVehicle(string vehicleNumber)const
	{
		int i = 0, j = 0;
		for (i = 0; i < totalRows; i++)
		{
			for (j = 0; j < slotsPerRow[i]; j++)
			{
				if (slots[i][j] == vehicleNumber)
				{
					cout << "Vehicle found at ROW " << i << " and SLOT " << j << endl;
					int* arr = new int[2];
					arr[0] = i;
					arr[1] = j;
					return arr;
				}
			}
		}
		return nullptr;
	}
	void setBlockCoordinates(int x, int y)
	{
		x_coordinate = x;
		y_coordinate = y;
	}
	void smartAllocate(string vehicleNumber, int desiredBlockIndex, ParkingBlock* allBlocks, int totalBlocks)
	{
		int best_b = -1, best_r = -1, best_s = -1;
		double distance = 0;
		double shortest = 999999999;

		float target_x = allBlocks[desiredBlockIndex].x_coordinate;
		float target_y = allBlocks[desiredBlockIndex].y_coordinate;

		for (int b = 0; b < totalBlocks; b++)
		{
			for (int i = 0; i < allBlocks[b].totalRows; i++)
			{
				for (int j = 0; j < allBlocks[b].slotsPerRow[i]; j++)
				{
					if (allBlocks[b].slots[i][j] == "EMPTY")
					{
						float x_coord = allBlocks[b].x_coordinate + j * 8.0f;
						float y_coord = allBlocks[b].y_coordinate + i * 16.0f;
						distance = sqrt((x_coord - target_x) * (x_coord - target_x) + (y_coord - target_y) * (y_coord - target_y));
						if (distance < shortest)
						{
							shortest = distance;
							best_b = b;
							best_r = i;
							best_s = j;
						}
					}
				}
			}
		}

		if (best_b != -1) {
			allBlocks[best_b].slots[best_r][best_s] = vehicleNumber;
			cout << endl << "Parking your car at BLOCK " << best_b << ", ROW " << best_r << " and SLOT " << best_s << "..." << endl;
			cout << "Car parked successfully" << endl << endl;
		}
		else {
			cout << "Error: No empty slots available in the entire parking system!" << endl;
		}
	}
	void displayBlock() const
	{
		cout << "Coordinates: (" << x_coordinate << ", " << y_coordinate << ")" << endl;
		for (int j = 0; j < totalRows; j++)
		{
			cout << "ROW " << j << ":   ";
			for (int k = 0; k < slotsPerRow[j]; k++)
			{
				cout << k << ". " << slots[j][k] << "   ";
			}
			cout << endl;
		}
		cout << endl;
	}
	//A3
	int countOcccuppied()const
	{
		int count = 0;
		for (int i = 0;i < totalRows;i++)
		{
			for (int j = 0;j < slotsPerRow[i];j++)
			{
				if (slots[i][j] != "EMPTY")
					count++;
			}
		}
		return count;
	}
	int countTotalSlots()const
	{
		int count = 0;
		for (int i = 0;i < totalRows;i++)
		{
			for (int j = 0;j < slotsPerRow[i];j++)
			{
				count++;
			}
		}
		return count;
	}
	int countEmptySlots()const
	{
		return countTotalSlots() - countOcccuppied();
	}
	//operator overloading
	friend ostream& operator<<(ostream& out, const ParkingBlock& b);
	friend istream& operator>>(istream& in, ParkingBlock& b);
	string* operator[](int index)
	{
		if (index < totalRows && index>=0)
			return this->slots[index];
		else
		{
			cout << "Error!!! Index out of Bounds" << endl;
			return nullptr;
		}
	}
	bool operator==(const ParkingBlock& s)const
	{
		if (totalRows != s.totalRows) return false;
		//if (x_coordinate != s.x_coordinate) return false;
		//if (y_coordinate != s.y_coordinate) return false;

		for (int i = 0; i < totalRows; i++)
		{
			if (slotsPerRow[i] != s.slotsPerRow[i]) return false;
			else
			{
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					if (slots[i][j] != s.slots[i][j]) return false;
				}
			}
		}
		return true;
	}
	bool operator!=(const ParkingBlock& b)const
	{
		if (*this == b)
			return false;
		else
			return true;
	}
	bool operator>(const ParkingBlock& b)const
	{
		if (this->countOcccuppied() > b.countOcccuppied())
			return true;
		else
			return false;
	}
	bool operator<(const ParkingBlock& b)const
	{
		if (this->countOcccuppied()<b.countOcccuppied())
			return true;
		else
			return false;
	}
	ParkingBlock operator+(const ParkingBlock& b2)
	{
		ParkingBlock res = *this;
		res.mergeVehicles(b2);
		return res;
	}
	ParkingBlock operator-(const ParkingBlock& b2)
	{
		ParkingBlock res = *this;
		for (int i = 0;i < res.totalRows;i++)
		{
			for (int j = 0;j < res.slotsPerRow[i];j++)
			{
				if (res.slots[i][j] != "EMPTY")
				{
					int* found = b2.searchVehicle(slots[i][j]);
					if (found != nullptr)
					{
						res.slots[i][j] = "EMPTY";
						delete[]found;
					}
				}
			}
		}
		return res;
	}
	ParkingBlock& operator+=(string vehicleNumber)
	{
		if (countEmptySlots() <= 0)
		{
			cout << "The Block is full" << endl;
		}
		else
		{
			int best_r = -1, best_s = -1;
			double distance = 0;
			double shortest = 999999999;
			int target_x = x_coordinate, target_y = y_coordinate;
			for (int i = 0; i < totalRows; i++)
			{
				for (int j = 0; j < slotsPerRow[i]; j++)
				{
					if (slots[i][j] == "EMPTY")
					{
						float x_coord = x_coordinate + j * 8.0f;
						float y_coord = y_coordinate + i * 16.0f;
						distance = sqrt((x_coord - target_x) * (x_coord - target_x) + (y_coord - target_y) * (y_coord - target_y));
						if (distance < shortest)
						{
							shortest = distance;
							best_r = i;
							best_s = j;
						}
					}
				}
			}

			slots[best_r][best_s] = vehicleNumber;
			cout << "Car Parked at ROW " << best_r << " and SLOT " << best_s << " successfully" << endl;

		}
		return *this;
	}
	ParkingBlock& operator-=(const ParkingBlock& other)
	{
		for (int i = 0;i < totalRows;i++)
		{
			for (int j = 0;j < slotsPerRow[i];j++)
			{
				if (slots[i][j] != "EMPTY")
				{
					int* found = other.searchVehicle(slots[i][j]);
					if (found != nullptr)
					{
						slots[i][j] = "EMPTY";
						delete[]found;
					}
				}
			}
		}
		return *this;
	}
	ParkingBlock& operator-=(const string& vehicleNumber)
	{
		int* arr = searchVehicle(vehicleNumber);
		if (arr!= nullptr)
		{
			slots[arr[0]][arr[1]] = "EMPTY";
			cout << "Vehicle removed successfully" << endl;
			delete[]arr;
		}

		return *this;
	}
	ParkingBlock& operator++()
	{
		addRows(1);
		addSlots(totalRows-1, 4);
		cout << "One Row of 4 Slots added successfully" << endl;
		return *this;
	}
	ParkingBlock operator++(int)
	{
		ParkingBlock pre = *this;
		++*this;
		//addRows(1);
		//addSlots(totalRows-1, 4);
		//cout << "One Row of 4 Slots added successfully" << endl;
		return pre;
	}
	ParkingBlock& operator--()
	{
		if (totalRows == 0)
			return *this;
		bool found = false;
		for (int i = 0;i < slotsPerRow[totalRows-1];i++)
		{
			if (slots[totalRows - 1][i] != "EMPTY")
				found = true;
		}
		if (found)
		{
			cout << "Error! The last row is not EMPTY" << endl;
		}
		else
		{
			ParkingBlock res = *this;
			for (int i = 0;i < totalRows;i++)
				delete[]slots[i];
			delete[]slots;
			delete[]slotsPerRow;

			totalRows--;
			slotsPerRow = new int[totalRows];
			slots = new string * [totalRows];
			for (int i = 0;i < totalRows;i++)
			{
				slotsPerRow[i] = res.slotsPerRow[i];
				slots[i] = new string[slotsPerRow[i]];
				for (int j = 0;j < slotsPerRow[i];j++)
				{
					slots[i][j] = res.slots[i][j];
				}
				
			}
			cout << "The last row (which was EMPTY) has been removed" << endl;
		}
		return *this;
	}
	ParkingBlock operator--(int)
	{
		if (totalRows == 0)
			return *this;
		bool found = false;
		for (int i = 0;i < slotsPerRow[totalRows - 1];i++)
		{
			if (slots[totalRows - 1][i] != "EMPTY")
				found = true;
		}
		if (found)
		{
			cout << "Error! The last row is not EMPTY" << endl;
		}
		else
		{
			ParkingBlock res = *this;
			for (int i = 0;i < totalRows;i++)
				delete[]slots[i];
			delete[]slots;
			delete[]slotsPerRow;

			totalRows--;
			slotsPerRow = new int[totalRows];
			slots = new string * [totalRows];
			for (int i = 0;i < totalRows;i++)
			{
				slotsPerRow[i] = res.slotsPerRow[i];
				slots[i] = new string[slotsPerRow[i]];
				for (int j = 0;j < slotsPerRow[i];j++)
				{
					slots[i][j] = res.slots[i][j];
				}

			}
			cout << "The last row (which was EMPTY) has been removed" << endl;
			return res;
		}
		return *this;
	}

	~ParkingBlock()//Destructor
	{
		for (int i = 0; i < totalRows; i++)
			delete[]slots[i];
		delete[]slots;
		delete[]slotsPerRow;
	}
};
//following separate cuz file handling outside rkhi from class
ParkingBlock* loadParkingLot(string file, int& blocks)
{
	fstream re(file, ios::in);
	ParkingBlock* tot = nullptr;
	if (re.is_open())
	{
		blocks = 0;
		re >> blocks;
		tot = new ParkingBlock[blocks];//array of Parking Blocks
		for (int i = 0; i < blocks; i++)
		{
			re >> tot[i];
			/*int rows;
			re >> rows;
			tot[i].addRows(rows);
			for (int j = 0; j < rows; j++)
			{
				int slot;
				re >> slot;
				tot[i].addSlots(j, slot);
			}*/
		}
		re.close();
		cout << "Loaded layout from file successfully." << endl;
	}
	else
	{
		cout << "Error!!! Could not open the file" << endl;
	}
	return tot;
}
void loadBlockCoordinates(string file, int b, ParkingBlock* tot)
{
	fstream re(file, ios::in);
	if (re.is_open())
	{
		for (int i = 0; i < b; i++)//runs for all blocks
		{
			int x, y;
			re >> x >> y;
			tot[i].setBlockCoordinates(x, y);//setting their coordinates
			cout << tot[i];//output block with coordinates
		}
		re.close();
		cout << "Coordinates loaded successfully." << endl;
		
	}
	else
	{
		cout << "Error in opening the block coordinate file" << endl;
	}
}
//A3
ostream& operator<<(ostream& out, const ParkingBlock& b)//cout
{
	b.displayBlock();
	return out;
}
istream& operator>>(istream& in, ParkingBlock& b)
{
	//b.emptyBlock(false); // Clean out old data silently

	if (b.slots != nullptr) {
		for (int i = 0; i < b.totalRows; i++)
			delete[] b.slots[i];
		delete[] b.slots;
		delete[] b.slotsPerRow;
		b.slots = nullptr;
		b.slotsPerRow = nullptr;
		b.totalRows = 0;
	}

	int rowsToAdd;
	in >> rowsToAdd;
	b.addRows(rowsToAdd);

	for (int i = 0; i < b.totalRows; i++)
	{
		int s = 0;
		in >> s;
		b.addSlots(i, s);
	}
	//b.emptyBlock();
	return in;
}
ParkingBlock* manualParking(int& b)
{
	b = 0;
	do
	{
		cout << "Enter the number of blocks you'd like: ";
		cin >> b;
		if (b <= 0)
			cout << endl << "Error!!! Invalid number of blocks entered" << endl;
	} while (b <= 0);
	ParkingBlock* m1 = new ParkingBlock[b];
	for (int i = 0; i < b; i++)
	{
		cout << "Enter the number of ROWS followed by number of SLOTS for Block "<<i<<": ";
		cin >> m1[i];
		/*int n, s;
		do {
			cout << "Enter Number of ROWS for Block " << i << ": ";
			cin >> n;
		} while (n < 1);
		m1[i].addRows(n);
		for (int j = 0; j < n; j++)
		{
			do {
				cout << "Enter Number of SLOTS for Row " << j << ": ";
				cin >> s;
			} while (s < 1);
			m1[i].addSlots(j, s);
		}*/
	}
	cout << endl << "MANUAL PARKING CREATED SUCCESSFULLY" << endl << endl;
	return m1;
}


int main()
{
	ParkingBlock* blocks = nullptr;
	int block_no = 0;
	int count = 0;

	do
	{
		cout << "============ DYNAMIC PARKING MENU ===========" << endl << endl;
		if (count == 0)//so it only works once only at initialisation
			cout << "0.  Initialize: load from file or enter layout manually at runtime" << endl;
		cout << "1.  Park a Vehicle" << endl;
		cout << "2.  Remove a Vehicle" << endl;
		cout << "3.  Display full parking system (uses operator<<)" << endl;
		cout << "4.  Resize SLots in a row" << endl;
		cout << "5.  Search for a Vehicle" << endl;
		cout << "6.  Empty a ROW" << endl;
		cout << "7.  Empty a BLOCK" << endl;
		cout << "8.  Transfer Vehicles in Blocks" << endl;
		cout << "9.  Smart-park a vehicle (operator+=)" << endl;
		cout << "10. Remove a block's vehicles from another (operator-= with block)" << endl;
		cout << "11. Remove a specific vehicle from a block (operator-= with string)" << endl;
		cout << "12. Add a row to a block (operator++)" << endl;
		cout << "13. Remove last empty row from a block (operator--)" << endl;
		cout << "14. Compare two blocks (operator==, operator<, operator>)" << endl;
		cout << "15. Merge two blocks into a new block (operator+)" << endl;
		cout << "16. Subtract vehicles into a new block (operator-)" << endl;
		cout << "17. Load Block Coordinates from a file" << endl;
		cout << "18. Exit" << endl;
		cout << endl << "Enter your choice: ";
		string choice;
		cin >> choice;

		if (choice == "0" && count == 0)//Initializing Parking
		{
			do
			{
				cout << "1. Load from file" << endl;
				cout << "2. Enter Manually" << endl;
				cout << "Enter your choice: ";
				cin >> choice;
				if (choice == "1")
				{
					blocks = loadParkingLot("file.txt", block_no);
					break;
				}
				else if (choice == "2")
				{
					blocks = manualParking(block_no);
					break;
				}
				else
				{
					cout << "Error!!! Invalid choice" << endl;
				}
			} while (true);
			if (blocks != nullptr)
				count++;
			else
				cout << "Error Parking not Initialised" << endl;
		}
		else if (choice == "1")//Parking a Car
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			int b, r, s;
			string vn;
			do {
				cout << "Enter the Block you'd like to park in: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			do {
				cout << "Enter the row you'd like to park in: ";
				cin >> r;
			} while (r < 0);
			do {
				cout << "Enter the slot you'd like to park in: ";
				cin >> s;
			} while (s < 0);
			do {
				cout << "Enter the Vehicle Number (e.g., ABC-123): ";
				cin >> vn;
				if (!isValidVehicleNumber(vn))
					cout << "Error: Invalid Vehicle Number format!" << endl;
			} while (!isValidVehicleNumber(vn));

			blocks[b].parkCar(r, s, vn);
		}
		else if (choice == "2")//Remove a Vehicle
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			int b, r, s;
			do {
				cout << "Enter the Block you'd like to REMOVE CAR from: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			do {
				cout << "Enter the row you'd like to REMOVE CAR from: ";
				cin >> r;
			} while (r < 0);
			do {
				cout << "Enter the slot you'd like to REMOVE CAR from: ";
				cin >> s;
			} while (s < 0);
			blocks[b].removeCar(r, s);
		}
		else if (choice == "3")//Display Parking
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			cout << "========== FULL PARKING ==========" << endl;
			for (int i = 0; i < block_no; i++)
			{
				cout << "BLOCK " << i << ":" << endl;
				//blocks[i].displayBlock();
				cout << blocks[i];
			}
			cout << "Parking Displayed Successfully" << endl;
		}
		else if (choice == "4")//Resize slots in a row
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			int b, r, s;
			do {
				cout << "Enter the Block you'd like to RESIZE SLOTS in: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			do {
				cout << "Enter the row you'd like to RESIZE SLOTS in: ";
				cin >> r;
			} while (r < 0);
			do {
				cout << "Enter the new no. of SLOTS: ";
				cin >> s;
			} while (s < 0);
			blocks[b].resizeSlots(r, s);
		}
		else if (choice == "5")//Search for a Vehicle
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			string vn;

			// === VALIDATION APPLIED HERE ===
			do {
				cout << "Enter the Vehicle Number (e.g., ABC-123): ";
				cin >> vn;
				if (!isValidVehicleNumber(vn)) cout << "Error: Invalid Vehicle Number format!" << endl;
			} while (!isValidVehicleNumber(vn));

			int* V_loc = nullptr;
			for (int i = 0; i < block_no && V_loc == nullptr; i++)
			{
				V_loc = blocks[i].searchVehicle(vn);
				if (V_loc != nullptr) {
					cout << "...in BLOCK " << i << endl;
					delete[] V_loc; // Prevent memory leak!
				}
			}
			if (V_loc == nullptr) cout << "Vehicle not found anywhere in the system." << endl;
		}
		else if (choice == "6")//Empty a Row
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			int b, r;
			do {
				cout << "Enter the Block you'd like to EMPTY a Row in: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			do {
				cout << "Enter the row you'd like to EMPTY: ";
				cin >> r;
			} while (r < 0);
			blocks[b].emptyRow(r);
		}
		else if (choice == "7")//EMPTY A BLOCK
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			int b;
			do {
				cout << "Enter the Block you'd like to EMPTY: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			blocks[b].emptyBlock();
		}
		else if (choice == "8")//Vehicle Transfer
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			int b1, b2;
			do {
				cout << "Enter the destination block: ";
				cin >> b1;
			} while (b1 < 0 || b1 >= block_no);
			do {
				cout << "Enter the source block: ";
				cin >> b2;
			} while (b2 < 0 || b2 >= block_no);
			blocks[b1].transferVehicles(blocks[b2]);
		}
		else if (choice == "9")//Smart Allocation
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			int b;
			do {
				cout << "Enter the Block you'd like to go to: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			string vn;
			do {
				cout << "Enter your vehicle number (e.g., ABC-123): ";
				cin >> vn;
				if (!isValidVehicleNumber(vn)) cout << "Error: Invalid Vehicle Number format!" << endl;
			} while (!isValidVehicleNumber(vn));
			blocks[b] += vn;
			//blocks[0].smartAllocate(vn, b, blocks, block_no);
		}
		else if (choice == "10")//Operator -= remove blocks vehicle from another block
		{
			int b1, b2;
			do {
				cout << "Enter the Block 1 (from which the vehicles will be removed)";
				cin >> b1;
			} while (b1 < 0 || b1 >= block_no);
			do {
				cout << "Enter the Block 2 (the vehciles of which are to be removed from first block)";
				cin >> b2;
			} while (b2 < 0 || b2 >= block_no);
			blocks[b1] -= blocks[b2];
		}
		else if (choice == "11")//Operator -= Remove a Specific Vehicle from a Block
		{
			int b;
			string vn;
			do
			{
				cout << "Which Block would you like to remove the Vehicle from?";
				cin >> b;
			} while (b < 0 || b >= block_no);
			do {
				cout << "Enter your vehicle number (e.g., ABC-123): ";
				cin >> vn;
				if (!isValidVehicleNumber(vn)) cout << "Error: Invalid Vehicle Number format!" << endl;
			} while (!isValidVehicleNumber(vn));
			blocks[b] -= vn;
		}
		else if (choice == "12")//Operator ++ Add a row to a block
		{
			int b;
			do
			{
				cout << "Enter the Block you would like to Add a Row in: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			do
			{
				cout << "What would you like to do?" << endl;
				cout << "1. Pre-increment (++block)" << endl;
				cout << "2. Post-increment (block++)" << endl;
				cout << "Choice: ";
				cin >> choice;
			} while (choice != "1" && choice != "2");
			if (choice == "1")
			{
				cout<<++blocks[b];
			}
			else
			{
				cout<<blocks[b]++;
				cout << blocks[b];
			}
		}
		else if (choice == "13")//Remove last empty row from a block (operator--)
		{
			int b;
			do
			{
				cout << "Enter the Block you would like to REMOVE a Row from: ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			do
			{
				cout << "What would you like to do?" << endl;
				cout << "1. Pre-decrement (--block)" << endl;
				cout << "2. Post-decrement (block--)" << endl;
				cout << "Choice: ";
				cin >> choice;
			} while (choice != "1" && choice != "2");
			if (choice == "1")
			{
				cout << --blocks[b];
			}
			else
			{
				cout<<blocks[b]--;
				cout << blocks[b];
			}
		}
		else if (choice == "14")//Compare two blocks (operator==, operator<, operator>)
		{
			int b1, b2;
			do {
				cout << "Enter the Block 1: ";
				cin >> b1;
			} while (b1 < 0 || b1 >= block_no);
			do {
				cout << "Enter the Block 2: ";
				cin >> b2;
			} while (b2 < 0 || b2 >= block_no);
			do
			{
				cout << "What would you like to do?" << endl;
				cout << "1. Block 1 == Block 2" << endl;
				cout << "2. Block 1 > Block 2" << endl;
				cout << "3. Block 1 < Block 2" << endl;
				cin >> choice;
			} while (choice != "1" && choice != "2" && choice != "3");
			if (choice == "1")
			{
				if (blocks[b1] == blocks[b2])
				{
					cout << "The Blocks are EQUAL" << endl;
				}
				else
				{
					cout << "The Blocks are NOT EQUAL" << endl;
				}
			}
			else if (choice == "2")
			{
				if (blocks[b1] > blocks[b2])
				{
					cout << "True: block1 has more occupied slots than block2 (Block 1 > Block 2)" << endl;
				}
				else
				{
					cout << "False: block1 does NOT have more occupied slots than block2 (Block 1 !> Block 2)" << endl;
				}
			}
			else
			{
				if (blocks[b1] < blocks[b2])
				{
					cout << "True: block1 has fewer occupied slots than block2 (Block 1 < Block 2)" << endl;
				}
				else
				{
					cout << "False: block1 does NOT have fewer occupied slots than block2 (Block 1 !< Block 2)" << endl;
				}
			}
		}
		else if (choice == "15")//Merge two blocks into a new block (operator+)
		{
			cout << "For b=b1+b2" << endl;
			int b, b1, b2;
			do {
				cout << "Enter the Final Block (b): ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			if (blocks[b].countOcccuppied() > 0)
			{
				cout << "Error! The Final Block is not EMPTY (where the both will be merged)" << endl;
				continue;
			}
			do {
				cout << "Enter the Block 1 (b1): ";
				cin >> b1;
			} while (b1 < 0 || b1 >= block_no);
			do {
				cout << "Enter the Block 2 (b2): ";
				cin >> b2;
			} while (b2 < 0 || b2 >= block_no);
			blocks[b] = blocks[b1] + blocks[b2];
			cout << blocks[b];
			//cout << blocks[b1] + blocks[b2];
		}
		else if (choice == "16")//Subtract vehicles into a new block (operator-)
		{
			cout << "For b=b1-b2" << endl;
			int b, b1, b2;
			do {
				cout << "Enter the Destination Block (b): ";
				cin >> b;
			} while (b < 0 || b >= block_no);
			if (blocks[b].countOcccuppied() > 0)
			{
				cout << "Error! The Destination Block is not EMPTY" << endl;
				continue;
			}
			do {
				cout << "Enter the Block 1 (b1): ";
				cin >> b1;
			} while (b1 < 0 || b1 >= block_no);
			do {
				cout << "Enter the Block 2 (b2): ";
				cin >> b2;
			} while (b2 < 0 || b2 >= block_no);
			blocks[b] = blocks[b1] - blocks[b2];
			cout << blocks[b];
			//cout << blocks[b1] - blocks[b2];
		}
		else if (choice == "17")//Loading Block Coordinates
		{
			if (!blocks)//check so that it won't run without parking system
			{
				cout << "Initialize parking first!" << endl;
				continue;
			}
			loadBlockCoordinates("coordinates.txt", block_no, blocks);
		}
		else if (choice == "18")//Exiting
		{
			cout << "Exiting..." << endl;
			if (blocks != nullptr)
				delete[] blocks;
			break;
		}
		else
		{
			if (count != 0 && choice == "0")
				cout << "System already initialized!" << endl;
			else
				cout << "Invalid Choice Entered" << endl;
		}
	} while (true);

	return 0;
}
