#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void create(string fname)
{
    vector<vector<string>> content;
    vector<string> row;
    string word;
    string c = "";
    string r = "";
    fstream fout;
    cout << "\nOption 1 Create CSV\n";
    cout << "create CSV headers \n";
    while (c != "x")
    {
        cout << "enter header name \n";
        getline(cin >> ws, word);
        
        row.push_back(word);
        system("cls");
        cout << "headers added \n";
        for (int i = 0; i < row.size(); i++)
        {
            cout << row[i] << ", ";
        }
        cout << "\nx to stop creating headers or c to proceed creating headers \n";
        getline(cin >> ws, c);
        cout << "\n";
        if (c == "X") c = "x";                
    }
    content.push_back(row);
    row.clear();
    c = "";
    cout << "add data row with " << content[0].size() << " values\n";   
    
    while (c != "x")
    {
        for (int i = 0; i < content[0].size(); i++)
        {   
            cout << "\n add data to column " << content[0][i] << "\n";
            getline(cin >> ws, word);
            row.push_back(word);
            system("cls");
        }
        content.push_back(row);
        row.clear();
        cout << "\nx to stop creating rows or any other simbol to create another row \n";
        getline(cin >> ws, c);
        cout << "\n";
        if (c == "X") c = "x";
    }
    fout.close(); 
    fout.open(fname, ios::out | ios::trunc);
    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            cout << content[i][j] << " ";
            if (content[i].size() - 1 == j) 
                 fout << content[i][j];
            else fout << content[i][j] << ",";            
        }
        cout << "\n";
        fout << "\n";
    }
    fout.close();
}
void read_record(string fname)
{
	vector<vector<string>> content;
	vector<string> row;
	string line, word;

	fstream file(fname, ios::in);
    cout << "\nOption 2 Display CSV\n";
	if (file.is_open())
	{
		while (getline(file, line))
		{
			row.clear();
			stringstream str(line);
            while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";

	for (int i = 0; i < content.size(); i++)
	{
		for (int j = 0; j < content[i].size(); j++)
		{
            cout << content[i][j] << ", ";
		}
		cout << "\n";
	}
}
void update_recode(string fname)
{
    string c = "";
    vector<vector<string>> content;
    vector<string> row;
    string line, word, save;
    int column1, row1;
    cout << "\nOption 3 Update CSV\n";
    cout << "which value would like to update? \n";
    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else cout << "\nCould not open the file\n";


    cout << "\nplease pick from\n";    
    cout << "column from 0 to " << content.size() - 1 << "\n";
    cout << "row from 0 to " << content[0].size() - 1 << "\n";
    cout << "\n";
    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            cout << content[i][j] << ",";
        }
        cout << "\n";
    }
    while (c != "x")
    {
        cout << "\npick row\n";
        //cin >> row1;
        while (!(cin >> row1))
        {
            cout << "Ooops! Non integer value entered!\n";
            cin.clear();
            cin.ignore(40, '\n');
        }
        cout << "\npick column\n";
        //cin >> column1;
        while (!(cin >> column1))
        {
            cout << "Ooops! Non integer value entered!\n";
            cin.clear();
            cin.ignore(40, '\n');
        }        

        if (row1 > content.size() - 1)
        {   
            cout << "\ncolumn max value is: " << content.size() -1 << " not: " << row1;
            cout << "\nit is change to maximum posible column value: " << content.size() -1 << "\n";
            row1 = content.size()-1;
        }

        if (column1 > content[0].size() - 1)
        {
            cout << "\nrow max value is: " << content[0].size() - 1 << " not: " << row1;
            cout << "\nit is change to maximum posible row value: " << content[0].size() - 1 << "\n";
            column1 = content[0].size() - 1;
        }

        cout << content[0][column1] << "-value: " << content[row1][column1] << "\n";
        cout << "change to:";
        getline(cin >> ws, word);
        content[row1][column1] = word;
        cout << "\n";
        for (int i = 0; i < content.size(); i++)
        {
            for (int j = 0; j < content[i].size(); j++)
            {
                cout << content[i][j] << ",";
            }
            cout << "\n";
        }
        cout << "\nx to exit or any other simbol to edit more values \n";
        getline(cin >> ws, c);
        cout << "\n";
        if (c == "X") c = "x";
    }
    cout << "\nWould you like exit and submit changes?";
    cout << "\nto save type s to discard changes x";
    cout << "\n";
    getline(cin >> ws, save);
    if (save == "S") save = "s";
    if (save == "X") save = "x";
    if (save == "s")
    {
        fstream fout;
        fout.close();
        fout.open(fname, ios::out | ios::trunc);;
        for (int i = 0; i < content.size(); i++)
        {
            for (int j = 0; j < content[i].size(); j++)
            {
                if (content[i].size() - 1 == j)
                    fout << content[i][j];
                else fout << content[i][j] << ",";
            }
            fout << "\n";
        }
        fout.close();
    }
}
void delete_recode(string fname)
{   
    vector<vector<string>> content, content2;
    vector<string> row, row2;
    string line, word, sure, cORr, save;
    int row1, column1;
    fstream file(fname, ios::in);
    cout << "\nOption 4 Delete selected values at CSV\n";
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
    }
    else cout << "Could not open the file\n";

    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            cout << content[i][j] << ", ";
        }
        cout << "\n";
    }
    while (cORr != "x")
    {
        cout << "\nwhat would you like to delete?";
        cout << "\nc for column\nr for row\nx to exit \n";
        getline(cin >> ws, cORr);

        if (cORr == "C") cORr = "c";
        if (cORr == "R") cORr = "r";
        if (cORr == "X") cORr = "x";

        if (cORr == "c")
        {
            cout << "column from 0 to " << content[0].size() - 1 << "\n";
            //cin >> column1;
            while (!(cin >> column1)) 
            {
                cout << "Ooops! Non integer value entered!\n";
                cin.clear();
                cin.ignore(40, '\n');
            }
            
            if (column1 > content[0].size() - 1)
            {
                cout << "\ncolumn max value is: " << content[0].size() - 1 << " not: " << column1;
                cout << "\nit is change to maximum posible column value: " << content[0].size() - 1 << "\n";
                column1 = content[0].size() - 1;
            }
            content2.clear();
            for (int i = 0; i < content.size(); i++)
            {
                row2.clear();
                for (int j = 0; j < content[i].size(); j++)
                {
                    if (j != column1)
                    {
                        row2.push_back(content[i][j]);
                    }
                }
                content2.push_back(row2);
            }
            content = content2;
        }

        if (cORr == "r")
        {
            cout << "row from 1 to " << content.size() - 1 << "\n";
            //cin >> row1;
            while (!(cin >> row1))
            {
                cout << "Ooops! Non integer value entered!\n";
                cin.clear();
                cin.ignore(40, '\n');
            }
            while (row1 == 0)
            {
                cout << "\nrow minimum value is: 1 not 0";
                cout << "\nchange row number higher than 0\n";
                //cin >> row1;
                while (!(cin >> row1))
                {
                    cout << "Ooops! Non integer value entered!\n";
                    cin.clear();
                    cin.ignore(40, '\n');
                }
            }

            if (row1 > content.size() - 1)
            {
                cout << "\nrow max value is: " << content.size() - 1 << " not: " << row1;
                cout << "\nit is change to maximum posible row value: " << content.size() - 1 << "\n";
                row1 = content.size() - 1;
            }
            content2.clear();
            for (int i = 0; i < content.size(); i++)
            {
                if (i != row1)
                {
                    row2.clear();
                    for (int j = 0; j < content[i].size(); j++)
                    {
                        row2.push_back(content[i][j]);
                    }
                    content2.push_back(row2);
                }
            }
            content = content2;
        }

        cout << "\n";
        for (int i = 0; i < content.size(); i++)
        {
            for (int j = 0; j < content[i].size(); j++)
            {
                cout << content[i][j] << ", ";
            }
            cout << "\n";
        }
    }
    cout << "\nWould you like exit and submit changes?";
    cout << "\nto save type s to discard changes x";
    cout << "\n";
    getline(cin >> ws, save);
    if (save == "S") save = "s";
    if (save == "X") save = "x";
    if (save == "s")
    {
        fstream fout;
        fout.close();
        fout.open(fname, ios::out | ios::trunc);;
        for (int i = 0; i < content.size(); i++)
        {
            for (int j = 0; j < content[i].size(); j++)
            {
                if (content[i].size() - 1 == j)
                    fout << content[i][j];
                else fout << content[i][j] << ",";
            }
            fout << "\n";
        }
        fout.close();
    }
}
int main()
{
    string fname;
       int menuO = 5;    
    //fname = "1.csv";
   
    while (menuO != 0)
    {
        switch (menuO)
        {
        case 1: create(fname);
                menuO = 404;
                break;
        case 2: read_record(fname);
                menuO = 404;
                break;
        case 3: update_recode(fname);
                menuO = 404;
                break;
        case 4: delete_recode(fname);
                menuO = 404;
                break;
        case 5: cout << "Enter the file location/name:\n";
                cout << "for example c:/1.csv or 1.csv\n";
                getline(cin >> ws, fname);
                cout << "\n";
                menuO = 404;
                break;
        case 0: cout << "\nEND" << "\n";
                break;

        default:cout << "\n\nfile name/location\n";
                cout << fname;
                cout << "\nPlease chose one of the following opitions\n";
                cout << "\n1 to create CSV file\n";
                cout << "2 Display selected CSV\n";
                cout << "3 Update selected CSV\n";
                cout << "4 Delete selected values at CSV\n";
                cout << "5 Change file name/location\n";
                cout << "0 exit\n";
                while (!(cin >> menuO)) 
                {
                    cout << "Ooops! Non integer value entered!\n";
                    cin.clear();
                    cin.ignore(40, '\n');
                }
                cout << "\n";
        }
    }	
	return 0;
}
