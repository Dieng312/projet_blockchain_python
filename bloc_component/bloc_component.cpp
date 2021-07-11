#include "Bloc.h"
#include <string>
#include <list>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace std;


Bloc::Bloc() {
	num=0;
	hash=std::string("111123456789A123456789A123456789A123456789A123456789A123456789A");
	previous_hash=std::string("000123456789A123456789A123456789A123456789A123456789A123456789A");
	nonce=42;
	TXM *txm = new TXM();
	tx0=*txm;
    difficulty = 3;
}


Bloc::Bloc(const nlohmann::json &j) {
	nlohmann::json transactions_json = j["transactions"];
    
	for (nlohmann::json::const_iterator it=transactions_json.begin(); it !=transactions_json.end(); ++it) {
	   TX *tx=new TX(*it);
	   txs.push_back(*tx);
	}
    num = j["num"];
    hash = j["hash"];
    nonce = j["nonce"];
    previous_hash = j["previous_hash"];
    TXM *txm = new TXM(j["txm"]) ;
    tx0 = *txm;
    difficulty = 3;
}



py::object Bloc::to_json() const{
    nlohmann::json bloc_json;
    bloc_json["num"] = num;
    bloc_json["hash"] = hash;
    bloc_json["nonce"] = nonce;
    bloc_json["previous_hash"] = previous_hash;
    bloc_json["difficulty"] = difficulty;

    nlohmann::json transactions_json;
    for (std::list<TX>::const_iterator it=txs.begin(); it != txs.end(); ++it) {
		transactions_json.push_back((*it).to_json());
	}
     
    bloc_json["transactions"] = transactions_json;
    bloc_json["txm"] = tx0.to_json();

    return bloc_json;
}

void Bloc::setNonce(int new_nonce){
    nonce = new_nonce;
}
unsigned int Bloc::getNonce(){
    return nonce;
}

void Bloc::setHash(std::string h){
    hash = h;
};
std::string Bloc::getHash(){
    return hash;
};
void Bloc::setPrevious_hash(std::string p_h){
    previous_hash = p_h;
};
std::string Bloc::getPrevious_hash(){
    return previous_hash;
};

void Bloc::computeHash(){
    hash = "";
    py::object bloc_json = to_json();
    hash = "";// py_hacheur::sha256(bloc_json);
};


bool Bloc::validationDifficultyBloc(){
    std::string valide = std::string("000000000000000000000000000000000000000000000000000000000000000");
    std::string str1 = hash.substr(0, difficulty);
    std::string str2 = valide.substr(0, difficulty);
    if( hash.length()!=HASH_SIZE || str1.compare(str2) =!0 ){
        return false;
    };
    return true;
};

bool validationBloc(){
    std::string h = hash;
    computeHash();
    if(validationDifficultyBloc() && hash = h) return true;
    return false;
};


namespace py = pybind11;


PYBIND11_MODULE(bloc_component, m) {
    py::class_<Bloc>(m, "Bloc")
	.def(py::init())
        .def(py::init<const nlohmann::json &>())
        .def("to_json", &Bloc::to_json)
        .def("setNonce", &Bloc::setNonce)
        .def("getNonce", &Bloc::getNonce)
        .def("setHash", &Bloc::sethash)
        .def("getHash", &Bloc::getHash)
        .def("setPrevious_hash", &Bloc::setPrevious_hash)
        .def("getPrevious_hash", &Bloc::getPrevious_hash
        .def("validationBloc", &Bloc::validationBloc);
}
