#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class rpq{
    public:
        rpq() {}
        ~rpq() {}

        int max_time(int size, const vector<vector<int> >& data) {
            int time = 0;
            int max_time = 0;

            for(int i = 0; i < size; i++) {
                time = max(time, data[i][0]) + data[i][1];
                max_time = (max(time+data[i][2],max_time));
            }
            
            return max_time;
        }

        vector<vector<int> > sort_r(vector<vector<int> >& data) {
            sort(data.begin(), data.end());
            return data;
        }
        // wlasna metoda uproszczonego sortowania
        vector<vector<int> > my_sort(int size, vector<vector<int> >& data) {
            int max[3] = {max_x(0, data)/size, max_x(1, data)/size, max_x(2, data)/size};
            int t = 0;

            while(t < size/12) {
                for(int j = 0; j < 3; j++) {
                    for(int i = 0; i < size-1; i++) {
                        if(data[i+1][j] - data[i][j] > max[j]) {
                            swap(data[i], data[i+1]);
                        }
                    } 
                }
                t++;
            }
            return data;
        }

    private:
        int max_x(int n, const vector<vector<int> >& data) {
            int max = data[0][n];
            for(int i = 1; i < data.size(); i++) {
                if(data[i][n] > max) {
                    max = data[i][n];
                }
            }
            return max;
        }

    };

int main() {
    ifstream file("data1.txt");
    string line = "";
    int size = 0;
    vector<vector<int> > data;

    if (file.is_open()) {

        getline(file, line);
        size = stoi(line);

        while (getline(file, line)) {
            vector<int> row;
            stringstream s_line(line);
            string number;

            while (getline(s_line, number, ' ')) {
                row.push_back(stoi(number));
            }

            data.push_back(row);
        }

        file.close();
    }

    rpq solver;

    int time = solver.max_time(size, data);
    cout << "max time = " << time << endl;

    vector<vector<int> > sorted = solver.sort_r(data);
    int time2 = solver.max_time(size, sorted);
    cout << "max time sorted = " << time2 << endl;

    vector<vector<int> > my_sorted = solver.my_sort(size, data);
    int time3 = solver.max_time(size, my_sorted);
    cout << "max time my method sorted = " << time3 << endl;

    return 0;
}