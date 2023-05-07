#pragma once

#include <random>
#include <hash-library/sha256.h>
#include "DataBaseAccessor.h"

static const Table users
{
	"USERS",
	{
		{"USERNAME", "TEXT"},
		{"PASSWORD", "TEXT"},
		{"SALT", "TEXT"},
	},
};

class User
{
	//Fields
protected:
	std::string username;
	std::string password;
	std::string salt;

public:
	
	//Functions
protected:
	std::string GenerateSalt();
	void SaltAndHashPassword();
	bool AssertUsernameAndPass(DatabaseAccessor& databaseAccessor);

public:
	User(std::string username, std::string password, bool salt = false);
	bool UserLogin(DatabaseAccessor& databaseAccessor);
	bool UserCreate(DatabaseAccessor& databaseAccessor)
	

};