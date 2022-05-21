#pragma once
#include <fstream>
#include "List.h"
#include  <limits>
#include <string>

using namespace std;



class Floyd_Warshell
{
	private:

		size_t number_of_airports; //Stores the number of cities
		List<string> list_of_airports; //Stores a list of cities
		int *matrix; //Matrix for algorithm implementation
		string* path_matrix; //Path Storage Matrix
		

	public:
		Floyd_Warshell()//Consructor
		{
			number_of_airports = 0;
		}
		Floyd_Warshell(size_t number) //Constructor
		{
			matrix = new int[number];
			path_matrix = new string[number];
			number_of_airports = number;
		}
		
		~Floyd_Warshell() //Destructor
		{
			delete[] path_matrix;
			delete[] matrix;
			number_of_airports = 0;
			list_of_airports.~List();

		}
		
		void read() //Reads data from the file and creates the necessary matrices
		{
			setlocale(LC_ALL, "Russian"); //Required for using Russian city names

			string temp = "";
			
			char buff;

			int calculater = 0;

			int number = 0;
			int firstairport;
			int secondairport;

			string firstairportname = "";
			string secondairportname = "";

			ifstream data("paths.txt");
			
			if (!data.is_open()) cout << "File Not open"<<endl; // We go through the entire file and enter all the unique names of the cities in the list
			else if (data.peek() != EOF)
			{
				data.get(buff);
				while (!data.eof())
				{	
								
					if (buff == '\n')
					{
					
						calculater = 0;
						temp = "";
					}
					if (buff == ';')
					{
				
						if (calculater == 0 || calculater == 1)
						{
							if (list_of_airports.isInList(temp) == INT_MAX)
							{
								list_of_airports.push_back(temp);
								
							}
						
						
						
						}
						if (calculater == 2 || calculater == 3)
						{
							
						}
					
						temp = "";
						calculater++;
					
					}
					if((buff != ';') && (buff != '\n'))
					{
						temp += buff;
					}
					data.get(buff);
				}
				
				data.close();
				
				number_of_airports = list_of_airports.get_size();
				number = number_of_airports;

				matrix = new int[(number)* (number)];    //We allocate memory for matrices
				path_matrix = new string[(number) * (number)];
			
			

				for (int i = 0; i < number; i++) //We fill the matrix with the maximum possible values, except for the main diagonal, where are zeros
				{
				
					for (int j = 0; j < number; j++)
					{
						if (i == j)
						{
							matrix[i * (number) + j] = 0;
							path_matrix[i * (number)+j] = "";
						
						}
						else
						{
							matrix[i * (number) + j] = INT_MAX;
							path_matrix[i * (number)+j] = "";

						}
						
					}
					

				}

				calculater = 0;
				temp = "";
			

				ifstream dataTwo("paths.txt"); data.get(buff);
				if (!dataTwo.is_open()) cout << "File Not open" << endl; //We fill in the matrix of paths and the matrix of costs
				else if (dataTwo.peek() != EOF)
				{	
					dataTwo.get(buff);
					while (!dataTwo.eof())
					{
						if (buff == '\n')
						{
							if (temp != "N/A")
							{
								matrix[secondairport * (number)+firstairport] = stoi(temp);
								path_matrix[secondairport * (number)+firstairport] = "->" + firstairportname;
								
							}

							firstairport=0;
							secondairport = 0;

							firstairportname = "";
							secondairportname = "";

							calculater = 0;
							temp = "";
						}
						if (buff == ';')
						{

							if (calculater == 0 || calculater == 1)
							{
								if (calculater == 0)
								{
									firstairport = list_of_airports.isInList(temp);
									firstairportname = temp;
									
								}
								if (calculater == 1)
								{
									
									secondairport = list_of_airports.isInList(temp);
									secondairportname = temp;
									
								}
																
								
							}
							if (calculater == 2)
							{
								
								
								if (temp != "N/A")
								{
									matrix[firstairport * (number) + secondairport] = stoi(temp);
									path_matrix[firstairport * (number)+secondairport] = "->" + secondairportname;
								}
								
							}

							calculater++;
							temp = "";


						}
						if ((buff != ';') && (buff != '\n'))
						{
							temp += buff;
						}
						
						dataTwo.get(buff);
					}
					

						

				}
				dataTwo.close();
				
			}
		}
		void mainAlgorithm() //Implementation of the Floyd-Warshell algorithm
		{
			for (int k = 0; k < number_of_airports; k++)
			{
				for (int i = 0; i < number_of_airports; i++)
				{
					for (int j = 0; j < number_of_airports; j++)
					{
						if (matrix[i * (number_of_airports)+k] != INT_MAX && matrix[k * (number_of_airports)+j] != INT_MAX)//Ñhecking to avoid exceeding the maximum value of the data type
						{
							if (matrix[i * (number_of_airports)+j] <= matrix[i * (number_of_airports)+k] + matrix[k * (number_of_airports)+j])
							{
								matrix[i * (number_of_airports)+j] = matrix[i * (number_of_airports)+j];
								path_matrix[i * (number_of_airports)+j] = path_matrix[i * (number_of_airports)+j];
							}
								
						}
						if (matrix[i * (number_of_airports)+k] != INT_MAX && matrix[k * (number_of_airports)+j] != INT_MAX)//Ñhecking to avoid exceeding the maximum value of the data type
						{
							if (matrix[i * (number_of_airports)+j] > matrix[i * (number_of_airports)+k] + matrix[k * (number_of_airports)+j])
							{ 
								matrix[i * (number_of_airports)+j] = matrix[i * (number_of_airports)+k] + matrix[k * (number_of_airports)+j];
								path_matrix[i * (number_of_airports)+j] = path_matrix[i * (number_of_airports)+k]  + path_matrix[k * (number_of_airports)+j];
							}
								
						}
						
					}

				}
			}

		}
		string getBestCost(string firstairport, string secondairport)//Output of Finding the cheapest path
		{
			if (matrix[list_of_airports.isInList(firstairport) * (list_of_airports.get_size()) + list_of_airports.isInList(secondairport)] == INT_MAX)
			{
				return "There is no such route";
			}
			else
			{
				return to_string(matrix[list_of_airports.isInList(firstairport) * (list_of_airports.get_size()) + list_of_airports.isInList(secondairport)]);
				
			}
		}
		string getBestPath(string firstairport, string secondairport)
		{
			if (matrix[list_of_airports.isInList(firstairport) * (list_of_airports.get_size()) + list_of_airports.isInList(secondairport)] == INT_MAX)
			{
				return "There is no such route";
			}
			else
			{
				return firstairport + path_matrix[list_of_airports.isInList(firstairport) * (list_of_airports.get_size()) + list_of_airports.isInList(secondairport)];

			}
		}
		void getMatrix()
		{
			for (int i = 0; i < number_of_airports; i++) //We fill the matrix with the maximum possible values, except for the main diagonal, where are zeros
			{

				for (int j = 0; j < number_of_airports; j++)
				{
					cout.width(10);
					cout<<	matrix[i * (number_of_airports)+j] << " ";
				}

				cout << endl;
			}
			
		}
		
};