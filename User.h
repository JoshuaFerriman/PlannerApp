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
	std::string hashedPassword;
	std::string salt;

public:
	
	//Functions
protected:
	std::string GenerateSalt();
	std::string SaltAndHashPassword(std::string password);
	bool AssertUsernameAndPass(DatabaseAccessor& databaseAccessor);

public:
	User();
	User(std::string username, std::string password);
	bool UserLogin(DatabaseAccessor& databaseAccessor);
	bool UserCreate(DatabaseAccessor& databaseAccessor);
	
	void TestGenerateSalt();
};