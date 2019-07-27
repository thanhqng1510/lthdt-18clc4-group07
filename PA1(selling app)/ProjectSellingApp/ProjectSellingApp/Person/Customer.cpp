#include <vector>

#include "Customer.h"
#include "../Utility/Util.h"

void Customer::GetOptionInput(unsigned int& option) {

}

Customer::Customer(const Account& account) 
: PersonInterface(account), m_point(0), m_menu_option(0) {}

void Customer::BucketCustomer() {
	//unordered_map_to_file <> 
}

void Customer::ShowMenu() {
	
}
 