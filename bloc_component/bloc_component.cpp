#include "Bloc.h"
#include <string>
#include <list>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace std;


Bloc::Bloc() {
	num=0;
	hash=std::string("000123456789A123456789A123456789A123456789A123456789A123456789A");
	previous_hash=std::string("000123456789A123456789A123456789A123456789A123456789A123456789A");
	nonce=42;
	TXM *txm = new TXM();
	tx0=*txm;
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
}



py::object Bloc::to_json() const{
    nlohmann::json bloc_json;
    bloc_json["num"] = this->num;
    bloc_json["hash"] = hash;
    bloc_json["nonce"] = nonce;
    bloc_json["previous_hash"] = previous_hash;

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


namespace py = pybind11;


PYBIND11_MODULE(bloc_component, m) {
    py::class_<Bloc>(m, "Bloc")
	.def(py::init())
        .def(py::init<const nlohmann::json &>())
        .def("to_json", &Bloc::to_json)
        .def("setNonce", &Bloc::setNonce)
        .def("getNonce", &Bloc::getNonce);
}
