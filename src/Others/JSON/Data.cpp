#include "JSON.h"

using namespace flame_ide::JSON;


Data::Data()
{
	is_object = false;
	is_array = false;
	is_single = false;
	
	level = 0;
}

Data::Data(bool is_object_type
		   , bool is_array_type
		   , bool is_single_type)
{
	this->is_object = is_object_type;
	this->is_array  = is_array_type;
	this->is_single = is_single_type;
	
	this->type = 100 * this->is_object
				 + 10 * this->is_array
				 + this->is_single;
	
	if(!this->is_single)
	{ is_container = true; }
	else
	{ is_container = false; }
}

Data::~Data() {}

unsigned long
Data::getLevel() const
{ return level; }

void
Data::setLevel(const unsigned long &new_level) const
{
	level = new_level;
	
	if(str_level.length())
	{ str_level.clear(); }
	
	for(size_t i = 0; i < new_level; i++)
	{ str_level.push_back(' '); }
}

bool
Data::isObject() const
{	return is_object; }

bool
Data::isArray() const
{	return is_array; }

bool
Data::isSingle() const
{	return is_single; }

bool
Data::isPair() const
{ return (!type); }

bool
Data::isContainer() const
{	return is_container; }

unsigned int
Data::getType() const
{	return type; }
