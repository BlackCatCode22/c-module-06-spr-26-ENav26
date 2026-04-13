#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

class Animal {
protected:
    string id;
    string name;
    int age;
    string sex;
    string species;
    string color;
    int weight;
    string origin;
    string birthDate;
    string arrivalDate;

public:
    Animal(string id, string name, int age, string sex,
           string species, string color, int weight, string origin,
           string birthDate, string arrivalDate) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->sex = sex;
        this->species = species;
        this->color = color;
        this->weight = weight;
        this->origin = origin;
        this->birthDate = birthDate;
        this->arrivalDate = arrivalDate;
    }

    string getID() { return id; }
    string getName() { return name; }
    int getAge() { return age; }
    string getSex() { return sex; }
    string getSpecies() { return species; }
    string getColor() { return color; }
    int getWeight() { return weight; }
    string getOrigin() { return origin; }
    string getBirthDate() { return birthDate; }
    string getArrivalDate() { return arrivalDate; }

    void setName(string newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setColor(string newColor) { color = newColor; }
    void setBirthDate(string newBirthDate) { birthDate = newBirthDate; }
    void setArrivalDate(string newArrivalDate) { arrivalDate = newArrivalDate; }

    virtual string getHabitat() {
        return "Animal Habitat";
    }

    virtual void printInfo(ofstream& outFile) {
        outFile << id << "; "
                << name << "; "
                << "birth date " << birthDate << "; "
                << age << " years old; "
                << color << " color; "
                << sex << "; "
                << weight << " pounds; "
                << origin <<  "; "
                << "arrived " << arrivalDate << endl;
    }
};

class Hyena : public Animal {
public:
    Hyena(string id, string name, int age, string sex, string color, int weight, string origin, string birthDate, string arrivalDate)
            : Animal(id, name, age, sex, "hyena", color, weight, origin, birthDate, arrivalDate) {}

    string getHabitat() override {
        return "Hyena Habitat";
    }
};

class Lion : public Animal {
public:
    Lion(string id, string name, int age, string sex, string color, int weight, string origin, string birthDate, string arrivalDate)
            : Animal(id, name, age, sex, "lion", color, weight, origin, birthDate, arrivalDate) {}

    string getHabitat() override {
        return "Lion Habitat";
    }
};

class Tiger : public Animal {
public:
    Tiger(string id, string name, int age, string sex, string color, int weight, string origin,string birthDate, string arrivalDate)
            : Animal(id, name, age, sex, "tiger", color, weight, origin, birthDate, arrivalDate) {}

    string getHabitat() override {
        return "Tiger Habitat";
    }
};

class Bear : public Animal {
public:
    Bear(string id, string name, int age, string sex, string color, int weight, string origin, string birthDate, string arrivalDate)
            : Animal(id, name, age, sex, "bear", color, weight, origin, birthDate, arrivalDate) {}

    string getHabitat() override {
        return "Bear Habitat";
    }
};


vector<string> splitCommaString(string line) {
    vector<string> items;
    stringstream ss(line);
    string item;

    while (getline(ss, item, ',')) {
        if (!item.empty() && item[0] == ' ') {
            item.erase(0, 1);
        }
        items.push_back(item);
    }

    return items;
}


void loadNamesFromLine(string line, vector<string>& speciesNames) {
    vector<string> parts = splitCommaString(line);

    for (int i = 0; i < parts.size(); i++) {
        if (!parts[i].empty()) {
            speciesNames.push_back(parts[i]);
        }
    }
}

string genBirthDay(int age, string season) {
    int arrivalYear = 2024;
    int birthYear = arrivalYear - age;

    string monthDay;

    if (season == "spring") {
        monthDay = "-03-15";
    }
    else if (season == "summer") {
        monthDay = "-06-15";
    }
    else if (season == "fall") {
        monthDay = "-09-15";
    }
    else if (season == "winter") {
        monthDay = "-12-15";
    }
    else {
        monthDay = "-01-01";
    }

    return to_string(birthYear) + monthDay;
}
string genUniqueID(string prefix, int count) {
    if (count < 10) {
        return prefix + "0" + to_string(count);
    }
    return prefix + to_string(count);
}
int main() {
    vector<Animal*> animals;

    vector<string> hyenaNames;
    vector<string> lionNames;
    vector<string> tigerNames;
    vector<string> bearNames;

    map<string, int> speciesCount;

    int hyenaCount = 1;
    int lionCount = 1;
    int tigerCount = 1;
    int bearCount = 1;

    string line;

    ifstream nameFile("animalNames.txt");

    if (!nameFile) {
        cout << "Could not open animalNames.txt" << endl;
        return 1;
    }

    while (getline(nameFile, line)) {
        if (line.find("Hyena Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, hyenaNames);
        }
        else if (line.find("Lion Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, lionNames);
        }
        else if (line.find("Bear Names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, bearNames);
        }
        else if (line.find("Tiger names:") != string::npos) {
            getline(nameFile, line);
            getline(nameFile, line);
            loadNamesFromLine(line, tigerNames);
        }
    }

    nameFile.close();

    ifstream inFile("arrivingAnimals.txt");

    if (!inFile) {
        cout << "Could not open arrivingAnimals.txt" << endl;
        return 1;
    }

    while (getline(inFile, line)) {
        vector<string> parts = splitCommaString(line);

        if (parts.size() < 6) {
            continue;
        }

        int age;
        string yearWord, oldWord, sex, species;

        stringstream firstStream(parts[0]);
        firstStream >> age >> yearWord >> oldWord >> sex >> species;

        string season = "unknown";
        stringstream seasonStream(parts[1]);
        string bornWord, inWord;
        seasonStream >> bornWord >> inWord >> season;

        string birthDate = genBirthDay(age, season);
        string arrivalDate = "2024-03-05";

        string color = parts[2];
        int colorPos = color.find(" color");
        if (colorPos != string::npos) {
            color = color.substr(0, colorPos);
        }

        int weight;
        string poundsWord;
        stringstream weightStream(parts[3]);
        weightStream >> weight >> poundsWord;

        string origin = parts[4] + ", " + parts[5];

        string id;
        string name;

        if (species == "hyena") {
            if (hyenaCount - 1 >= hyenaNames.size()) break;

            id = genUniqueID("Hy", hyenaCount);
            name = hyenaNames[hyenaCount - 1];
            animals.push_back(new Hyena(id, name, age, sex, color, weight, origin, birthDate, arrivalDate));
            hyenaCount++;
            speciesCount["hyena"]++;
        }
        else if (species == "lion") {
            if (lionCount - 1 >= lionNames.size()) break;

            id = genUniqueID("Li", lionCount);
            name = lionNames[lionCount - 1];
            animals.push_back(new Lion(id, name, age, sex, color, weight, origin, birthDate, arrivalDate));
            lionCount++;
            speciesCount["lion"]++;
        }
        else if (species == "tiger") {
            if (tigerCount - 1 >= tigerNames.size()) break;

            id = genUniqueID("Ti", tigerCount);
            name = tigerNames[tigerCount - 1];
            animals.push_back(new Tiger(id, name, age, sex, color, weight, origin, birthDate, arrivalDate));
            tigerCount++;
            speciesCount["tiger"]++;
        }
        else if (species == "bear") {
            if (bearCount - 1 >= bearNames.size()) break;

            id = genUniqueID("Be", bearCount);
            name = bearNames[bearCount - 1];
            animals.push_back(new Bear(id, name, age, sex, color, weight, origin, birthDate, arrivalDate));
            bearCount++;
            speciesCount["bear"]++;
        }
    }
    inFile.close();

    ofstream outFile("zooPopulation.txt");

    if (!outFile) {
        cout << "Could not create zooPopulation.txt" << endl;
        return 1;
    }

    outFile << "Zoo New Animal Report\n\n";

    outFile << "Hyena Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "hyena") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total hyenas: " << speciesCount["hyena"] << "\n\n";

    outFile << "Lion Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "lion") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total lions: " << speciesCount["lion"] << "\n\n";

    outFile << "Tiger Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "tiger") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total tigers: " << speciesCount["tiger"] << "\n\n";


    outFile << "Bear Habitat:\n";
    for (int i = 0; i < animals.size(); i++) {
        if (animals[i]->getSpecies() == "bear") {
            animals[i]->printInfo(outFile);
        }
    }
    outFile << "Total bears: " << speciesCount["bear"] << "\n\n";

    outFile.close();

    for (int i = 0; i < animals.size(); i++) {
        delete animals[i];
    }

    cout << "Report created successfully in zooPopulation.txt" << endl;

    return 0;
}