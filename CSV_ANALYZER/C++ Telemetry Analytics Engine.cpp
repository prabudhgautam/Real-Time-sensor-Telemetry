#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// Implmntd data analyss logic 
class Datastore {
    public:
    float distance;
    string date;
    string time;
};

vector<Datastore> records; 

class CSV_datareader {
    public: void readData() {
        ifstream file("../Sensor_dataloggs.csv");
        if (file.is_open()){
            string line;
            getline(file, line); // Skip header line
            string distance, date, time;
            while (getline(file, line)) {
                stringstream ss(line);
                getline(ss, distance, ',');
                getline(ss, date,',');
                getline(ss, time,',');
                cout << "distance:"<< distance << " date:"<< date << " time:"<< time << endl;
                Datastore data;
                data.distance = stof(distance);
                data.date = date;
                data.time = time;
                records.push_back(data);
            }
            
            file.close();

        }
        else {
                cout << "Unable to open file" << endl;
        }
    }
};

class Data_analyzer {
    public: void analyzer() {
        float  minimum_distance = records[0].distance;
        float maximum_distance = records[0].distance;
        for (int i=1; i<records.size(); i++) {
            if (records[i].distance < minimum_distance) {
                minimum_distance = records[i].distance;
            }
            if (records[i].distance > maximum_distance){
                maximum_distance = records[i].distance;
            }
            
        }
        cout << "Minimum distance: " << minimum_distance << endl;
        cout << "Maximum distance: " << maximum_distance << endl;
    }
    public: void average() {
        float sum = 0.0;
        for (int i=0; i<records.size();i++) {
            sum = sum + records[i].distance;
        }
        float average_distance = sum / records.size();
        cout << "Average distance: " << average_distance << endl;
    }
};

int main() {
    CSV_datareader reader;
    reader.readData();
    cout << "Total records stored: " << records.size() << endl;
    Data_analyzer analyzer;
    analyzer.analyzer();
    analyzer.average();
    return 0;}