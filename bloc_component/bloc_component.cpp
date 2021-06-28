#include "Bloc.h"
#include <string>
#include <list>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace std;


Bloc::Bloc(const nlohmann::json &j) {
	nlohmann::json transactions_json = j["transactions"];
    
	for (nlohmann::json::const_iterator it=transactions_json.begin(); it !=transactions_json.end(); ++it) {
	   TX *tx=new TX(*it);
	   txs.push_back(*tx);
	}

    num = j["num"];
    std::string hash_tmp = j["hash"];
    strncpy(hash, hash_tmp.c_str(), 64);
    nonce = j["nonce"];
    std::string previous_tmp = j["previous_hash"];
    strncpy(previous_hash ,previous_tmp.c_str(), 64);
    TXM *txm = new TXM(j["txm"]) ;
    tx0 = *txm;
}



nlohmann::json Bloc::to_json(){
    nlohmann::json bloc_json;
    bloc_json["num"] = this->num;
    bloc_json["hash"] = hash;
    bloc_json["nonce"] = nonce;
    bloc_json["previous_hash"] = previous_hash;

    nlohmann::json transactions_json;
    for (std::list<TX> it=txs.begin(); it != txs.end(); ++it) {
		transactions_json.push_back((*it).to_json());
	}
     
    bloc_json["transactions"] = transactions_json;
    bloc_json["txm"] = tx0;

    return bloc_json;
}

void Bloc::setNonce(int new_nonce){
    nonce = new_nonce;
}
unsigned int Bloc::getNonce(){
    return nonce;
}




PYBIND11_MODULE(bloc_component, m) {
    py::class_<Bloc>(m, "Bloc")
        .def(py::init<const nlohmann::json &>())
        .def("to_json", &Bloc::to_json)
        .def("setNonce", &Bloc::setNonce)
        .def("getNonce", &Bloc::getNonce)
}