#include<iostream>
#include<string>
#include<fstream>
using namespace std;
void CreateParking(string*** blocks,int block_size, int* row, int** slot)
{
	for (int i = 0;i < block_size;i++)
	{
		int r;
		cout << "Enter NO. OF ROWS for Block " << i + 1 << ": ";
		cin >> r;
		blocks[i] = new string * [r];
		row[i] = r;
		slot[i] = new int[r];//Dynamic array of row-size which will contain number of slots per each row
		for (int j = 0;j < r;j++)
		{
			int s;
			cout << "Block " << i + 1 << " Enter NO.OF SLOTS for Row " << j + 1 << ": ";
			cin >> s;
			blocks[i][j] = new string[s];
			slot[i][j] = s;
		}
	}
}
void AllParkingEmpty(string*** slot,int bs,int *row_size,int **slot_size)
{
	for (int i = 0;i < bs;i++)
	{
		for (int j = 0;j < row_size[i];j++)
		{
			for (int k = 0;k < slot_size[i][j];k++)
			{
				slot[i][j][k] = "EMPTY";
			}
		}
	}
}
void ShowParking(string*** slot, int bs, int* row_size, int** slot_size)
{
	cout << endl;
	cout << "==========PARKING==========" << endl << endl;
	for (int i = 0;i < bs;i++)
	{
		cout << "BLOCK " << i + 1 << ": " << endl;

		for (int j = 0;j < row_size[i];j++)
		{
			cout << "ROW " << j + 1 << ": ";
			for (int k = 0;k < slot_size[i][j];k++)
			{
				cout << k + 1 << "." << slot[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}
void ParkCar(string*** slot, int bs, int* row_size, int** slot_size)
{
	cout << endl;
	cout << "Enter the BLOCK where you'd like to PARK your car: ";
	int b;
	cin >> b;
	if (b > bs || b < 1)//Check for Block
	{
		cout << "ERROR, Invalid BLOCK Entered" << endl;
		return;
	}
	cout << "Enter the ROW where you'd like to PARK your car: ";
	int r;
	cin >> r;
	if (r > row_size[b-1] || r < 1)//Check for Row
	{
		cout << "ERROR, Invalid ROW Entered" << endl;
		return;
	}
	cout << "Enter the SLOT where you'd like to PARK your car: ";
	int s;
	cin >> s;
	if (s > slot_size[b-1][r-1] || s < 1)//Check for Slot
	{
		cout << "ERROR, Invalid SLOT Entered" << endl;
		return;
	}
	if (slot[b-1][r-1][s-1] == "EMPTY")
	{
		cout << endl << "Enter the Number of your Car: ";
		cin >> slot[b-1][r-1][s-1];
		cout << endl << "Parking your car..." << endl << endl;
		cout << "Your car is parked successfully" << endl << endl;
	}
	else
	{
		cout << "Error The Slot is already occupied" << endl;
	}
}
void RemoveCar(string*** slot, int bs, int* row_size, int** slot_size)
{
	cout << endl;
	cout << "Enter the BLOCK where you'd like to REMOVE your car from: ";
	int b;
	cin >> b;
	if (b > bs || b < 1)//Check for Block
	{
		cout << "ERROR, Invalid BLOCK Entered" << endl;
		return;
	}
	cout << "Enter the ROW where you'd like to REMOVE your car from: ";
	int r;
	cin >> r;
	if (r > row_size[b-1] || r < 1)//Check for Row
	{
		cout << "ERROR, Invalid ROW Entered" << endl;
		return;
	}
	cout << "Enter the SLOT where you'd like to REMOVE your car from: ";
	int s;
	cin >> s;
	if (s > slot_size[b-1][r-1] || s < 1)//Check for Slot
	{
		cout << "ERROR, Invalid SLOT Entered" << endl;
		return;
	}
	if (slot[b-1][r-1][s-1] != "EMPTY")
	{
		do {
			string option;
			cout << endl << "Is your CAR NUMBER: " << slot[b - 1][r - 1][s - 1] << " ? (Y/N): ";
			cin >> option;
			if (option == "y" || option == "Y")
			{
				cout << endl;
				cout << "Removing your Car..." << endl << endl;
				slot[b - 1][r - 1][s - 1] = "EMPTY";
				cout << "CAR REMOVED SUCCESSFULLY" << endl;
				break;
			}
			else if (option == "n" || option == "N")
			{
				cout << "CAR NOT REMOVED" << endl;
				break;
			}
			else
			{
				cout << "Error!!! Invalid Input" << endl;
			}
		} while (true);
	}
	else
	{
		cout << "Your car is not parked there (SLOT IS EMPTY)" << endl;
	}
}
void ChangeParking(string*** &blocks, int& block_size, int* &row, int** &slot)
{
	int b;
	cout << "Enter the Block you'd like to change: ";
	cin >> b;
	if (b > block_size || b < 1)//Check for Block
	{
		cout << "ERROR, Invalid BLOCK Entered" << endl;
		return;
	}
	b--;
	int ro;
	cout << "Enter the number of row you'd like to change: ";
	cin >> ro;
	if (ro > row[b] || ro < 1)//Check for Row
	{
		cout << "ERROR, Invalid ROW Entered" << endl;
		return;
	}
	ro--;
	int s;
	cout << "Enter the updated number of total slots you'd like in this row: ";
	cin >> s;
	string* temp = new string[s];
	int i = 0;
	for (;i < slot[b][ro] && i < s;i++)
		temp[i] = blocks[b][ro][i];
	for (;i < s;i++)
		temp[i] = "EMPTY";

	delete[]blocks[b][ro];
	blocks[b][ro] = temp;
	slot[b][ro] = s;

	temp = nullptr;
	delete[]temp;
}
void SearchCar(string*** slot, int bs, int* row_size, int** slot_size)
{
	string inp;
	cout << "Enter the Number of your Car: ";
	cin >> inp;
	bool flag = false;
	for (int i = 0;i < bs;i++)
	{
		for (int j = 0;j < row_size[i];j++)
		{
			for (int k = 0;k < slot_size[i][j];k++)
			{
				if (slot[i][j][k] == inp)
				{
					cout << endl;
					cout << "Car found successfully" << endl;
					cout << "Location: " << endl;
					cout << "Block: " << i + 1 << "  Row: " << j + 1 << "  Slot: " << k + 1 << endl << endl;
					flag = true;
				}
				if (flag == true)
					break;
			}
			if (flag == true)
				break;
		}
		if (flag == true)
			break;
	}
}
void SmartParkingFinder(string*** blocks, int block_size, int* row, int** slot, int b_x[], int b_y[])
{
	int bc, best_b, best_r, best_s;
	cout << "Enter the block you'd like to go to: ";
	cin >> bc;
	int x_coord, y_coord;
	double distance = 0;
	double shortest = 999999999;
	for (int i = 0;i < block_size;i++)
	{
		for (int j = 0;j < row[i];j++)
		{
			for (int k = 0;k < slot[i][j];k++)
			{
				if (blocks[i][j][k] == "EMPTY")
				{

					x_coord = b_x[i] + k * 8;
					y_coord = b_y[i] + j * 16;
					distance = sqrt((x_coord - b_x[bc - 1]) * (x_coord - b_x[bc - 1]) + (y_coord - b_y[bc - 1]) * (y_coord - b_y[bc - 1]));
					if (distance < shortest)
					{
						shortest = distance;
						best_b = i;
						best_r = j;
						best_s = k;
					}
				}
			}
		}
	}
	cout << "The best parking position is at Block " << best_b + 1 << " ROW " << best_r + 1 << " SLOT " << best_s + 1 << endl;
	cout << "Would you like to park your car there? (Y/N): ";
	string choice;
	cin >> choice;
	if (choice == "Y" || choice == "y")
	{
		cout << "Enter your Car Number: ";
		string car;
		cin >> car;
		blocks[best_b][best_r][best_s] = car;
		cout << endl << "Parking your car..." << endl << endl;
		cout << "Car parked successfully" << endl << endl;
	}
	else
	{
		cout << "Parking Cancelled" << endl;
		return;
	}
}
int main()
{
	int block_size = 0;
	int* block_x = nullptr;
	int* block_y = nullptr;
	fstream re("file.txt",ios::in);
	if (re.is_open())
	{
		int line;
		re>>line;
		block_size = line;

		block_x = new int[block_size];
		block_y = new int[block_size];
		for (int i = 0;i < block_size;i++)
		{
			re >> block_x[i] >> block_y[i];
		}
		re.close();
	}
	else
	{
		cout << "Error in opening the file" << endl;
		cout << "Manually Creating Parking (without x,y coordinates)" << endl;
		cout << "Enter number of blocks: ";
		cin >> block_size;
	}

	string*** blocks = new string** [block_size];//The Parking structure
	int* row = new int[block_size];//An array to store NUMBER OF ROWS of each block
	int** slot = new int*[block_size];//An array to store NUMBER OF SLOTS per row of each block
	CreateParking(blocks, block_size, row, slot);
	AllParkingEmpty(blocks, block_size, row, slot);
	cout << "Parking Successfully created" << endl << endl;
	
	do {
		cout << endl;
		cout << "====== DYNAMIC PARKING SYSTEM ======" << endl << endl;
		cout << "1. Park your Car" << endl;
		cout << "2. Remove your Car" << endl;
		cout << "3. Change Number of Parking Slots in a row" << endl;
		cout << "4. View Current Parking" << endl;
		cout << "5. Find your car" << endl;
		cout << "6. Exit" << endl;
		cout << endl << "Enter your choice: ";
		string choice;
		cin >> choice;
		if (choice == "1")
		{
			bool found = false;
			for (int i = 0;i < block_size;i++)
			{
				for (int j = 0;j < row[i];j++)
				{
					for (int k = 0;k < slot[i][j];k++)
					{
						if (blocks[i][j][k] == "EMPTY")
							found = true;
					}
				}
			}
			if (found)
			{
				cout << "1. Normal Car Parking" << endl;
				cout << "2. Smart Car Parking" << endl;
				cin >> choice;
				if (choice == "1")
					ParkCar(blocks, block_size, row, slot);
				else if (choice == "2")
					SmartParkingFinder(blocks, block_size, row, slot, block_x, block_y);
			}
			else
			{
				cout << "Error!!! Parking is full" << endl;
			}
		}
		else if (choice == "2")
			RemoveCar(blocks, block_size, row, slot);
		else if (choice == "3")
			ChangeParking(blocks, block_size, row, slot);
		else if (choice == "4")
			ShowParking(blocks, block_size, row, slot);
		else if (choice == "5")
			SearchCar(blocks, block_size, row, slot);
		else if (choice == "6")
		{
			cout << "Exiting..." << endl << endl;
			break;
		}
		else
			cout << "Error!!! Invalid choice entered" << endl << endl;
	} while (true);
	//DELETE
	{
		for (int i = 0; i < block_size; i++)
		{
			for (int j = 0; j < row[i]; j++)
			{
				delete[] blocks[i][j];
			}
			delete[] blocks[i];
		}
		delete[] blocks;

		for (int i = 0; i < block_size; i++)
		{
			delete[] slot[i];
		}
		delete[] slot;
		delete[] row;
	}
}