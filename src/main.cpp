#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

#include <gtkmm.h>

#include "rapidjson/document.h"

/*
	g++ -std=c++11 main.cpp `pkg-config gtkmm-3.0 --cflags --libs` -o ../bin/UltimateBravery
*/

using namespace rapidjson;
using namespace std;

const vector<string> goldMaking= {"Eye_of_the_Equinox_item.jpg","Face_of_the_Mountain.png","Eye_of_the_Watchers_item.jpg","Talisman_of_Ascension.png","Eye_of_the_Oasis_item.jpg","Frost_Queen's_Claim_item.png"};

string getRandomChampion(){
	std::random_device rd;
	std::mt19937 rng(rd());
	
	ifstream champNameJSONFile("assets/championName.json");
	if(!champNameJSONFile.is_open()){
		cerr<<"File Error : championName.json not loaded"<<endl;
		return "ERROR";
	}
	else{
		string championName((istreambuf_iterator<char>(champNameJSONFile) ),
    						(istreambuf_iterator<char>()    ) );
    		Document championNameJSON;
    		championNameJSON.Parse(championName.c_str());
		std::uniform_int_distribution<int> uniChamp(0,championNameJSON.Size()-1);
	
		return championNameJSON[uniChamp(rng)].GetString();
	}
}
string getIcon(string champName){
	ifstream champIconJSONFile("assets/championIcon.json");
	if(!champIconJSONFile.is_open()){
		cerr<<"File Error : championIcon.json not loaded"<<endl;
		return "ERROR";
	}
	else{
		string championIcon((istreambuf_iterator<char>(champIconJSONFile) ),
    						(istreambuf_iterator<char>()    ) );
    	Document championIconJSON;
    	
    	championIconJSON.Parse(championIcon.c_str());
		return championIconJSON[champName.c_str()].GetString();
	}
}
string getRandomSpell(string champName){
	std::random_device rd;     
	std::mt19937 rng(rd());
	
	ifstream spellJSONFile("assets/spell.json");
	if(!spellJSONFile.is_open()){
		cerr<<"File Error : spell.json not loaded"<<endl;
		return "ERROR";
	}
	else{
		string spell( 	(istreambuf_iterator<char>(spellJSONFile) ),
                    	(istreambuf_iterator<char>()    ) );
                    	
		Document spellJSON;
		spellJSON.Parse(spell.c_str());
		std::uniform_int_distribution<int> uniSpell(0,2);
	
		return spellJSON[champName.c_str()][uniSpell(rng)].GetString();
	}
}

vector<string> getRandomSumms(){
	std::random_device rd;     
	std::mt19937 rng(rd());
		
	ifstream summsJSONFile("assets/summs.json");
	if(!summsJSONFile.is_open()){
		cerr<<"File Error : summs.json not loaded"<<endl;
		return vector<string>({"ERROR"});
	}
	else{
		string summs( 	(istreambuf_iterator<char>(summsJSONFile) ),
                   		(istreambuf_iterator<char>()    ) );
		Document summsJSON;
		summsJSON.Parse(summs.c_str());

		vector<string> summsList; 
		std::uniform_int_distribution<int> uniSumms(0,summsJSON.Size()-1);
		while(summsList.size()<2){
			int randInt = uniSumms(rng);
			if(find(summsList.begin(),summsList.end(),summsJSON[randInt].GetString()) == summsList.end()){
				summsList.push_back(summsJSON[randInt].GetString());
			}
		}
		return summsList;
	}
}

vector<string> getRandomItems(){
	std::random_device rd;     
	std::mt19937 rng(rd());    

	ifstream itemJSONFile("assets/item.json");
	if(!itemJSONFile.is_open()){
		cerr<<"File Error : item.json not loaded"<<endl;
		return vector<string>({"ERROR"});
	}
	string item( 	(istreambuf_iterator<char>(itemJSONFile) ),
                    (istreambuf_iterator<char>()    ) );
             	
	Document itemJSON;
	itemJSON.Parse(item.c_str());
	
	std::uniform_int_distribution<int> uniBoots(0,itemJSON["boots"].Size()-1);
	string rBoots = itemJSON["boots"][uniBoots(rng)].GetString();
	
	vector<string> coreItems;
	std::uniform_int_distribution<int> uniItems(0,itemJSON["core"].Size()-1);
	bool goldMk = false;
	while(coreItems.size()<5){
		int randInt = uniItems(rng);
		if(find(coreItems.begin(),coreItems.end(),itemJSON["core"][randInt].GetString()) == coreItems.end()){
			if(find(goldMaking.begin(),goldMaking.end(),itemJSON["core"][randInt].GetString()) != goldMaking.end()){
				if(!goldMk){
					goldMk=true;
					coreItems.push_back(itemJSON["core"][randInt].GetString());
				}
			}
			else{
				coreItems.push_back(itemJSON["core"][randInt].GetString());
			}
		}
	}
	
	std::uniform_int_distribution<int> uniEli(0,itemJSON["elixir"].Size()-1);
	string rElixir = itemJSON["elixir"][uniEli(rng)].GetString();
	
	vector<string> randomItems;
	randomItems.push_back(rBoots);
	for(auto it = coreItems.begin();it != coreItems.end();it++){
		randomItems.push_back(*it);
	}
	randomItems.push_back(rElixir);
	return randomItems;
}

class UltimateBravery : public Gtk::Window{
	public:
		UltimateBravery();
		virtual ~UltimateBravery();
	protected:
		void on_button_clicked(Glib::ustring data);
		void generateBuild();
		
		Gtk::Button m_reroll;
		Gtk::Frame m_stuffFrame;
		Gtk::Label m_name;
		Gtk::Box m_mainBox,m_stuffBox,m_champBox,m_spellBox,m_summBox,m_miscBox;
		Gtk::Image m_item3,m_item2,m_boots,m_item4,m_item5,m_item6,m_champIcon,m_spell,m_summ1,m_summ2,m_elixir;
};

void UltimateBravery::generateBuild(){
	auto champ = getRandomChampion();
	m_champIcon.set("assets/champion/"+getIcon(champ));

	m_name.set_markup("<span font='48' weight='bold'>"+champ+"</span>");

	m_spell.set("assets/spell/"+champ+"/"+getRandomSpell(champ));

	auto summs =getRandomSumms();
	m_summ1.set("assets/summs/"+summs[0]);
	m_summ2.set("assets/summs/"+summs[1]);

	auto randItems = getRandomItems();
	m_boots.set("assets/item/Boots/"+randItems[0]);
	m_item2.set("assets/item/"+randItems[1]);
	m_item3.set("assets/item/"+randItems[2]);
	m_item4.set("assets/item/"+randItems[3]);
	m_item5.set("assets/item/"+randItems[4]);
	m_item6.set("assets/item/"+randItems[5]);

	m_elixir.set("assets/item/Elixir/"+randItems[6]);
}

UltimateBravery::UltimateBravery() : m_mainBox(Gtk::ORIENTATION_VERTICAL),m_summBox(Gtk::ORIENTATION_VERTICAL),m_stuffFrame("Items"),m_reroll("Reroll"),m_miscBox(Gtk::ORIENTATION_HORIZONTAL,20){
	generateBuild();

	m_champBox.pack_start(m_champIcon);
	
	m_champBox.pack_start(m_name);
	
	m_champBox.pack_start(m_spellBox);

	m_spellBox.pack_start(m_spell);
	
	m_summBox.pack_start(m_summ1);
	m_summBox.pack_start(m_summ2);
	m_spellBox.pack_start(m_summBox);
	
	m_mainBox.pack_start(m_champBox);

	set_border_width(5);
	m_stuffBox.pack_start(m_boots);
	m_stuffBox.pack_start(m_item3);
	m_stuffBox.pack_start(m_item2);
	m_stuffBox.pack_start(m_item4);
	m_stuffBox.pack_start(m_item5);
	m_stuffBox.pack_start(m_item6);
	
	m_stuffFrame.add(m_stuffBox);
	
	m_mainBox.pack_start(m_stuffFrame);
	
	m_miscBox.pack_start(m_elixir);
	m_miscBox.pack_start(m_reroll);
	m_reroll.set_border_width(5);
	m_reroll.set_size_request(100,20);
	m_mainBox.pack_start(m_miscBox);
	
	m_reroll.signal_clicked().connect(sigc::bind<Glib::ustring>( sigc::mem_fun(*this,&UltimateBravery::on_button_clicked), "Reroll") );
	
	add(m_mainBox);
	m_mainBox.show_all();
}

UltimateBravery::~UltimateBravery(){}

void UltimateBravery::on_button_clicked(Glib::ustring data){

	generateBuild();
	m_mainBox.hide();
	m_mainBox.show_all();
}

int main(int argc, char *argv[]){
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.ultimatebravery.base");

  UltimateBravery ub;
  ub.set_default_size(700, 400);

  return app->run(ub);
}
