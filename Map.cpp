#pragma once
#include "Map.hpp"

using namespace std;

Map::Map()
{

    m_Continents =list<Continent*>(); // list of all the continents
   m_Territories =  std::list<Territory*>();
   m_author = new string();

}

Map::Map(string line) // creating map from the map section in the file
{

    string Line = string(line.substr(0, line.find("\n") + 1));
    Line = Line.substr(0, line.find("=") + 1);
    m_author = new string(line.substr(Line.length()));

    line = line.substr(line.find("\n") + 1);// PARSE THE REST IF NEEDED


}
Map::~Map() // destructor
{

    delete m_author;
    m_author = nullptr;

    for (std::list<Continent*>::iterator it = m_Continents.begin(); it != m_Continents.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    
    for (std::list<Territory*>::iterator it = m_Territories.begin(); it != m_Territories.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
    
}



string Map::Validate()
{

    // going through the territories and checking that all of them have at least one connection  to check for a connected graph
    std::list<Territory*>::iterator it;
    for (it = m_Territories.begin(); it != m_Territories.end(); ++it) {

        if ((*it)->m_Connections.size() == 0) {
            return "a Territories has no connection";
        }
    }

    std::list<Continent*>::iterator itCont;
    // going through the continents and checking that all of them have at least one connection  to check for a connected graph and have at least one memeber
    for (itCont = m_Continents.begin(); itCont != m_Continents.end(); ++itCont) {

        if ((*itCont)->m_Connections.size() == 0) {
            return "a Continents has no connection";
        }
        if ((*itCont)->m_Territories.size() == 0) {
            return "a continetnt has no territories";
        }
    }

    // going through the territories and checking that all of them are part of one continent each

    for (it = m_Territories.begin(); it != m_Territories.end(); ++it) {
        int count = 0;
        for (itCont = m_Continents.begin(); itCont != m_Continents.end(); ++itCont) {

            if (getTerritory((*itCont)->m_Territories, *(*it)->m_name) != nullptr) {
                count += 1;

            }


        }
        if (count != 1) {
            cout << *(*it)->m_name << " has more than one or no continent " << endl;
            return "a territory  has more than one continent";

        }
    }


    return "";
}

Map& Map::operator=(const Map& map) { // assign operator
    m_author = new string(*map.m_author);
    m_Territories = list<Territory*>(map.m_Territories);
    m_Continents = list<Continent*>(map.m_Continents);
    return *this;
}


Map::Map(const Map& map) { // copy constructor
    m_author = new string(*map.m_author);
    m_Territories = list<Territory*>(map.m_Territories);
    m_Continents = list<Continent*>(map.m_Continents);
}


ostream& operator<<(ostream& strm, const Map& map) // cout operator
{
    string str = "";
    string strcont = "";


    for (list<Continent*>::const_iterator itcont = (map.m_Continents).begin(); itcont != map.m_Continents.end(); ++itcont) {
        strcont += *(*itcont)->m_name + " , ";
    }
    for (list<Territory*>::const_iterator it = (map.m_Territories).begin(); it != map.m_Territories.end(); ++it) {
        str += *(*it)->m_name + " , ";
    }
    return strm << "Author : " << *(map.m_author) << endl << " My Continents :  " << strcont << endl << endl << " My terrytories " << str << endl;
};


//////////////////////////////////////////////////CONTINENT /////////////////////////////////////////////////////////////

Continent::~Continent() // destructor
{

    delete m_name;
    m_name = nullptr;
    for (std::list<Continent*>::iterator it = m_Connections.begin(); it != m_Connections.end(); ++it) {
        if (*it !=NULL)
        delete *it;
        *it= nullptr;
    }
    for (std::list<Territory*>::iterator it = m_Territories.begin(); it != m_Territories.end(); ++it) {
        delete *it;
        *it= nullptr;
    }
}
Continent::Continent(string line) // constructor using the line in the file
{
    string Line = string(line.substr(0, line.find("\n") + 1));
    m_name = new string(Line.substr(0, line.find("=")));
    line = line.substr(line.find("=") + 1);
    control_val=new int(stoi(line));


}

Continent::Continent() // constructor using the line in the file
{
    m_Territories =  std::list<Territory*>(); // store all territories in this continent
    m_Connections = std::list<Continent*>();
    m_name = new string();

}

bool Continent::addTerritory(Territory* ter)
{
    m_Territories.insert(m_Territories.begin(), ter);
    return false;
}


bool Continent::AddConnection(Continent* con)
{
    if (getContinent(m_Connections, *con->m_name) == nullptr) {
        m_Connections.insert(m_Connections.begin(), con);
    }
    return false;
    return false;
}

Continent::Continent(const Continent& ter) // copy constructor
{
    this->m_name = new string(*ter.m_name);
    this->m_Territories = list<Territory*>(ter.m_Territories);
    this->m_Connections = list<Continent*>(ter.m_Connections);

}

Continent& Continent::operator=(const Continent& ter) // assign operator
{

    this->m_name = new string(*ter.m_name);

    this->m_Territories = list<Territory*>(ter.m_Territories);
    this->m_Connections = list<Continent*>(ter.m_Connections);
    return *this;
}


ostream& operator<<(ostream& strm, const Continent& cont) // cout operator
{
    string str = "";
    string strcont = "";


    for (list<Continent*>::const_iterator itcont = (cont.m_Connections).begin(); itcont != cont.m_Connections.end(); ++itcont) {
        strcont += *(*itcont)->m_name + " , ";
    }
    for (list<Territory*>::const_iterator it = (cont.m_Territories).begin(); it != cont.m_Territories.end(); ++it) {
        str += *(*it)->m_name + " , ";
    }

    return strm << "Name OF THE CONTINENT  : " << *(cont.m_name) << endl << " My terrytories :  " << strcont << endl << endl << " Connected to these Continents  :  " << str << endl;
};

//////////////////////////////////////////////////TERRITORY /////////////////////////////////////////////////////////////



Territory::~Territory() // destructor
{
    delete m_continent_name;
    m_continent_name = nullptr;
    delete m_name;
    m_name = nullptr;
    delete m_x;
    m_x = nullptr;
    delete m_y;
    m_y = nullptr;
}

Territory::Territory(const Territory& ter) // copy constructor
{
    this->m_continent_name = new string(*ter.m_continent_name);
    this->m_name = new string(*ter.m_name);
    this->m_x = new string(*ter.m_x);
    this->m_y = new string(*ter.m_y);
    this->m_Connections = list<Territory*>(ter.m_Connections);
}


Territory::Territory() // default constructor
{
    m_continent_name = new string();
    m_name = new string();
    m_x = new string();
    m_y = new string();
    m_Connections = list<Territory*>();
    this->armies = new int(0);
}

Territory& Territory::operator=(const Territory& ter) // assign operator
{
    this->armies = new int(*ter.armies);
    this->m_continent_name = new string(*ter.m_continent_name);
    this->m_name = new string(*ter.m_name);
    this->m_x = new string(*ter.m_x);
    this->m_y = new string(*ter.m_y);
    this->m_Connections = list<Territory*>(ter.m_Connections);
    return *this;
}



Territory::Territory(std::string line) // create a territory from a line in the territory section
{
    armies = new int(0);
    m_name = new string(line.substr(0, line.find(",")));

    line = line.substr(line.find(",") + 1);

    m_x = new string(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);

    m_y = new string(line.substr(0, line.find(",")));
    line = line.substr(line.find(",") + 1);

    m_continent_name = new string(line.substr(0, line.find(",")));

    line = line.substr(line.find(",") + 1);

}


bool Territory::AddConnection(Territory* ter)
{
    if (getTerritory(m_Connections, *ter->m_name) == nullptr) {
        m_Connections.insert(m_Connections.begin(), ter);
    }
    return false;
}

void Territory::AddTroops(int ter)
{

    *armies=*armies +ter;
}
void Territory::RemoveTroops(int ter)
{

    *armies = *armies - ter;
}

bool Territory::isAdjacent(Territory* ter)
{
    std::list<Territory*>::iterator it;
    for (it = m_Connections.begin(); it != m_Connections.end(); ++it) {

        if (*ter->m_name == *(*it)->m_name) {
            return true ;
        }
    }
    return false;
}

ostream& operator<<(ostream& strm, const Territory& cont) // cout operator
{
    string str = "";

    for (list<Territory*>::const_iterator it = (cont.m_Connections).begin(); it != cont.m_Connections.end(); ++it) {
        str += *(*it)->m_name + " , ";
    }

    return strm << "Name OF THE territory  : " << *(cont.m_name) << endl
        << "Xposition   : " << *(cont.m_x) << endl << "   Yposition   : " << *(cont.m_y) << endl
        << "Part of the  Continent  : " << *(cont.m_continent_name) << endl <<

        " Connected terrytories :  " << str << endl;
};


//////////////////////////////////////////////////MAPLOADER /////////////////////////////////////////////////////////////


ostream& operator<<(ostream& strm, const MapLoader& map) // cout operator
{
    string desc;
    string intializedmap;
    if (map.m_map_desc != nullptr)
        desc = *map.m_map_desc;
    else
        return strm << " The description of the map has not been defined yet  " << endl;

    if (map.m_map != nullptr)
        intializedmap = "and the map has been initialized ";
    else
        return strm << " This is the description already read however the map has not been initialized \n here is the description \n" << desc << endl;
    return strm << " This is the description already read and the map was initialized  \n here is the description \n" << desc << endl;

    // TODO: insert return statement here
}

MapLoader& MapLoader::operator=(const MapLoader& map) { // assign operator
    this->m_map_desc = new string(*map.m_map_desc);
    this->m_map = new Map(*map.m_map);
    return *this;
}


MapLoader::MapLoader(const MapLoader& map) { // copy contructor
    this->m_map_desc = new string(*map.m_map_desc);
    this->m_map = new Map(*map.m_map);
}

MapLoader::MapLoader() //default constructor
{
    m_map_desc = new string();
    m_map = new Map();
}

MapLoader::~MapLoader()// destructor
{
    delete m_map;
    m_map = nullptr; // avoiding dangling pointer
    delete m_map_desc;
    m_map_desc = nullptr;
}

// extra visual helper methods
void MapLoader::Print(std::list<Continent*> Li) { // printing a list of continents
    std::list<Continent*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {
        cout << *(*it)->m_name << " CONTAINS THESE : ";
        Print((*it)->m_Territories);
        cout << endl;
    }

}

void MapLoader::Print(std::list<Territory*> Li) { // printing a list of territories
    std::list<Territory*>::iterator it;
    std::list<Territory*>::iterator it2;
    for (it = Li.begin(); it != Li.end(); ++it) {
        cout << *(*it)->m_name << endl << "AND AM CONNECTED TO THESE ";
        cout << (*it)->m_Connections.size() << endl;


    }
    cout << endl;

}




void  MapLoader::LoadMap()
{
    string description = "";
    string map = m_map_desc->substr(m_map_desc->find("[Map]"), m_map_desc->find("[Continents]"));
    map = map.substr(6);
    //reading the map description
    m_map = new Map(map);
    description = m_map_desc->substr(m_map_desc->find("[Continents]"));
    string cont = description.substr(0, description.find("[Territories]"));
    cont = cont.substr(13);

    string contLine = "";
    // reading the continent description
    while (cont != "") {
        contLine = cont.substr(0, cont.find("\n") + 1);
        if (contLine.find("=") != std::string::npos) {
            Continent* continent = new Continent(contLine);
            m_map->m_Continents.insert(m_map->m_Continents.begin(), continent);
        }
        cont = cont.substr(cont.find("\n") + 1);

    }


    // reading the territories one by one and creating a territory for each line
    string TerritoryLine = "emptyline";
    string Territories = m_map_desc->substr(m_map_desc->find("[Territories]") + 14);
    string TerritoryLink = Territories;

    while (Territories != "") {

        TerritoryLine = Territories.substr(0, Territories.find("\n") + 1);
        if (TerritoryLine.find(",") != std::string::npos) {

            Territory* ter = new  Territory(TerritoryLine);
            m_map->m_Territories.insert(m_map->m_Territories.begin(), ter);
        }
        Territories = Territories.substr(Territories.find("\n") + 1);

    }
    // linking all the territories and putting them in respective continent
    while (TerritoryLink != "") {

        TerritoryLine = TerritoryLink.substr(0, TerritoryLink.find("\n") + 1);
        if (TerritoryLine.find(",") != std::string::npos) {


            Link(TerritoryLine);
        }
        TerritoryLink = TerritoryLink.substr(TerritoryLink.find("\n") + 1);

    }




}


// link each territory and add it to its continent
void  MapLoader::Link(string line) {

    string terr_name = line.substr(0, line.find(","));
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);
    line = line.substr(line.find(",") + 1);

    string contin = line.substr(0, line.find(","));
    Territory* terri = getTerritory(m_map->m_Territories, terr_name);
    Continent* cont = getContinent(m_map->m_Continents, contin);

    if (cont == nullptr) {
        cout << contin << " : CONTINENT NOT FOUND   ";
        exit(0);
    }
    cont->addTerritory(terri);
    line = line.substr(line.find(",") + 1) + ",";

    string name = "initial";

    while (line != "") {
        name = line.substr(0, line.find(","));
        name = name.substr(0, name.find("\n"));

        Territory* addTerri = getTerritory(m_map->m_Territories, name);
        if (addTerri == nullptr) {
            cout << name << "TERRITORY NOT FOUND BRO";
            exit(0);
        }
        terri->AddConnection(addTerri);

        if (*addTerri->m_continent_name != *terri->m_continent_name) {
            Continent* addCont = getContinent(m_map->m_Continents, *addTerri->m_continent_name);
            cont->AddConnection(addCont);
        }

        line = line.substr(line.find(",") + 1);

    }

}



// reading the file and putting it all in a string
string MapLoader::ReadDescription(std::string FilePath)
{
    string text = "";


    string Line;
    // open file in read mode
    ifstream input(FilePath);
    // Read line
    if (!getline(input, Line)){cout<<"No file found \n";
        
        return "no file found";
    };
    text += Line + "\n";
    // until file is empty: print line, then read other line
    while (getline(input, Line)) {


        text += Line + "\n";
    }
    
    if (text.find("[Continents]") == std::string::npos) {
        cout << "The file does not contain section continent ";
        return "The file does not contain section continent ";
    }    if (text.find("[Territories]") == std::string::npos) {
        cout << "The file does not contain section Territories ";
        return "The file does not contain section Territories ";
    }    if (text.find("[Map]") == std::string::npos) {
        cout << "The file does not contain section Map ";
        return  "The file does not contain section Map ";
    }
    *m_map_desc = text;

    input.close();
    return  "";


}
//////////////////////////////////////////////////UTILITY /////////////////////////////////////////////////////////////


Continent* getContinent(std::list<Continent*> Li, string name) {
    std::list<Continent*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {
        if (name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}

Territory* getTerritory(std::list<Territory*> Li, string name) {
    std::list<Territory*>::iterator it;
    for (it = Li.begin(); it != Li.end(); ++it) {

        if (name == *(*it)->m_name) {
            return (*it);
        }
    }
    return nullptr;
}

