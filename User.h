#pragma once

#include <random>
#include <hash-library/sha256.h>
#include "DataBaseAccessor.h"

static const Table users
{
	"USERS",
	{
		{"USERNAME", "TEXT", true},
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
	static std::string SaltAndHashPassword(std::string password, std::string salt);
	bool AssertUsernameAndPass(DatabaseAccessor& databaseAccessor);
	bool UserCreateRecord(DatabaseAccessor& databaseAccessor);

public:
	User();
	User(std::string username, std::string password);
	User(DatabaseAccessor& databaseAccessor, std::string username, std::string password);

	std::string GetUsername();

	static bool UserLogin(DatabaseAccessor& databaseAccessor, std::string username, std::string password, User* currentUser);
	
	void TestGenerateSalt();
};